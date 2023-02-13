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
    int init_x = 100, init_y = 100;
    int i;

    SDL_Rect rect;
    rect.h = wallsize;
    rect.w = wallsize;
    rect.x = init_x;
    rect.y = init_y;

    for (i = 0; i< mapLines; i++)
    {
        for (int j = 0; j<mapCols; j++)
        {
            if (map[8*i + j] == 1)
            {
                rect.x = init_x + 25*j; //25*mapCols en gros
                rect.y = init_y + 25*i; //25*mapLines

                window->renderRectangle(&rect, color->r, color->g, color->b, color->a);
            }
        }
    }
}
