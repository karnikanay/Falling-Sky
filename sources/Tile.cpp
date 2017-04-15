#include "../headers/Tile.hpp"
#include <time.h>
#include <iostream>

void Tile::clearCells()
{
    for(int i = 0; i < 4; i++)
    {
        if(cellArray[i].y >= 0)
            parentGrid->setCell(cellArray[i].x, cellArray[i].y, Grid::Empty);
    }
}

void Tile::moveDown()
{
    // Empty the earlier cells first
    clearCells();

    // If all blocks can move down, then move the tile one step down
    bool shouldMoveDown = true;
    int i = 0;

    while(shouldMoveDown && (i < 4))
    {
        if((cellArray[i].y >= Grid::GRID_NUM_ROWS - 1) ||
           ((cellArray[i].y >= -1) && (parentGrid->getCell(cellArray[i].x, cellArray[i].y + 1) != Grid::Empty)))
            shouldMoveDown = false;
        i++;
    }

    if (shouldMoveDown)
    {
        for(int i = 0; i < 4; i++)
        {
            cellArray[i].y++;
        }
        tileCenter.y++;
    }
    else
    {
        update();
        tileState = tileStates::Fallen;
    }
}

Tile::tileStates Tile::getTileState()
{
    return tileState;
}

void Tile::initializePosition()
{
    switch(tileShape)
    {
    case tileShapes::Straight:
        cellArray[0].x = 3; cellArray[0].y = -1;
        cellArray[1].x = 3; cellArray[1].y = -2;
        cellArray[2].x = 3; cellArray[2].y = -3;
        cellArray[3].x = 3; cellArray[3].y = -4;
        tileCenter.x = 3;   tileCenter.y = -3;
        break;
    case tileShapes::ZigZag1:
        cellArray[0].x = 5; cellArray[0].y = -1;
        cellArray[1].x = 4; cellArray[1].y = -1;
        cellArray[2].x = 4; cellArray[2].y = -2;
        cellArray[3].x = 3; cellArray[3].y = -2;
        tileCenter.x = 4;   tileCenter.y = -2;
        break;
    case tileShapes::ZigZag2:
        cellArray[0].x = 4; cellArray[0].y = -1;
        cellArray[1].x = 3; cellArray[1].y = -1;
        cellArray[2].x = 5; cellArray[2].y = -2;
        cellArray[3].x = 4; cellArray[3].y = -2;
        tileCenter.x = 4;   tileCenter.y = -1;
        break;
    case tileShapes::L1:
        cellArray[0].x = 4; cellArray[0].y = -1;
        cellArray[1].x = 3; cellArray[1].y = -1;
        cellArray[2].x = 3; cellArray[2].y = -2;
        cellArray[3].x = 3; cellArray[3].y = -3;
        tileCenter.x = 3;   tileCenter.y = -2;
        break;
    case tileShapes::L2:
        cellArray[0].x = 4; cellArray[0].y = -1;
        cellArray[1].x = 3; cellArray[1].y = -1;
        cellArray[2].x = 4; cellArray[2].y = -2;
        cellArray[3].x = 4; cellArray[3].y = -3;
        tileCenter.x = 4;   tileCenter.y = -2;
        break;
    case tileShapes::T:
        cellArray[0].x = 4; cellArray[0].y = -1;
        cellArray[1].x = 5; cellArray[1].y = -2;
        cellArray[2].x = 4; cellArray[2].y = -2;
        cellArray[3].x = 3; cellArray[3].y = -2;
        tileCenter.x = 4;   tileCenter.y = -1;
        break;
    case tileShapes::Square:
        cellArray[0].x = 4; cellArray[0].y = -1;
        cellArray[1].x = 3; cellArray[1].y = -1;
        cellArray[2].x = 4; cellArray[2].y = -2;
        cellArray[3].x = 3; cellArray[3].y = -2;
        tileCenter.x = 3;   tileCenter.y = -2;
        break;
    default:
        break;
    }
}

