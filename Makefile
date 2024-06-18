CXX = clang++

CXXFLAGS = -std=c++20 -stdlib=libc++ -g \
		-Wall -Wextra -Wpedantic \
		-Wno-unused-parameter -Wno-unused-variable \
		-Wno-deprecated-volatile -Wno-unused-function \
		-I/usr/local/include/glad \
		-I/usr/local/include/glm \
		$(shell pkg-config --cflags assimp glfw3 spdlog)

LDFLAGS = -g -framework OpenGL -framework IOKit \
		  -framework CoreVideo -framework Cocoa \
		  -L/usr/local/lib -lglad \
		  $(shell pkg-config --libs assimp glfw3 spdlog)


GAME_OUT = ./a.out
CXX_SRC = $(wildcard src/*.cpp)
CXX_OBJ = $(CXX_SRC:.cpp=.o)

.PHONY: all clean

all: $(GAME_OUT)

$(GAME_OUT): $(CXX_OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(CXX_OBJ) $(GAME_OUT)

run: all
	$(GAME_OUT)
