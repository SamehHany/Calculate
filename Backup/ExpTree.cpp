#include <sstream>
#include <math.h>
#include <queue>
#include <stack>
#include "ExpTree.h"



bool memberOf(char m, char *a, int size)
{
	int i;
	for(i = 0; i < size; i++)
		if(a[i] == m)
			return true;
	return false;
}

//returns true if input character is a digit or a point
bool isNum(char x)
{
	if((x >= 48 && x <= 57) || x == '.')
		return true;
	else return false;
}


bool strIsNum(string s)
{
	int i;
	int len = s.length();
	for(i = 0; i < len; i++)
	{
		if(!isNum(s[i]))
			return false;
	}
	return true;
}

//returns true if input character is an alphabetic character
bool isAlph(char x)
{
	if((x >= 65 && x <= 90) || (x >= 97 && x <= 122))
		return true;
	else return false;
}

void parse(string e, char* skip, int lenS, char* tok, int lenT, string *&parsed, int &lenP)
{
	int i, j; //used for indexing in loops
	if(e[e.length() - 1] != '\0')
		e += '\0';
	int len = e.length();
	string *save;
	string *temp; //holds a temporary array of strings
	int pLen = 15;	//initial guess of the value of 'sizeP'
	int I = 0;	//index to the location to store the next token in
	int iT = 0; //index to the location to start tokenizing from in 'e'
	save = new string[pLen];
	string token;
	bool inTok = false; //is true if the loop is within a token, and false otherwise
	bool Exc = false; //is true when there is an exception to tokenize at
	for(i = 0; i < len; i++)
	{
		if(!memberOf(e[i], skip, lenS) && !memberOf(e[i], tok, lenT) && i+1 < len && !Exc)
		{
			if(!inTok)
			{
				iT = i; //So the function knows where does the next token start from
				inTok = true;
			}

			//if a number was followed by a variable or a function, then make an exception & tokenize
			if(i-1 < len)
			{
				if(isNum(e[i]) && isAlph(e[i+1]))
					Exc = true;
			}
			continue;
		}
		
		else
		{
			if(inTok) //if the last iteration was within a token
			{
				if(I + 1 >= pLen)
				{
					temp = new string [pLen];
					for(j = 0; j < pLen; j++)
						temp[j] = save[j];
					delete [] save;
					save = new string[pLen + 15];
					for(j = 0; j < pLen; j++)
						save[j] = temp[j];
					pLen += 15;
					delete [] temp;
				}
				save[I].append(e, iT, i-iT);
				I++; //so the next token is stored in the next location in the array

				inTok = false;
			}

			if(memberOf(e[i], tok, lenT))
			{
				save[I] = e[i];
				I++;
			}

			if(Exc)
			{
				Exc = false;
				iT = i;
				inTok = true;
			}

		}
	}
	

	parsed = new string[I];

	for(i = 0; i < I; i++)
		parsed[i] = save[i];
	lenP = I;

	delete [] save;
}


int charToDig(char x)
{
	switch(x)
	{
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	}
}

//convert a string of digits to double
double strToDbl(string n)
{
	int i, len = n.length();
	double result = 0;
	int point = len; //contains an index to the decimal point
	bool p = false; //is true if there is a decimal point in the number
	bool failed = false; //is true if the string couldn't be converted to double
	for(i = 0; i < len; i++)
	{
		if(n[i] == '.')
		{
			point = i;
			break;
		}
	}
	for(i = 0; i < len; i++)
	{
		if(n[i] == '.')
		{
			if(!p)
				p = true;
			else if(p)
			{
				failed = true;
				break;
			}
		}
		else
		{
			if(i < point)
				result += charToDig(n[i]) * pow((double)10, (double)(point - (i + 1)));
			else if(i > point)
				result += charToDig(n[i]) * pow((double)10, (double)(point - i));
		}
	}

	if(!failed)
		return result;
	else return NULL;
}


/*ExpTree::*/Node::Node()
{
	type = NULL;
	op = NULL;
	number = NULL;
	var = "";
	left = NULL;
	right = NULL;
}

void ExpTree::deleteNodes(Node *&N)
{
	if(N != NULL)
	{
		if(N->left != NULL)
			deleteNodes(N->left);
		if(N->right != NULL)
			deleteNodes(N->right);
		delete N;
	}
}

void ExpTree::SetLength(string e, int &a, int &b)
{
	bool p = false;	//determines if a point exists in a number
	bool inN = false;	//determines whether the loop is currently indexing a number
	int cn = 0;		//counts the number of operands
	int co = 0;		//counts the number of operators
	int len = e.length();
	int i;
	for(i = 0; i < len; i++)
	{
		if(inN == false)
		{
			if(e[i] == '0' || e[i] == '1' || e[i] == '2' || e[i] == '3' || e[i] == '4' || e[i] == '5' || e[i] == '6' || e[i] == '7' || e[i] == '8' || e[i] == '9' || e[i] == '.')
			{
				inN = true;
				cn++;
			}
			else if(e[i] == '+' || e[i] == '-' || e[i] == '*' || e[i] == '/' || e[i] == '%')
				co++;
		}
		else if(inN == true)
		{
			if(e[i] != '0' && e[i] != '1' && e[i] != '2' && e[i] != '3' && e[i] != '4' && e[i] != '5' && e[i] != '6' && e[i] != '7' && e[i] != '8' && e[i] != '9')
			{
				if(e[i] == '.')
				{
					if(p == true)
					{
						inN == false;
						p == false;
					}
					else if(p == false)
						p == true;
				}
			}
		}
	}
	a = cn;
	b = co;
}


