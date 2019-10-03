
#include <iostream>
#include <fstream>

#include "./map.h"
#include "./game.h"
#include "./components/tilecomponent.h"

Map::Map(AssetManager& assets, EntityManager& entities, int scale, int size) 
    : assets{assets}, entities{entities}, scale{scale}, tileSize{size} {
        this->texture = assets.getTexture("jungle-tiletexture");
}

void Map::loadMap(std::string filePath, int mapSizeX, int mapSizeY) {
    std::fstream mapFile;
    mapFile.open(filePath);

    for(int y = 0; y < mapSizeY; y++){
        for(int x = 0; x <mapSizeX; x++){
            char ch;
            mapFile.get(ch);
            int sourceRectY = atoi(&ch) * tileSize;
            mapFile.get(ch);
            int sourceRectX = atoi(&ch) * tileSize;
            this->addTile(sourceRectX, sourceRectY, x * scale * tileSize, y * scale * tileSize);
            mapFile.ignore();
        }
    }

    mapFile.close();
}

void Map::addTile(int sourceRectX, int sourceRectY, int x, int y){
    Entity& newTile{entities.addEntity("tile", LayerType::TileMap)};
    newTile.addComponent<TileComponent>(sourceRectX, sourceRectY, x, y, tileSize, scale, texture);
}