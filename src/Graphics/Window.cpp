#include "jampch.h"
#include "Window.hpp"
#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "PowerLogger.hpp"

void error_callback(int error, const char* description)
{
	//PLOG_ERROR("Error: {}", description);
}

void glad_cb(const char* name, void* funcptr, int len_args, ...) {

}


void Jam::Window::open(int width, int height, const std::string& title)
{
	if(!glfwInit()) {
		throw std::runtime_error("Cannot initialize glfw!");
	}

	//glfwSetErrorCallback(error_callback);

	m_handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!m_handle) {
		throw std::runtime_error("Could not open window!");
	}

	glfwMakeContextCurrent(m_handle);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
#ifdef GLAD_DEBUG
	glad_set_pre_callback(glad_cb);
	glad_set_post_callback(glad_cb);
#endif
}

void Jam::Window::update()
{
	glfwSwapBuffers(m_handle);
	glfwPollEvents();
}

void Jam::Window::close()
{
	glfwTerminate();
	m_handle = nullptr;
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

Jam::Window::Window() : Jam::Frame({ 0,0 }, { 0,0 }, { 0,0 }, { 0,0}), m_handle(nullptr)
{
}

Jam::Window::Window(int width, int height, const std::string& title) : Jam::Frame({ 0,0 }, { 1,1 }, {0,0}, {width, height})
{
	open(width, height, title);
}

Jam::Window::~Window()
{
	if (m_handle) {
		close();
		m_handle = nullptr;
	}
}
