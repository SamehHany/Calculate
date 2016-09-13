#include <math.h>
#include <queue>
#include "ExpTree.h"



double pi = 4*atan((double)1);

double e = exp((double)1);


OpToNum::OpToNum()
{
	M["+"] = 1;
	M["-"] = 2;
	M["*"] = 3;
	M["/"] = 4;
	M["^"] = 5;
	M["%"] = 6;
	//M["log"] = 7;
	M["cos"] = 8;
	M["sin"] = 8;
	M["tan"] = 8;
	M["acos"] = 8;
	M["asin"] = 8;
	M["atan"] = 8;
	M["log"] = 8; //log would return 7 if it had 2 parameters
	M["ln"] = 8;
}

unsigned char OpToNum::Op(string s){
	return M[s];
}

bool OpToNum::exists(string s)
{
	map<string, unsigned char>::iterator it;

	it = M.find(s);
	if(it != M.end())
		return true;
	else if(it == M.end())
		return false;
}


SingleValue::SingleValue()
{
	M["cos"] = 1;
	M["sin"] = 2;
	M["tan"] = 3;
	M["acos"] = 4;
	M["asin"] = 5;
	M["atan"] = 6;
	M["log"] = 7;
	M["ln"] = 8;
}

unsigned char SingleValue::Op(string s){
	return M[s];
}

bool SingleValue::exists(string s)
{
	map<string, unsigned char>::iterator it;

	it = M.find(s);
	if(it != M.end())
		return true;
	else if(it == M.end())
		return false;
}

NumToOp::NumToOp()
{
	M[1] = "+";
	M[2] = "-";
	M[3] = "*";
	M[4] = "/";
	M[5] = "^";
	M[6] = "%";
	M[7] = "log";
	M[8] = "single_value";
}

string NumToOp::Op(unsigned char x){
	return M[x];
}


OpToNum OpToNum1;
SingleValue SingleValue1;
NumToOp NumToOp1;


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


