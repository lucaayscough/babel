#!/bin/bash

sdl2=$(pkg-config --libs --cflags sdl2)
clang -Wall -Wextra -std=c11 -pedantic -g -O0 ${sdl2} main.c -o out &&
echo "Launching executable:"
./out
