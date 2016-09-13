#include "ExpTree.h"


//log(100)*(123+(422+4242*4534-5)*cos(1.5)-4 - 3 +5/6 * 3) % 7*asin(0,5)
//log(100)*3^2+5^(4+6)*(123+(422+4242*4534-5)*cos(1.5)-4 - 3 +5/6 * 3) % 7*asin(0.5) / ln(5)
//log(100)*log(2, 1048576)*3^2+5^(4+6)*(123+(422+4242*4534-5)*cos(1.5)-4 4324*342+cos(log(2, 8))- 3 +5/6 * 3) *asin(0.5) / ln(5)
int main()
{
	cout.precision(15);
	ExpTree T;
	//string e;
	//getline(cin, e);
	T.BuildExp("log(x^ 2)  - 2*x^3+(cos(sin(atan(2*x)))^2");
	//x = 3;
	//T.subst("x", 3);
	T.Breadth1st();
	T.InOrder();
	cout<<endl<<T.solve(3)<<endl;

	return 0;
}