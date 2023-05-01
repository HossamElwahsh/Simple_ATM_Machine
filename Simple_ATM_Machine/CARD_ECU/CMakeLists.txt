cmake_minimum_required(VERSION 3.25)
#project(CARD_ECU C)

set(CMAKE_C_STANDARD 11)

include_directories(CARD_ECU)
include_directories(CARD_ECU/APP)
include_directories(CARD_ECU/HAL/lcd)
include_directories(CARD_ECU/HAL/temp_sensor)
include_directories(CARD_ECU/LIB)
include_directories(CARD_ECU/MCAL/dio)
include_directories(CARD_ECU/MCAL/timer)

add_executable(
        CARD_ECU
        CARD_ECU/APP/app_interface.h
        CARD_ECU/APP/app_program.c
        CARD_ECU/HAL/lcd/lcd_config.h
        CARD_ECU/HAL/lcd/lcd_interface.h
        CARD_ECU/HAL/lcd/lcd_private.h
        CARD_ECU/HAL/lcd/lcd_program.c
        CARD_ECU/LIB/bit_math.h
        CARD_ECU/LIB/std.h
        CARD_ECU/MCAL/dio/dio_config.h
        CARD_ECU/MCAL/dio/dio_interface.h
        CARD_ECU/MCAL/dio/dio_private.h
        CARD_ECU/MCAL/dio/dio_program.c
        CARD_ECU/MCAL/timer/timer_config.h
        CARD_ECU/MCAL/timer/timer_interface.h
        CARD_ECU/MCAL/timer/timer_private.h
        CARD_ECU/MCAL/timer/timer_program.c
        CARD_ECU/main.c
        CARD_ECU/HAL/kpd/kpd_program.c
        CARD_ECU/HAL/buzzer/buzzer.c
        )
