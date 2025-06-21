#pragma once

#include <cstdint>

namespace Engine
{
    using Entity = uint32_t;
    constexpr Entity kInvalidEntity = static_cast<Entity>(-1);
}