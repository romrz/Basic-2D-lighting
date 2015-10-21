#include <iostream>
#include <SFML/Graphics.hpp>
#include "TileMap.h"

void processInput(sf::RenderWindow& window);

bool running = true;

int main() {
  sf::Vector2i mapSize(10, 10);
  sf::Vector2i tileSize(16, 16);
  
  sf::Texture texture;
  if (!texture.loadFromFile("tileset.png")) {
    std::cout << "Unable to load the texture" << std::endl;
    return 0;
  }

  Tile tileset[3] = {
    Tile(texture, sf::IntRect(0, 0, tileSize.y, tileSize.x)),
    Tile(texture, sf::IntRect(tileSize.x, 0, tileSize.y, tileSize.x)),
    Tile(texture, sf::IntRect(2 * tileSize.x, 0, tileSize.y, tileSize.x))
  };
  
  char map[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
  };
  
  TileMap tileMap(mapSize, tileSize, &map[0][0], &tileset[0]);
  tileMap.scale(4, 4);
  
  sf::RenderWindow window(sf::VideoMode(4*tileSize.x*mapSize.x, 4*tileSize.y*mapSize.y), "Basic 2D Lighting");
  
  sf::Event event;
  while(running) {
    processInput(window);

    window.draw(tileMap);
    window.display();    
  }

  return 0;
}

void processInput(sf::RenderWindow& window) {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      running = false;
    }
  }
}
