#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include <functional>

#include "vendor.h"
#include "Events.hpp"
#include "../../PowerLogger.hpp"

namespace Jam
{
	class Widget 
	{
	protected:
		Widget* m_parent;
		glm::vec2 m_localPos, m_pixelPos, m_localSize, m_pixelSize;
	public:

		glm::mat4 getTransform() const {
			return glm::translate<float>(glm::mat4(1.0f), glm::vec3(m_pixelPos, 0)) * glm::scale<float>(glm::mat4(1.0f), glm::vec3(m_pixelSize, 1.0f));
		}

		void setParent(Widget* p) {
			m_parent = p;
		}

		Widget* getParent() {
			return m_parent;
		}

		void setLocalPos(glm::vec2 pos) {
			m_localPos = pos;
		} 
		
		void setPixelPos(glm::vec2 pos) {
			m_pixelPos = pos;
		} 

		glm::vec2 getLocalPos() const {
			return m_localPos;
		}
		
		glm::vec2 getPixelPos() const {
			return m_pixelPos;
		}

		void setLocalSize(glm::vec2 s) { 
			m_localSize = s;
		}
		
		void setPixelSize(glm::vec2 s) { 
			m_pixelSize = s;
		}

		glm::vec2 getLocalSize() const {
			return m_localSize;

		}
		glm::vec2 getPixelSize() const {
			return m_pixelSize;
		}

		virtual void handleEvent(std::shared_ptr<Event> event)
		{
		}

		Widget() : m_parent(nullptr), m_localPos(0,0), m_pixelPos(0,0), m_localSize(0,0), m_pixelSize(0,0) {}
		virtual ~Widget() = default;
	};

	using WidgetPtr = std::shared_ptr<Widget>;

	class Container : public Widget
	{
	protected:
		std::vector<WidgetPtr> m_children;

	public:

		virtual void handleEvent(std::shared_ptr<Event> event) override
		{
			for(WidgetPtr child : m_children) {
				if(!event->handled){
					child->handleEvent(event);
				}
			}
		}

		virtual void addChild(WidgetPtr ptr) {
			ptr->setParent(this);
			m_children.push_back(ptr);
		}

		virtual void removeChild(WidgetPtr ptr) {
			ptr->setParent(nullptr);
			m_children.erase(std::find(m_children.begin(), m_children.end(), ptr));
		}

		void clearChildren() {
			for (auto& c : m_children) {
				c->setParent(nullptr);
			}
			m_children.clear();
		}

		const std::vector<WidgetPtr>& getChildren() const {
			return m_children;
		}

		Container() {}
		~Container() = default;
	};

	class Layout
	{
	protected:
		Container* m_parent;
	public:
		void setParent(Container* p) {
			m_parent = p;
		}

		virtual void start() {}
		virtual void end() {}

		virtual glm::vec2 calcPos(glm::vec2 lPos, glm::vec2 lSize) = 0;
		virtual glm::vec2 calcSize(glm::vec2 lSize) = 0;

		virtual ~Layout() = default;
	};

	class HChronoLayout : public Layout 
	{
	private:
		float sizeCnt = 0;
		glm::vec2 pixelsPerUnit;
	public:
		virtual void start() override { 
			sizeCnt = 0;
			glm::vec2 totalSize = { 0,0 };
			for (const auto& child : m_parent->getChildren()) {
				totalSize += child->getLocalSize();
			}
			pixelsPerUnit  = { m_parent->getPixelSize().x / totalSize.x, m_parent->getPixelSize().y / totalSize.y };
		}
		
		virtual void end() {
		}

		virtual glm::vec2 calcPos(glm::vec2 lPos, glm::vec2 lSize) { 
			glm::vec2 out(pixelsPerUnit.x * (float)sizeCnt, 0);
			sizeCnt += lSize.x;
			return m_parent->getPixelPos() + out;
		}

