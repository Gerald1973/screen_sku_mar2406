#ifndef LCD_H
#define LCD_H

/**
 * @file lcd.h
 * @author Gérald Maréchal (smilesmile1973@gmail.com)
 * @brief header file used for the communication between the raspberry Pi Pico
 *        and the LCD screen SKU MAR 2406 initially planned for the Arduino. 
 * @version 0.1
 * @date 2021-03-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
/**
 * @brief Set the Out object
 * 
 * @param value true make the GPIO as out else in
 */
void setDataOut(bool value);

/**
 * @brief the implementation of this method needs to initialize the Raspberry 
 *        Pi Pico
 * 
 */
void init_pico();

/**
 * @brief writing of the byte to the pins used for the data transmission.
 * 
 * @param data one byte
 */
void writeToPins(uint8_t data);

/**
 * @brief read the result of a command on the pins.
 * 
 * @return uint8_t  one byte
 */
uint8_t readPins();

/**
 * @brief send the given command to the lcd screen. 
 *  for more information about the commands, see the datasheet of the ILI9341
 * 
 * @param cmd one byte 
 */
void lcd_write_command(uint8_t cmd);

/**
 * @brief used to write the parameter of a given command.
 * 
 * @param cmd one byte
 */
void lcd_write_data(uint8_t cmd);

/**
 * @brief Method used to fetch some informations of the lcd screen.
 * 
 * @param cmd for example: CMD_READ_ID4 or CMD_READ_DISPLAY_BRIGHTNESS or CMD_READ_SELF_DIAG,...
 * @param numberOfResult number of bytes to be taken in account for the results 
 * @param start which byte to start
 * @param results an array of byte where the size needs to be at less numberOfResult
 */
void lcd_read_info(uint8_t cmd, int numberOfResult, int start, uint8_t *results);

/**
 * @brief bootstrap startup of the LCD screen.
 * 
 */
void lcd_init(void);

/**
 * @brief Define the page, consider a page like a rectangle defined by the top left corner and the bottom right corner.
 * 
 * 
 * @param x1 left top corner x 
 * @param y1 left top corner y
 * @param x2 right bottom corner x
 * @param y2 right bottom corner Y
 */
void set_address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/**
 * @brief the implementation of this method will draw a pixel at the given position. 
 * 
 * @param x the X position (column)
 * @param y the y position (row)
 * @param r the red value [0..255]
 * @param g the green value [0..255]
 * @param b the blue value [0..255]
 */
void pset(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);

#endif