#pragma once
#include "Sfml/graphics.hpp"
#include "Button.h"


class Tile
{
    int flags = 0; //counts number of flags that are on the screen
    std::array <Tile *, 8> neighbors;
    Vector2f position;
public:
    int numBombs = 0;
    bool isBomb =false;
    enum State{REVEALED,HIDDEN,FLAGGED, EXPLODED};
    Tile(Vector2f _position);
    Vector2f getLocation(){return position;};
    std::array<Tile*,8>& getNeighbors();
    void setNeighbors(std::array<Tile*,8> neighbors);
    void onClickLeft();
    void onClickRight();
    void draw();
    Sprite sprite;
    Texture texture;
    Sprite tempSprite;
    Texture tempTexture;
    //use to compare the positions of two given tiles nesciary to find a tile when only the position is given
    bool operator==(const Tile& other) const
    {
        return position == other.position;
    };
    void setState(State state){m_state = state;};
    State getState(){return m_state;};
protected:
    void revealNeighbors();
private:
    State m_state = HIDDEN;
};