#/bin/sh
fastrtpsgen -example CMake ../../../HelloWorld.idl
mkdir build && cd build
cmake ..
make
