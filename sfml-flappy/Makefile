build:
	g++ -w -std=c++17 -Wfatal-errors \
	./src/*.cpp \
	-o game \
	-I"./libs" \
	-L"./libs/lua" \
	-llua \
	-lsfml-graphics \
	-lsfml-audio \
	-lsfml-window \
	-lsfml-network \
	-lsfml-system;

clean:
	rm ./game;

run:
	./game;
