echo off
set GXX=D:/Apps/llvm-mingw-20250709-msvcrt-x86_64/bin/g++.exe
set INCLUDES=-I include -I C:/vcpkg/installed/x64-mingw-dynamic/include
set LIBS=-L C:/vcpkg/installed/x64-mingw-dynamic/lib -lSDL3
set SOURCES=src/main.cpp src/Physics.cpp src/Renderer.cpp
set OUTPUT=build/sandbox.exe

%GXX% -O2 -std=c++17 %INCLUDES% %SOURCES% %LIBS% -o %OUTPUT%
