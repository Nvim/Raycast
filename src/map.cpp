#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>
#include "../include/RenderWindow.hpp"
#include "../include/Map.hpp"

int xyToIndex(int lines, int cols)
{
    return 8*lines + cols;
}

Map::Map(RenderWindow *p_win, s_Color *p_color, uint8_t p_wallsize)
{
    window = p_win;
    color = p_color;
    wallsize = p_wallsize;
}


void Map::drawMap()
{
    SDL_Rect rect;
    rect.h = wallsize;
    rect.w = wallsize;

    for (int lines = 0; lines< mapLines; lines++)
    {
        for ( int cols = 0; cols<mapCols; cols++)
        {
            if (map[xyToIndex(lines, cols)] == 1)
            {
                rect.x = INIT_X + wallsize*cols; //25*mapCols en gros
                rect.y = INIT_Y + wallsize*lines; //25*mapLines

                window->renderRectangle(&rect, color);
            }
        }
    }
}
