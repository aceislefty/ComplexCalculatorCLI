#include "Tester.h"

void startTest()
{
	Complex a(4, 6);
	Complex b(6, -8);
	double d = 3;
	cout << "First: " << a << "\tSecond: "<< b << "\tDouble: "<< d << endl << endl;
	Complex c = a + b;
	cout << "("<< a << ") + "<< "("<< b << ") = " << c << endl;
	c = d + a;
	cout << "("<< d << ") + "<< "("<< a << ") = " << c << endl;
	c = b + a;
	cout << "("<< b << ") + "<< "("<< a << ") = " << c << endl;
	c = a + d;
	cout << "("<< a << ") + "<< "("<< d << ") = " << c << endl;
	
	a = Complex(-3,9);
	b = Complex(6,-3);
	d = 25;
	cout <<"=======================================================\n";
	cout << "First: " << a << "\tSecond: "<< b << "\tDouble: "<< d << endl << endl;
	c = a - b;
	cout << "("<< a << ") - "<< "("<< b << ") = " << c << endl;
	c = d - a;
	cout << "("<< d << ") - "<< "("<< a << ") = " << c << endl;
	c = b - a;
	cout << "("<< b << ") - "<< "("<< a << ") = " << c << endl;
	c = a - d;
	cout << "("<< a << ") - "<< "("<< d << ") = " << c << endl;

	a = Complex(4,2);
	b = Complex(-3,3);
	d = 5;
	cout <<"=======================================================\n";
	cout << "First: " << a << "\tSecond: "<< b << "\tDouble: "<< d << endl << endl;
	c = a * b;
	cout << "("<< a << ") * "<< "("<< b << ") = " << c << endl;
	c = d * a;
	cout << "("<< d << ") * "<< "("<< a << ") = " << c << endl;
	c = b * a * 0;
	cout << "("<< b << ") * "<< "("<< a << ")" <<" * 0 = " << c << endl;
	c = a * d;
	cout << "("<< a << ") * "<< "("<< d << ") = " << c << endl;

	a = Complex(8,8);
	b = Complex(2,2);
	d = 4;
	cout <<"=======================================================\n";
	cout << "First: " << a << "\tSecond: "<< b << "\tDouble: "<< d << endl << endl;
	c = a / b;
	cout << "("<< a << ") / "<< "("<< b << ") = " << c << endl;
	c = d / a;
	cout << "("<< d << ") / "<< "("<< a << ") = " << c << endl;
	c = b / a;
	cout << "("<< b << ") / "<< "("<< a << ")" <<" = " << c << endl;
	c = a / d;
	cout << "("<< a << ") / "<< "("<< d << ") = " << c << endl;

	a = Complex(2, 3);
	b = Complex(2,-2);
	d = 4;
	cout <<"=======================================================\n";
	cout << "First: " << a << "\tSecond: "<< b << "\tDouble: "<< d << endl << endl;
	d = abs(a);
	cout << "abs("<<a<<") = " << d << endl;
	d = abs(b);
	cout << "abs("<<b<<") = " << d << endl;
	d = abs(-5);
	cout << "abs(-5) = " << d << endl;

	a = Complex("3.98+5.67i");
	cout << "***** From String ******** " << a <<" **************" << endl;
	cout << "Just one double in Ctor  "<< Complex(18345.5645,-12121) << endl;
	Complex(18345.5645, -12121).readComplex();

}