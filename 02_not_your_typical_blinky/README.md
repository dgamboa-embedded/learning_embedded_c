# Project 02: Not your typical blinky

## Objectives:
* Turn on the green led (LD2) on ARM Cortex-M4 STM32 F446RE-NUCLEO microcontroller without relying on HAL (Hardware Abstraction Layers) or any operating system (Bare-Metal).
* Read ARM Cortex-M4 STM32 F446RE-NUCLEO microcontroller's schematic (MB1136-C-03) to find the LD2 and the SB's (solder bridges) involved on it's path to a certain pin on the board (PA5). 
* Read the user manual (UM1724), section 7.11 in order to check the solder bridges interacting with LD2 on its way to the PA5 pin on the board.
* Use the multimeter to find out if there is a closed circuit between the LD2 and the PA5 pin. 

## Technical Insights:

## 1. Finding the green user LED LD2 on the board's schematic and User Manual:

Before diving into technical details, let's take a look at the microcontroller's schematic (MB1136-C-03):

![schematic_LD2_connections](./images/schematic_LD2_closed_circuit.png)

![schematic_LD2_connections](./images/schematic_LD2_closed_circuit_zoom.png)

Looking closer to the extension connectors page, we can find the LD2, and following the right path, there's a resistor with a resitance of 510 ohms. traversing the path there's the solder bridge SB21 which is closed, so the current flows through it and reaches a bifurcation here it's notorious that LD2 is connected to the Arduino's Pin number 6 (D13) on CN9 module.LD2 also reaches the D13 line and here there are two possible paths. Despite that, in red letters one can tell that the SB29 is only closed for F302R8 microcontroller, that mean there's no connection between LD2 and PB13. On the other hand, SB42 is closed, hence LD2 is connected to PA5, and this is very important because the connection between the green led and the pin has been found. 

if one take a look at section 7.11 of the user manual (UM1724), we can notice that the soldier bridge is connected to Arduino's D13, exactly as stated before.

![schematic_LD2_connections](./images/user_manual_solder_bridges.png) 

This proves that the electrical current flows through SB21 in order to reach Arduino. 

There's also a more physical aproach so to speak, to find if a solder bridge is closed or not. For that purpose, let's take a look at the STM32 F446RE-NUCLEO board's backside:

![schematic_LD2_connections](./images/Nucleo-F446RE_back_side.png) 

If a certain solder bridge has a resistor (the black one with a 0 on the center) connecting both metal sides, that SB is closed. On the other hand, if there's no resistor connecting both sides, the SB is open, hence the electrical current doesn't flows through it. 

**Notice that SB21 and SB42 both have the resistor connecting both sides, so there's indeed a closed circuit between LD2 and PA5, Furthermore, the SB29 doesn't present the black resistor, hence it's open**

## 2. Using the multimeter to test if there's actually a closed circuit between LD2 and PA5:

Other way to prove that there's a closed circuit between LD2 and PA5 is using the multimeter, passing 2 Volts through its probes to check if LD2 turns ON the green light. If it does, there's indeed a close circuit between LD2 and PA5, and thats exactly what i proved with the following image.

![schematic_LD2_connections](./images/turning_led_on_with_multimeter.png) 

According to the schematic, there's a 510 ohms resistance between LD2 and SB21, if there's a closed circuit between LD2 and PA5, one can measure the resistance, as follows.

![schematic_LD2_connections](./images/measuring_resistance.png)  

I actually measured the resistance in kiloohms so the resistance we found was 0.511 kiloohms (511 ohms), which is almost exactly as stated by the schematic.

The conclusion is: **there's a closed circuit between LD2 and PA5.**