		virtual glm::vec2 calcSize(glm::vec2 lSize) {
			return glm::vec2(lSize.x, 1) * glm::vec2(pixelsPerUnit.x, m_parent->getPixelSize().y);
		}
	};

	class VChronoLayout : public Layout 
	{
	private:
		float sizeCnt = 0;
		glm::vec2 pixelsPerUnit;
	public:
		virtual void start() override { 
			sizeCnt = 0;
			glm::vec2 totalSize = { 0,0 };
			for (const auto& child : m_parent->getChildren()) {
				totalSize += child->getLocalSize();
			}
			pixelsPerUnit  = { m_parent->getPixelSize().x / totalSize.x, m_parent->getPixelSize().y / totalSize.y };
		}
		
		virtual void end() {
		}

		virtual glm::vec2 calcPos(glm::vec2 lPos, glm::vec2 lSize) { 
			glm::vec2 out(0, pixelsPerUnit.y * (float)(sizeCnt));
			sizeCnt += lSize.y;
			return m_parent->getPixelPos() + out;
		}

		virtual glm::vec2 calcSize(glm::vec2 lSize) {
			return glm::vec2(1,lSize.y) * glm::vec2(m_parent->getPixelSize().x, pixelsPerUnit.y);
		}
	};

	/*
	class FlowLayout : public Layout
	{

	};

	class GridLayout : public Layout
	{

	};
	*/

	class Frame : public Container
	{
	private:
		std::shared_ptr<Layout> m_layout;
		bool m_visible = true;

	public:
		virtual void handleEvent(std::shared_ptr<Event> event) override
		{
			if(m_visible) {
				Container::handleEvent(event);
			}
		}

		void refreshPixelPositions() {
			if (!m_layout) return;

			m_layout->start();

			for (auto& child : m_children) {
				child->setPixelPos(m_layout->calcPos(child->getLocalPos(), child->getLocalSize()));
				child->setPixelSize(m_layout->calcSize(child->getLocalSize()));

				auto fp = std::dynamic_pointer_cast<Frame>(child);
				if(fp) {
					fp->refreshPixelPositions();
				}
			}

			m_layout->end();
		}


		virtual void addChild(WidgetPtr child) override {
			Container::addChild(child);
			refreshPixelPositions();
		}

		virtual void removeChild(WidgetPtr child) override {
			Container::removeChild(child);
			refreshPixelPositions();
		}

		void setLayout(std::shared_ptr<Layout> layout) {
			m_layout = layout;
			m_layout->setParent(this);
		}
		
		void show() {
			m_visible = true;
		}

		void hide() {
			m_visible = false;
		}
		
		bool visible() const {
			return m_visible;
		}

		//void setCatchEvents(bool);
		//bool catchingEvents() const;

		Frame() {
			setLocalPos({0,0});
			setLocalSize({1,1});
			setPixelPos({0,0});
			setPixelSize({0,0});
		}

		Frame(glm::vec2 lPos, glm::vec2 lSize, glm::vec2 pPos, glm::vec2 pSize) {
			setLocalPos(lPos);
			setLocalSize(lSize);
			setPixelPos(pPos);
			setPixelSize(pSize);
		}
	};

	using FramePtr = std::shared_ptr<Frame>;

	class ButtonWidget : public Widget {
	private:
		std::function<void()> m_cb;

	public:

		void setCallback(std::function<void()> cb) {
			m_cb = cb;
		}

		virtual void handleEvent(std::shared_ptr<Event> event) override
		{
			auto btn = std::dynamic_pointer_cast<ButtonPressEvent>(event);
			if(btn) {
				if(btn->button == 0 && btn->x > m_pixelPos.x && btn->x < m_pixelPos.x + m_pixelSize.x && 
					btn->y > m_pixelPos.y && btn->y < m_pixelPos.y + m_pixelSize.y) {
						m_cb();
						event->handled = true;
					}
			}
		}
	};

}