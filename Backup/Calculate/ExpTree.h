#include <iostream>
#include <string>
#include <map>

using namespace std;


class OpToNum
{
private:
	map<string, unsigned char> M;
public:
	OpToNum();
	unsigned char Op(string s);
	bool exists(string s);


};

class SingleValue
{
private:
	map<string, unsigned char> M;
public:
	SingleValue();
	unsigned char Op(string s);
	bool exists(string s);
};


class NumToOp
{
private:
	map<unsigned char, string> M;
public:
	NumToOp();
	string Op(unsigned char x);
};


bool memberOf(char m, char *a, int size);


void parse(string e, char* skip, int lenS, char* tok, int lenT, string *&parsed, int &lenP);
/*e: Expression string.
 *skip: array of characters to be skipped during parsing.
 *sizeS: Length of the array containing characters to be skipped.
 *tok: array of characters to be tokenized singly.
 *sizeT: Length of the array containing characters to be singly tokenized.
 *parsed: an array of strings that will contain the tokens.
 *sizeP: Length of the array containing the tokenz.
*/

//struct Node;

class ExpTree
{
private:
	struct Node;
	Node *root;
	void deleteNodes(Node *&N);
	void InOrderHelper(Node *N);
	void HelperInsert(Node *N, Node *&R);
	void BuildHelper(string *T, int start, int end, Node *&N);
	double evaluateHelper(Node *N);
	void substHelper(string var, double x, Node *&N);
	double solveHelper(double x, Node *N);
	//Node* copyHelper(Node *N);
public:
	ExpTree();
	~ExpTree();
	void clear();
	void Breadth1st();
	void InOrder();
	void Insert(Node *N);
	void BuildExp(string e);
	double evaluate();
	void subst(string var, double x);
	double solve(double x);
	bool empty();
	//ExpTree copy();
	//string ViewExp();
	//string SimplifyExp();
};


struct ExpTree::Node
{
	char type;   //0 for an operator node, and 1 for an operand node, 2 for a variable node
	unsigned char op;
	double number;
	string var;
	Node *left;
	Node *right;
	Node();
};

