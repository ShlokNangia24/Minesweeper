#pragma once
#include "iostream"
#include "GameState.h"
#include <random>

//Generates a given amount of bombs on a plane of given size
GameState::GameState(Vector2i _dimensions, int _numMines)
{
    dimensions = _dimensions;
    numMines = _numMines;
    std::vector<std::string> locations;
    std::string location;
    for(int i = 0; i < dimensions.y; i++)
    {
        for(int j = 0; j < dimensions.x; j++)
        {
            location+= "0";
        }
        locations.push_back(location);
        location = "";
    }
    for(int i = 0; i < numMines; i++)
    {
        int x = rand() % dimensions.x;
        int y = rand() % dimensions.y;
        if(locations[y][x] == '0')
        {
            locations[y][x] = '1';
        }
        else
        {
            i--;
        }
    }
    for(float i = 0; i < dimensions.y; i++)
    {
        for(float j = 0; j < dimensions.x; j++)
        {
            Tile tempTile = Tile(Vector2f(j*32,i*32));
            if(locations[i][j] == '1')
            {
                tempTile.isBomb = true;
                m_tiles.emplace_back(tempTile);
            }
            else
            {
                m_tiles.emplace_back(tempTile);
            }
        }
    }
    for(auto &tile: m_tiles)
    {
        tile.setNeighbors(setNeighbors(tile));
    }
}
//Randomly generates a board given an imported board
GameState::GameState(const char *filepath)
{
    int x;
    int y;
    std::vector<std::string> locations;
    std::ifstream inStream(filepath);
    if(inStream.is_open())
    {
         //counts the number of values on the line returning the x dimension
        while(!inStream.eof())
        {
            std::string line;
            std::getline(inStream, line);
            locations.push_back(line);
        }
        x=locations[0].length();
        y = locations.size();
        if(y> 16)
        {
            y=16;
        }
    }
    else
    {
        std::cerr << "Error opening file" << std::endl;
    }
    dimensions = Vector2i(x, y);
    numMines = 0;
    for(auto location: locations)
    {
        int temp = std::count(location.begin(), location.end(), '1');
        numMines += temp;
    }
    for(float i = 0; i < dimensions.y; i++)
    {
        for(float j = 0; j < dimensions.x; j++)
        {
            Tile tempTile = Tile(Vector2f(j*32,i*32));
            if(locations[i][j] == '1')
            {
                tempTile.isBomb = true;
                m_tiles.emplace_back(tempTile);
            }
            else
            {
                m_tiles.emplace_back(tempTile);
            }
        }
    }
    for(auto &tile: m_tiles)
    {
        tile.setNeighbors(setNeighbors(tile));
    }
}

int GameState::getFlagCount()
{
    return flagCount;
}

int GameState::getMineCount()
{
    return numMines;
}

GameState::PlayStatus GameState::getPlayStatus()
{
    return playStatus;
}

void GameState::setPlayStatus(GameState::PlayStatus status)
{
    playStatus = status;

}
//gets the tile at the given position
Tile *GameState::getTile(int x, int y)
{
    Tile *result = nullptr;
    Vector2f tempPosition = Vector2f(x, y);
    Tile temp = Tile(tempPosition);
    for(auto &tile: m_tiles)
    {
        if(tile == temp)
        {
            result = &tile;
            return result;
        }
    }
    return nullptr;
}
//sets the neighbors around a tile
std::array<Tile*, 8> GameState::setNeighbors(Tile tile)
{
    //since the tiles are all 32 by 32 I can use the get location function and edit the position values to get the neighbors
    std::array<Tile*, 8> neighbors;
   neighbors[0] = getTile(tile.getLocation().x - 32, tile.getLocation().y - 32);
   neighbors[1] = getTile(tile.getLocation().x, tile.getLocation().y - 32);
   neighbors[2] = getTile(tile.getLocation().x + 32, tile.getLocation().y - 32);
   neighbors[3] = getTile(tile.getLocation().x - 32, tile.getLocation().y);
   neighbors[4] = getTile(tile.getLocation().x + 32, tile.getLocation().y);
   neighbors[5] = getTile(tile.getLocation().x - 32, tile.getLocation().y + 32);
   neighbors[6] = getTile(tile.getLocation().x, tile.getLocation().y +32);
   neighbors[7] = getTile(tile.getLocation().x + 32, tile.getLocation().y + 32);
   return neighbors;
}
