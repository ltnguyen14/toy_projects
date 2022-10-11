#pragma once
#include "cstdint"
#include "stddef.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uintmax_t uintmax;

typedef float f32;
typedef double f64;

typedef unsigned char byte;

// Useful functions
#define ARRAY_COUNT(arr) (sizeof(arr) / sizeof((arr)[0]))
#define MIN(x, y) ((x) < (y)) ? (x) : y
#define MAX(x, y) ((x) > (y)) ? (x) : y
#define BIT(x) (1 << (x))

//
#define  B(x)  (x)
#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)
#define GB(x) ((x) << 30)
#define TB(x) (((u64)x) << 40)

//
#define global static
#define global_static static const

