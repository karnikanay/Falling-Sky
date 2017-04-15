#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Tile.hpp"
#include "Grid.hpp"

class Game
{
private:

    sf::Image fsWindowIcon;

    sf::RenderWindow fsWindow;
    static constexpr float FS_WINDOW_WIDTH = Grid::GRID_NUM_COLS * Grid::GRID_CELL_WIDTH;
    static constexpr float FS_WINDOW_HEIGHT = Grid::GRID_NUM_ROWS * Grid::GRID_CELL_HEIGHT;

    Grid* fsGrid;
    Tile* fsCurrentTile;
    int fsCurrentTileColor;

    sf::Clock tileClock; // To keep track of time, so the tile moves down periodically
    int tileFallTime = 750;

public:

    Game();
    void start();

private:

    void processEvents();
    void update();
    void render();

    void handleKeyboard(sf::Keyboard::Key key, bool isPressed);
};
