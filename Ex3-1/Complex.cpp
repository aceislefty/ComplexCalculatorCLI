/*
 * File:	Complex.cpp					Version	:	1.0	(Stable)						() = type
 * Author: 	Sagi Dayan																	[] = variable name
 * Email:	sagidayan@gmail.com							 								[P] = private method
 *
 *								________________________JCE 2014______________________________
 */
#include "Complex.h"

/**
* Constructors
*/
Complex::Complex(double r, double i) //Defaults: r = 0, i = 0 (As mentiond in the header file)
{
	this->real = r;
	this->imaginery = i;
}

Complex::Complex(const string &str) //Constructing a Complex object from a given String.
{
	int pEndR, pEndI;
	int i = 0;
	for(; ( ('0' <= str[i] && str[i] <= '9') || str[i] == '.') ; i++);
	pEndR = i;
	for(i++; ( ('0' <= str[i] && str[i] <= '9') || str[i] == '.') ; i++);
	pEndI = i;
	string strReal = str.substr(0, pEndR);
	string strIm = str.substr(pEndR, (pEndI - pEndR));
	this->real = atof(strReal.c_str());
	this->imaginery = atof(strIm.c_str());
}

// Empty Decontructor... just for proper Programing pactice 
Complex::~Complex()
{
	// EMPTY //
}

/**
 * Getters:
 */
double Complex::getReal() const
{
	return this->real;
}

double Complex::getImaginery() const
{
	return this->imaginery;
}


    /**
	* All these methods are linked together to be able to read (speak out via Sound) a number.
	* by breaking up the 'Problem' into small managble sub Problems.
	* the main idea is to determen in what way to read a Digit in the Number, by the place of the digit in a
	* givven Queue.
	* 
	*/

void Complex::readComplex() // Reading [this] Complex Object
{
	readReal(); //Read the Real Part
	readImag(); //Read the imaginary Part
}

void Complex::readReal() 																// Converting this.real into
{																						// a Queue of digits.
	if(real == 0)																		// then sending it to a methods
	{																					// that will be able to read a
		PlaySound(TEXT("soundfiles\\0.wav"), NULL, SND_SYNC | SND_FILENAME);			// Queue.
		return;																		
	}																				
	double re_temp = abs(real);														
	if(real < 0)																	
		PlaySound(TEXT("soundfiles\\minus.wav"), NULL, SND_SYNC | SND_FILENAME);	
	string numAsStr;																
	queue<int> intReal;																
	queue<int> floatReal;															
	int i = 0;																		
	bool hasFloat = false;															

	stringstream stream;
	stream << re_temp;
	numAsStr = stream.str();
	
	for(; i < numAsStr.length() ; i++)
	{
		if(numAsStr[i] != '.')
			intReal.push(numAsStr[i] - '0');
		else
			hasFloat = true;
		if(hasFloat)
			break;
	}
	if(hasFloat)
		for(i++; i < numAsStr.length() ; i++)
		{
			if(numAsStr[i] != 'i')
				floatReal.push(numAsStr[i] - '0');
		}

		readNumberFromQueue(intReal);
		if(hasFloat)
			PlaySound(TEXT("soundfiles\\point.wav"), NULL, SND_SYNC | SND_FILENAME);
		readNumberFromQueue(floatReal);
}

void Complex::readImag()																	// Converting this.imaginery into
{																							// a Queue of digits.
	if(imaginery == 0)																		// then sending it to a methods
		return;																				// that will be able to read a
	double image = abs(imaginery);															// Queue.
	if(imaginery > 0)																		
		PlaySound(TEXT("soundfiles\\plus.wav"), NULL, SND_SYNC | SND_FILENAME);				
	else																					
		PlaySound(TEXT("soundfiles\\minus.wav"), NULL, SND_SYNC | SND_FILENAME);			
	string numAsStr;
	queue<int> intImage;
	queue<int> floatImage;
	int i = 0;
	bool hasFloat = false;

	stringstream stream;
	stream << image;
	numAsStr = stream.str();
	
	for(; i < numAsStr.length() ; i++)
	{
		if(numAsStr[i] != '.')
			intImage.push(numAsStr[i] - '0');
		else
			hasFloat = true;
		if(hasFloat)
			break;
	}
	if(hasFloat)
		for(i++; i < numAsStr.length() ; i++)
		{
			if(numAsStr[i] != 'i')
				floatImage.push(numAsStr[i] - '0');
		}

		readNumberFromQueue(intImage);
		if(hasFloat)
			PlaySound(TEXT("soundfiles\\point.wav"), NULL, SND_SYNC | SND_FILENAME);
		readNumberFromQueue(floatImage);
		PlaySound(TEXT("soundfiles\\i.wav"), NULL, SND_SYNC | SND_FILENAME);
}


