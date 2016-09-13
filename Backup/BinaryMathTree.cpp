#include "BinaryMathTree.h"
#include <queue>

Node::Node()
{
	type = NULL;
	op = NULL;
	number = NULL;
	left = NULL;
	right = NULL;
}

/*BinaryMathTree::Node::Node()
{
	type = NULL;
	op = NULL;
	number = NULL;
	left = NULL;
	right = NULL;
}*/

void BinaryMathTree::HelperDestructor(Node *&N)
{
	if(N->left != NULL)
		HelperDestructor(N->left);
	if(N->right != NULL)
		HelperDestructor(N->right);
	delete N;
}

BinaryMathTree::BinaryMathTree(){
	root = NULL;
}

BinaryMathTree::~BinaryMathTree(){
	HelperDestructor(root);
}

void BinaryMathTree::SetRoot(Node *root)
{
	this->root->type = root->type;
	this->root->op = root->op;
	this->root->number = root->number;
	this->root->left = root->left;
	this->root->right = root->right;
}

void BinaryMathTree::Breadth1st()
{
	queue<Node*> q;
	q.push(root);
	while(!q.empty())
	{
		if(q.front() != NULL)
		{
			if(q.front()->type == 1)
				cout<<"\t"<<q.front()->op;
			else if(q.front()->type == 0)
				cout<<"\t"<<q.front()->number;
		}
		if(q.front()->left != NULL)
			q.push(q.front()->left);
		if(q.front()->right != NULL)
			q.push(q.front()->right);
		q.pop();
	}
	cout<<endl<<endl;
}

template <typename T>
void BinaryMathTree::SetValue(T root)
{
	if(typeid(T).name() == "char")
	{
		this->root->op == root;
		this->root->number == NULL;
		this->root->type == 0;
	}
	else if(typeid(T).name() == "int" || typeid(T).name() == "double" || typeid(T).name() == "float" || typeid(T).name() == "long double" || typeid(T).name() == "long float")
	{
		this->root->number == root;
		this->root->op == NULL;
		this->root->type == 1;
	}
}

void BinaryMathTree::Insert(Node *N)
{
	Node **Np;
	Np = &root;
	queue<Node**> q;
	q.push(Np);
	while(!q.empty())
	{
		if(*q.front() == NULL)
		{
			*q.front() = new Node;
			(*q.front())->type = N->type;
			(*q.front())->op = N->op;
			(*q.front())->number = N->number;
			(*q.front())->left = N->left;
			(*q.front())->right = N->right;
			break;
		}
		if((*q.front())->type == 1)   //type is operator
		{
			Np = &(*q.front())->left;
			q.push(Np);
			Np = &(*q.front())->right;
			q.push(Np);
			q.pop();
		}

		else if((*q.front())->type == 0)   //type is operand
		{
			q.pop();
			continue;
		}
	}
}