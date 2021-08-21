#include <stdio.h>
#include "pico/stdlib.h"
#include "constants.h"
#include "lcd.h"
#include "graphism.h"
#include "characters_c64.h"
#include "bsp/board.h"
#include "tusb.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+
void print_greeting(void);
void led_blinking_task(void);

extern void cdc_task(void);
extern void hid_app_task(void);

//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+
#if CFG_TUH_CDC
CFG_TUSB_MEM_SECTION static char serial_in_buffer[64] = { 0 };

void tuh_mount_cb(uint8_t dev_addr)
{
  // application set-up
  printf("A device with address %d is mounted\r\n", dev_addr);

  tuh_cdc_receive(dev_addr, serial_in_buffer, sizeof(serial_in_buffer), true); // schedule first transfer
}

void tuh_umount_cb(uint8_t dev_addr)
{
  // application tear-down
  printf("A device with address %d is unmounted \r\n", dev_addr);
}

// invoked ISR context
void tuh_cdc_xfer_isr(uint8_t dev_addr, xfer_result_t event, cdc_pipeid_t pipe_id, uint32_t xferred_bytes)
{
  (void) event;
  (void) pipe_id;
  (void) xferred_bytes;

  printf(serial_in_buffer);
  tu_memclr(serial_in_buffer, sizeof(serial_in_buffer));

  tuh_cdc_receive(dev_addr, serial_in_buffer, sizeof(serial_in_buffer), true); // waiting for next data
}

void cdc_task(void)
{

}

#endif

//--------------------------------------------------------------------+
// TinyUSB Callbacks
//--------------------------------------------------------------------+

//--------------------------------------------------------------------+
// Blinking Task
//--------------------------------------------------------------------+
void led_blinking_task(void)
{
  const uint32_t interval_ms = 1000;
  static uint32_t start_ms = 0;

  static bool led_state = false;

  // Blink every interval ms
  if ( board_millis() - start_ms < interval_ms) return; // not enough time
  start_ms += interval_ms;

  board_led_write(led_state);
  led_state = 1 - led_state; // toggle
}

//--------------------------------------------------------------------+
// HELPER FUNCTION
//--------------------------------------------------------------------+
void print_greeting(void)
{
  char const * const rtos_name[] =
  {
      [OPT_OS_NONE]      = "None",
      [OPT_OS_FREERTOS]  = "FreeRTOS",
      [OPT_OS_MYNEWT]    = "Mynewt OS",
      [OPT_OS_CUSTOM]    = "Custom OS implemnted by application",
      [OPT_OS_PICO]      = "Raspberry Pi Pico SDK",
      [OPT_OS_RTTHREAD]  = "RT-Thread"
  };

  printf("----------------------------------------------------\r\n");
  printf("TinyUSB Host Example\r\n");
  printf("If you find any bugs or problems, feel free to open\r\n");
  printf("an issue at https://github.com/hathach/tinyusb\r\n");
  printf("----------------------------------------------------\r\n\r\n");

  printf("This Host demo is configured to support:\r\n");
  printf("  - RTOS = %s\r\n", rtos_name[CFG_TUSB_OS]);
}

int main()
{
    stdio_init_all();
    sleep_ms(2000);
    init_pico();
    lcd_init();
    uint8_t tmps[4] = {0};
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
            pset(x, y, y % 255, x, 255 - (y % 255));
        }
    }
    graph_line(0, 0, WIDTH, HEIGHT, BLACK);
    graph_line(WIDTH, 0, 0, HEIGHT, WHITE);
    graph_circle(WIDTH / 2, HEIGHT / 2, WIDTH / 2, WHITE);
    uint16_t posy = 0;
    uint16_t posx = 0;
    int c = 0;
    board_init();
    print_greeting();
    tusb_init();
    char TMPSTRING[200]={0};
    for (int i = 0; i < 2; i++)
    {
        sprintf(TMPSTRING,"%dABC\n",i);
        printf(TMPSTRING);
        print_text(TMPSTRING, YELLOW);
    }

    while (1)
    {
        // tinyusb host task
        tuh_task();
        led_blinking_task();

#if CFG_TUH_CDC
        cdc_task();
#endif

#if CFG_TUH_HID
        hid_app_task();
#endif
    }
}