#pragma once

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define global static
#define internal static
#define local_persist static

#define kb(n) (1000 * (n))
#define mb(n) (1000000 * (n))
#define gb(n) (1000000000 * (n))
#define tb(n) (1000000000000 * (n))

#define min(A, B) (((A) < (B)) ? (A) : (B))
#define max(A, B) (((A) > (B)) ? (A) : (B))
#define clamp(A, X, B) (((X) < (A)) ? (A) : ((X) > (B)) ? (B) : (X))
#define mod(X, N) (((X) % (N) + (N)) % (N))
#define abs(X) ((X) < 0 ? (-(X)) : (X))
#define cmp(A, B) ((A) < (B) ? (-1) : ((A) > (B) ? (1) : (0)))

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef int8_t b8;
typedef int16_t b16;
typedef int32_t b32;
typedef int64_t b64;
typedef float f32;
typedef double f64;
typedef union u128 {
    u8 u8[16];
    u16 u16[8];
    u32 u32[4];
    u64 u64[2];
} u128;
typedef union u256 {
    u8 u8[32];
    u16 u16[16];
    u32 u32[8];
    u64 u64[4];
    u128 u128[2];
} u256;
typedef union u512 {
    u8 u8[64];
    u16 u16[32];
    u32 u32[16];
    u64 u64[8];
    u128 u128[4];
    u256 u256[2];
} u512;
