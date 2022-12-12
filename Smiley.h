#pragma
#include "Button.h"
//I created the Smiley class as a subset of the Button class to make it easier for me to change the smiley's sprite
class Smiley : public Button
{
public:
    enum State{WIN, LOSE, PLAYING};
    Texture winTexture;
    Texture loseTexture;
    Texture playingTexture;
    Sprite sprite;
    Smiley(Vector2f _position, std::function<void(void)> _onClick) : Button(_position, _onClick)
    {
        winTexture.loadFromFile("images\\face_win.png");
        loseTexture.loadFromFile("images\\face_lose.png");
        playingTexture.loadFromFile("images\\face_happy.png");
    };
    void draw()
    {
        sprite.setPosition(400,512);
        switch(state)
        {
            case WIN:
                sprite.setTexture(winTexture);
                break;
            case LOSE:
                sprite.setTexture(loseTexture);
                break;
            case PLAYING:
                sprite.setTexture(playingTexture);
                break;
        }
    }
    void setState(State _state)
    {
        state = _state;
    }
    Sprite* returnSprite()
    {
        return &sprite;
    }
private:
    State state = PLAYING;
};


