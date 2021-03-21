#include <stdio.h>
#include "pico/stdlib.h"
#include "constants.h"
#include "lcd.h"

int main()
{
    stdio_init_all();
    sleep_ms(2000);
    init_pico();
    lcd_init();
    uint8_t tmps[4] = {0};
    while (1)
    {
        ili_read(CMD_READ_ID4, 3, 1, tmps);
        printf("IC Version           : %x\n", tmps[0]);
        printf("IC model name part 1 : %x\n", tmps[1]);
        printf("IC model name part 2 : %x\n", tmps[2]);
        ili_read(CMD_READ_DISPLAY_BRIGHTNESS, 2, 0, tmps);
        printf("Brightness           : %x\n", tmps[0]);
        printf("Brightness           : %x\n", tmps[1]);
        ili_read(CMD_READ_SELF_DIAG, 1, 1, tmps);
        printf("Self diag            : %x\n", tmps[0]);
        sleep_ms(1000);
    }
    return 0;
}