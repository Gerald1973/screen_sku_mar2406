#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <stdio.h>

extern const uint8_t LCD_RST_RESX;
extern const uint8_t LCD_CS_CSX;
extern const uint8_t LCD_RS_DCX;
extern const uint8_t LCD_WR_WRX;
extern const uint8_t LCD_RD_RDX;

extern const uint8_t LCD_D0;
extern const uint8_t LCD_D1;
extern const uint8_t LCD_D2;
extern const uint8_t LCD_D3;
extern const uint8_t LCD_D4;
extern const uint8_t LCD_D5;
extern const uint8_t LCD_D6;
extern const uint8_t LCD_D7;

extern const uint16_t WIDTH;
extern const uint16_t HEIGHT;
extern const uint16_t WIDTH_IN_CHAR;
extern const uint16_t HEIGHT_IN_CHAR;

//Command
extern const uint8_t CMD_NO_OP;
extern const uint8_t CMD_SOFTWARE_RESET;
extern const uint8_t CMD_READ_DISPLAY_ID;
extern const uint8_t CMD_READ_DISPLAY_STATUS;
extern const uint8_t CMD_READ_SELF_DIAG;
extern const uint8_t CMD_SLEEP_OUT;
extern const uint8_t CMD_DISPLAY_OFF;
extern const uint8_t CMD_DISPLAY_ON;
extern const uint8_t CMD_COLUMN_ADDRESS_SET;
extern const uint8_t CMD_PAGE_ADDRESS_SET;
extern const uint8_t CMD_MEMORY_WRITE;
extern const uint8_t CMD_MEMORY_ACCESS_CONTROL;
extern const uint8_t CMD_PIXEL_FORMAT_SET;
extern const uint8_t CMD_DISPLAY_FUNCTION_CONTROL;
extern const uint8_t CMD_FRAME_CONTROL;
extern const uint8_t CMD_POWER_CONTROL_1;
extern const uint8_t CMD_POWER_CONTROL_2;
extern const uint8_t CMD_VCOM_CONTROL_1;
extern const uint8_t CMD_VCOM_CONTROL_2;
extern const uint8_t CMD_READ_ID4;
extern const uint8_t CMD_READ_DISPLAY_BRIGHTNESS;
extern const uint8_t CMD_POWER_CONTROL_A;
extern const uint8_t CMD_POWER_CONTROL_B;
extern const uint8_t CMD_DRIVER_TIMING_CONTROL_A;
extern const uint8_t CMD_DRIVER_TIMING_CONTROL_B;
extern const uint8_t CMD_POWER_ON_SEQUENCE_CONTROL;
extern const uint8_t CMD_PUMP_RATIO_CONTROL;
#endif