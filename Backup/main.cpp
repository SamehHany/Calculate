#include "BinaryMathTree.h"
#include <queue>
void SetNode(Node *&x, bool type, char op, double number)
{
	x = new Node;
	x->type = type;
	x->op = op;
	x->number = number;
}

int main()
{
	Node *n[9];
	BinaryMathTree T;
	SetNode(n[0], 1, '+', NULL);
	SetNode(n[1], 1, '+', NULL);
	SetNode(n[2], 0, NULL, 1);
	SetNode(n[3], 0, NULL, 2);
	SetNode(n[4], 1, '-', NULL);
	SetNode(n[5], 1, '-', NULL);
	SetNode(n[6], 0, NULL, 3);
	SetNode(n[7], 0, NULL, 4);
	SetNode(n[8], 0, NULL, 5);

	int i;

	for(i = 0; i < 9; i++)
		T.Insert(n[i]);
	T.Breadth1st();
	SetNode(T.root->right->left, 0, NULL, 6);
	SetNode(T.root->right->right, 0, NULL, 7);
	T.Breadth1st();
	for(i = 0; i < 9; i++)
		delete n[i];

	/*for(i = 0; i < 9; i++)
	{
		cout<<" ";
		if(n[i]->type == 0)
			cout<<n[i]->number;
		else if(n[i]->type == 1)
			cout<<n[i]->op;
	}
	cout<<endl<<endl;*/
	//cout<<typeid(int).name()<<endl;
	return 0;
}