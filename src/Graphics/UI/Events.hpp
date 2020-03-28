#pragma once

namespace Jam
{
    class Event {
    public:
        bool handled;
        virtual ~Event() = default;
    };

    class ButtonPressEvent : public Event {
    public:
        int button;
        double x, y;
        virtual ~ButtonPressEvent() = default;
    };

    class KeyPressEvent : public Event {
    public:
        int key;
        double x, y;
        virtual ~KeyPressEvent() = default;
    };
}