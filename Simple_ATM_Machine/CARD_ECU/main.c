/*
 * main.c
 *
 *   Created on: May 1, 2023
 *       Author: Hacker Kermit - https://github.com/HossamElwahsh/Simple_ATM_Machine.git
 *  Description: This application has two modes of operation:
 *					1. Programming Mode
 *					   1.1. The CARD MCU will enter this mode after reset
 *					   1.2. For the first time only the MCU will send the following message on the terminal
 *						    1.2.1. "Please Enter Card PAN:" and wait for the PAN
 *						    1.2.2. "Please Enter New PIN:" and wait for the PIN
 *							1.2.3. "Please Confirm New PIN:" and wait for the PIN
 *							1.2.4. If PIN is matched, then change to user mode
 *							1.2.5. If PIN is not matched, not numeric and exceeds 4 characters, then "Wrong PIN" message is displayed and repeat from step 2
 *						1.3 For any further resets
 *							1.3.1 "Please press 1 for entering user mode and 2 for programming mode:" message is sent
 */ 


#include "main.h"

int main(void)
{
    /* App initialization */
	APP_initialization();

    /* App start program */
	APP_startProgram();
}