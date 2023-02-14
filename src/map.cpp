#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>
#include "../include/RenderWindow.hpp"
#include "../include/Map.hpp"

Map::Map(RenderWindow *p_win, s_Color *p_color, uint8_t p_wallsize)
{
    window = p_win;
    color = p_color;
    wallsize = p_wallsize;
}

void Map::drawMap()
{
    int i, j;

    SDL_Rect rect;
    rect.h = wallsize;
    rect.w = wallsize;

    for (i = 0; i< mapLines; i++)
    {
        for ( j = 0; j<mapCols; j++)
        {
            if (map[8*i + j] == 1)
            {
                rect.x = INIT_X + wallsize*j; //25*mapCols en gros
                rect.y = INIT_Y + wallsize*i; //25*mapLines

                window->renderRectangle(&rect, color);
            }
        }
    }
}
