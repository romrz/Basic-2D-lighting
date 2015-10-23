#include <iostream>
#include <SFML/Graphics.hpp>
#include "TileMap.h"

void processInput(sf::RenderWindow& window);

bool running = true;

int main() {
  sf::Vector2i mapSize(15, 10);
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
  
  char map[mapSize.y][mapSize.x] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
  };
  
  TileMap tileMap(mapSize, tileSize, &map[0][0], &tileset[0]);
  tileMap.scale(4, 4);

  sf::Shader shader;
  if (!shader.loadFromFile("shader.vert", "shader.frag")) {
    std::cout << "Unable to load the shaders" << std::endl;
    return 0;
  }

  sf::RenderWindow window(sf::VideoMode(800, 4*tileSize.y*mapSize.y), "Basic 2D Lighting");

  float time = 0;
  shader.setParameter("time", time);
  shader.setParameter("texture", sf::Shader::CurrentTexture);
  
  sf::Event event;
  while(running) {
    processInput(window);

    shader.setParameter("time", time);

    sf::Vector2i pos = sf::Mouse::getPosition(window);
    float x = pos.x;
    
    time += 0.01;
    
    window.clear(sf::Color(12, 13, 69));
    window.draw(tileMap, &shader);
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
