CC := gcc
CXX := g++
CXX_FLAGS := -w -std=c++17 -Wfatal-errors
SRC_FILES := $(filter-out src/main.cpp, $(wildcard src/*.cpp))
INCLUDES := -I"./libs"
LIBS := #-lsfml-system -lsfml-network #-lpthread

build:
	$(CXX) $(CXX_FLAGS) $(SRC_FILES) ./src/main.cpp \
	-o app.bin $(INCLUDES) $(LIBS);

test:
	$(CXX) $(CXX_FLAGS) $(SRC_FILES) ./tests/*.cpp \
	-o test.bin $(INCLUDES) $(LIBS) && ./test.bin;

clean:
	rm ./app.bin ./test.bin;

run:
	./app.bin;

.PHONY: all test clean run
