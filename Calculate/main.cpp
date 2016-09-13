//Name: Sameh Hany Ahmed Abdelrehim
//Program Number: 691


#include "Func.h"
#include <sstream>

Func F;


void Bisection(double a, double b, double tol)
{
	int i;
	double fp, p, prev;
	stringstream ss(stringstream::in | stringstream::out);
	cout<<"i\tai\t\tbi\t\tPi\t\tf(Pi)\t\tError"<<endl<<endl;
	for(i = 0 ; ; i++)
	{
		cout.precision(6);
		p = (a+b)/2;
		fp = F.solve(p);
		cout<<i<<"\t"<<a;
		ss<<a;
		if(ss.str().length() <= 7)
			cout<<"\t\t";
		else
			cout<<"\t";
		cout<<b;
		ss.str("");
		ss<<b;
		if(ss.str().length() <= 7)
			cout<<"\t\t";
		else
			cout<<"\t";
		cout<<p;
		ss.str("");
		ss<<p;
		if(ss.str().length() <= 7)
			cout<<"\t\t";
		else
			cout<<"\t";
		cout<<fp;
		if(i == 0)
			cout<<endl<<endl;
		else if(i > 0)
		{
			ss.str("");
			ss<<fp;
			if(ss.str().length() <= 7)
				cout<<"\t\t";
			else
				cout<<"\t";
			cout.precision(2);
			cout<<abs(prev - p)<<endl<<endl;
		}
		ss.str("");
		if(abs(fp) < abs(tol))
			break;
		if(F.solve(a)*fp > 0)
			a = p;
		else b = p;
		prev = p;
	}
}


void Secant(double a, double b, double tol)
{
	int i;
	double fp, p, prev;
	stringstream ss(stringstream::in | stringstream::out);
	cout<<"i\tPi\t\t\tf(Pi)\t\t\tError"<<endl<<endl;
	cout<<"\t"<<a<<"\t\t\t"<<F.solve(a)<<endl<<endl;
	for(i = 0; ; i++)
	{
		cout.precision(6);
		p = b - ((F.solve(b))/(F.solve(b) - F.solve(a))) * (b - a);
		fp = F.solve(p);
		
		cout<<i<<"\t"<<p;
		ss<<p;
		if(ss.str().length() <= 7)
			cout<<"\t\t\t";
		else
			cout<<"\t\t";
		cout<<fp;
		if(i > 0)
		{
			ss.str("");
			ss<<fp;
			if(ss.str().length() <= 7)
				cout<<"\t\t\t";
			else
				cout<<"\t\t";
			cout<<abs(prev - p)<<endl<<endl;
		}
		else cout<<endl<<endl;
		ss.str("");
		if(abs(fp) < abs(tol))
			break;
		if(i % 2 == 0)
			a = p;
		else b = p;
		prev = p;
	}
}



void FalsePosition(double a, double b, double tol)
{
	int i;
	double fp, p, prev;
	stringstream ss(stringstream::in | stringstream::out);
	cout<<"i\tai\t\tbi\t\tPi\t\tf(Pi)\t\tError"<<endl<<endl;
	for(i = 0 ; ; i++)
	{
		cout.precision(6);
		p = b - ((F.solve(b))/(F.solve(b) - F.solve(a))) * (b - a);
		fp = F.solve(p);
		cout<<i<<"\t"<<a;
		ss<<a;
		if(ss.str().length() <= 7)
			cout<<"\t\t";
		else
			cout<<"\t";
		cout<<b;
		ss.str("");
		ss<<b;
		if(ss.str().length() <= 7)
			cout<<"\t\t";
		else
			cout<<"\t";
		cout<<p;
		ss.str("");
		ss<<p;
		if(ss.str().length() <= 7)
			cout<<"\t\t";
		else
			cout<<"\t";
		cout<<fp;
		if(i == 0)
			cout<<endl<<endl;
		else if(i > 0)
		{
			ss.str("");
			ss<<fp;
			if(ss.str().length() <= 7)
				cout<<"\t\t";
			else
				cout<<"\t";
			cout.precision(2);
			cout<<abs(prev - p)<<endl<<endl;
		}
		ss.str("");
		if(abs(fp) < abs(tol))
			break;
		if(F.solve(a)*fp > 0)
			a = p;
		else b = p;
		prev = p;
	}
}



void NewRaph(double a, double tol)
{
	int i;
	double fp, p, prev, diff, fa, inc;
	const double d = 0.00001;
	stringstream ss(stringstream::in | stringstream::out);
	cout<<"i\tPi\t\t\tf(Pi)\t\t\tError"<<endl<<endl;
	cout<<"\t"<<a<<"\t\t\t"<<F.solve(a)<<endl<<endl;
	prev = a;
	for(i = 0; ; i++)
	{
		cout.precision(6);

		fa = F.solve(a);
		inc = d*fa;
		diff = (F.solve(prev + inc) - F.solve(prev - inc))/((prev + inc) - (prev - inc));
		p = prev - F.solve(prev)/diff;
		fp = F.solve(p);
		
		cout<<i<<"\t"<<p;
		ss<<p;
		if(ss.str().length() <= 7)
			cout<<"\t\t\t";
		else
			cout<<"\t\t";
		cout<<fp;
		if(i > 0)
		{
			ss.str("");
			ss<<fp;
			if(ss.str().length() <= 7)
				cout<<"\t\t\t";
			else
				cout<<"\t\t";
			cout<<abs(prev - p)<<endl<<endl;
		}
		else cout<<endl<<endl;
		ss.str("");
		if(abs(fp) < abs(tol))
			break;
		prev = p;
	}
}




void run()
{
	double a, b, tol;
	string input;
	while(true)
	{
		input.clear();
		cout<<"Enter function"<<endl;
		cin>>ws;
		getline(cin, input);

		F.clear();
		F.read(input);
		input.clear();

		if(!F.empty())
		{

			cout<<endl<<"Specify which method to use"<<endl;
			getline(cin, input);
			if(input == "bisection")
			{
				cout<<endl<<"Enter range"<<endl;
				cin>>a;
				cin>>b;
				cout<<endl<<"Enter tolerance"<<endl;
				cin>>tol;
				Bisection(a, b, tol);
			}

			else if(input == "secant")
			{
				cout<<endl<<"Enter range"<<endl;
				cin>>a;
				cin>>b;
				cout<<endl<<"Enter tolerance"<<endl;
				cin>>tol;
				Secant(a, b, tol);
			}

			else if(input == "false position")
			{
				cout<<endl<<"Enter range"<<endl;
				cin>>a;
				cin>>b;
				cout<<endl<<"Enter tolerance"<<endl;
				cin>>tol;
				FalsePosition(a, b, tol);
			}

			else if(input == "newton" || input == "newton-raphson")
			{
				cout<<endl<<"Enter initial value"<<endl;
				cin>>a;
				cout<<endl<<"Enter tolerance"<<endl;
				cin>>tol;
				NewRaph(a, tol);
			}


			cout<<endl<<endl;
		}
	}
}



int main()
{
	//cout.precision(15);
	//string e;
	//getline(cin, e);
	//F.read("e^6+4*pi-sin(2*pi*2)");
	run();
	//cout<<endl<<F.solve(3)<<endl;

	return 0;
}



//log(100)*log(2, 1048576)*3^2+5^(4+6)*(123+(422+4242*4534-5)*cos(1.5)-4+ 4324*342+cos(log(2, 8))- 3 +5/6 * 3) *asin(0.5) / ln(5)