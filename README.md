# Diseq
Diseq is a small C library for displaying ANSI escape sequences in the terminal. This makes it possible to control things such as text styling, colour, position, how user input is handled, etc.

## Use
Diseq is an stb-style single header library - that means that the entire library is contained within a single header file - definitions and all! It is possible to configure some library functions using compile-time definitions - you can also opt-out of the default implementation (which depends on libc) and roll your own.

Simply include the header file in your code, and use the functions. If you want the default implementation, do `#define DISEQ_IMPLEMENTATION` before the `#include` directive.

## Warning
This library is in early beta, and is designed to be bare-bones. I don't plan for big changes to the API, but additions may certainly happen (I'll try to keep future changes backwards-compatible, but there's no promise!).
