# arm code

------

- IDE platform: Keil uVision V5.23.0.0
- OS: Windows 10
- ARM CPU: ARM cortex-M3, STM32F103ZET6
- ARM OS: FreeRTOS V10.1.1



1. Entry

   Double click the following file and open the project in Keil.

   ```
   Project/Demo.uvprojx
   ```

2. Introduction

   The project contains several folders, in Explorer.

   - App (contains all the user-defined apps, which will be used in OS)
     - battery
     - bumper
     - button
     - canbus
     - canopen
     - lifter
     - nvidiacom
     - safetymanager
     - statusmanager
   - Bsp (basic driver for different part, such as can, usart, timer and so on.)
   - CANOpen (CANOpen library)
     - inc
       - stm32
     - src
   - Doc (Readme and record for file changes)
   - FreeRTOS (FreeRTOS library)
     - include
     - portable
       - IAR
         - ARM_CM0
         - ARM_CM3
         - ARM_CM4F
         - ARM_CM4F_MPU
         - ARM_CM7
       - MemMang
       - RVDS
   - Libraries (Libraries about the ARM core)
     - CMSIS
       - CoreSupport
       - DeviceSupport
         - startup
     - STM32F10x_StdPeriph_Driver
       - inc
       - src
   - Project (Project file for Keil, entry of project)