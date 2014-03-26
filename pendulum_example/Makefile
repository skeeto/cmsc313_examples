CXXFLAGS += -std=c++11 -Wall $(sdl2-config --cflags)
LDFLAGS  += -lstdc++ -lm -lGL $(shell sdl2-config --libs)
FORMAT = clang-format-3.5

OBJS = vec.o particle.o spring.o pendulum.o graphics.o program.o
BIN = pendulum

all: $(BIN)

graphics.o : graphics.cc graphics.hh
pendulum.o : pendulum.cc spring.hh particle.hh
spring.o : spring.cc spring.hh vec.hh
particle.o : particle.cc particle.hh vec.hh
vec.o : vec.cc vec.hh
program.o : program.cc pendulum.hh

$(BIN) : $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

.PHONY : all clean run format

run : $(BIN)
	./$^

format :
	$(FORMAT) -style=google -i *.cc *.hh

clean:
	rm -f $(OBJS) $(BIN)
