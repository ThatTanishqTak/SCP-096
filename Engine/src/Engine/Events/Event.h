#pragma once

namespace Engine
{
    enum class EventType
    {
        None = 0,
        Quit,
    };

    struct Event
    {
        EventType Type{ EventType::None };
    };
}