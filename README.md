# c-option

Lightweight (single header file) C module implementing generic option type.

`short`, `int`, `long` and `unsigned` types are not supported as they usually conflict in the `_Generic` macro with `int16_t`, `int32_t`, `int64_t` and `unsigned`  types.
As types from `stdint.h` always have specified width they are favored over C standard types.

## Why?

Sometimes there is a difference between data zero value and no data at all.
In such a case C offers pointers and checking against `NULL`.
However, such apporach has at least two drawbacks:

1. It is quite easy to dereference pointer without checking if it is not `NULL`.
2. In some contexts dynamic memory allocation would be required, and bare-metal embedded systems usually do not support dynamic memory allocation (for good reasons).

This module implements option type not requiring dynamic memory allocation and being much more safer than using pointer.
In case of unused return value from `opt_get` compiler will issue the warning:
```
In file included from main.c:4:
main.c: In function ‘main’:
option.h:57:25: warning: ignoring return value of ‘_opt_int32_t_get’, declared with attribute warn_unused_result [-Wunused-result]
   57 | #define opt_get(o, ptr) _Generic((o),\
      |                         ^
main.c:14:2: note: in expansion of macro ‘opt_get’
   14 |  opt_get(o, &i);
      |
```

## Usage

Simply copy the `option.h` file into the project.

Variable type indicates the type of the inner variable, for example `opt_int8_t`, `opt_double_t`, `opt_bool_t` etc.
However, methods for setting a value to `none` or `some`, or getting the value `opt_get` are generic.
`none` is simple macro `#define none {._none = true}`, `some` and `opt_get` are generic macros.

### Standard types only

Simply `#include "option.h"`.

```C
#include <stdio.h>
#include <stdint.h>

#include "option.h"

opt_int32_t foo(void) {
	return some((int32_t)0);
}

int main(int argc, char *argv[]) {
	opt_int32_t o = none;
	int32_t i;

	if (opt_get(o, &i))
		printf("some(%d)\n", i);
	else
		printf("none\n");

	o = foo();

	if (opt_get(o, &i))
		printf("some(%d)\n", i);
	else
		printf("none\n");

	return 0;
}
```

### Custom types
