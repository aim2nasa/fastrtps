CXX = g++
CXXFLAGS = -fPIC -g -O2 -Wall -Wextra -std=c++11

LIBNAME = libKeyedMsg
TARGET = $(LIBNAME).so.1
SRCS = KeyedMsg.cxx KeyedMsgPubSubTypes.cxx
OBJS = ${SRCS:.cxx=.o}

all : $(TARGET)
	@echo $@:$(TARGET)...

$(TARGET) : $(OBJS)
	@echo $@:$(OBJS)...
	$(CXX) -shared -Wl,-soname,$@ -o $@ $(OBJS) $(LIBS)
	@echo $*
	ln -s $@ $(LIBNAME).so
	@mv $(LIBNAME).* ..

%.o: %.cxx
	@echo $@:$^...
	$(CXX) -c $< $(INCLUDES) $(CXXFLAGS)

clean:
	@echo $@...
	rm -rf *.o $(TARGET) *.so
