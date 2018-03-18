# RTOS project
Repo includes src (no library and drivers) files for RTOS project.
The design assuptions were:
1. Changing brightness of diodes using touch sensor
2. Changing diodes using button
3. Displaying level of brightness on display

Current functionalities are:
1. Timers as PWM handling brightness of diodes
2. Touch sensor for brightness changing
3. Button interrupts for state machine handling
4. LCD screen for displaying results (SPI)
5. Queues to pass neccesary variables between threads

TBD:
1. Code optimization
2. Adding semaphores
