#include "Audio.h"

static ALCcontext* s_context;

void InitAudio()
{
	alutInit();
	ALCdevice* device;
	device = alcOpenDevice(NULL);
	if (!device) throw std::exception("Could not open the default device");

	s_context = alcCreateContext(device, NULL);
	if (!s_context) {
		throw std::exception("Could not create context");
	}
	alcMakeContextCurrent(s_context);
}

void DeinitAudio()
{
	alutExit();
	alcDestroyContext(s_context);
}
