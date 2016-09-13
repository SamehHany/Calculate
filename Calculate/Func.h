#include "ExpTree.h"

class Func
{
private:
	ExpTree T;

public:
	Func();
	Func(string e);
	void read(string e);
	double solve(double x);
	void clear();
	bool empty();
};