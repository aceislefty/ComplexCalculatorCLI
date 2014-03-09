/*
 * File:	Calculator.cpp				Version	:	1.0	(Stable)						() = type
 * Author: 	Sagi Dayan					ID		:	300242435							[] = variable name
 * Email:	sagidayan@gmail.com							 								[P] = private method
 *
 *								________________________JCE 2014______________________________
 */
#include "Calculator.h"

/* Moves the curser to a diffarent coordinate */
void gotoxy(int x, int y) 
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}


/* Starts the app - returns 0 if exited as expected */
int startApp()
{
	char input, sign = NULL;  //input is the input key from user, sign is an operator
	string complexAsString;   //this will be the string input via Complex input mode, to create a complex object
	double arg;				  // the double input in regular mode
	queue<Complex> q;         // a Queue of arguments - idealy will hold 2 at max
	bool speakMode = false;   // speak mode flag
	
	printCalc();
	toggleSpeak(false);
	gotoxy(x_screen, y_screen);
	do												 // While input != q
	{
		input = getch();
		switch(input)
		{
			case 'e':					// start getting complex string via input - and creating Complex obj, pushing to queue
				toggleMode(true);
				gotoxy(x_screen, y_screen);
				clearScreen();
				if(!q.empty() && sign == NULL)
					break;
				cin >> complexAsString;
				q.push(Complex(complexAsString));
				toggleMode(false);
				gotoxy(x_screen, y_screen);
				complexAsString.clear();
				break;
			case '+':										 // operator input, if we have 2 args in queue - caculate
			case '-':										 // and show sub answer so far, else, change the (sign) and get
			case '/':										 // another arg.
			case '*':
				if(!complexAsString.empty()) //check if we have a "Regular" input... if so - make an obj and push to queue
				{
					arg = atof(complexAsString.c_str());
					q.push(Complex(arg));
				}
				if(q.empty()) // if the queue is empty - do nothing.
					break;
				else if(q.size() >=2) // if we have 2 or more (not a chance) calculate
					calculate(q, sign);
				sign=input; // after all these options - change the sign, and clear the complexAsString just in case.
				complexAsString.clear();
				break;
			case '=':
				if(!complexAsString.empty()) // if we have an arg wating in complexAsString, create obj and push
				{
					arg = atof(complexAsString.c_str());
					q.push(Complex(arg));
					complexAsString.clear();
				}
				clearScreen();	
				if(q.empty())	// if there are no args - do nothing
					break;
				else if(q.size() == 1) // if there is only one arg in queue, show it (if in Speak - read it), and get out
				{
					cout << q.front();
					if(speakMode)
						q.front().readComplex();
					break;
				}
				calculate(q, sign); // after these options if we are here - we need to calculate, show answes and maybe read.
				if(speakMode)
					q.front().readComplex();
				break;
			case 'h': // Goto Help Screen
				printHelp();
				printCalc(); // when get back print UI
				gotoxy(x_screen, y_screen);
				break;
			case 'q':
				/* Exit :=) */
				break;
			case 's': // toggle speack mode On <-> Off
				speakMode = !speakMode;
				toggleSpeak(speakMode);
				break;
			case 'r': // shows and maybe read the Real part in Complex (the only arg in queue)
				clearScreen();
				if(!q.empty()) //cant be more then one here - if so, the first in queue
				{
					cout << q.front().getReal();
					if(speakMode)
						Complex(q.front().getReal()).readComplex();
				}
				break; // if no input - get out
			case 'm': // shows the imaginery part of the Complex
				clearScreen();
				if(!q.empty()) //cant be more then one here - if so, the first in queue
				{
					cout << q.front().getImaginery();
					if(speakMode)
						Complex(q.front().getImaginery()).readComplex();
				}
				break;// if no input - get out
			case 'a': //   shows the abs() of  Complex ; and speak if on
				clearScreen();
				if(!q.empty())
				{
					Complex temp = abs(q.front());
					cout << temp;
					if(speakMode)
						temp.readComplex();
				}
				break;
			case 'c':  // clear all - screen, queue and complexAsString
				clearScreen();
				emptyQ(q);
				complexAsString.clear();
				break;
			case '0':
			case '1':						// if the input is a digit or '.' add every input to 
			case '2':						// complexAsSttring, to be able to 
			case '3':						// Create an object out of it.
			case '4':						// 
			case '5':						// only allowd in Regular Mode!
			case '6':						// 
			case '7':						// 
			case '8':
			case '9':
			case '.':
				if(complexAsString.empty())
					clearScreen();
				complexAsString.push_back(input);
				cout << input;
				break;
		}
	}while(input != 'q');
	return 0; // Exit App
}



void calculate(queue<Complex> & q, char sign) // Clculate according to the operator!
{
	gotoxy(x_screen, y_screen);
	Complex arg_1 = q.front();
	q.pop();
	Complex arg_2 = q.front();
	q.pop();
	switch(sign)
	{
		case '+':
			q.push(arg_1 + arg_2);
			cout << q.front();
			break;
		case '-':
			q.push(arg_1 - arg_2);
			cout << q.front();
			break;
		case '*':
			q.push(arg_1 * arg_2);
			cout << q.front();
			break;
		case '/':
			q.push(arg_1 / arg_2);
			
			cout << q.front();
			break;
		default: // Not getting here... if so - just exit to avoid Bugs!
			break;
	}
}

void clearScreen() // Clears the screen of calculator
{
	gotoxy(1,1); //Begining of Visual screen...
	cout << "                                                ";
	gotoxy(x_screen, y_screen);
}

void emptyQ(queue<Complex> &q) // empty the Queue
{
	while(!q.empty())
		q.pop();
}

