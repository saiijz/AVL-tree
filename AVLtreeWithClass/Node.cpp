#include "Node.h"

int Node::outputKey()
{
	return this->key;
}

Node* Node::createNode(int iValue)
{
	key = iValue;
	bf = CENTER;
	return this;
}

Node::Node(int v, Node* l, Node* r, Balance bf)
{
	key = v;
	pLeft = l;
	pRight = r;
	this->bf = bf;
}

Node::Node()
{
	pLeft = NULL;
	pRight = NULL;
}


Node::~Node()
{
}

void addNode(Node *&pRoot, int i) {
	if (!pRoot) {
		pRoot = new Node;
		pRoot->createNode(i);
		return;
	}
	else {
		if (pRoot->key == i) {
			return;
		}
		if (pRoot->key > i) {
			addNode(pRoot->pLeft, i);
			balanceTree(pRoot);
			return;
		}
		if (pRoot->key < i) {
			addNode(pRoot->pRight, i);
			balanceTree(pRoot);
			return;
		}
	}
}

void leftBalance(Node *&pRoot, Balance bf)
{
	if (bf == LEFT) {
		rightRotate(pRoot);
		return;
	}
	if (bf == RIGHT) {
		leftRotate(pRoot->pLeft);
		rightRotate(pRoot);
		return;
	}
	return;
}

int rightBalance(Node*& pRoot, Balance bf) {
	if (bf == RIGHT) {
		leftRotate(pRoot);
		return 1;
	}
	if (bf == LEFT) {
		rightRotate(pRoot->pRight);
		leftRotate(pRoot);
		return 1;
	}
}

Node * search(Node *pRoot, int i)
{
	if (!pRoot) {
		return NULL;
	}
	if (pRoot->pRight->key == i || pRoot->pLeft->key == i) {
		return pRoot;
	}
	if (pRoot->key > i) {
		return pRoot = search(pRoot->pLeft, i);
	}
	if (pRoot->key < i) {
		return pRoot = search(pRoot->pRight, i);
	}
}

void balanceTree(Node *&pRoot) {
	int h;
	h = checkBalance(pRoot);
	if (h == 0) {
			pRoot->bf = CENTER;
			return;
	}
	if (h == 1) {
			pRoot->bf = LEFT;
			return;
	}
	if (h > 1) {
			leftBalance(pRoot, pRoot->pLeft->bf);
			pRoot->bf = static_cast<Balance>(checkBalance(pRoot));
			pRoot->pLeft->bf = static_cast<Balance>(checkBalance(pRoot->pLeft));
			pRoot->pRight->bf = static_cast<Balance>(checkBalance(pRoot->pRight));
			return;
	}
	if (h == -1) {
			pRoot->bf = RIGHT;
			return;
	}
	if (h < -1) {
			rightBalance(pRoot, pRoot->pRight->bf) ;
			pRoot->bf = static_cast<Balance>(checkBalance(pRoot));
			pRoot->pLeft->bf = static_cast<Balance>(checkBalance(pRoot->pLeft));
			pRoot->pRight->bf = static_cast<Balance>(checkBalance(pRoot->pRight));
			return;
	}
}

Balance checkBalanceFactor(Node * pRoot, Balance bf)
{
	if (bf == LEFT) {
		return pRoot->pLeft->bf;
	}
	if (bf == RIGHT) {
		return pRoot->pRight->bf;
	}
}

