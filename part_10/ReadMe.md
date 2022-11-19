

University of Pennsylvania, ESE 5190: Intro to Embedded Systems, Lab 2B

    Harish Ramesh, worked with Sugata Sen
    https://www.linkedin.com/in/harishramesh1998/, https://www.linkedin.com/in/sugata-sen/
    Tested on: Lenovo Legion Slim-7, Windows-11; ASUS ROG GL-552 VW, Windows-10
    
### Functionality implemented:
For part 9 we are using the APDS sensor data, and checking the colour packet sent, 
1. to the pio
2. to the ws2812 ( Neopixel LED )

We also noted the "C" channel value, as a suitable proxy for the ambient brightness level during the experiment. We conducted the experiment in both dark and bright room conditions, and adjusted the ADATA register to suitably small integration time, so the Neopixel closely tracks the colour and brightness that is sensed by APDS coour sensor.



### Output
Dark room :


https://user-images.githubusercontent.com/38978733/202830302-173b13c8-71ae-4842-bd18-4b5474969e3b.mp4






Bright room :



https://user-images.githubusercontent.com/38978733/202830310-8420493d-e6d2-4e91-84bf-8cdbc87835a0.mp4

