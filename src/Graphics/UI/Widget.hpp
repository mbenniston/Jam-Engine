#pragma once
#include <memory>
#include <vector>

#include "vendor.h"

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

		Widget() : m_parent(nullptr), m_localPos(0,0), m_pixelPos(0,0), m_localSize(0,0), m_pixelSize(0,0) {}
		virtual ~Widget() = default;
	};

	using WidgetPtr = std::shared_ptr<Widget>;

	class Container : public Widget
	{
	protected:
		std::vector<WidgetPtr> m_children;

	public:
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

		virtual glm::vec2 calcPos(glm::vec2 lPos) = 0;
		virtual glm::vec2 calcSize(glm::vec2 lSize) = 0;

		virtual ~Layout() = default;
	};

	class HChronoLayout : public Layout 
	{
	private:
		unsigned int counter = 0;
		glm::vec2 pixelsPerUnit;
	public:
		virtual void start() override { 
			glm::vec2 totalSize = { 0,0 };
			for (const auto& child : m_parent->getChildren()) {
				totalSize += child->getLocalSize();
			}
			pixelsPerUnit  = { m_parent->getPixelSize().x / totalSize.x, m_parent->getPixelSize().y / totalSize.y };
		}
		
		virtual void end() {
		}

		virtual glm::vec2 calcPos(glm::vec2 lPos) { 
			return glm::vec2(pixelsPerUnit.x * (float)(counter++), 0);
		}

		virtual glm::vec2 calcSize(glm::vec2 lSize) {
			return lSize * pixelsPerUnit;
		}
	};

	/*
	class FlowLayout : public Layout
	{

	};

	class GridLayout : public Layout
	{

	};*/

	class Frame : public Container
	{
	private:
		std::shared_ptr<Layout> m_layout;
		bool m_visible = true;

		void refreshPixelPositions() {
			if (!m_layout) return;

			m_layout->start();

			for (auto& child : m_children) {
				child->setPixelPos(m_layout->calcPos(child->getLocalPos()));
				child->setPixelSize(m_layout->calcPos(child->getLocalSize()));
			}

			m_layout->end();
		}

	public:

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

		Frame(glm::vec2 lPos, glm::vec2 lSize, glm::vec2 pPos, glm::vec2 pSize) {
			setLocalPos(lPos);
			setLocalSize(lSize);
			setPixelPos(pPos);
			setPixelSize(pSize);
		}
	};

	using FramePtr = std::shared_ptr<Frame>;

}