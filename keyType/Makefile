CXX = g++
CXXFLAGS = -g -O2 -Wall -Wextra -std=c++11
INCLUDES = -I$(shell pwd)/gen

TARGET_PUB = pub
SRCS_PUB = pub_main.cpp KeyedMsgPublisher.cpp
OBJS_PUB = ${SRCS_PUB:.cpp=.o}

TARGET_SUB = sub
SRCS_SUB = sub_main.cpp KeyedMsgSubscriber.cpp
OBJS_SUB = ${SRCS_SUB:.cpp=.o}

LIBS = -lfastrtps -L$(shell pwd) -lKeyedMsg -lpthread

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
	rm -rf *.o $(TARGET_PUB) $(TARGET_SUB) *.so*
