#include "../headers/Grid.hpp"
#include <iostream>
Grid::Grid(sf::RenderWindow* newParentWindow, sf::Vector2f newGridLocation)
{
    // Load the textures
    loadTextures();

    // Set all cells empty
    for(int i = 0; i < GRID_NUM_COLS; i++)
    {
        for(int j = 0; j < GRID_NUM_ROWS; j++)
        {
            setCell(i, j, cellContents::Empty);
        }
    }

    // Set grid's parent window and location
    parentWindow = newParentWindow;
    gridLocation = newGridLocation;

    // Set the sprite positions
    for(int i = 0; i < GRID_NUM_COLS; i++)
    {
        for(int j = 0; j < GRID_NUM_ROWS; j++)
        {
            spriteArray[i][j].setPosition(gridLocation.x + GRID_CELL_WIDTH*i, gridLocation.y + GRID_CELL_HEIGHT*j);
        }
    }

}

void Grid::clear()
{
    for(int i = 0; i < GRID_NUM_COLS; i++)
    {
        for(int j = 0; j < GRID_NUM_ROWS; j++)
        {
            cellArray[i][j] = cellContents::Empty;
        }
    }
}

void Grid::setCell(int cellCol, int cellRow, cellContents newCellContents)
{
    cellArray[cellCol][cellRow] = newCellContents;
}

Grid::cellContents Grid::getCell(int cellCol, int cellRow)
{
    return cellArray[cellCol][cellRow];
}

void Grid::update()
{
    // Update sprite textures according to the cell array
    for(int i = 0; i < GRID_NUM_COLS; i++)
    {
        for(int j = 0; j < GRID_NUM_ROWS; j++)
        {
            switch(cellArray[i][j])
            {
            case cellContents::Blue:
                spriteArray[i][j].setTexture(cellTextureBlue);
                break;
            case cellContents::Green:
                spriteArray[i][j].setTexture(cellTextureGreen);
                break;
            case cellContents::Orange:
                spriteArray[i][j].setTexture(cellTextureOrange);
                break;
            case cellContents::Red:
                spriteArray[i][j].setTexture(cellTextureRed);
                break;
            case cellContents::Yellow:
                spriteArray[i][j].setTexture(cellTextureYellow);
                break;
            default:
                //spriteArray[i][j].setColor(sf::Color(0, 0, 0, 0));
                break;
            }
        }
    }
}

void Grid::deleteRow(int rowNum)
{
    for(int i = 0; i < GRID_NUM_COLS; i++)
    {
        for(int j = rowNum; j > 0; j--)
        {
            setCell(i, j, getCell(i, j-1));
        }
    }

    for(int i = 0; i < GRID_NUM_COLS; i++)
    {
        setCell(i, 0, cellContents::Empty);
    }
}

void Grid::draw()
{
    for(int i = 0; i < GRID_NUM_COLS; i++)
    {
        for(int j = 0; j < GRID_NUM_ROWS; j++)
        {
            if(getCell(i, j) != Grid::Empty)
                parentWindow->draw(spriteArray[i][j]);
        }
    }
}

void Grid::loadTextures()
{
    cellTextureBlue.loadFromFile("resources/block_blue.png");
    cellTextureGreen.loadFromFile("resources/block_green.png");
    cellTextureOrange.loadFromFile("resources/block_orange.png");
    cellTextureRed.loadFromFile("resources/block_red.png");
    cellTextureYellow.loadFromFile("resources/block_yellow.png");
}
