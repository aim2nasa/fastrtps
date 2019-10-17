CXX = g++
CXXFLAGS = -g -O2 -Wall -Wextra -std=c++11
IDL = ../../HelloWorld.idl

TARGET_PUB = pub
SRCS_PUB = pub_main.cpp
OBJS_PUB = ${SRCS_PUB:.cpp=.o}

TARGET_SUB = sub
SRCS_SUB = sub_main.cpp
OBJS_SUB = ${SRCS_SUB:.cpp=.o}

LIBS = -lfastrtps -L$(shell pwd) -lHelloWorld

all : pre-build main-build

pre-build:
	@echo PRE
	@cd gen;make

main-build: $(TARGET_PUB) $(TARGET_SUB)

$(TARGET_PUB) : $(OBJS_PUB)
	@echo $@:$^...
	$(CXX) -o $@ $^ $(LIBS)

$(TARGET_SUB) : $(OBJS_SUB)
	@echo $@:$^...
	$(CXX) -o $@ $^ $(LIBS)

%.o : %.cpp
	@echo $@:$^...
	$(CXX) -c $< $(INCLUDES) $(CXXFLAGS)

clean:
	@echo $@...
	@cd gen;make clean
	rm -rf *.o $(TARGET_PUB) $(TARGET_SUB) *.so*

idl:
	fastrtpsgen $(IDL) -d gen