//returns true if ththeharacters sfof input string represent a number
bool strIsNum(string s)
{
	if(s == "e" || s == "pi")
		return true;
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
	if(n == "e")
		return e;
	else if(n == "pi")
		return pi;
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


ExpTree::Node::Node()
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
		N = NULL;
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
	if(root != NULL)
	{


	queue<Node*> q;
	q.push(root);
	while(!q.empty())
	{
		if(q.front() != NULL)
		{
			if(q.front()->type == 0)		//type is operator
				cout<<" "<<NumToOp1.Op(q.front()->op);
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
}

void ExpTree::InOrderHelper(Node *N)
{
	if(N != NULL)
	{


	if(N->left != NULL)
		InOrderHelper(N->left);

	cout<<" ";
	if(N->type == 0)
		cout<<NumToOp1.Op(N->op);
	else if(N->type == 1)
		cout<<N->number;
	else if(N->type == 2)
		cout<<N->var;

	if(N->right != NULL)
		InOrderHelper(N->right);


	}
}

void ExpTree::InOrder(){
	InOrderHelper(root);
	cout<<endl;
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


void ExpTree::Insert(Node *N){
	HelperInsert(N, root);
}


void ExpTree::BuildHelper(string *T, int start, int end, Node *&N)
{
	int i; //for loop indexing
	int mid = (start + end)/2;
	int bracket = 0; //contains the number of opening brackets that have not been closed yet
					 //is zero if all the brackets are closed

	bool rob = true; //is false if outer brackets shouldn't be removed
					 //stands for "Remove Outer Brackets"
	
	//if expression is contained within brackets, eliminate these brackets
	for(i = start; i <= mid; i++)
	{
		//for skipping data inclosed within brackets
		if(T[start] == "(" && T[end] == ")")
		{
			for(int j = start + 1; j <= end - 1; j++)
			{
				if(T[j] == "(")
					bracket++;
				else if(T[j] == ")")
					bracket--;

				if(bracket < 0)
				{
					bracket = 0;
					rob = false;
					break;
				}
			}

			if(bracket == 0 && rob)
			{
				start++;
				end--;
			}
		}
		else break;
	}
	
	int nAdd = 0; //will contain the number of addition operators
	int nSub = 0; //will contain the number of subtraction operators
	int nMul = 0; //will contain the number of multiplication operators
	int nDiv = 0; //will contain the number of division operators
	int nRem = 0; //will contain the number of remainder operators
	int nPow = 0; //will contain the number of power operators
	int nLog = 0; //will contain the number of log operators
	int nSingle = 0; //will contain the number of single value operators
					 //Eg: cos(x)
	unsigned char op = 0; //will contain the operator to be inserted
	int I; //index to the token to be inserted
	int count; //integer used for counting
	Node *temp;
	
	//count operators
	for(i = start; i <= end; i++)
	{
		if(T[i] == "(")
		{
			bracket++;
			continue;
		}
		else if(T[i] == ")")
		{
			bracket--;
			continue;
		}

		if(bracket == 0)
		{
			if(T[i] == "+")
				nAdd++;
			else if(T[i] == "-")
				nSub++;
			else if(T[i] == "*")
				nMul++;
			else if(T[i] == "/")
				nDiv++;
			else if(T[i] == "%")
				nRem++;
			else if(T[i] == "^")
				nPow++;//fix
			else if(T[i] == "log" /*& T[i+1] == "(" && T[i+3] == "," && T[i+5] == ")"*/)
				nLog++;
			else if(SingleValue1.exists(T[i]))
				nSingle++;
		}
	}
	

	if(bracket == 0)
	{



	//determine which operator to be the root
	int pivot;
	count = 0;
	bool isLog = false; //true if a log operator was selected to be inserted as root of subtree
	bool isSingle = false; //true if a single value operator was selected to be inserted as root of subtree
	if(nAdd > 0)
	{
		//for skipping data inclosed within brackets
		op = 1;
		pivot = (nAdd/2)+1;
		for(i = start; i <= end; i++)
		{
			if(T[i] == "(")
			{
				bracket++;
				continue;
			}
			else if(T[i] == ")")
			{
				bracket--;
				continue;
			}

			//if data is not inclosed within brackets
			if(bracket == 0)
			{
				if(T[i] == "+")
					count++;
				if(count >= pivot)
				{
					I = i;
					break;
				}
			}
		}
	}

	else if(nSub > 0)
	{
		op = 2;
		pivot = nSub;
		for(i = start; i <= end; i++)
		{
			if(T[i] == "(")
			{
				bracket++;
				continue;
			}
			else if(T[i] == ")")
			{
				bracket--;
				continue;
			}

			if(bracket == 0)
			{
				if(T[i] == "-")
					count++;
				if(count >= pivot)
				{
					I = i;
					break;
				}
			}
		}
	}

	else if(nMul > 0)
	{
		op = 3;
		pivot = (nMul/2)+1;
		for(i = start; i <= end; i++)
		{
			if(T[i] == "(")
			{
				bracket++;
				continue;
			}
			else if(T[i] == ")")
			{
				bracket--;
				continue;
			}

			if(bracket == 0)
			{
				if(T[i] == "*")
					count++;
				if(count >= pivot)
				{
					I = i;
					break;
				}
			}
		}
	}

	else if(nDiv > 0)
	{
		op = 4;
		pivot = nDiv;
		for(i = start; i <= end; i++)
		{
			if(T[i] == "(")
			{
				bracket++;
				continue;
			}
			else if(T[i] == ")")
			{
				bracket--;
				continue;
			}

			if(bracket == 0)
			{
				if(T[i] == "/")
					count++;
				if(count >= pivot)
				{
					I = i;
					break;
				}
			}
		}
	}

	else if(nRem > 0)
	{
		op = 6;
		pivot = nRem;
		for(i = start; i <= end; i++)
		{
			if(T[i] == "(")
			{
				bracket++;
				continue;
			}
			else if(T[i] == ")")
			{
				bracket--;
				continue;
			}

			if(bracket == 0)
			{
				if(T[i] == "%")
					count++;
				if(count >= pivot)
				{
					I = i;
					break;
				}
			}
		}
	}

	else if(nPow > 0)
	{
		op = 5;
		pivot = nPow;
		for(i = start; i <= end; i++)
		{
			if(T[i] == "(")
			{
				bracket++;
				continue;
			}
			else if(T[i] == ")")
			{
				bracket--;
				continue;
			}

			if(bracket == 0)
			{
				if(T[i] == "^")
					count++;
				if(count >= pivot)
				{
					I = i;
					break;
				}
			}
		}
	}

	else if(nLog > 0)
	{

		for(i = start + 2; i < end; i++)
		{
			if(T[i] == "(")
			{
				bracket++;
				continue;
			}
			else if(T[i] == ")")
			{
				bracket--;
				continue;
			}
			if(bracket == 0 && T[i] == ",")
			{
				isLog = true;
				pivot = i;
				break;
			}
		}



		if(isLog)
		{
			op = 7;

			temp = new Node;
			temp->type = 0;
			temp->op = op;
			temp->number = NULL;
			temp->var = "";

			HelperInsert(temp, N);

			delete temp;


			BuildHelper(T, start + 2, pivot-1, N->left);
			BuildHelper(T, pivot+1, end-1, N->right);
		}

		else
		{
			nSingle++;
			nLog--;
			op = 8; //single value log (base 10)
		}
	}

	if(!isLog && nSingle > 0 && nAdd == 0 && nSub == 0 && nMul == 0 && nDiv == 0 && nRem == 0 && nPow == 0)
	{
		op = 8;
		isSingle = true;

		temp = new Node;
		temp->type = 0;
		temp->op = op;
		temp->number = NULL;
		temp->var = "";

		HelperInsert(temp, N);

		delete temp;

		temp = new Node;
		temp->type = 1;
		temp->op = NULL;
		temp->number = SingleValue1.Op(T[start]);
		temp->var = "";

		HelperInsert(temp, N->left);

		delete temp;

		BuildHelper(T, start+2, end-1, N->right);
	}



	
	
	if(!isLog && !isSingle)
	{
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
			if(start == end)
			{
				if(strIsNum(T[start]))
				{
					temp = new Node;
					temp->type = 1;
					temp->op = NULL;
					temp->number = strToDbl(T[start]);
					temp->var = "";
				}
				else if(!OpToNum1.exists(T[start]))
				{
					temp = new Node;
					temp->type = 2;
					temp->op = NULL;
					temp->number = NULL;
					temp->var = T[start];
				}

			}
		}


		HelperInsert(temp, N);

		delete temp;
		
		if((end - start)  >= 1)
		{
			BuildHelper(T, start, (I - 1), N->left);
			BuildHelper(T, (I + 1), end, N->right);
		}

	}


	}

	else if(bracket > 0)
	{
		clear();
		cout<<endl<<endl<<"1 or more opening brackets have have not been closed"<<endl<<endl;
	}

	else if(bracket < 0)
	{
		clear();
		cout<<endl<<endl<<"1 or more closing brackets do not have a corresponding opening bracket"<<endl<<endl;
	}

}

//(422+4242*4534-5)-4-3 + 5
//(1231+(422+4242*4534-5)-4-3 + 5 / 6 * 3) %   7
//1231+422+4242*4534-5-4-3

void ExpTree::BuildExp(string e)
{
	char skip[] = {' ', '\t', '\n'};
	char tok[] = {'+', '-', '*', '/', '^', '%', '(', ')', '[', ']', '<', '>', ',', ';'};
	int len1 = sizeof(skip)/sizeof(skip[0]);
	int len2 = sizeof(tok)/sizeof(tok[0]);
	string *parsed; //will contain an array of tokens after parsing
	int len; //will contain the number of tokens
	parse(e, skip, len1, tok, len2, parsed, len);
	BuildHelper(parsed, 0, len-1, root);

	delete [] parsed;
}



double ExpTree::evaluateHelper(Node *N)
{
	if(N->type == 0)
	{
		switch(N->op)
		{
		case 1:
			return evaluateHelper(N->left) + evaluateHelper(N->right);
			break;

		case 2:
			return evaluateHelper(N->left) - evaluateHelper(N->right);
			break;

		case 3:
			return evaluateHelper(N->left) * evaluateHelper(N->right);
			break;

		case 4:
			return evaluateHelper(N->left) / evaluateHelper(N->right);
			break;

		case 5:
			return pow(evaluateHelper(N->left), evaluateHelper(N->right));
			break;

		case 6:
			return (int)evaluateHelper(N->left) % (int)evaluateHelper(N->right);
			break;

		case 7:
			return log(evaluateHelper(N->right))/log(evaluateHelper(N->left));
			break;

		case 8:
			switch((int)(N->left->number))
			{
			case 1:
				return cos(evaluateHelper(N->right));
				break;

			case 2:
				return sin(evaluateHelper(N->right));
				break;

			case 3:
				return tan(evaluateHelper(N->right));
				break;

			case 4:
				return acos(evaluateHelper(N->right));
				break;

			case 5:
				return asin(evaluateHelper(N->right));
				break;

			case 6:
				return atan(evaluateHelper(N->right));
				break;

			case 7:
				return log10(evaluateHelper(N->right));
				break;

			case 8:
				return log(evaluateHelper(N->right));
				break;
			}
			break;
		}
	}


	else if(N->type == 1)
		return N->number;
}



double ExpTree::evaluate(){
	return evaluateHelper(root);
}



void ExpTree::substHelper(string var, double x, Node *&N)
{
	if(N->left != NULL)
		substHelper(var, x, N->left);
	if(N->right != NULL)
		substHelper(var, x, N->right);
	if(N->type == 2 && N->var == var)
	{
		N->type = 1;
		N->var = "";
		N->number = x;
	}
}


void ExpTree::subst(string var, double x){
	substHelper(var, x, root);
}





double ExpTree::solveHelper(double x, Node *N)
{
	if(N->type == 0)
	{
		switch(N->op)
		{
		case 1:
			return solveHelper(x, N->left) + solveHelper(x, N->right);
			break;

		case 2:
			return solveHelper(x, N->left) - solveHelper(x, N->right);
			break;

		case 3:
			return solveHelper(x, N->left) * solveHelper(x, N->right);
			break;

		case 4:
			return solveHelper(x, N->left) / solveHelper(x, N->right);
			break;

		case 5:
			return pow(solveHelper(x, N->left), solveHelper(x, N->right));
			break;

		case 6:
			return (int)solveHelper(x, N->left) % (int)solveHelper(x, N->right);
			break;

		case 7:
			return log(solveHelper(x, N->right))/log(solveHelper(x, N->left));
			break;

		case 8:
			switch((int)(x, N->left->number))
			{
			case 1:
				return cos(solveHelper(x, N->right));
				break;

			case 2:
				return sin(solveHelper(x, N->right));
				break;

			case 3:
				return tan(solveHelper(x, N->right));
				break;

			case 4:
				return acos(solveHelper(x, N->right));
				break;

			case 5:
				return asin(solveHelper(x, N->right));
				break;

			case 6:
				return atan(solveHelper(x, N->right));
				break;

			case 7:
				return log10(solveHelper(x, N->right));
				break;

			case 8:
				return log(solveHelper(x, N->right));
				break;
			}
			break;
		}
	}


	else if(N->type == 1)
		return N->number;
	else if(N->type == 2)
		return x;
}



double ExpTree::solve(double x){
	return solveHelper(x, root);
}


bool ExpTree::empty()
{
	if(root == NULL)
		return true;
	else return false;
}