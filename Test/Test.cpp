#include "ExpTree.h"

void Ins(Node *&N, char type, char op, double number)
{
	N->type = type;
	N->op = op;
	N->number = number;
}


int main()
{
	ExpTree T;
	Node *n[9];
	int i;
	for(i = 0; i < 9; i++)
		n[i] = new Node;

	Ins(n[0], 0, '+', NULL);
	Ins(n[1], 0, '+', NULL);
	Ins(n[2], 1, NULL, 1);
	Ins(n[3], 1, NULL, 2);
	Ins(n[4], 0, '-', NULL);
	Ins(n[5], 0, '-', NULL);
	Ins(n[6], 1, NULL, 3);
	Ins(n[7], 1, NULL, 4);
	Ins(n[8], 1, NULL, 5);

	for(i = 0; i < 9; i++)
		T.Insert(n[i]);
	//T.clear();
	T.Breadth1st();

	for(i = 0; i < 9; i++)
		delete n[i];

	return 0;
}