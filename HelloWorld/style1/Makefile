IDL = ../HelloWorld.idl

TARGET_PUB = pub
SRCS_PUB = pub_main.cpp
OBJS_PUB = ${SRCS_PUB:.cpp=.o}

all : pre-build main-build

pre-build:
	@echo PRE
	@fastrtpsgen $(IDL) -d gen
	@cd gen;make

main-build: $(TARGET_PUB)

$(TARGET_PUB) : $(OBJS_PUB)
	@echo $@:$^...
	$(CXX) -o $@ $^

%.o : %.cpp
	@echo $@:$^...
	$(CXX) -c $< $(INCLUDES) $(CXXFLAGS)


clean:
	@echo $@...
	@cd gen;make clean
	rm -rf *.o $(TARGET_PUB)
