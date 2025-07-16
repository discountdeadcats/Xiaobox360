# Xbox 360 Controller USB Adapter

This is an adapter that allows you to connect an Xbox 360 controller to a PC via USB. It works with the Xiao RP2040, but can presumably be ported to other microcontrollers. It is pretty simple, and I did not invent all the code—AI helped me a lot.

## What You Need

- An Xbox RF board (Slim or Full Fat)
- A microcontroller (I use the Xiao RP2040)
- A USB-C port/cable
- Some basic soldering knowledge

## Wiring

I've included some basic wiring diagrams.
You also have to select the drivers manually on the computer they're not that hard to find

This is the case I used
https://www.thingiverse.com/thing:2912903

this is the inspiration for the project 
https://github.com/ginokgx/xbox360slimRF/tree/main


## BOM

USB C port https://www.digikey.com/short/wnwh8wq2 you can also hack up an old cable
Xiao RP2040 https://www.digikey.com/short/29jcv89m
Xbox 360 RF  board

## wiring  guide
### usb c port
- D+ to D+ on rf board
- D- to D- on rf board
- Gnd to gnd
- 5v to p1 (5v) on rp2040

### xiao rp20 
- SDA p6 to  sda on rf board 
- SCL p7 to scl on rf board 
- p2 to rf button
