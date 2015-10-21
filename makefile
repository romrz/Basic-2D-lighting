build: main.cpp TileMap.cpp TileMap.h
	g++ -std=c++11 main.cpp TileMap.cpp -o main.exe -IC:/SFML_MGW/include -LC:/SFML_MGW/lib -lsfml-graphics -lsfml-window -lsfml-system
