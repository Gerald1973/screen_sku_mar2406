#ifndef CHARACTERS_C64_H
#define CHARACTERS_C64_H
#include <stdio.h>
#include "graphism.h"

const uint8_t CHAR_HEIGHT;
const uint8_t CHAR_WIDTH;
const uint16_t char_characters[4096];

/**
 * @brief Build a row of the matrix character
 * 
 * @param byte the given line 
 * @param result the pointer on the char matrix to put the color
 * @param color the given color
 */
void char_write_binary(uint8_t byte, uint16_t *result, Color color);

/**
 * @brief As the offset of the character map can be different from th ASCII table.
 * this method converts the given char based on his ASCII code to th offset in the map.
 * 
 * @param c the given char 
 * @return uint8_t the corresponding offset
 */
uint16_t char_ascii_offset(char c);

/**
 * @brief This method builds the character matrix in the given results array.
 * 
 * @param c the char to build the matrix
 * @param results an array containing 
 */
void char_build_matrix(char c, uint16_t *results, Color color);

/**
 * @brief Draw the given char at the given position.
 * 
 * @param c the character
 * @param x the column
 * @param y the row
 * @param color the color
 */
void char_draw(char c, uint16_t x, uint16_t y, Color color);

#endif