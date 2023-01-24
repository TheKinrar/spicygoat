#pragma once

#include "traits/Halfable.h"
#include "traits/Orientable.h"
#include "traits/OrientableOpposite.h"
#include "traits/WallMountable.h"

namespace Traits {

static inline constexpr Halfable halfable;
static inline constexpr Orientable orientable;
static inline constexpr OrientableOpposite orientableOpposite;
static inline constexpr WallMountable wallMountable;

}
