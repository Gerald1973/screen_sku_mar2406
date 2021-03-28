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
const Color BLACK;
const Color RED;
const Color GREEN;
const Color BLUE;
const Color WHITE;
const Color YELLOW;

/**
 * @brief The point
 * 
 * @param x0 x
 * @param y0 y
 * @param c  color
 */
void plot(uint16_t x0, uint16_t y0, Color c);

/**
 * @brief The line
 * 
 * @param x0 origin x
 * @param y0 origin y
 * @param x1 end x
 * @param y1 end y
 * @param c  one color
 */
void line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, Color c);

/**
 * @brief The circle
 * 
 * @param x0 origin x
 * @param y0 origin x
 * @param radius radius
 * @param c one color
 */
void circle(uint16_t x0, uint16_t y0, uint16_t radius, Color c);

#endif