#ifndef GRAPHISM_H
#define GRAPHISM_H

#include <stdio.h>

/**
 * @brief Structure to contain the color definition.
 * r g b, are unsigned byte.
 * 
 */
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

/**
 * @brief constants declaration
 * 
 */
extern const Color BLACK;
extern const Color RED;
extern const Color GREEN;
extern const Color BLUE;
extern const Color WHITE;
extern const Color YELLOW;

/**
 * @brief The point
 * 
 * @param x0 x
 * @param y0 y
 * @param c  color
 */
void graph_plot(uint16_t x0, uint16_t y0, Color c);

/**
 * @brief The line
 * 
 * @param x0 origin x
 * @param y0 origin y
 * @param x1 end x
 * @param y1 end y
 * @param c  one color
 */
void graph_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, Color c);

/**
 * @brief The circle
 * 
 * @param x0 origin x
 * @param y0 origin x
 * @param radius radius
 * @param c one color
 */
void graph_circle(uint16_t x0, uint16_t y0, uint16_t radius, Color c);

/**
 * @brief Clear the screen with the given color.
 * 
 * @param c the given color
 */
void graph_fill_area(uint16_t x1, uint16_t y1, uint16_t  x2, uint16_t y2, Color c);

#endif