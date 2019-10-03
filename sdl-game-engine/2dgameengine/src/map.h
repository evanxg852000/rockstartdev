#ifndef MAP_H
#define MAP_H

#include <string>

#include <SDL2/SDL.h>

#include "./assetmanager.h"
#include "./entitymanager.h"

class Map {
public:
    Map(AssetManager& assets, EntityManager& entities, int scale, int size);
    virtual ~Map() = default;
    void loadMap(std::string filePath, int mapSizeX, int mapSizeY);
    void addTile(int sourceRectX, int sourceRectY, int x, int y);

private:
    AssetManager& assets;
    EntityManager& entities;
    SDL_Texture* texture;
    int scale;
    int tileSize;
};

#endif