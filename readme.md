# BFC v1.0.0
* Brainfuck compiler

## Building

* Clone the repo
```sh
git clone https://github.com/Tacomies/brainfuck/
```

* Using CMake and Make

```sh
mkdir build
cd build
cmake ..
make
```

* Manually

```sh
gcc -c src/loader.cpp
gcc -c src/transpiler.cpp
gcc -o bfc src/main.cpp loader.o transpiler.o
rm loader.o transpiler.o 
```

## Usage

```sh
bfc <source file path> <destination path>
```

## Dependencies
* [GCC](https://gcc.gnu.org/) is required for BFC to work
