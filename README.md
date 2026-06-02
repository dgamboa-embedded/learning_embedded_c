# STM32F446RE Bare-Metal Embedded-C Development Journey

## The main purpose of this repository is to keep track of my journey while learning bare-metal embedded-c (C for embedded systems) in Fastbit Embedded Brain Academy's: Microcontroller Embedded C Programming: Absolute Beginners course. 

### Hardware used: 

1. ARM CORTEX-M4 STM32 F446RE-NUCLEO board.
2. STLINK/V3-SET programmer/debugger.

The course expects the STM32F407 DISCOVERY board for the code examples implementation. That means: I have to checkout the documentation of my board to find the equivalent pin or memory location, which derives in a deeper understanding of the hardware's architecture.

### Development environment: 

STM32CubeIDE 1.19.0 version.

### Table of contents:
* [01 - Embedded Hello World](./01_embedded_hello_world): redirect the output of printf to the ITM (Instrumentation Trace Macrocell Unit)  inside the processor and read the output via SWD debugging protocol and the SWV console in the IDE.