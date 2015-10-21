#include <SFML/Graphics.hpp>

// A Tile is just a Sprite
typedef sf::Sprite Tile;

class TileMap : public sf::Drawable, public sf::Transformable {
 public:
  TileMap(sf::Vector2i& size, sf::Vector2i& tileSize, char* map, Tile* tileset);
  ~TileMap() {}

  sf::Vector2i getSize() { return mSize; }
  sf::Vector2i getTileSize() { return mTileSize; }
  void setTile(char t, int x, int y) { mMap[y * mSize.x + x] = t; }
  char getTile(int x, int y) const { return mMap[y * mSize.x + x]; }

 protected:
  sf::Vector2i mSize;
  sf::Vector2i mTileSize;
  char* mMap = nullptr;
  Tile* mTileset = nullptr;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
