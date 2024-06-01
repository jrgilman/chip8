#!/usr/bin/env bash

cmake -S . -B build -DUNIT_TEST=1 && cmake --build ./build/ && ./build/tests/chip8_tests