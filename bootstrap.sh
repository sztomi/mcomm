#!/bin/sh
./scripts/codegen.py -v -d ./src ./generated/generated.cc
premake5 gmake
