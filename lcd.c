#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "hardware/divider.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/dma.h"
#include "hardware/pio.h"
#include "constants.h"
#include "lcd.h"

void setDataOut(bool value)
{
    gpio_set_dir(LCD_D0, value);
    gpio_set_dir(LCD_D1, value);
    gpio_set_dir(LCD_D2, value);
    gpio_set_dir(LCD_D3, value);
    gpio_set_dir(LCD_D4, value);
    gpio_set_dir(LCD_D5, value);
    gpio_set_dir(LCD_D6, value);
    gpio_set_dir(LCD_D7, value);
}

void init_pico()
{
    puts("DEBUG: init.");
    gpio_init(LCD_CS_CSX);
    gpio_init(LCD_RD_RDX);
    gpio_init(LCD_RS_DCX);
    gpio_init(LCD_RST_RESX);
    gpio_init(LCD_WR_WRX);

    gpio_init(LCD_D0);
    gpio_init(LCD_D1);
    gpio_init(LCD_D2);
    gpio_init(LCD_D3);
    gpio_init(LCD_D4);
    gpio_init(LCD_D5);
    gpio_init(LCD_D6);
    gpio_init(LCD_D7);

    gpio_set_dir(LCD_CS_CSX, GPIO_OUT);
    gpio_set_dir(LCD_RD_RDX, GPIO_OUT);
    gpio_set_dir(LCD_RS_DCX, GPIO_OUT);
    gpio_set_dir(LCD_RST_RESX, GPIO_OUT);
    gpio_set_dir(LCD_WR_WRX, GPIO_OUT);

    setDataOut(GPIO_OUT);
}

void writeToPins(uint8_t data)
{
    gpio_put(LCD_D0, data & 0x01);
    gpio_put(LCD_D1, (data >> 1) & 0x01);
    gpio_put(LCD_D2, (data >> 2) & 0x01);
    gpio_put(LCD_D3, (data >> 3) & 0x01);
    gpio_put(LCD_D4, (data >> 4) & 0x01);
    gpio_put(LCD_D5, (data >> 5) & 0x01);
    gpio_put(LCD_D6, (data >> 6) & 0x01);
    gpio_put(LCD_D7, (data >> 7) & 0x01);
}

uint8_t readPins()
{
    uint8_t result = 0;
    result = result | gpio_get(LCD_D0);
    result = result | (gpio_get(LCD_D1) << 1);
    result = result | (gpio_get(LCD_D2) << 2);
    result = result | (gpio_get(LCD_D3) << 3);
    result = result | (gpio_get(LCD_D4) << 4);
    result = result | (gpio_get(LCD_D5) << 5);
    result = result | (gpio_get(LCD_D6) << 6);
    result = result | (gpio_get(LCD_D7) << 7);
    return result;
}

void lcd_write_command(uint8_t cmd)
{
    setDataOut(true);
    gpio_put(LCD_CS_CSX, 0);
    gpio_put(LCD_RST_RESX, 1);
    gpio_put(LCD_RS_DCX, 1);
    gpio_put(LCD_WR_WRX, 1);
    gpio_put(LCD_RD_RDX, 1);
    gpio_put(LCD_RS_DCX, 0);
    gpio_put(LCD_WR_WRX, 0);
    writeToPins(cmd);
    gpio_put(LCD_WR_WRX, 1);
    gpio_put(LCD_RS_DCX, 1);
    gpio_put(LCD_CS_CSX, 1);
}

void lcd_write_data(uint8_t cmd)
{
    setDataOut(true);
    gpio_put(LCD_CS_CSX, 0);
    gpio_put(LCD_RST_RESX, 1);
    gpio_put(LCD_RS_DCX, 1);
    gpio_put(LCD_WR_WRX, 1);
    gpio_put(LCD_RD_RDX, 1);
    gpio_put(LCD_WR_WRX, 0);
    writeToPins(cmd);
    gpio_put(LCD_WR_WRX, 1);
    gpio_put(LCD_CS_CSX, 1);
}

/**
 * @brief read infos from ILI9341.
 * 
 * @param cmd the read command number. 
 * @param numberOfResult the number of result.
 * @param start the start of data, some command send directly the result,
 *              some command send the the result from start. Based 0.
 * @param results an array to store the value(s)
 * @return uint8_t* 
 */
