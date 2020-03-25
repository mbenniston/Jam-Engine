#pragma once
#include <string>

#include "vendor.h"

#include "UI/Widget.hpp"
#include "UI/UIRenderer.hpp"

struct GLFWwindow;

namespace Jam
{
	class Window final : public Frame
	{
	private:
		GLFWwindow* m_handle;
		UIRenderer* m_renderer;

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