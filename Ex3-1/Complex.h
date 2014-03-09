/*
 * File:	Complex.h					Version	:	1.0	(Stable)						() = type
 * Author: 	Sagi Dayan																	[] = variable name
 * Email:	sagidayan@gmail.com							 								[P] = private method
 *
 *								________________________JCE 2014______________________________
 */

#pragma once

#include <iostream>
#include <windows.h>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <sstream>
#include <mmsystem.h>
#include <conio.h>


using namespace std;

class Complex{
public:
	// Constructors
	Complex(double = 0, double = 0);
	Complex(const string &);
	// DeConstructor
	~Complex();
	// Getters
	double getReal() const;
	double getImaginery() const;
	// Functions
	void readComplex();
private:
	double real, imaginery;
	/**
	* All these methods are linked together to be able to read (speak out via Sound) a number.
	* by breaking up the 'Problem' into small managble sub Problems.
	* the main idea is to determen in what way to read a Digit in the Number, by the place of the digit in a
	* givven Queue.
	* 
	*/
	void readReal();
	void readImag();
	void readNumberFromQueue(queue<int>&);
	void readDigit(int, int);
	void readZero(int);
	void readOne(int);
	void readTow(int);
	void readThree(int);
	void readFore(int);
	void readFive(int);
	void readSix(int);
	void readSeven(int);
	void readEight(int);
	void readNine(int);
	void readTens(int);
	/* End of the Reading Methods */

};

/**
 * Overloading methods for the Comlex Class
 */
// Operator<<
std::ostream& operator<<(std::ostream& os, const Complex& complex);
// Operator+
Complex operator+(const Complex& first, const Complex& second);
Complex operator+(const double& d, const Complex& c);
Complex operator+(const Complex& c, const double& d);
// Operator-
Complex operator-(const Complex& first, const Complex& second);
Complex operator-(const double& d, const Complex& c);
Complex operator-(const Complex& c, const double& d);
// Operator/
Complex operator/(const Complex& first, const Complex& second);
Complex operator/(const double& d, const Complex& c);
Complex operator/(const Complex& c, const double& d);
// Operator*
Complex operator*(const Complex& first, const Complex& second);
Complex operator*(const double& d, const Complex& c);
Complex operator*(const Complex& c, const double& d);
//abs()
double abs(Complex);
