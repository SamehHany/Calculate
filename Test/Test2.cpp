#include "ExpTree.h"


int main()
{
	string *p;
	int len;
	char skip[] = {' ', '\t', '\n'};
	char tok[] = {'+', '-', '*', '/', '^', '%', '(', ')', '[', ']', '<', '>', ';'};
	int len1 = sizeof(skip)/sizeof(char);
	int len2 = sizeof(tok)/sizeof(char);
	parse("  (123 + 456)   + 789cos(x)   +2x  ", skip, len1, tok, len2, p, len);
	for(int i = 0; i < len; i++)
		cout<<" "<<p[i]<<" ";
	cout<<endl<<len<<endl;

	delete [] p;
	return 0;
}