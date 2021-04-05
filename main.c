#include <stdio.h>
#include "pico/stdlib.h"
#include "constants.h"
#include "lcd.h"
#include "graphism.h"
#include "characters_c64.h"

int main()
{
    stdio_init_all();
    sleep_ms(2000);
    init_pico();
    lcd_init();
    uint8_t tmps[4] = {0};
    while (1)
    {
        printf("A_0001\n");
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
        //clear_screen(GREEN);
        for (uint16_t y = 0; y < HEIGHT; y++)
        {
            for (uint16_t x = 0; x < WIDTH; x++)
            {
                pset(x, y, y % 255, x , 255 - (y % 255));
            }
        }
        graph_line(0, 0, 240, 320, BLACK);
        graph_line(240, 0, 0, 320, WHITE);
        graph_circle(120, 160, 120, WHITE);
        uint16_t posy = 0;
        uint16_t posx = 0;
        for (int i = 0; i < 224; i++) {
            posx = (i * CHAR_WIDTH) % WIDTH;
            posy = ((i * CHAR_WIDTH) / WIDTH) * CHAR_HEIGHT;
            char_draw(i + 32, posx ,posy, WHITE);
        }
        sleep_ms(2000);
        //graph_fill_area(0, 0, 240, 320, RED);
    }
    return 0;
}