#pragma once

#include <string>

#include <glm/glm.hpp>

struct GLFWwindow;

namespace Jam
{
	class Window final
	{
	private:
		GLFWwindow* m_handle;

	public:

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