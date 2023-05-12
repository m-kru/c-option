#include <assert.h>
#include <stdbool.h>

#include "option.h"

typedef struct {
	int a;
	int b;
} custom_t;

opt_new_type(custom_t);

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
	opt_get_case(custom_t),
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
	bool b;
	assert(opt_get(o, &b));
	assert(b);
}

void test_opt_char(void) {
	opt_char_t o = none;
	assert(is_none(o));

	o = some((char)('a'));
	assert(!is_none(o));
	char c;
	assert(opt_get(o, &c));
	assert(c == 'a');
}

void test_opt_double(void) {
	opt_double_t o = none;
	assert(is_none(o));

	o = some(1.12);
	assert(!is_none(o));
	double d;
	assert(opt_get(o, &d));
	assert(d == 1.12);
}

void test_opt_float(void) {
	opt_float_t o = none;
	assert(is_none(o));

	o = some((float)1.12);
	assert(!is_none(o));
	float f;
	assert(opt_get(o, &f));
	assert(f == (float)(1.12));
}

void test_opt_int(void) {
	opt_int_t o = none;
	assert(is_none(o));

	o = some(1);
	assert(!is_none(o));
	int i;
	assert(opt_get(o, &i));
	assert(i == 1);
}

void test_opt_long(void) {
	opt_long_t o = none;
	assert(is_none(o));

	o = some((long)(1));
	assert(!is_none(o));
	long l;
	assert(opt_get(o, &l));
	assert(l == 1);
}

void test_opt_short(void) {
	opt_short_t o = none;
	assert(is_none(o));

	o = some((short)(1));
	assert(!is_none(o));
	short s;
	assert(opt_get(o, &s));
	assert(s == 1);
}

void test_opt_unsigned(void) {
	opt_unsigned_t o = none;
	assert(is_none(o));

	o = some((unsigned)111);
	assert(!is_none(o));
	unsigned u;
	assert(opt_get(o, &u));
	assert(u == 111);
}

void test_opt_custom_type(void) {
	opt_custom_t_t o = none;
	assert(is_none(o));

	o = some((
		(custom_t){.a = 1, .b = 2}
	));
	assert(!is_none(o));

	custom_t c;
	assert(opt_get(o, &c));
	assert(c.a == 1);
	assert(c.b == 2);
}

int main(int argc, char *argv[]) {
	test_opt_bool();
	test_opt_char();
	test_opt_double();
	test_opt_float();
	test_opt_int();
	test_opt_long();
	test_opt_short();
	test_opt_unsigned();

	test_opt_custom_type();

	return 0;
}
