#pragma once

#include <spicygoat/block/traits/Halfable.h>
#include <spicygoat/block/traits/Orientable.h>
#include <spicygoat/block/traits/OrientableOpposite.h>
#include <spicygoat/block/traits/WallMountable.h>

namespace Traits {

static inline constexpr Halfable halfable;
static inline constexpr Orientable orientable;
static inline constexpr OrientableOpposite orientableOpposite;
static inline constexpr WallMountable wallMountable;

}
