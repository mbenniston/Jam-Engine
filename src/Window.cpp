#include "Window.hpp"
#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Jam::Window::open(int width, int height, const std::string& title)
{
	assert(glfwInit() == GLFW_TRUE);

	m_handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_handle);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void Jam::Window::update()
{
	glfwSwapBuffers(m_handle);
	glfwPollEvents();
}

void Jam::Window::close()
{
	glfwTerminate();
}

glm::ivec2 Jam::Window::getSize() const
{
	int width, height;
	glfwGetWindowSize(m_handle, &width, &height);
	return { width, height };
}

int Jam::Window::getWidth() const
{
	int width;
	glfwGetWindowSize(m_handle, &width, nullptr);
	return width;
}

int Jam::Window::getHeight() const
{
	int height;
	glfwGetWindowSize(m_handle, nullptr, &height);
	return height;
}

bool Jam::Window::shouldClose() const
{
	return glfwWindowShouldClose(m_handle);
}

Jam::Window::Window() : m_handle(nullptr)
{
}

Jam::Window::Window(int width, int height, const std::string& title)
{
	open(width, height, title);
}

Jam::Window::~Window()
{
	if (m_handle) {
		close();
	}
}
