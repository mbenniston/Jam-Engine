#pragma once

#define JAM_DEBUG
#include <string>

#include "vendor.h"


struct GLFWwindow;

namespace Jam
{
	class Window final
	{
	private:
		GLFWwindow* m_handle;

	public:

		inline GLFWwindow* getHandle() {
			return m_handle;
		}

		void open(int width, int height, const std::string& title);
		void update();
		void close();

		glm::ivec2 getSize() const;
		int getWidth() const;
		int getHeight() const;

		bool shouldClose() const;

		Window();
		Window(int width, int height, const std::string& title);
		~Window();
	};
}