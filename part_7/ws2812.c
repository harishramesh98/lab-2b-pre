#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "D:\Course Stuff\Fall'22\ESE 519\lab\SDK\pico-sdk\src\boards\include\boards\adafruit_qtpy_rp2040.h"
#define IS_RGBW true
#define NUM_PIXELS 150

#ifdef PICO_DEFAULT_WS2812_PIN
#define WS2812_PIN PICO_DEFAULT_WS2812_PIN
#else
// default to pin 2 if the board doesn't have a default WS2812 pin defined
#define WS2812_PIN 2
#endif
#define PICO_DEFAULT_WS2812_POWER_PIN 11
#define QTPY_BOOT_PIN 21
const uint bootpin = QTPY_BOOT_PIN;
PIO pio = pio0;
int sm = 0;
int sm1 = 1;

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

// typedef struct{
//     uint32_t statval;
// } status;

void replay_data(int *sequence){
    for(int i=0; i<5000; i++){
		sleep_ms(1);
		if(sequence[i] == 1){
			put_pixel(0xFF00FF);
			printf("%d", 1);
		} else{
			put_pixel(0);
			printf("%d", 0);
			}
        	put_pixel(0);
	    sleep_ms(1);
		}

	printf("\n");
}

// void replay_data_slow(int *sequence){
//     for(int i=0; i<5000; i++){
// 		sleep_ms(1);
// 		if(sequence[i] == 1){
// 			put_pixel(0xFF00FF);
// 			printf("%d", 1);
// 		} else{
// 			put_pixel(0);
// 			printf("%d", 0);
// 			}
//             sleep_ms(1);
//         	put_pixel(0);
// 	    sleep_ms(1);
// 		}

// 	printf("\n");
// }

void record_data(int *sequence){
   for(int i=0; i<5000; i++){
		sleep_ms(2);
		if((uint8_t)pio_sm_get(pio,sm1)==0){
			sequence[i] = 1;
		}
	}
	sleep_ms(2000);
}

int main() {
    //set_sys_clock_48();
    const uint POW_PIN = PICO_DEFAULT_WS2812_POWER_PIN;
    gpio_init(POW_PIN);
    gpio_set_dir(POW_PIN, GPIO_OUT);
    gpio_put(POW_PIN,1);
    stdio_init_all();

    // PIO pio = pio0;
    // int sm = 0;
    // uint offset = pio_add_program(pio, &ws2812_program);

//     PIO pio = pio0;
//     int sm = 0;
//     int sm1 = 1;
    uint offset = pio_add_program(pio, &ws2812_program);
    uint offset1 = pio_add_program(pio, &bootpin_program);


    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);
    bootpin_program_init(pio,sm1,offset1,bootpin);
    const int y;
    int t = 0;
    int i = 0;

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    int sequence[5000];
    while(!(stdio_usb_connected()));

    while (1) {
        char input;
printf("Choose mode:\n");
        scanf("%c",&input);
        if (input=='r'){
            for(int i=0; i<5000; i++){
		        sequence[i] = 0;
	        }
            printf("recording...\n");
            record_data(sequence);
            printf("Recorded\n");
        }
        else if (input == 'p'){
            printf("playing\n");
            replay_data(sequence);
            printf("Played\n");
        }
        // else if (input == 's'){
        //     replay_data_slow(sequence);
        // }
    }
}
