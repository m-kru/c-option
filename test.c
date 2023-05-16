#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "option.h"

typedef struct {
	int a;
	int b;
} custom_t;

opt_new_type_t(custom_t);

#undef opt_some_custom_types
#define opt_some_custom_types\
	opt_some_case(custom_t),
#undef some
#define some(x) _Generic((x),\
	opt_some_custom_types\
	opt_some_std_types\
)(x)

#undef opt_get_custom_types
#define opt_get_custom_types\
	opt_get_case_t(custom_t),
#undef opt_get
#define opt_get(o, ptr) _Generic((o),\
	opt_get_custom_types\
	opt_get_std_types\
)(o, ptr)

void test_opt_bool(void) {
	opt_bool_t o = none;
	assert(is_none(o));

	o = some((bool)(true));
	assert(!is_none(o));
	bool x;
	assert(opt_get(o, &x));
	assert(x);
}

void test_opt_char(void) {
	opt_char_t o = none;
	assert(is_none(o));

	o = some((char)('a'));
	assert(!is_none(o));
	char x;
	assert(opt_get(o, &x));
	assert(x == 'a');
}

void test_opt_double(void) {
	opt_double_t o = none;
	assert(is_none(o));

	o = some(1.12);
	assert(!is_none(o));
	double x;
	assert(opt_get(o, &x));
	assert(x == 1.12);
}

void test_opt_float(void) {
	opt_float_t o = none;
	assert(is_none(o));

	o = some((float)1.12);
	assert(!is_none(o));
	float x;
	assert(opt_get(o, &x));
	assert(x == (float)(1.12));
}

void test_opt_int8_t(void) {
	opt_int8_t o = none;
	assert(is_none(o));

	o = some((int8_t)8);
	assert(!is_none(o));
	int8_t x;
	assert(opt_get(o, &x));
	assert(x == 8);
}

void test_opt_int16_t(void) {
	opt_int16_t o = none;
	assert(is_none(o));

	o = some((int16_t)16);
	assert(!is_none(o));
	int16_t x;
	assert(opt_get(o, &x));
	assert(x == 16);
}

void test_opt_int32_t(void) {
	opt_int32_t o = none;
	assert(is_none(o));

	o = some((int32_t)32);
	assert(!is_none(o));
	int32_t x;
	assert(opt_get(o, &x));
	assert(x == 32);
}

void test_opt_int64_t(void) {
	opt_int64_t o = none;
	assert(is_none(o));

	o = some((int64_t)64);
	assert(!is_none(o));
	int64_t x;
	assert(opt_get(o, &x));
	assert(x == 64);
}

void test_opt_uint8_t(void) {
	opt_uint8_t o = none;
	assert(is_none(o));

	o = some((uint8_t)8);
	assert(!is_none(o));
	uint8_t x;
	assert(opt_get(o, &x));
	assert(x == 8);
}

void test_opt_uint16_t(void) {
	opt_uint16_t o = none;
	assert(is_none(o));

	o = some((uint16_t)16);
	assert(!is_none(o));
	uint16_t x;
	assert(opt_get(o, &x));
	assert(x == 16);
}

void test_opt_uint32_t(void) {
	opt_uint32_t o = none;
	assert(is_none(o));

	o = some((uint32_t)32);
	assert(!is_none(o));
	uint32_t x;
	assert(opt_get(o, &x));
	assert(x == 32);
}

void test_opt_uint64_t(void) {
	opt_uint64_t o = none;
	assert(is_none(o));

	o = some((uint64_t)64);
	assert(!is_none(o));
	uint64_t x;
	assert(opt_get(o, &x));
	assert(x == 64);
}

void test_opt_custom_type(void) {
	opt_custom_t o = none;
	assert(is_none(o));

	o = some((
		(custom_t){.a = 1, .b = 2}
	));
	assert(!is_none(o));

	custom_t x;
	assert(opt_get(o, &x));
	assert(x.a == 1);
	assert(x.b == 2);
}

int main(int argc, char *argv[]) {
	test_opt_bool();
	test_opt_char();
	test_opt_double();
	test_opt_float();

	test_opt_int8_t();
	test_opt_int16_t();
	test_opt_int32_t();
	test_opt_int64_t();

	test_opt_uint8_t();
	test_opt_uint16_t();
	test_opt_uint32_t();
	test_opt_uint64_t();

	test_opt_custom_type();

	return 0;
}
