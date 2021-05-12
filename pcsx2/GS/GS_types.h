
#pragma once

#include <xbyak/xbyak.h>
#include <xbyak/xbyak_util.h>
#define MIE_INTEGER_TYPE_DEFINED
#define XBYAK_ENABLE_OMITTED_OPERAND

#include <cfloat>

typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef unsigned int uint32;
typedef signed int int32;
typedef unsigned long long uint64;
typedef signed long long int64;

#ifndef RESTRICT

#ifdef __INTEL_COMPILER

#define RESTRICT restrict

#elif defined(_MSC_VER)

#define RESTRICT __restrict

#elif defined(__GNUC__)

#define RESTRICT __restrict__

#else

#define RESTRICT

#endif

#endif

#define _MM_TRANSPOSE4_SI128(row0, row1, row2, row3) \
	{ \
		__m128 tmp0 = _mm_shuffle_ps(_mm_castsi128_ps(row0), _mm_castsi128_ps(row1), 0x44); \
		__m128 tmp2 = _mm_shuffle_ps(_mm_castsi128_ps(row0), _mm_castsi128_ps(row1), 0xEE); \
		__m128 tmp1 = _mm_shuffle_ps(_mm_castsi128_ps(row2), _mm_castsi128_ps(row3), 0x44); \
		__m128 tmp3 = _mm_shuffle_ps(_mm_castsi128_ps(row2), _mm_castsi128_ps(row3), 0xEE); \
		(row0) = _mm_castps_si128(_mm_shuffle_ps(tmp0, tmp1, 0x88)); \
		(row1) = _mm_castps_si128(_mm_shuffle_ps(tmp0, tmp1, 0xDD)); \
		(row2) = _mm_castps_si128(_mm_shuffle_ps(tmp2, tmp3, 0x88)); \
		(row3) = _mm_castps_si128(_mm_shuffle_ps(tmp2, tmp3, 0xDD)); \
	}


extern void* vmalloc(size_t size, bool code);
extern void vmfree(void* ptr, size_t size);

// _wfopen has to be used on Windows for pathnames containing non-ASCII characters.
inline FILE* px_fopen(const std::string& filename, const std::string& mode)
{
#ifdef _WIN32
	return _wfopen(convert_utf8_to_utf16(filename).c_str(), convert_utf8_to_utf16(mode).c_str());
#else
	return fopen(filename.c_str(), mode.c_str());
#endif
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

#ifdef __cpp_constinit
#define CONSTINIT constinit
#elif __has_attribute(require_constant_initialization)
#define CONSTINIT __attribute__((require_constant_initialization))
#else
#define CONSTINIT
#endif
