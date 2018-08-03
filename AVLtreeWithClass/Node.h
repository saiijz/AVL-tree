#include <iostream>
#pragma once
enum Balance {
	CENTER = 0,
	LEFT = 1,
	RIGHT = -1,
	FAIL = 999
};
class Node
{
protected:
	int key;
	Node* pLeft;
	Node* pRight;
	Balance bf;

public:
	friend class Tree;
	Node* createNode(int);
	int outputKey();
	Node(int, Node*, Node*,Balance);
	friend void addNode(Node*&, int);
	friend void leftBalance(Node*&, Balance);
	friend int rightBalance(Node*&, Balance);
	friend Node* search(Node*, int);
	friend void balanceTree(Node*&);
	friend Balance checkBalanceFactor(Node*, Balance);
	friend int deleteNode(Node*&, int);
	friend int deleteLeaf(Node*&);
	friend int deleteRoot(Node*&);
	friend int deleteBranch(Node*&, Balance);
	friend int checkBalance(Node*&);
	friend int checkHeight(Node*&);
	friend void rightRotate(Node*&);
	friend void leftRotate(Node*&);
	Node();
	~Node();
};

