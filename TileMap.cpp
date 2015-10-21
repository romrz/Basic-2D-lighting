#include "TileMap.h"

TileMap::TileMap(sf::Vector2i& size,
                 sf::Vector2i& tileSize,
                 char* map,
                 Tile* tileset) {
  mSize = size;
  mTileSize = tileSize;
  mMap = map;
  mTileset = tileset;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  Tile* tile;
  for (int y = 0; y < mSize.y; y++)
    for (int x = 0; x < mSize.x; x++) {
      tile = &mTileset[getTile(x, y)];
      tile->setPosition(x * mTileSize.x, y * mTileSize.y);
      target.draw(*tile, getTransform());
    }
}
