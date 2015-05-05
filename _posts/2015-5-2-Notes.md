---
layout: post
title: Notes
---

[What is the difference between char s[] and char *s in C?](http://stackoverflow.com/questions/1704407/what-is-the-difference-between-char-s-and-char-s-in-c)

	char s[] = "hello";
Creates one object - a char array of size 6, called s, initialised with the values 'h', 'e', 'l', 'l', 'o', '\0'. Where this array is allocated in memory, and how long it lives for, depends on where the declaration appears. If the declaration is within a function, it will live until the end of the block that it is declared in, and almost certainly be allocated on the stack; if it's outside a function, it will probably be stored within an "initialised data segment" that is loaded from the executable file into writeable memory when the program is run.

	char *s ="hello";
Creates two objects:
- a read-only array of 6 chars containing the values 'h', 'e', 'l', 'l', 'o', '\0', which has no name and has static storage duration (meaning that it lives for the entire life of the program); and
- a variable of type pointer-to-char, called s, which is initialised with the location of the first character in that unnamed, read-only array.
