#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Grid.hpp"

class Tile
{
public:

    enum tileStates {Falling, Fallen};
    bool isInGrid = false;

private:

    enum tileShapes {Straight, ZigZag1, ZigZag2, L1, L2, T, Square};
    tileStates tileState;
    int tileShape;
    Grid::cellContents tileContents;

    Grid* parentGrid;
    sf::Vector2i cellArray[4]; // This vector array stores the x & y locations of the 4 cells of the in the grid
    sf::Vector2i tileCenter; // This is the location of the center-most cell of the tile. This cell may be empty.

public:

    Tile(Grid* newParentGrid, int tileColor);

    void moveLeft();
    void moveRight();
    void moveDown();
    void rotate();
    tileStates getTileState();

    void update();

private:

    void initializePosition();
    void clearCells();
};
