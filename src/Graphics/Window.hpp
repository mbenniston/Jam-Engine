#pragma once
#include <string>

#include "vendor.h"

#include "UI/Widget.hpp"
#include "UI/UIRenderer.hpp"

#include "../Assets/Assets.h"

struct GLFWwindow;

namespace Jam
{
	static constexpr std::array<const char*, 3> DEFAULT_ICON_PATHS = {"icons/icon.png", "icons/icon2.png", "icons/icon3.png"};
	
	struct WindowSpec
	{
		int width = 1280, height = 720;
		bool resizable = true, decorated = false, transparentfb = false;
		std::string title = "Jam Window";
	};

	class Window final : public Frame
	{
	private:
		GLFWwindow* m_handle;
		UIRenderer* m_renderer;

	public:

		inline GLFWwindow* getHandle() {
			return m_handle;
		}

		void open(const WindowSpec& ws);
		void update();
		void close();

		void setIcon(const std::vector<File>& file);

		glm::ivec2 getSize() const;
		int getWidth() const;
		int getHeight() const;

		glm::ivec2 getPos() const;
		void setPos(glm::ivec2 pos) const;

		bool shouldClose() const;

		glm::vec2 getMousePosition() const;
		bool getMouseButton(int btn) const;

		Window();
		Window(const WindowSpec& ws);
		~Window();
	};
}