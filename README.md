# c-option

Lightweight (single header file) C module implementing generic option type.

`short`, `int`, `long` and `unsigned` types are not supported as they usually conflict in the `_Generic` macro with `int16_t`, `int32_t`, `int64_t` and `uint*_t`  types.
As types from `stdint.h` always have specified width they are favored over C standard types.

## Why?

Sometimes there is a difference between data zero value and no data at all.
In such a case C offers pointers and checking against `NULL`.
However, such apporach has at least two drawbacks:

1. It is quite easy to dereference pointer without checking if it is not `NULL`.
2. In some contexts dynamic memory allocation would be required, and bare-metal embedded systems usually do not support dynamic memory allocation (for good reasons).

This module implements option type not requiring dynamic memory allocation and being much more safer than using a pointer.
In case of unused return value from the `opt_get` compiler will issue a warning:
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

```c
#include <stdio.h>
#include <stdint.h>

#include "option.h"

opt_int32_t foo(void) {
	return some((int32_t)0);
}

int main(int argc, char *argv[]) {
	opt_int32_t o = none;
	int32_t i;

	if opt_get(o, &i)
		printf("some(%d)\n", i);
	else
		printf("none\n");

	o = foo();

	if opt_get(o, &i)
		printf("some(%d)\n", i);
	else
		printf("none\n");

	return 0;
}
```

### Custom types

One possible way to add custom option types is to create a separate `option.h` header within the project.
In the custom `option.h` include `option.h` from this repository.
In your project files include your custom `option.h` header.
Then use proper macros to add custom option types.

```c
#ifndef _MY_OPTION_H_
#define _MY_OPTION_H_

#include <c-option/option.h

// Do whatever you want. This is normal header file.

typedef struct {
	int a;
	int b;
} my_t;

opt_new_type(my_t);

#undef opt_some_custom_types
#define opt_some_custom_types\
	opt_some_case(my_t),
#undef some
#define some(x) _Generic((x),\
	opt_some_custom_types\
	opt_some_std_types\
)(x)

#undef opt_get_custom_types
#define opt_get_custom_types\
	opt_get_case(my_t),
#undef opt_get
#define opt_get(o, ptr) _Generic((o),\
	opt_get_custom_types\
	opt_get_std_types\
)(o, ptr)

#endif // _MY_OPTION_H_
```

Most of what is seen in the above listing is copied only once.
As one can see, `my_t` is used in three places.
This is verbose.
If you know how to do it better, please let me know.
The good news is if you miss any of the three macros, the compilation will exit with error.

To add support for next custom type three macro calls are needed:
- `opt_new_type` / `opt_new_type_t`,
- `opt_some_case`,
- `opt_get_case` / `opt_get_case_t`.
-
`opt_some_case` is common. Use:
- `opt_new_type` and `opt_get_case` if your type name **does not have** the `_t` suffix,
- `opt_new_type_t` and `opt_get_case_t` if your type name **has** the `_t` suffix.

You can also implement a simple Perl or Python script that will automatically generate your custom option header file based on whatever input you want.

## Safety
This module does not guarantee 100% safety.
However, it is much safer to use than pointer approach if you follow the rules.
Theoretically, with access to the AST (Abstract Syntax Tree) it should be possible to implement a linter that would guarantee 100% safety.