void Tile::update()
{
    for(int i = 0; i < 4; i++)
    {
        if(cellArray[i].y >= 0)
        {
            parentGrid->setCell(cellArray[i].x, cellArray[i].y, tileContents);
        }
    }

    isInGrid = true;
    int i = 0;
    while(isInGrid && (i < 4))
    {
        if(cellArray[i].y < 0)
            isInGrid = false;
        i++;
    }
}

Tile::Tile(Grid* newParentGrid, int tileColor)
{
    /* Never ever forget this nonsense */
    parentGrid = newParentGrid;

    // Initialize random seed
    srand(time(NULL));
    srand(rand());

    // Set a random color and shape and set state as falling
    tileContents = (Grid::cellContents)tileColor;
    tileShape = rand() % 7;
    tileState = tileStates::Falling;

    // Initialize the position of the cells of the tile according to its shape
    initializePosition();

    // Rotate the tile from 0 to 3 times at random
    for(int i = 0; i < (rand() % 4); i++)
        rotate();

    // Move the tile a few random number of steps left or right
    if(rand() % 3 != 0)
    {
        for(int i = 0; i < (rand() % (Grid::GRID_NUM_COLS - 3)); i++)
            moveRight();
    } else
    {
        for(int i = 0; i < (rand() %  4); i++)
            moveLeft();
    }
}

void Tile::moveLeft()
{
    // Empty the earlier cells first
    clearCells();

    // If all blocks can move left, then move the tile one step left
    bool shouldMoveLeft = true;
    int i = 0;

    while(shouldMoveLeft && (i < 4))
    {
        if((cellArray[i].x == 0) ||
           ((parentGrid->getCell(cellArray[i].x - 1, cellArray[i].y) != Grid::Empty) && (cellArray[i].y >= 0)))
            shouldMoveLeft = false;
        i++;
    }
    if (shouldMoveLeft)
    {
        for(int i = 0; i < 4; i++)
        {
            cellArray[i].x--;
        }
        tileCenter.x--;
    }
}

void Tile::moveRight()
{
    // Empty the earlier cells first
    clearCells();

    // If all blocks can move right, then move the tile one step right
    bool shouldMoveRight = true;
    int i = 0;

    while(shouldMoveRight && (i < 4))
    {
        if((cellArray[i].x == Grid::GRID_NUM_COLS - 1) ||
           ((parentGrid->getCell(cellArray[i].x + 1, cellArray[i].y) != Grid::Empty) && (cellArray[i].y >= 1)))
            shouldMoveRight = false;
        i++;
    }
    if (shouldMoveRight)
    {
        for(int i = 0; i < 4; i++)
        {
            cellArray[i].x++;
        }
        tileCenter.x++;
    }
}

void Tile::rotate()
{
    clearCells();

    sf::Vector2i newCellArray[4];
    bool shouldRotate = true;

    for(int i = 0; i < 4; i++)
    {
        newCellArray[i].x = tileCenter.x + cellArray[i].y - tileCenter.y;
        newCellArray[i].y = tileCenter.y - cellArray[i].x + tileCenter.x;
    }

    int i = 0;
    while(shouldRotate && (i<4))
    {
        if((newCellArray[i].x < 0) ||
           (newCellArray[i].x > (Grid::GRID_NUM_COLS - 1)) ||
           (newCellArray[i].y > (Grid::GRID_NUM_ROWS - 1)))
        {
            shouldRotate = false;
        }
        else if(((parentGrid->getCell(newCellArray[i].x, newCellArray[i].y)) != Grid::Empty) &&
                (newCellArray[i].y > 0))
                    shouldRotate = false;
        i++;
    }

    if(shouldRotate)
    {
        for(int i = 0; i < 4; i++)
        {
            cellArray[i] = newCellArray[i];
        }
    }
}
