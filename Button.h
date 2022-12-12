#pragma once
#include"SFML/Graphics.hpp"

using namespace sf;

class Button
{
    Vector2f position;
    std::function<void(void)> _onClick;
    Sprite* sprite;;
protected:
    ~Button(){delete sprite;}

public:
    Button(Vector2f _position, std::function<void(void)> _onClick);
    Vector2f getPosition();
    Sprite* getSprite();
    void onClick();
    void setSprite(Sprite* _sprite);
    void setOnClick(std::function<void(void)> _onClick){this->_onClick = _onClick;};
};



