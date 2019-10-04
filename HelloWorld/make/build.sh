#/bin/sh
fastrtpsgen -example x64Linux2.6gcc ../HelloWorld.idl
make -f makefile_x64Linux2.6gcc 
