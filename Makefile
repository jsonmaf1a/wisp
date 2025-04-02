CXX = g++
SRC = $(wildcard src/*.cpp)
CXXFLAGS = -std=c++23 -MMD -MP -Iinclude
LDFLAGS = -lpthread -lsfml-graphics -lsfml-system

OBJ = $(SRC:src/%.cpp=lib/%.o)
LIB = lib/wisp.a
DEPS = $(OBJ:.o=.d)

.PHONY: all clean lib

all: $(LIB)

$(LIB): $(OBJ) | build
	ar rcs $(LIB) $(OBJ)

lib/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p lib

clean:
	$(RM) -vr lib $(LIB)

-include $(DEPS)
