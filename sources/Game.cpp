#include "../headers/Game.hpp"
#include <time.h>
#include <iostream>

Game::Game()
{
    // Create the game window
    fsWindowIcon.loadFromFile("resources/icon.png");
    fsWindow.create(sf::VideoMode(FS_WINDOW_WIDTH, FS_WINDOW_HEIGHT), "Falling Sky");
    fsWindow.setIcon(fsWindowIcon.getSize().x, fsWindowIcon.getSize().y, fsWindowIcon.getPixelsPtr());

    // Create the grid in fsWindow at (0,0)
    fsGrid = new Grid(&fsWindow, sf::Vector2f(0.f, 0.f));

    // Create the first tile in the fsGrid with a random color
    srand(time(NULL));
    srand(rand());
    fsCurrentTileColor = (rand() % 5) + 1;
    fsCurrentTile = new Tile(fsGrid, fsCurrentTileColor);

    // Start the clock to move the tile down periodically
    tileClock.restart();
}

void Game::start()
{
    while(fsWindow.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while(fsWindow.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            fsWindow.close();
            break;
        case sf::Event::KeyPressed:
            handleKeyboard(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handleKeyboard(event.key.code, false);
            break;
        default:
            break;
        }
    }
}

void Game::handleKeyboard(sf::Keyboard::Key key, bool isPressed)
{
    switch(key)
    {
    case sf::Keyboard::Left:
        if(isPressed)
            fsCurrentTile->moveLeft();
        break;
    case sf::Keyboard::Right:
        if(isPressed)
            fsCurrentTile->moveRight();
        break;
    case sf::Keyboard::Up:
        if(isPressed)
            fsCurrentTile->rotate();
        break;
    case sf::Keyboard::Down:
        if(isPressed)
            tileFallTime = 175;
        else
            tileFallTime = 750;
        break;
    case sf::Keyboard::Space:
        if(isPressed)
        {
            while(fsCurrentTile->getTileState() == Tile::Falling)
                fsCurrentTile->moveDown();
        }
    default:
        break;
    }
}

void Game::update()
{
    if(fsCurrentTile->getTileState() == Tile::tileStates::Fallen)
    {
        for(int i = 0; i < Grid::GRID_NUM_ROWS; i++)
        {
            bool isRowComplete = true;
            int j = 0;

            while(isRowComplete && (j < Grid::GRID_NUM_COLS))
            {
                if(fsGrid->getCell(j, i) == Grid::Empty)
                    isRowComplete = false;
                j++;
            }

            if(isRowComplete)
            {
                fsGrid->deleteRow(i);
                fsCurrentTile->moveDown();
            }
        }

        if(!fsCurrentTile->isInGrid)
        {
            fsGrid->clear();
        }

        // Delete the fallen tile
        delete fsCurrentTile;
        fsCurrentTile = nullptr;

        // Create a delay
        tileClock.restart();
        while(tileClock.getElapsedTime().asMilliseconds() <= 400)
        {

        }
        tileClock.restart();

        // Create a new tile
        fsCurrentTileColor++;
        fsCurrentTileColor %= 5;
        fsCurrentTileColor++;
        fsCurrentTile = new Tile(fsGrid, fsCurrentTileColor);
    }

    if(tileClock.getElapsedTime().asMilliseconds() >= tileFallTime)
    {
        fsCurrentTile->moveDown();
        tileClock.restart();
    }

    fsCurrentTile->update();
    fsGrid->update();
}

void Game::render()
{
    // Clear the game window
    fsWindow.clear(sf::Color(0, 0, 0)); // Set the background color to almost white

    // Draw the grid to the window
    fsGrid->draw();

    // Display the window
    fsWindow.display();
}