void printCalc() //Print the UI
{
	system("cls");
	cout << " ================================================    Calculator Mode:" << endl;
	cout << "|                                                |" << endl;
	cout << " ================================================ " << endl;
	cout << "|  ___   ___   ___   ___      ___       ________ |" << endl;
	cout << "| | 7 | | 8 | | 9 | | + |    | C |     | abz(z) ||      Speak Mode:" << endl;
	cout << "|  ¯¯¯   ¯¯¯   ¯¯¯   ¯¯¯      ¯¯¯       ¯¯¯¯¯¯¯¯ |" << endl;
	cout << "|  ___   ___   ___   ___      ___        _______ |" << endl;
	cout << "| | 4 | | 5 | | 6 | | - |    | h |      | Speak ||" << endl;
	cout << "|  ¯¯¯   ¯¯¯   ¯¯¯   ¯¯¯      ¯¯¯        ¯¯¯¯¯¯¯ |" << endl;
	cout << "|  ___   ___   ___   ___      _________   ______ |" << endl;
	cout << "| | 1 | | 2 | | 3 | | * |    | real(z) | | M(z) ||" << endl;
	cout << "|  ¯¯¯   ¯¯¯   ¯¯¯   ¯¯¯      ¯¯¯¯¯¯¯¯¯   ¯¯¯¯¯¯ |" << endl;
	cout << "|  ___   ___   ___   ___      _________________  |" << endl;
	cout << "| | 0 | | . | | = | | / |    | Enter Compl(e)x | |" << endl;
	cout << "|  ¯¯¯   ¯¯¯   ¯¯¯   ¯¯¯      ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯  |" << endl;
	cout << " ================================================ " << endl;
	toggleMode(FALSE);
}

void printHelp(){
	system("cls"); //Clear the Screen.. and print help file
cout << " ,---------Press Any Key To Go Back------. " << endl;
cout << "|      Key     |          Outcome         |" << endl;
cout << "|-----------------------------------------|" << endl;
cout << "|       e      |   Start Complex Input    |     For A Complex Input " << endl;
cout << "|-----------------------------------------|   Tutorial Press h again." << endl;
cout << "|      1-0     |          Digits          |" << endl;
cout << "|-----------------------------------------|" << endl;
cout << "|       =      |          Equals          |" << endl;
cout << "|-----------------------------------------|" << endl;
cout << "|       +      |           Plus           |" << endl;
cout << "|-----------------------------------------|" << endl;
cout << "|       -      |           Minus          |" << endl;
cout << "|-----------------------------------------|" << endl;
cout << "|       /      |           Divide         |" << endl;
cout << "|-----------------------------------------|" << endl;
cout << "|       *      |       Multiplication     |" << endl;
cout << "|-----------------------------------------|" << endl;
cout << "|       r      |       Get real value     |" << endl;
cout << "|-----------------------------------------|" << endl;
cout << "|       m      |    Get imaginary value   |" << endl;
cout << "|-----------------------------------------|" << endl;
cout << "|       c      |        Clear Screen      |" << endl;
cout << "|-----------------------------------------|" << endl;
cout << "|       a      | Calculate absolute value |" << endl;
cout << "|-----------------------------------------|" << endl;
cout << "|       q      |       Exit Program       |" << endl;
cout << "|-----------------------------------------|" << endl;
cout << "|       c      |        Clear Screen      |" << endl;
cout << " ----------------------------------------'" << endl;


if(getch() == 'h') // if user want tutorial
	tutorial();


}

void tutorial() // Prints the tutorial
{
	int x = 46 , y = 6; //Position on screen...
	string tutorial = "Press \'e\' to enter Complex Mode...\nThen Type your Complex As So:\n\t\t2+2i        \nAnd Press Enter! - Thats all.";
	gotoxy(x, y);
	for(int i = 0; i < tutorial.length() ; i++)
	{
		if(tutorial[i] == '\n')
			gotoxy(x, ++y);
		else
			cout << tutorial[i];
		Sleep(100);
	}
	y+=2;
	gotoxy(x, y);
	cout << "Press Any Key To Go Back";
	getch();
}

void toggleMode(bool mod) // toggle with animation
{
	int numOfFrames = 3;
	string reg = "Regular [<<    ] Complex";
	string mid = "Regular [  <>  ] Complex";
	string comp = "Regular [    >>] Complex";
	stack<string> stk;
	PlaySound(TEXT("soundfiles\\toggle.wav"), NULL, SND_SYNC | SND_FILENAME);
	if(mod)
	{
		stk.push(comp);
		stk.push(mid);
		stk.push(reg);
	}
	else
	{
		stk.push(reg);
		stk.push(mid);
		stk.push(comp);
	}
	while(!stk.empty())
	{
		gotoxy(x_Mode, y_cMode);
		cout << stk.top();
		stk.pop();
		Sleep(30);
	}
	gotoxy(x_screen,y_screen);
}

void toggleSpeak(bool mod) // toggle with animation
{
	int numOfFrames = 3;
	string reg = "     On [<<    ] Off";
	string mid = "     On [  <>  ] Off";
	string spk = "     On [    >>] Off";
	stack<string> stk;
	if(!mod)
	{
		stk.push(spk);
		stk.push(mid);
		stk.push(reg);
	}
	else
	{
		stk.push(reg);
		stk.push(mid);
		stk.push(spk);
	}
	while(!stk.empty())
	{
		gotoxy(x_Mode, y_sMode);
		cout << stk.top();
		stk.pop();
		Sleep(30);
	}
	PlaySound(TEXT("soundfiles\\toggle.wav"), NULL, SND_SYNC | SND_FILENAME);
	gotoxy(x_screen,y_screen);
}


