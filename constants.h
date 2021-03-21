#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <stdio.h>

const uint8_t LCD_RST_RESX;
const uint8_t LCD_CS_CSX;
const uint8_t LCD_RS_DCX;
const uint8_t LCD_WR_WRX;
const uint8_t LCD_RD_RDX;

const uint8_t LCD_D0;
const uint8_t LCD_D1;
const uint8_t LCD_D2;
const uint8_t LCD_D3;
const uint8_t LCD_D4;
const uint8_t LCD_D5;
const uint8_t LCD_D6;
const uint8_t LCD_D7;

const uint16_t WIDTH;
const uint16_t HEIGHT;

//Command
const uint8_t CMD_NO_OP;
const uint8_t CMD_SOFTWARE_RESET;
const uint8_t CMD_READ_DISPLAY_ID;
const uint8_t CMD_READ_DISPLAY_STATUS;
const uint8_t CMD_READ_SELF_DIAG;
const uint8_t CMD_SLEEP_OUT;
const uint8_t CMD_DISPLAY_OFF;
const uint8_t CMD_DISPLAY_ON;
const uint8_t CMD_COLUMN_ADDRESS_SET;
const uint8_t CMD_PAGE_ADDRESS_SET;
const uint8_t CMD_MEMORY_WRITE;
const uint8_t CMD_MEMORY_ACCESS_CONTROL;
const uint8_t CMD_PIXEL_FORMAT_SET;
const uint8_t CMD_DISPLAY_FUNCTION_CONTROL;
const uint8_t CMD_FRAME_CONTROL;
const uint8_t CMD_POWER_CONTROL_1;
const uint8_t CMD_POWER_CONTROL_2;
const uint8_t CMD_VCOM_CONTROL_1;
const uint8_t CMD_VCOM_CONTROL_2;
const uint8_t CMD_READ_ID4;
const uint8_t CMD_READ_DISPLAY_BRIGHTNESS;
const uint8_t CMD_POWER_CONTROL_A;
const uint8_t CMD_POWER_CONTROL_B;
const uint8_t CMD_DRIVER_TIMING_CONTROL_A;
const uint8_t CMD_DRIVER_TIMING_CONTROL_B;
const uint8_t CMD_POWER_ON_SEQUENCE_CONTROL;
const uint8_t CMD_PUMP_RATIO_CONTROL;
#endif