#pragma once
#include <iostream>
#include "Toolbox.h"
#include "minesweeper.h"



int main()
{
    return launch();
}
//launches an instance of the game
int launch()
{
    int numFlags = 0;
    int numBombsFlagged = 0;
    Toolbox &toolbox = Toolbox::getInstance();
    toolbox.gameState = new GameState();
    toolbox.window.create(VideoMode(800, 600), "P4 - Minesweeper, Shlok Nangia");
    while(toolbox.window.isOpen())
    {
        numBombsFlagged = 0;
        toolbox.window.clear(Color(255,255,255));
        for(auto tile: toolbox.gameState->m_tiles)
        {
            tile.draw();
            toolbox.window.draw(tile.sprite);
            if(tile.tempSprite.getTexture() != nullptr)
            {
                toolbox.window.draw(tile.tempSprite);
            }
            if(tile.isBomb)
            {
                if(tile.getState() == Tile::FLAGGED)
                {
                    numBombsFlagged++;
                }
            }
            if((numBombsFlagged == toolbox.gameState->getMineCount()) &&  (numBombsFlagged== toolbox.gameState->getFlagCount()))
                //if the number of flags on bombs, bombs, and the total flag count are equal then they play was able to flag all of the bombs
            {
                toolbox.newGameButton->setState(Smiley::WIN);
                toolbox.gameState->setPlayStatus(GameState::WIN);
            }

        }
        numFlags = toolbox.gameState->getMineCount() - toolbox.gameState->getFlagCount();
        Texture digits;
        digits.loadFromFile("images\\digits.png");
        if(numFlags >= 0)
        {
            std::string flags = std::to_string(numFlags);
            if(numFlags < 10)
            {
                flags = "0" + flags; //since the flags string only has one digit we need to add a 0 to the front of it so that the number is two digits
            }
            if(numFlags < 100)
            {
                int tens = flags.at(0) -48;
                int ones = flags[1] -48;
                Sprite digitOne;
                digitOne.setTexture(digits);
                digitOne.setTextureRect(IntRect(0,0,21,32));
                digitOne.setPosition(0,512);
                toolbox.window.draw(digitOne);
                Sprite digitTwo;
                digitTwo.setTexture(digits);
                digitTwo.setTextureRect(IntRect(21*(tens),0,21,32));
                digitTwo.setPosition(21,512);
                toolbox.window.draw(digitTwo);
                Sprite digitThree;
                digitThree.setTexture(digits);
                digitThree.setTextureRect(IntRect(21*(ones),0,21,32));
                digitThree.setPosition(42,512);
                toolbox.window.draw(digitThree);
            }
            else  //Pretty sure I can remove the if stamenet but it broke when I did so i'm not going to be doing that
            {
                int hundreds = flags.at(0) -48;
                int tens = flags.at(1) -48;
                int ones = flags.at(2) -48;
                Sprite digitOne;
                digitOne.setTexture(digits);
                digitOne.setTextureRect(IntRect(21*(hundreds),0,21,32));
                digitOne.setPosition(0,512);
                toolbox.window.draw(digitOne);
                Sprite digitTwo;
                digitTwo.setTexture(digits);
                digitTwo.setTextureRect(IntRect(21*(tens),0,21,32));
                digitTwo.setPosition(21,512);
                toolbox.window.draw(digitTwo);
                Sprite digitThree;
                digitThree.setTexture(digits);
                digitThree.setTextureRect(IntRect(21*(ones),0,21,32));
                digitThree.setPosition(42,512);
                toolbox.window.draw(digitThree);
            }
        }
        else
        {
            //makes the value positive, and displays the negative value on the board to make it look like a negative number
            int temp = numFlags * -1;
            std::string flags = std::to_string(temp);
            Sprite negative;
            negative.setTexture(digits);
            negative.setTextureRect(IntRect(21*10,0,21,32));
            negative.setPosition(0,512);
            toolbox.window.draw(negative);
            if(temp < 100)
            {
                flags = "0" + flags;
                if(temp<10)
                {
                    flags = "0" + flags;
                }
            }
            Sprite digitOne;
            digitOne.setTexture(digits);
            digitOne.setTextureRect(IntRect(21*(flags[0]-48),0,21,32));
            digitOne.setPosition(21,512);
            toolbox.window.draw(digitOne);
            Sprite digitTwo;
            digitTwo.setTexture(digits);
            digitTwo.setTextureRect(IntRect(21*(flags[1]-48),0,21,32));
            digitTwo.setPosition(42,512);
            toolbox.window.draw(digitTwo);
            Sprite digitThree;
            digitThree.setTexture(digits);
            digitThree.setTextureRect(IntRect(21*(flags[2]-48),0,21,32));
            digitThree.setPosition(63,512);
            toolbox.window.draw(digitThree);
        }
        toolbox.newGameButton->draw();
        toolbox.debugButton->setOnClick([&toolbox](){toggleDebugMode(toolbox);});
        toolbox.newGameButton->setOnClick([&toolbox](){ restart(toolbox);});
        toolbox.testButton1->setOnClick([&toolbox](){ testOne(toolbox);});
        toolbox.testButton2->setOnClick([&toolbox](){ testTwo(toolbox);});
        toolbox.window.draw(*(toolbox.debugButton->getSprite()));
        toolbox.window.draw(*(toolbox.newGameButton->returnSprite()));
        toolbox.window.draw(*(toolbox.testButton1->getSprite()));
        toolbox.window.draw(*(toolbox.testButton2->getSprite()));
        toolbox.window.display();
        Event event;
        while(toolbox.window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                toolbox.window.close();
            }
            render(toolbox, event);
        }

    }
    delete toolbox.gameState; //prevents memory leak from when you close the window
    return 1;

}
//restarts the game with 50 random bombs scattered across a 25x16 grid
void restart(Toolbox& toolbox)
{
    if(getDebugMode(toolbox))
    {
        toggleDebugMode(toolbox);
    }
    delete toolbox.gameState;
    toolbox.gameState = new GameState();
    toolbox.newGameButton->setState(Smiley::State::PLAYING);
}

