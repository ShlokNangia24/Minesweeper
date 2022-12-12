#pragma once
#include "Tile.h"
//sets the neihbors of a tile given an array of them
void Tile::setNeighbors(std::array<Tile *, 8> neighbors)
{
    for(auto neighbor: neighbors)
    {
        if(neighbor != nullptr)
        {
            if (neighbor->isBomb)
            {
                numBombs++;
            }
        }
    }
    this->neighbors = neighbors;
};

std::array<Tile *, 8> &Tile::getNeighbors()
{
    return neighbors;
}

//reveals the tile, and neigbors depending on the number of bombs near i
void Tile::onClickLeft()
{
    if (m_state == Tile::HIDDEN)
    {
        m_state = REVEALED;
        if (isBomb)
        {
            m_state = EXPLODED;
        }
        else
        {
            if(numBombs == 0)
            {
                revealNeighbors();
            }
        }
    }
}
//reveals all neighbors of the tile
void Tile::revealNeighbors()
{
    for(auto neighbor : neighbors)
    {
        if(neighbor != nullptr && neighbor->m_state == Tile::HIDDEN && !neighbor->isBomb && numBombs ==0)
        {
            neighbor->m_state = REVEALED;
            if(neighbor->numBombs == 0)
            {
                neighbor->revealNeighbors();
            }
        }
        else if(numBombs > 0)
        {
            neighbor->m_state = REVEALED;
        }
    }
}

//when the user uses right click the tile will be flagged or unflagged
void Tile::onClickRight()
{
    if (m_state == Tile::HIDDEN)
    {
        m_state = FLAGGED;
    }
    else if (m_state == Tile::FLAGGED)
    {
        m_state = HIDDEN;
    }

}

//renders the tile on the screen based on its state
void Tile::draw()
{
    switch (m_state)
    {
        case Tile::HIDDEN:
            texture.loadFromFile("images\\tile_hidden.png");
            sprite.setTexture(texture);
            sprite.setPosition(position.x, position.y);
            break;
        case Tile::REVEALED:
            texture.loadFromFile("images\\tile_revealed.png");
            sprite.setTexture(texture);
            sprite.setPosition(position.x, position.y);
            if(numBombs != 0)
            {
                tempTexture.loadFromFile("images\\number_" + std::to_string(numBombs) + ".png");
                tempSprite.setTexture(tempTexture);
                tempSprite.setPosition(position.x, position.y);
            }
            break;
        case Tile::FLAGGED:
            texture.loadFromFile("images\\tile_revealed.png");
            sprite.setTexture(texture);
            sprite.setPosition(position.x, position.y);
            tempTexture.loadFromFile("images\\flag.png");
            tempSprite.setTexture(tempTexture);
            tempSprite.setPosition(position.x, position.y);
            break;
        case Tile::EXPLODED:
            texture.loadFromFile("images\\tile_revealed.png");
            sprite.setTexture(texture);
            sprite.setPosition(position.x, position.y);
            tempTexture.loadFromFile("images\\mine.png");
            tempSprite.setTexture(tempTexture);
            tempSprite.setPosition(position.x, position.y);
            break;
    }

}

Tile::Tile(Vector2f _position)
{
    position = _position;
}

