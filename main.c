#include <stdio.h>
#include "pico/stdlib.h"
#include "constants.h"
#include "lcd.h"
#include "graphism.h"

int main()
{
    stdio_init_all();
    sleep_ms(2000);
    init_pico();
    lcd_init();
    uint8_t tmps[4] = {0};
    while (1)
    {
        lcd_read_info(CMD_READ_ID4, 3, 1, tmps);
        printf("IC Version           : %x\n", tmps[0]);
        printf("IC model name part 1 : %x\n", tmps[1]);
        printf("IC model name part 2 : %x\n", tmps[2]);
        lcd_read_info(CMD_READ_DISPLAY_BRIGHTNESS, 2, 0, tmps);
        printf("Brightness           : %x\n", tmps[0]);
        printf("Brightness           : %x\n", tmps[1]);
        lcd_read_info(CMD_READ_SELF_DIAG, 1, 1, tmps);
        printf("Self diag            : %x\n", tmps[0]);
        sleep_ms(1000);
        printf(" Test RGB\n");
        for (uint16_t y = 0; y < HEIGHT; y++)
        {
            for (uint16_t x = 0; x < WIDTH; x++)
            {
                pset(x, y, y % 255, y % 255, y % 255);
            }
        }
        line(0, 0, 240, 320, BLACK);
        line(240, 0, 0, 320, WHITE);
        circle(120, 160, 120, YELLOW);
    }
    return 0;
}