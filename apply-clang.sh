#!/bin/sh

PATH=$PATH:"/c/Program Files/LLVM/bin/":"/d/Program Files/LLVM/bin/"

CLANG_BINARY="clang-format.exe"

for filename in `find src test -iname "*.cpp" -o -iname "*.h"`
do
    echo "Formatting $filename"
    "$CLANG_BINARY" -i "$filename"
done

for filename in `find lib/freertossupport lib/cliSupport -iname "*.cpp" -o -iname "*.h"`
do
    echo "Formatting $filename"
    "$CLANG_BINARY" -i "$filename"
done
