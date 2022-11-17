
University of Pennsylvania, ESE 5190: Intro to Embedded Systems, Lab 2B

    Harish Ramesh, worked with Sugata Sen
    https://www.linkedin.com/in/harishramesh1998/, https://www.linkedin.com/in/sugata-sen/
    Tested on: Lenovo Legion Slim-7, Windows-11; ASUS ROG GL-552 VW, Windows-10
    
### Modifications implemented:
Modifications were made in the ws2812.pio file to use the PIO in the QTPY effectively.
The major things implemented were:

.program bootpin <br />
set pindirs, 0 <br />
.wrap_target <br />
label: <br />
    in pins, 1 <br />
    push <br />
    jmp label <br />
.wrap <br />


static inline void bootpin_program_init(PIO pio, uint sm, uint offset, uint pin) {

    pio_sm_config c = bootpin_program_get_default_config(offset);
    sm_config_set_in_pins(&c, pin);
    sm_config_set_in_shift(&c, false, true, 0);
    pio_gpio_init(pio, pin);
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, false);
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_enabled(pio, sm, true);


### Output
![]()