void Complex::readNumberFromQueue(queue<int> &stk) // according to the queue size and the first element in queue it will send
{												   // the digit to the right method for reading!
	if(stk.empty())								   // Untill the queue is empty
		return;

	while(!stk.empty())
	{
		switch(stk.front())
		{
		case 1:
			if((stk.size() != 8) && (stk.size() != 5) && (stk.size() != 2))  // 8, 5, 2 are places that we can have "10" - "19"
			{																 // there for we need to handle those areas diffarently
				readDigit(stk.front(), stk.size());
				switch (stk.size())
				{
				case 4:
					PlaySound(TEXT("soundfiles\\thousand.wav"), NULL, SND_SYNC | SND_FILENAME);
					break;
				case 7:
					PlaySound(TEXT("soundfiles\\million.wav"), NULL, SND_SYNC | SND_FILENAME);
				default:
					break;
				}
			}else
			{
				stk.pop();
				readTens(stk.front());
				switch (stk.size())
				{
				case 4:
					PlaySound(TEXT("soundfiles\\thousand.wav"), NULL, SND_SYNC | SND_FILENAME);
					break;
				case 7:
					PlaySound(TEXT("soundfiles\\million.wav"), NULL, SND_SYNC | SND_FILENAME);
				default:
					break;
				}
			}
			break;
		default:
			readDigit(stk.front(), stk.size());
			switch (stk.size())
			{
			case 4:
				PlaySound(TEXT("soundfiles\\thousand.wav"), NULL, SND_SYNC | SND_FILENAME);
				break;
			case 7:
				PlaySound(TEXT("soundfiles\\million.wav"), NULL, SND_SYNC | SND_FILENAME);
			default:
				break;
			}
			break;
		}
		stk.pop();
	}
}

void Complex::readDigit(int digit, int place) // gets the digit and its place
{
	switch(digit)
	{
	case 0:
		readZero(place);
		break;
	case 1:
		readOne(place);
		break;
	case 2:
		readTow(place);
		break;
	case 3:
		readThree(place);
		break;
	case 4:
		readFore(place);
		break;
	case 5:
		readFive(place);
		break;
	case 6:
		readSix(place);
		break;
	case 7:
		readSeven(place);
		break;
	case 8:
		readEight(place);
		break;
	case 9:
		readNine(place);
		break;
	}
}

void Complex::readZero(int place) // reads zero
{
	/* Nothing Yet */
	return;
}

