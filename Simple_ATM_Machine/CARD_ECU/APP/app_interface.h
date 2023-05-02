/*
 * app_interface.h
 *
 *   Created on: Apr 10, 2023
 *       Author: Hacker Kermit - https://github.com/AbdelrhmanWalaa/Moving-Car-Project.git
 *  Description: This file contains all Application (APP) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */ 

#ifndef APP_H_
#define APP_H_

/* APP Includes */
/* LIB */
#include "../LIB/std.h"
#include "../LIB/bit_math.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* MCAL */
#include "../MCAL/dio/dio_interface.h"
#include "../MCAL/timer/timer_interface.h"


/*HAl*/

/* APP Macros */

/* APP Delays */

/* APP STATES */

/* APP Buttons */

/* APP Actions */

/* APP Functions' Prototypes */

/**
 *
 */
void APP_initialization( void );

/**
 * @return void.
 */
void APP_startProgram  ( void );

#endif /* APP_H_ */