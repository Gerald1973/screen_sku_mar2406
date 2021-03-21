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

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 9600

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5

// GPIO defines
// Example uses GPIO 2
#define GPIO 2

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS 17
#define PIN_SCK 18
#define PIN_MOSI 19

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9




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

void Lcd_Write_Com(uint8_t cmd)
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

void Lcd_Write_Data(uint8_t cmd)
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
void ili_read(uint8_t cmd, int numberOfResult, int start, uint8_t *results)
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

    Lcd_Write_Com(CMD_POWER_CONTROL_A);
    Lcd_Write_Data(0x39);
    Lcd_Write_Data(0x2C);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x34);
    Lcd_Write_Data(0x02);

    Lcd_Write_Com(CMD_POWER_CONTROL_B);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0XC1);
    Lcd_Write_Data(0X30);

    Lcd_Write_Com(CMD_DRIVER_TIMING_CONTROL_A);
    Lcd_Write_Data(0x85);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x78);

    Lcd_Write_Com(CMD_DRIVER_TIMING_CONTROL_B);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x00);

    Lcd_Write_Com(CMD_POWER_ON_SEQUENCE_CONTROL);
    Lcd_Write_Data(0x64);
    Lcd_Write_Data(0x03);
    Lcd_Write_Data(0X12);
    Lcd_Write_Data(0X81);

    Lcd_Write_Com(CMD_PUMP_RATIO_CONTROL);
    Lcd_Write_Data(0x20);

    Lcd_Write_Com(CMD_POWER_CONTROL_1);  //Power control
    Lcd_Write_Data(0x23); //VRH[5:0]

    Lcd_Write_Com(CMD_POWER_CONTROL_2);  //Power control
    Lcd_Write_Data(0x10); //SAP[2:0];BT[3:0]

    Lcd_Write_Com(CMD_VCOM_CONTROL_1);  //VCM control
    Lcd_Write_Data(0x3e); //Contrast
    Lcd_Write_Data(0x28);

    Lcd_Write_Com(CMD_VCOM_CONTROL_2);  //VCM control2
    Lcd_Write_Data(0x86); //--

    Lcd_Write_Com(CMD_MEMORY_ACCESS_CONTROL); // Memory Access Control
    Lcd_Write_Data(0x48);

    Lcd_Write_Com(CMD_PIXEL_FORMAT_SET);
    Lcd_Write_Data(0x55);

    Lcd_Write_Com(CMD_FRAME_CONTROL);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x18);

    Lcd_Write_Com(CMD_DISPLAY_FUNCTION_CONTROL); // Display Function Control
    Lcd_Write_Data(0x08);
    Lcd_Write_Data(0x82);
    Lcd_Write_Data(0x27);

    Lcd_Write_Com(CMD_SLEEP_OUT); //Exit Sleep
    sleep_ms(120);

    Lcd_Write_Com(CMD_DISPLAY_ON); //Display on
    Lcd_Write_Com(CMD_MEMORY_WRITE);
}


