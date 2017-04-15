#ifndef __GRID__
#define __GRID__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Grid
{
public:

    enum cellContents {Empty, Yellow, Green, Blue, Red, Orange};

    static const int GRID_NUM_COLS = 10;
    static const int GRID_NUM_ROWS = 20;

    static constexpr float GRID_CELL_WIDTH = 24.f;
    static constexpr float GRID_CELL_HEIGHT = 24.f;

private:

    sf::Texture cellTextureYellow;
    sf::Texture cellTextureGreen;
    sf::Texture cellTextureBlue;
    sf::Texture cellTextureRed;
    sf::Texture cellTextureOrange;

    cellContents cellArray[GRID_NUM_COLS][GRID_NUM_ROWS];
    sf::Sprite spriteArray[GRID_NUM_COLS][GRID_NUM_ROWS];

    sf::RenderWindow* parentWindow;
    sf::Vector2f gridLocation;

public:

    Grid(sf::RenderWindow* newParentWindow, sf::Vector2f newGridLocation);

    void setCell(int cellCol, int cellRow, cellContents newCellContents);
    cellContents getCell(int cellCol, int cellRow);

    void deleteRow(int rowNum);

    void clear();
    void update();
    void draw();

private:

    void loadTextures();
};
#endif // __GRID__
