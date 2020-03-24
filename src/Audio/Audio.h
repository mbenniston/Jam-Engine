#pragma once

#include "vendor.h"

#include "../Assets/AssetLoader.h"
#include "../misc.hpp"
#include "../PowerLogger.hpp"

namespace Jam
{
	class Buffer
	{
	private:
		ALuint m_id = 0;

		friend class Source;
	public:

		void load(const Jam::File& file) {
			m_id = alutCreateBufferFromFileImage(file.getData().data(), (ALsizei)file.getData().size());
			if (m_id == 0) {
				throw std::exception("Could not load wave file!");
			}
		}

		void gen() {
			MISC_CHECK_GEN_ID(m_id);
			alGenBuffers(1, &m_id);
		}

		void remove() {
			MISC_CHECK_REM_ID(m_id);
			alDeleteBuffers(1, &m_id);
			m_id = 0;
		}
	};

	class Source
	{
	private:
		ALuint m_id = 0;

	public:

		void setBuffer(const Buffer& buf) {
			alSourcei(m_id, AL_BUFFER, buf.m_id);
		}

		void setPosition(const glm::vec3& position) {
			alSource3f(m_id, AL_POSITION, position.x, position.y, position.z);
		}

		glm::vec3 getPosition() const {
			ALfloat x, y, z;
			alGetSource3f(m_id, AL_POSITION, &x, &y, &z);
			return glm::vec3(x, y, z);
		}

		void play() const {
			alSourcePlay(m_id);
		}

		void stop() const {
			alSourceStop(m_id);
		}

		ALenum getState() const {
			ALint b;
			alGetSourcei(m_id, AL_SOURCE_STATE, &b);
			return b;
		}

		bool isPlaying() const {
			return getState() == AL_PLAYING;
		}

		void gen() {
			MISC_CHECK_GEN_ID(m_id);
			alGenSources(1, &m_id);
		}

		void remove() {
			MISC_CHECK_REM_ID(m_id);
			alDeleteSources(1, &m_id);
			m_id = 0;
		}
	};

	class Listener
	{
	private:

	public:

		Listener() {
		}
	};

	void InitAudio();
	void DeinitAudio();
}