void lcd_read_info(uint8_t cmd, int numberOfResult, int start, uint8_t *results)
{
    gpio_put(LCD_CS_CSX, 0);
    gpio_put(LCD_RST_RESX, 1);
    setDataOut(GPIO_OUT);
    gpio_put(LCD_WR_WRX, 1);
    gpio_put(LCD_RD_RDX, 1);
    gpio_put(LCD_RS_DCX, 0);
    gpio_put(LCD_WR_WRX, 0);
    writeToPins(cmd);
    gpio_put(LCD_WR_WRX, 1);
    gpio_put(LCD_RS_DCX, 1);
    setDataOut(GPIO_IN);
    for (int i = 0; i < numberOfResult + start; i++)
    {
        gpio_put(LCD_RD_RDX, 0);
        if (i >= start)
        {
            results[i - start] = readPins();
        }
        gpio_put(LCD_RD_RDX, 1);
    }
    gpio_put(LCD_CS_CSX, 1);
}

void lcd_init(void)
{
    gpio_put(LCD_RST_RESX, 1);
    sleep_ms(5);
    gpio_put(LCD_RST_RESX, 0);
    sleep_ms(15);
    gpio_put(LCD_RST_RESX, 1);
    sleep_ms(15);

    gpio_put(LCD_CS_CSX, 1);
    gpio_put(LCD_WR_WRX, 1);
    gpio_put(LCD_CS_CSX, 0); //CS

    lcd_write_command(CMD_POWER_CONTROL_A);
    lcd_write_data(0x39);
    lcd_write_data(0x2C);
    lcd_write_data(0x00);
    lcd_write_data(0x34);
    lcd_write_data(0x02);

    lcd_write_command(CMD_POWER_CONTROL_B);
    lcd_write_data(0x00);
    lcd_write_data(0XC1);
    lcd_write_data(0X30);

    lcd_write_command(CMD_DRIVER_TIMING_CONTROL_A);
    lcd_write_data(0x85);
    lcd_write_data(0x00);
    lcd_write_data(0x78);

    lcd_write_command(CMD_DRIVER_TIMING_CONTROL_B);
    lcd_write_data(0x00);
    lcd_write_data(0x00);

    lcd_write_command(CMD_POWER_ON_SEQUENCE_CONTROL);
    lcd_write_data(0x64);
    lcd_write_data(0x03);
    lcd_write_data(0X12);
    lcd_write_data(0X81);

    lcd_write_command(CMD_PUMP_RATIO_CONTROL);
    lcd_write_data(0x20);

    lcd_write_command(CMD_POWER_CONTROL_1); //Power control
    lcd_write_data(0x23);                   //VRH[5:0]

    lcd_write_command(CMD_POWER_CONTROL_2); //Power control
    lcd_write_data(0x10);                   //SAP[2:0];BT[3:0]

    lcd_write_command(CMD_VCOM_CONTROL_1); //VCM control
    lcd_write_data(0x3e);                  //Contrast
    lcd_write_data(0x28);

    lcd_write_command(CMD_VCOM_CONTROL_2); //VCM control2
    lcd_write_data(0x86);                  //--

    lcd_write_command(CMD_MEMORY_ACCESS_CONTROL); // Memory Access Control
    lcd_write_data(0x48);

    lcd_write_command(CMD_PIXEL_FORMAT_SET);
    lcd_write_data(0x55); //16 bits by pixel

    lcd_write_command(CMD_FRAME_CONTROL);
    lcd_write_data(0x00);
    lcd_write_data(0x18);

    lcd_write_command(CMD_DISPLAY_FUNCTION_CONTROL); // Display Function Control
    lcd_write_data(0x08);
    lcd_write_data(0x82);
    lcd_write_data(0x27);

    lcd_write_command(CMD_SLEEP_OUT); //Exit Sleep
    sleep_ms(120);

    lcd_write_command(CMD_DISPLAY_ON); //Display on
    //lcd_write_command(CMD_MEMORY_WRITE);
}

void set_address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    lcd_write_command(CMD_COLUMN_ADDRESS_SET);
    lcd_write_data(x1 >> 8);
    lcd_write_data(x1);
    lcd_write_data(x2 >> 8);
    lcd_write_data(x2);
    lcd_write_command(CMD_PAGE_ADDRESS_SET);
    lcd_write_data(y1 >> 8);
    lcd_write_data(y1);
    lcd_write_data(y2 >> 8);
    lcd_write_data(y2);
    lcd_write_command(CMD_MEMORY_WRITE);
}

/*
00000000 00000000 00000000

*/
void pset(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b)
{
    set_address(x,y,x,y);
    uint16_t result = (r >> 2) << 11;
    result = result + ((g >> 3) << 6);
    result = result + (b >> 2);
    lcd_write_data(result >> 8);
    lcd_write_data(result);
}