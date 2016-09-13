#include "Include.h"


	struct Node
	{
		bool type;   //0 for an operand node, and 1 for an operator node
		char op;
		double number;
		Node *left;
		Node *right;
		Node();
	};

class BinaryMathTree
{
private:
	/*struct Node
	{
		bool type;   //0 for an operand node, and 1 for an operator node
		char op;
		double number;
		Node *left;
		Node *right;
		Node();
	};*/
	//Node *root;
	void HelperDestructor(Node *&N);
public:
	Node *root;
	BinaryMathTree();
	~BinaryMathTree();
	void SetRoot(Node *root);
	void Breadth1st();
	template <typename T>
	void SetValue(T root);
	void Insert(Node *N);
	void BuildExpression(string e);
	double CalcExp();
};

