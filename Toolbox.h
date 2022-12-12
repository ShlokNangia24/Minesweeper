#pragma once
#include"GameState.h"
#include "Smiley.h"

class Toolbox
{
    Toolbox();
    Texture debugTexture;  //kept getting internal OpenGL calls failing when I used a vector/map so to prevent that I just made sepereate textures and sprites for each of them
    Sprite debugSprite;
    Texture newGameTexture;
    Sprite newGameSprite;
    Texture testOneTexture;
    Sprite testOneSprite;
    Texture testTwoTexture;
    Sprite testTwoSprite;
public:
    static Toolbox& getInstance()
    {
        //return instance of the toolbox singleton
        static Toolbox instance;
        return instance;
    };
    GameState* gameState;
    sf::RenderWindow window;
    Button* debugButton;
    Smiley* newGameButton;
    Button* testButton1;
    Button* testButton2;
    bool debugMode = false;

};
Toolbox::Toolbox()
{
    debugButton = new Button(Vector2f(528,512), [](){});
    Sprite tempSprite;
    Texture temp;
    debugTexture.loadFromFile("images\\debug.png");
    debugSprite.setTexture(debugTexture);
    debugButton->setSprite(&debugSprite);
    newGameButton = new Smiley(Vector2f(400,512), [](){});
    testButton1 = new Button(Vector2f(592,512), [](){});
    testOneTexture.loadFromFile("images\\test_1.png");
    testOneSprite.setTexture(testOneTexture);
    testButton1->setSprite(&testOneSprite);
    testButton2 = new Button(Vector2f(656,512), [](){});
    testTwoTexture.loadFromFile("images\\test_2.png");
    testTwoSprite.setTexture(testTwoTexture);
    testButton2->setSprite(&testTwoSprite);
}