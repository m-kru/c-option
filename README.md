# c-option

Lightweight (single header file) C module implementing generic option type.

`short`, `int`, `long` and `unsigned` types are not supported as they usually conflict in the `_Generic` macro with `int16_t`, `int32_t`, `int64_t` and `unsigned`  types.
As types from `stdint.h` always have specified width they are favored over C standard types.

## Why?

## Usage

### Standard types only

### Custom types

## Examples
