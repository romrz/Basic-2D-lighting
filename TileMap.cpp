#include "TileMap.h"

TileMap::TileMap(sf::Vector2i& size, sf::Vector2i& tileSize,
                 char* map, Tile* tileset) {
  mSize = size;
  mTileSize = tileSize;
  mMap = map;
  mTileset = tileset;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {

  states.transform *= getTransform();
  
  Tile* tile;
  for (int y = 0; y < mSize.y; y++)
    for (int x = 0; x < mSize.x; x++) {
      if(getTile(x, y) == 0) continue;
      tile = &mTileset[getTile(x, y) - 1];
      tile->setPosition(x * mTileSize.x, y * mTileSize.y);
      target.draw(*tile, states);
    }
}
