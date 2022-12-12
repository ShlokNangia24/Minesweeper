#include "Button.h"

//sets the button's position
Button::Button(Vector2f _position, std::function<void(void)> _onClick)
{
    position = _position;
    this->_onClick = _onClick;

}

//returns the button's position
Vector2f Button::getPosition()
{
    return position;
}

//sets the button's sprite
void Button::setSprite(Sprite *sprite)
{
    sprite->setPosition(position);
    this->sprite = sprite;
}

//returns the button's sprite
Sprite* Button::getSprite()
{
    return sprite;
}

void Button::onClick()
{
    _onClick();
}
