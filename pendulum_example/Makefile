CXXFLAGS += -std=c++11 -Wall $(sdl2-config --cflags)
LDFLAGS  += -lstdc++ -lm -lGL $(shell sdl2-config --libs)

OBJS = vec.o particle.o spring.o pendulum.o main.o
BIN = pendulum

all: $(BIN)

pendulum.o : pendulum.cc spring.hh particle.hh
spring.o : spring.cc spring.hh vec.hh
particle.o : particle.cc particle.hh vec.hh
vec.o : vec.cc vec.hh
main.o : main.cc vec.hh

$(BIN) : $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

.PHONY : all clean run

run : $(BIN)
	./$^

clean:
	rm -f $(OBJS) $(BIN)
