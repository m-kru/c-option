// SPDX-License-Identifier: MIT
// https://github.com/m-kru/c-panic
// Copyright (c) 2023 Michał Kruszewski

#ifndef _OPTION_H_
#define _OPTION_H_

#include <stdbool.h>

#define none {._none = true}
#define is_none(o) (o._none)


#define opt_some_case(type) type: _opt_ ## type

#define opt_some_custom_types

#define opt_some_std_types\
	opt_some_case(bool),\
	opt_some_case(char),\
	opt_some_case(double),\
	opt_some_case(float),\
	opt_some_case(int8_t),\
	opt_some_case(int16_t),\
	opt_some_case(int32_t),\
	opt_some_case(int64_t),\
	opt_some_case(uint8_t),\
	opt_some_case(uint16_t),\
	opt_some_case(uint32_t),\
	opt_some_case(uint64_t)

#define some(x) _Generic((x),\
	opt_some_custom_types\
	opt_some_std_types\
)(x)


#define opt_get_case(type) opt_ ## type ##_t: _opt_ ## type ## _get
#define opt_get_case_t(type) opt_ ## type: _opt_ ## type ## _get

#define opt_get_std_types\
	opt_get_case(bool),\
	opt_get_case(char),\
	opt_get_case(double),\
	opt_get_case(float),\
	opt_get_case_t(int8_t),\
	opt_get_case_t(int16_t),\
	opt_get_case_t(int32_t),\
	opt_get_case_t(int64_t),\
	opt_get_case_t(uint8_t),\
	opt_get_case_t(uint16_t),\
	opt_get_case_t(uint32_t),\
	opt_get_case_t(uint64_t)

#define opt_get_custom_types

#define opt_get(o, ptr) _Generic((o),\
	opt_get_custom_types\
	opt_get_std_types\
)(o, ptr)


#define opt_new_type(type)\
typedef struct {bool _none; type _x;} opt_ ## type ## _t;\
\
static inline __attribute__((always_inline))\
opt_ ## type ## _t _opt_ ## type (type x) { \
	opt_ ## type ## _t o = {._none = false, ._x = x}; \
	return o; \
}\
\
__attribute__((warn_unused_result))\
static inline __attribute__((always_inline))\
bool _opt_ ## type ## _get(opt_ ## type ## _t o, type *i) {\
	if (o._none)\
		return false;\
	*i = o._x;\
	return true;\
}

#define opt_new_type_t(type)\
typedef struct {bool _none; type _x;} opt_ ## type;\
\
static inline __attribute__((always_inline))\
opt_ ## type  _opt_ ## type (type x) { \
	opt_ ## type o = {._none = false, ._x = x}; \
	return o; \
}\
\
__attribute__((warn_unused_result))\
static inline __attribute__((always_inline))\
bool _opt_ ## type ## _get(opt_ ## type o, type *i) {\
	if (o._none)\
		return false;\
	*i = o._x;\
	return true;\
}

opt_new_type(bool)
opt_new_type(char)
opt_new_type(double)
opt_new_type(float)

opt_new_type_t(int8_t)
opt_new_type_t(int16_t)
opt_new_type_t(int32_t)
opt_new_type_t(int64_t)

opt_new_type_t(uint8_t)
opt_new_type_t(uint16_t)
opt_new_type_t(uint32_t)
opt_new_type_t(uint64_t)

#endif // _OPTION_H_
