CXX = g++
CXXFLAGS = -g -O2 -Wall -Wextra -std=c++11
IDL = ../HelloWorld.idl

TARGET_PUB = pub
SRCS_PUB = pub_main.cpp
OBJS_PUB = ${SRCS_PUB:.cpp=.o}

LIBS = -lfastrtps

all : pre-build main-build

pre-build:
	@echo PRE
	@cd gen;make

main-build: $(TARGET_PUB)

$(TARGET_PUB) : $(OBJS_PUB)
	@echo $@:$^...
	$(CXX) -o $@ $^ $(LIBS)

%.o : %.cpp
	@echo $@:$^...
	$(CXX) -c $< $(INCLUDES) $(CXXFLAGS)

clean:
	@echo $@...
	@cd gen;make clean
	rm -rf *.o $(TARGET_PUB)

idl:
	fastrtpsgen $(IDL) -d gen
