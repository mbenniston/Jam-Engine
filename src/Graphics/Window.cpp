#include "jampch.h"
#include "Window.hpp"
#include <cassert>

#include "vendor.h"
#include "PowerLogger.hpp"
#include "UI/Events.hpp"


static void keypress_cb(GLFWwindow* handle, int key, int scancode, int action, int mods)
{
	Jam::Window* win = (Jam::Window*)glfwGetWindowUserPointer(handle); 
	if(action == GLFW_PRESS) {
		auto event = std::make_shared<Jam::KeyPressEvent>();
		event->key = key;
		event->handled = false;
		glfwGetCursorPos(handle, &event->x, &event->y);
		win->handleEvent(event);
	}
}

static void mousebtn_cb(GLFWwindow* handle, int btn, int action, int mods) 
{
	//generate event and dispatch to widgets only if within the bounds of the widget
	Jam::Window* win = (Jam::Window*)glfwGetWindowUserPointer(handle); 
	if(action == GLFW_PRESS) {
		auto event = std::make_shared<Jam::ButtonPressEvent>();
		event->button = btn;
		event->handled = false;
		glfwGetCursorPos(handle, &event->x, &event->y);
		win->handleEvent(event);
	}
}

static void resize_cb(GLFWwindow* handle, int w,int h)
{
	Jam::Window* win = (Jam::Window*)glfwGetWindowUserPointer(handle); 
	win->setPixelSize(glm::vec2{w,h});
	win->refreshPixelPositions();
}

void error_callback(int error, const char* description)
{
	PLOG_ERROR("Error: {}", description);
}


void glad_cb(const char* name, void* funcptr, int len_args, ...) {
	// static void* lastFuncPointer = nullptr;
	// if(funcptr != lastFuncPointer) {
	// 	PLOG_ERROR("GL Error in: {}", name);
	// 	lastFuncPointer = funcptr;
	// }
}


void Jam::Window::open(int width, int height, const std::string& title)
{
	if(!glfwInit()) {
		throw std::runtime_error("Cannot initialize glfw!");
	}

	//glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

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

	glfwSetWindowUserPointer(m_handle, this);
	glfwSetFramebufferSizeCallback(m_handle, resize_cb);
	glfwSetMouseButtonCallback(m_handle, mousebtn_cb);
	glfwSetKeyCallback(m_handle, keypress_cb);

	m_renderer = new UIRenderer();
	setPixelSize((glm::vec2)getSize());

	setIcon({ DEFAULT_ASSETS.openFile("icons/icon.png"), DEFAULT_ASSETS.openFile("icons/icon2.png"), DEFAULT_ASSETS.openFile("icons/icon3.png") });
}

void Jam::Window::update()
{
	m_renderer->renderUI(this);

	glfwSwapBuffers(m_handle);
	glfwPollEvents();
}

void Jam::Window::close()
{
	m_renderer->release();
	delete m_renderer;

	glfwTerminate();
	m_handle = nullptr;
}

static GLFWimage loadImage(const Jam::File& file)
{
	int width, height, channels;
	GLFWimage icon;
	icon.pixels = stbi_load_from_memory(file.getData().data(), file.getData().size(), &width, &height, &channels, 4);
	icon.width = width;
	icon.height = height;
	if (icon.pixels) {
		if (channels != 4) {
			throw std::exception("Icon file doesnt have the correct amount of channels!");
		}
	}
	else {
		throw std::exception("Could not load icon file!");
	}
	return icon;
}

void Jam::Window::setIcon(const std::vector<File>& files)
{
	std::vector<GLFWimage> images;

	for (const File& file : files) {
		images.push_back(loadImage(file));
	}
	glfwSetWindowIcon(m_handle, images.size(), images.data());

	for (GLFWimage image : images) {
		stbi_image_free(image.pixels);
	}
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

Jam::Window::Window() : Jam::Frame({ 0,0 }, { 0,0 }, { 0,0 }, { 0,0 }), m_handle(nullptr)
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

glm::vec2 Jam::Window::getMousePosition() const
{
	double x, y;
	glfwGetCursorPos(m_handle, &x, &y);
	return glm::vec2((float)x, (float)y);
}

bool Jam::Window::getMouseButton(int btn) const 
{
	return glfwGetMouseButton(m_handle, btn) == GLFW_PRESS;
}