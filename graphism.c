#include "graphism.h"
#include "constants.h"
#include "lcd.h"
#include <stdlib.h>

const Color BLACK = {0, 0, 0};
const Color RED = {255, 0, 0};
const Color GREEN = {0, 255, 0};
const Color BLUE = {0, 0, 255};
const Color WHITE = {255, 255, 255};
const Color YELLOW = {255, 255, 0};

void plot(uint16_t x0, uint16_t y0, Color c)
{
    pset(x0, y0, c.r, c.g, c.b);
}

void line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, Color c)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    for (;;)
    {
        plot(x0, y0, c);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void drawCircle(int xc, int yc, int x, int y, Color c)
{
    plot(xc + x, yc + y, c);
    plot(xc - x, yc + y, c);
    plot(xc + x, yc - y, c);
    plot(xc - x, yc - y, c);
    plot(xc + y, yc + x, c);
    plot(xc - y, yc + x, c);
    plot(xc + y, yc - x, c);
    plot(xc - y, yc - x, c);
}

void circle(uint16_t xc, uint16_t yc, uint16_t r, Color c)
{
    int x = 0, y = r;
    int d = 3 - 2 * r;
    drawCircle(xc, yc, x, y, c);
    while (y >= x)
    {
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }
        drawCircle(xc, yc, x, y, c);
    }
}

void clear_screen(uint16_t x1, uint16_t y1, uint16_t  x2, uint16_t y2, Color c)
{
    fill_area(x1, y1, x2, y2, c.r, c.g, c.b);
}
