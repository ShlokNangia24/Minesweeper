#pragma once
#include "Tile.h"
#include <fstream>

class GameState
{
public:
    enum PlayStatus{WIN, LOSS, PLAYING};
    GameState(Vector2i _dimensions = Vector2i(25,16), int _numMines  = 50);
    GameState(const char* filepath);
    int getFlagCount();
    int getMineCount();
    Tile* getTile(int x, int y);
    PlayStatus getPlayStatus();
    void setPlayStatus(PlayStatus status);
    std::array<Tile*, 8> setNeighbors(Tile tile);
    void flagInc(){flagCount++;};
    void flagDec(){flagCount--;};
private:
    int flagCount=0;
    int numMines;
    PlayStatus playStatus;
    Vector2i dimensions;
public:
    std::vector<Tile> m_tiles;
    Vector2i getDimensions(){return dimensions;}
};



