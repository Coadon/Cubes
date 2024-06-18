#pragma once

#include <ctime>
#include <cmath>
#include <cassert>
#include <cstddef>
#include <cstring>

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include <cstdint>
#include <inttypes.h>

#include "glm/glm.hpp"

#include "spdlog/spdlog.h"

#define LOGGER (*spdlog::get("main"))

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float float32_t, f32;
typedef double float64_t, f64;

typedef void *HANDLE;
