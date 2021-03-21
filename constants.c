#include<stdio.h>
#include"constants.h"

const uint8_t LCD_RST_RESX = 17;
const uint8_t LCD_CS_CSX = 18;
const uint8_t LCD_RS_DCX = 19;
const uint8_t LCD_WR_WRX = 20;
const uint8_t LCD_RD_RDX = 21;

const uint8_t LCD_D0 = 0;
const uint8_t LCD_D1 = 1;
const uint8_t LCD_D2 = 2;
const uint8_t LCD_D3 = 3;
const uint8_t LCD_D4 = 4;
const uint8_t LCD_D5 = 5;
const uint8_t LCD_D6 = 6;
const uint8_t LCD_D7 = 7;

const uint16_t WIDTH = 240;
const uint16_t HEIGHT = 320;

//Command
const uint8_t CMD_NO_OP = 0x00;
const uint8_t CMD_SOFTWARE_RESET = 0x01;
const uint8_t CMD_READ_DISPLAY_ID = 0x04;
const uint8_t CMD_READ_DISPLAY_STATUS = 0x09;
const uint8_t CMD_READ_SELF_DIAG = 0x0f;
const uint8_t CMD_SLEEP_OUT = 0x11;
const uint8_t CMD_DISPLAY_OFF = 0x28;
const uint8_t CMD_DISPLAY_ON = 0x29;
const uint8_t CMD_COLUMN_ADDRESS_SET = 0x2A;
const uint8_t CMD_PAGE_ADDRESS_SET = 0x2B;
const uint8_t CMD_MEMORY_WRITE = 0x2c;
const uint8_t CMD_MEMORY_ACCESS_CONTROL = 0x36;
const uint8_t CMD_PIXEL_FORMAT_SET = 0x3A;
const uint8_t CMD_DISPLAY_FUNCTION_CONTROL = 0XB6;
const uint8_t CMD_FRAME_CONTROL = 0xB1;
const uint8_t CMD_POWER_CONTROL_1 = 0XC0;
const uint8_t CMD_POWER_CONTROL_2 = 0XC1;
const uint8_t CMD_VCOM_CONTROL_1 = 0XC5;
const uint8_t CMD_VCOM_CONTROL_2 = 0xC7;
const uint8_t CMD_READ_ID4 = 0xD3;
const uint8_t CMD_READ_DISPLAY_BRIGHTNESS = 0x52;
const uint8_t CMD_POWER_CONTROL_A = 0xCB;
const uint8_t CMD_POWER_CONTROL_B = 0xCF;
const uint8_t CMD_DRIVER_TIMING_CONTROL_A = 0xE8;
const uint8_t CMD_DRIVER_TIMING_CONTROL_B = 0xea;
const uint8_t CMD_POWER_ON_SEQUENCE_CONTROL = 0xed;
const uint8_t CMD_PUMP_RATIO_CONTROL = 0xf7;