int deleteNode(Node *&pRoot, int i)
{
	if (!pRoot) {
		return 0;
	}
	if (pRoot->key == i) {
		if (!pRoot->pLeft && !pRoot->pRight) {
			deleteLeaf(pRoot);
			return 1;
		}
		if (pRoot->pRight && pRoot->pLeft) {
			deleteRoot(pRoot);
			return 2;
		}
		if (pRoot->pRight && !pRoot->pLeft) {
			deleteBranch(pRoot, pRoot->bf);
			return 2;
		}
		if (!pRoot->pRight && pRoot->pLeft) {
			deleteBranch(pRoot, pRoot->bf);
			return 2;
		}
	}
	if (pRoot->key > i) {
		int check;
		check = deleteNode(pRoot->pLeft, i);
		if (check == 1) {
			pRoot->pLeft = NULL;
		}
		balanceTree(pRoot);
		return 0;
	}
	if (pRoot->key < i) {
		int check;
		check = deleteNode(pRoot->pRight, i);
		if (check == 1) {
			pRoot->pRight = NULL;
		}
		balanceTree(pRoot);
		return 0;
	}
}

int deleteLeaf(Node *&pRoot)
{
	delete pRoot;
	return 1;
}

int deleteRoot(Node *&pRoot)
{
	Node * pTemp{ pRoot->pRight };
	if (pTemp->pLeft) {
		while (!pTemp->pLeft) {
			pTemp = pTemp->pLeft;
		}
		Node* pDel{ pTemp->pLeft };
		pRoot->key = pDel->key;
		delete pDel;
		pTemp->pLeft = NULL;
		balanceTree(pRoot);
		balanceTree(pRoot->pRight);
		balanceTree(pRoot->pLeft);
	}
	else {
		pRoot->key = pTemp->key;
		delete pTemp;
		pRoot->pRight = NULL;
		balanceTree(pRoot);
	}
	return 2;
}

int deleteBranch(Node *&pRoot, Balance bf)
{
	if (bf == RIGHT) {
		Node* pTemp{ pRoot->pRight };
		pRoot->key = pRoot->pRight->key;
		pRoot->pRight = NULL;
		delete pTemp;
		balanceTree(pRoot);
		return 0;
	}
	if (bf == LEFT) {
		Node *pTemp{ pRoot->pLeft };
		pRoot->key = pRoot->pLeft->key;
		pRoot->pLeft = NULL;
		delete pTemp;
		balanceTree(pRoot);
		return 0;
	}
}

int checkBalance(Node *&pRoot) //kiểm tra sự chênh lệch chiều cao 2 nhánh con của 1 node
{
	if (!pRoot->pLeft && !pRoot->pRight) {
		return 0;
	}
	int l{ 0 };
	int r{ 0 };
	l = checkHeight(pRoot->pLeft);
	r = checkHeight(pRoot->pRight);
	return l - r;
}

int checkHeight(Node *&pRoot) //kiểm tra chiều cao một nhánh
{
	if (!pRoot) {
		return 0;
	}
	if (!pRoot->pLeft && !pRoot->pRight) {
		return 1;
	}
	int l{ 0 };
	int r{ 0 };
	if (pRoot->pLeft) {
		l++;
	}
	if (pRoot->pRight) {
		r++;
	}
	l += checkHeight(pRoot->pLeft);
	r += checkHeight(pRoot->pRight);

	if (l > r) {
		return l;
	}
	else {
		return r;
	}
}

void rightRotate(Node *&pRoot)
{  
	if (!pRoot->pLeft->pRight) {
		pRoot->pLeft->pRight = pRoot;
		pRoot = pRoot->pLeft;
		pRoot->pRight->pLeft = NULL;
		return;
	}
	else {
		Node* pTemp{ pRoot->pLeft->pRight };
		pRoot->pLeft->pRight = pRoot;
		pRoot = pRoot->pLeft;
		pRoot->pRight->pLeft = pTemp;
		return;
	}
}

void leftRotate(Node *&pRoot)
{
	if (!pRoot->pRight->pLeft) {
		pRoot->pRight->pLeft = pRoot;
		pRoot = pRoot->pRight;
		pRoot->pLeft->pRight = NULL;
		return;
	}
	else {
		Node *pTemp{ pRoot->pRight->pLeft };
		pRoot->pRight->pLeft = pRoot;
		pRoot = pRoot->pRight;
		pRoot->pLeft->pRight = pTemp;
		return;
	}
}
