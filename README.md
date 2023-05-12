# c-option

Lightweight (single header file) C module implementing generic option type.

`short`, `int` and `long` types are not supported as they usually conflict in the `_Generic` macro with `int16_t`, `int32_t` and `int64_t` types.
As types from `stdint.h` always have specified width they are favored over C standard types.
