/*
 * File:	Caculator.h					Version	:	1.0	(Stable)						() = type
 * Author: 	Sagi Dayan					ID		:	300242435							[] = variable name
 * Email:	sagidayan@gmail.com							 								[P] = private method
 *
 *								________________________JCE 2014______________________________
 */
#pragma once

#include <iostream>
#include <windows.h>
#include <cmath>
#include "Complex.h"
#include <conio.h>
#include <stack>
#include <queue>
#include <mmsystem.h>

#define x_Mode		50 /* X position of all Toggles (starting point) */
#define y_cMode		2  /* Y Position of the  input (Complex) Mode*/
#define y_sMode		6  /* Y Position of the  Speak Mode */
#define x_screen	5  /* X Position of the Calculator screen */
#define y_screen	1  /* Y Position of the Calculator screen */

void gotoxy(int x, int y); /* Moves the curser to a diffarent coordinate */
int startApp(); /* Starts the app - returns 0 if exited as expected */
void printHelp(); /* Prints The Help Page */
void printCalc(); /* Prints The Calc UI */
void clearScreen(); /* Clears The Calcuator Screen */
void calculate(queue<Complex> &, char); /* Calculates according to operator (the char) and 2 args in queue */
void emptyQ(queue<Complex> &); /* Clear the Queue */
void tutorial(); /* Prints out the Tutorial in the help screen */
void toggleSpeak(bool); /* Toggles speak mode  - on<->off  - animation*/
void toggleMode(bool);/* Toggles the input mode - Regular <--> Complex - animation */