// renders all UI elements of the board
void render(Toolbox& toolbox, Event event)
{
    if(event.type == Event::MouseButtonPressed)
    {

        Vector2i pos = Mouse::getPosition(toolbox.window);
        if(pos.y> 512) //when something is below 512 I know that the person is clicking on one of the buttons in the button class
        {
            int x = pos.x/64*64 +16;
            if(x == 528)
            {
                toolbox.debugButton->onClick();
            }
            else if(x == 400)
            {
                toolbox.newGameButton->onClick();
            }
            else if(x == 592)
            {
                toolbox.testButton1->onClick();
            }
            else if(x == 656)
            {
                toolbox.testButton2->onClick();
            }
        }
        if(event.mouseButton.button == Mouse::Left)
        {
            if(pos.y <512)
            {
                Tile *temp = toolbox.gameState->getTile((pos.x/32)*32, (pos.y/32)*32);
                if(temp != nullptr)
                {
                    temp->onClickLeft();
                    if(temp->isBomb && temp->getState() == Tile::EXPLODED)
                    {
                        toolbox.newGameButton->setState(Smiley::LOSE);
                        toolbox.gameState->setPlayStatus(GameState::LOSS);
                    }
                }
            }

        }
        else if(event.mouseButton.button == Mouse::Right)
        {
            Tile *temp = toolbox.gameState->getTile((pos.x/32)*32, (pos.y/32)*32);
            if(temp != nullptr)
            {
                temp->onClickRight();
                if(temp->getState() == Tile::State::FLAGGED)
                {
                    toolbox.gameState->flagInc();
                }
                else if(temp->getState() == Tile::State::HIDDEN)
                {
                    toolbox.gameState->flagDec();
                }
            }
        }
    }
}
//Reveals all the bombs
void toggleDebugMode(Toolbox& toolbox)
{
    if(getDebugMode(toolbox))
    {
        toolbox.debugMode = false;
        for(auto &tiles: toolbox.gameState->m_tiles)
        {
            if(tiles.isBomb)
            {
                tiles.setState(Tile::State::HIDDEN);
            }
        }
    }
    else
    {
        toolbox.debugMode = true;
        for(auto &tiles: toolbox.gameState->m_tiles)
        {
            if(tiles.isBomb)
            {
                tiles.setState(Tile::State::EXPLODED);
            }
        }
    }
}
//imports a test board from a text file
void testOne(Toolbox& toolbox)
{
    if(getDebugMode(toolbox))
    {
        toggleDebugMode(toolbox);
    }
    delete toolbox.gameState;
    toolbox.gameState = new GameState("boards\\testboard1.brd");
    toolbox.newGameButton->setState(Smiley::State::PLAYING);
    toolbox.gameState->setPlayStatus(GameState::PLAYING);
}
void testTwo(Toolbox& toolbox)
{
    if(getDebugMode(toolbox))
    {
        toggleDebugMode(toolbox);
    }
    delete toolbox.gameState;
    toolbox.gameState = new GameState("boards\\testboard2.brd");
    toolbox.newGameButton->setState(Smiley::State::PLAYING);
    toolbox.gameState->setPlayStatus(GameState::PLAYING);
}

