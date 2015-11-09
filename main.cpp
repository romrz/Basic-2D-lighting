#include <iostream>
#include <SFML/Graphics.hpp>
#include "TileMap.h"

void processInput(sf::RenderWindow& window);

bool running = true;

int main() {
  sf::Vector2i mapSize(15, 10);
  sf::Vector2i tileSize(16, 16);

  // Loads the textures
  sf::Texture torchTexture;
  if (!torchTexture.loadFromFile("torch.png")) {
    std::cout << "Unable to load the texture" << std::endl;
    return 0;
  }
  sf::Texture texture;
  if (!texture.loadFromFile("tileset.png")) {
    std::cout << "Unable to load the texture" << std::endl;
    return 0;
  }

  // Creates the torch sprite
  sf::Sprite torch(torchTexture, sf::IntRect(0, 0, 32, 48));
  torch.scale(4,4);

  // Creates the tileset for the tile map
  Tile tileset[3] = {
    Tile(texture, sf::IntRect(0, 0, tileSize.y, tileSize.x)),
    Tile(texture, sf::IntRect(tileSize.x, 0, tileSize.y, tileSize.x)),
    Tile(texture, sf::IntRect(2 * tileSize.x, 0, tileSize.y, tileSize.x))
  };

  // Sets the map array
  char map[mapSize.y][mapSize.x] = {
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
  };

  // Creates the tilemap
  TileMap tileMap(mapSize, tileSize, &map[0][0], &tileset[0]);
  tileMap.scale(4, 4);

  sf::Shader shader;
  if (!shader.loadFromFile("vert_shader.vert", "frag_shader.frag")) {
    std::cout << "Unable to load the shaders" << std::endl;
    return 0;
  }

  sf::RenderWindow window(sf::VideoMode(800, 640), "Basic 2D Lighting");
  window.setVerticalSyncEnabled(true);

  shader.setParameter("texture", sf::Shader::CurrentTexture);
  shader.setParameter("resolution", window.getSize().x, window.getSize().y);
  shader.setParameter("ambientData", 0.3, 0.3, 0.8, 0.3);
  shader.setParameter("lightData", 1.0, 0.8, 0.2, 2);
  shader.setParameter("lightSize", 0.3, 0);

  // Variables for torch animation
  float animTime = 0;
  int frame = 0;

  sf::Clock clock;
  sf::Time frameTime, time;
  sf::Event event;
  while(running) {
    frameTime = clock.restart();
    time += frameTime;
    
    processInput(window);

    sf::Vector2i pos = sf::Mouse::getPosition(window);
    torch.setPosition(pos.x - 64, pos.y - 96);

    // Animates
    if(animTime >= 150) {
      frame++;
      if(frame == 3) frame = 0;
      torch.setTextureRect(sf::IntRect(frame*32, 0, 32, 48));
      animTime = 0;
    }
    animTime += frameTime.asMilliseconds();

    shader.setParameter("mouse", pos.x, 640 - pos.y);
    shader.setParameter("time", 10 * time.asSeconds(), 0);
    
    window.clear(sf::Color(12, 13, 69));
    window.draw(tileMap, &shader);
    window.draw(torch);
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