void Complex::readTens(int secondDigit) // reads 10 - 19 AKA Tens
{
	switch(secondDigit)
	{
	case 0:
		PlaySound(TEXT("soundfiles\\10.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 1:
		PlaySound(TEXT("soundfiles\\11.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 2:
		PlaySound(TEXT("soundfiles\\12.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 3:
		PlaySound(TEXT("soundfiles\\13.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 4:
		PlaySound(TEXT("soundfiles\\14.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 5:
		PlaySound(TEXT("soundfiles\\15.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 6:
		PlaySound(TEXT("soundfiles\\16.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 7:
		PlaySound(TEXT("soundfiles\\17.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 8:
		PlaySound(TEXT("soundfiles\\18.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 9:
		PlaySound(TEXT("soundfiles\\19.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	}

}
void Complex::readOne(int place) // Read One or One Hundred
{
	switch(place)
	{
	case 1:
	case 4:
	case 7:
		PlaySound(TEXT("soundfiles\\1.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 3:
	case 6:
	case 9:
		PlaySound(TEXT("soundfiles\\100.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	}
}

void Complex::readTow(int place) // Read tow or tow hundred or twenty
{
	switch(place)
	{
	case 1:
	case 4:
	case 7:
		PlaySound(TEXT("soundfiles\\2.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 2:
	case 5:
	case 8:
		PlaySound(TEXT("soundfiles\\20.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 3:
	case 6:
	case 9:
		PlaySound(TEXT("soundfiles\\200.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	}
}

void Complex::readThree(int place) //reads three or three hundred or thirty
{
	switch(place)
	{
	case 1:
	case 4:
	case 7:
		PlaySound(TEXT("soundfiles\\3.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 2:
	case 5:
	case 8:
		PlaySound(TEXT("soundfiles\\30.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 3:
	case 6:
	case 9:
		PlaySound(TEXT("soundfiles\\300.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	}
}

void Complex::readFore(int place) // Reads fore, fore Hundred, or Forty
{
	switch(place)
	{
	case 1:
	case 4:
	case 7:
		PlaySound(TEXT("soundfiles\\4.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 2:
	case 5:
	case 8:
		PlaySound(TEXT("soundfiles\\40.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 3:
	case 6:
	case 9:
		PlaySound(TEXT("soundfiles\\400.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	}
}

void Complex::readFive(int place) // Reads Five, fifty, five hundred
{
	switch(place)
	{
	case 1:
	case 4:
	case 7:
		PlaySound(TEXT("soundfiles\\5.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 2:
	case 5:
	case 8:
		PlaySound(TEXT("soundfiles\\50.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 3:
	case 6:
	case 9:
		PlaySound(TEXT("soundfiles\\500.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	}
}

void Complex::readSix(int place) // Reads six, six hundred, sixty
{
	switch(place)
	{
	case 1:
	case 4:
	case 7:
		PlaySound(TEXT("soundfiles\\6.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 2:
	case 5:
	case 8:
		PlaySound(TEXT("soundfiles\\60.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 3:
	case 6:
	case 9:
		PlaySound(TEXT("soundfiles\\600.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	}
}


void Complex::readSeven(int place) // Reads seven, seven hundred, seventy
{
	switch(place)
	{
	case 1:
	case 4:
	case 7:
		PlaySound(TEXT("soundfiles\\7.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 2:
	case 5:
	case 8:
		PlaySound(TEXT("soundfiles\\70.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 3:
	case 6:
	case 9:
		PlaySound(TEXT("soundfiles\\700.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	}
}

void Complex::readEight(int place) // Reads Eight, ehigty, eight hundred
{
	switch(place)
	{
	case 1:
	case 4:
	case 7:
		PlaySound(TEXT("soundfiles\\8.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 2:
	case 5:
	case 8:
		PlaySound(TEXT("soundfiles\\80.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 3:
	case 6:
	case 9:
		PlaySound(TEXT("soundfiles\\800.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	}
}


void Complex::readNine(int place) // Reads nine, nine hundred, ninty
{
	switch(place)
	{
	case 1:
	case 4:
	case 7:
		PlaySound(TEXT("soundfiles\\9.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 2:
	case 5:
	case 8:
		PlaySound(TEXT("soundfiles\\90.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	case 3:
	case 6:
	case 9:
		PlaySound(TEXT("soundfiles\\900.wav"), NULL, SND_SYNC | SND_FILENAME);
		break;
	}
}
/**
* Start of overloading Operators
*/
// Operator<<
std::ostream& operator<<(std::ostream& os, const Complex& complex) 
{
	if(complex.getImaginery()>0)
		os << complex.getReal() << "+" << complex.getImaginery() << "i";
	else if(complex.getImaginery() == 0)
		os << complex.getReal();
	else
		os << complex.getReal()  << complex.getImaginery() << "i";
	return os ;
}
// Operator+
Complex operator+(const Complex& first, const Complex& second)
{
	return Complex(first.getReal() + second.getReal() , first.getImaginery() + second.getImaginery());
}
Complex operator+(const double& d, const Complex& c) 
{
	return Complex(d + c.getReal() , c.getImaginery());
}
Complex operator+(const Complex& c, const double& d) 
{
	return Complex(c.getReal() + d , c.getImaginery());
}
// Operator-
Complex operator-(const Complex& first, const Complex& second)
{
	return Complex(first.getReal() - second.getReal() , first.getImaginery() - second.getImaginery());
}
Complex operator-(const double& d, const Complex& c) 
{
	return Complex(d - c.getReal() , 0 - c.getImaginery()); //Reversing The imaginery component...0-i
}
Complex operator-(const Complex& c, const double& d) 
{
	return Complex(c.getReal() - d , c.getImaginery());
}
// Operator/
Complex operator/(const Complex& first, const Complex& second)
{
	double denominator = ( second.getReal() * second.getReal() ) +  ( second.getImaginery() * second.getImaginery() );
	//check if legal
	if(denominator == 0)
		return Complex(); // return 0+0i == error for now!
	//else...
	double newReal = (first.getReal()*second.getReal() + first.getImaginery()*second.getImaginery()) / denominator;
	double newImaginery = ((-first.getReal())*second.getImaginery() + first.getImaginery()*second.getReal()) / denominator;
	return Complex(newReal , newImaginery);
}
Complex operator/(const double& d, const Complex& c) 
{
	return Complex(d, 0) / c;
}
Complex operator/(const Complex& c, const double& d) 
{
	if(d == 0)
		return Complex(); // return 0+0i == error for now!
	//else...
	return Complex(c.getReal() / d , c.getImaginery() / d);
}
// Operator*
Complex operator*(const Complex& first, const Complex& second)
{
	double newReal = (first.getReal()*second.getReal() - first.getImaginery()*second.getImaginery());
	double newImaginery = (first.getImaginery()*second.getReal() + first.getReal()*second.getImaginery());
	return Complex(newReal , newImaginery);
}
Complex operator*(const double& d, const Complex& c) 
{
	return Complex(d * c.getReal() , d * c.getImaginery());
}
Complex operator*(const Complex& c, const double& d) 
{
	return Complex(d * c.getReal() , d * c.getImaginery());
}

// Overiding/adding cmath abs() for Complex Class - this function will be global.
double abs(Complex c)
{
	return sqrt( pow(c.getReal(), 2) + pow(c.getImaginery(), 2) );
}

/**
* End of overloading Operators
*/