void ExpTree::HelperInsert(Node *N, Node *&R)
{
	Node **Np;
	Np = &R;
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
			(*q.front())->var = N->var;
			(*q.front())->left = N->left;
			(*q.front())->right = N->right;
			break;
		}

		if((*q.front())->type == 0)   //type is operator
		{
			Np = &(*q.front())->left;
			q.push(Np);
			Np = &(*q.front())->right;
			q.push(Np);
			q.pop();
		}

		else if((*q.front())->type == 1 || (*q.front())->type == 2)   //type is operand or variable
		{
			q.pop();
			continue;
		}
	}
}


ExpTree::ExpTree(){
	root = NULL;
}

ExpTree::~ExpTree(){
	deleteNodes(root);
}

void ExpTree::clear(){
	deleteNodes(root);
}

void ExpTree::Breadth1st()
{
	queue<Node*> q;
	q.push(root);
	while(!q.empty())
	{
		if(q.front() != NULL)
		{
			if(q.front()->type == 0)		//type is operator
				cout<<" "<<q.front()->op;
			else if(q.front()->type == 1)	//type is operand
				cout<<" "<<q.front()->number; 
			else if(q.front()->type == 2)	//type is expression string
				cout<<" "<<q.front()->var;
		}
		if(q.front()->left != NULL)
			q.push(q.front()->left);
		if(q.front()->right != NULL)
			q.push(q.front()->right);
		q.pop();
	}
	cout<<endl<<endl;
}

void ExpTree::Insert(Node *N)
{
	/*Node **Np;
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
			(*q.front())->var = N->var;
			(*q.front())->left = N->left;
			(*q.front())->right = N->right;
			break;
		}

		if((*q.front())->type == 0)   //type is operator
		{
			Np = &(*q.front())->left;
			q.push(Np);
			Np = &(*q.front())->right;
			q.push(Np);
			q.pop();
		}

		else if((*q.front())->type == 1 || (*q.front())->type == 2)   //type is operand or variable
		{
			q.pop();
			continue;
		}
	}*/

	HelperInsert(N, root);
}



void ExpTree::BuildHelper(string *T, int start, int end, Node *&N)
{
	int nAdd = 0; //will contain the number of addition operators
	int nSub = 0; //will contain the number of subtraction operators
	int nMul = 0; //will contain the number of multiplication operators
	int nDiv = 0; //will contain the number of division operators
	int op = 0; //will contain the operator to be inserted
	int I; //index to the token to be inserted
	int count; //integer used for counting
	Node *temp;
	int i;

	//count operators
	for(i = start; i <= end; i++)
	{
		if(T[i] == "+")
			nAdd++;
		else if(T[i] == "-")
			nSub++;
		else if(T[i] == "*")
			nMul++;
		else if(T[i] == "/")
			nDiv++;
	}

	//determine which operator to be the root
	int midOp;
	count = 0;
	if(nAdd > 0)
	{
		op = 1;
		midOp = (nAdd/2)+1;
		for(i = start; i <= end; i++)
		{
			if(T[i] == "+")
				count++;
			if(count >= midOp)
			{
				I = i;
				break;
			}
		}
	}



	
	if(op != 0)		//if there is an operator in the array of tokens
	{
		temp = new Node;
		temp->type = 0;
		temp->op = op;
		temp->number = NULL;
		temp->var = "";
	}

	else if(op == 0)
	{
		temp = new Node;
		temp->type = 1;
		temp->op = NULL;
		temp->number = strToDbl(T[start]);
		temp->var = "";
	}

	Insert(temp);

	delete temp;

	if((end - start)  > 1)
	{
		BuildHelper(T, start, (I - 1), N->left);
		BuildHelper(T, (I + 1), end, N->right);
	}

}
//1231+422+4242+4534


void ExpTree::BuildExp(string e)
{
	char skip[] = {' ', '\t', '\n'};
	char tok[] = {'+', '-', '*', '/', '^', '%', '(', ')', '[', ']', '<', '>', ';'};
	int len1 = sizeof(skip)/sizeof(skip[0]);
	int len2 = sizeof(tok)/sizeof(tok[0]);
	string *parsed; //will contain an array of tokens after parsing
	int len; //will contain the number of tokens
	parse(e, skip, len1, tok, len2, parsed, len);
	BuildHelper(parsed, 0, len-1, root);

	delete [] parsed;
}