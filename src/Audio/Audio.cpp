#include "jampch.h"
#include "Audio.h"

namespace Jam
{
	static ALCcontext* s_context;
	static ALCdevice* s_device;

	void InitAudio()
	{
		alutInitWithoutContext();
		s_device = alcOpenDevice(NULL);
		if (!s_device) throw std::exception("Could not open the default device");

		s_context = alcCreateContext(s_device, NULL);
		if (!s_context) {
			throw std::exception("Could not create context");
		}
		alcMakeContextCurrent(s_context);
	}

	void DeinitAudio()
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(s_context);
		alcCloseDevice(s_device);
		alutExit();
	}
}