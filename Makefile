SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:src/%.cpp=build/%.o)
LD = g++
CXX = g++
CXXFLAGS = -std=c++23
OUT = bin/chuzzle

build/%.o: src/%.cpp
	$(shell echo 1>&2 -e "Compiling \e[1m\e[32m$<\e[0m")

	@$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: chuzzle
chuzzle: $(OUT)
$(OUT): $(OBJS)
	@$(LD) $(LDFLAGS) $(OBJS) -o $(OUT)

.PHONY: clean
clean:
	@rm -rf build/
	@rm -rf bin/
	@mkdir build/
	@mkdir bin/
