#include "pch.h"
#include "BST.h"

Element* BST::Split(int i, BST& B, BST& C, Element& x)
// Split the binary search tree with respect to key i
{
	if (!root) {// empty tree
		B.root = C.root = 0;
		return 0;
	}

	BstNode* Y = new BstNode;
	BstNode* L = Y;
	BstNode* Z = new BstNode;
	BstNode* R = Z;
	BstNode* t = root;
	while (t)
		if (i == t->data.key) {  // split at t
			L->RightChild = t->LeftChild;
			R->LeftChild = t->RightChild;
			x = t->data;
			B.root = Y->RightChild; delete Y;
			C.root = Z->LeftChild; delete Z;
			return &x;
		}
		else if (i < t->data.key) {
			R->LeftChild = t;
			R = t;
			t = t->LeftChild;
		}
		else {
			L->RightChild = t;
			L = t;
			t = t->RightChild;
		}
	L->RightChild = R->LeftChild = 0;
	B.root = Y->RightChild;
	delete Y;
	C.root = Z->LeftChild;
	delete Z;
	return nullptr;
}

BstNode* BST::Search(BstNode* b, const Element& x)
{
	if (!b) return 0;
	if (x.key == b->data.key) return b;
	if (x.key < b->data.key) return Search(b->LeftChild, x);
	return Search(b->RightChild, x);
};


BstNode* BST::Search(const Element& x)
{
	return Search(root, x);
}


BstNode* BST::IterSearch(const Element& x)
{
	for (BstNode* t = root; t; )
	{
		if (x.key == t->data.key) return t;
		if (x.key < t->data.key) t = t->LeftChild;
		else t = t->RightChild;
	}
	return 0;
}

//BstNode* BST::Search(int k){//Search by rank;
//	BstNode *t = root;
//	while (1)
//	{
//		if (k == t->LeftSize) return t;
//		if (k < t->LeftSize) t = t->LeftChild;
//		else {
//			k -= LeftSize;
//			t = t->RightChild;
//		}
//	}
//	return 0;
//}

void BST::recalculateWeight(BstNode* root)
{
	BstNode* leftNode = root->LeftChild;
	BstNode* rightNode = root->RightChild;
	if (leftNode != nullptr) {
		recalculateWeight(leftNode);
		root->LeftSize = leftNode->LeftSize + leftNode->RightSize + 1;
	}
	else {
		root->LeftSize = 0;
	}

	if (rightNode != nullptr) {
		recalculateWeight(rightNode);
		root->RightSize = rightNode->LeftSize + rightNode->RightSize + 1;
	}
	else {
		root->RightSize = 0;
	}
}

BstNode* BST::findUnbalancedNode(BstNode* root)
{
	BstNode* leftNode = root->LeftChild;
	BstNode* rightNode = root->RightChild;

	BstNode* target = nullptr;

	int balanceWeight = abs(root->LeftSize - root->RightSize);

	if (leftNode != nullptr) {
		target = findUnbalancedNode(leftNode);
		if (target) {
			return target;
		}
	}

	if (rightNode != nullptr) {
		target = findUnbalancedNode(rightNode);
		if (target) {
			return target;
		}
	}

	if (balanceWeight >= BALANCE_POINT) {
		return root;
	}

	return nullptr;
}

bool BST::Insert(const Element& x)
{
	BstNode* p = root;
	BstNode* q = 0;
	BstNode* mid = nullptr;

	while (p) {
		q = p;
		if (x.key == p->data.key) return false; //x.key is already in t
		if (x.key < p->data.key) {
			p->LeftSize += 1;
			p = p->LeftChild;
		}
		else {
			p->RightSize += 1;
			p = p->RightChild;
		}
	};
	p = new BstNode;
	p->LeftChild = p->RightChild = 0; p->data = x;
	p->LeftSize = p->RightSize = 0;
	if (!root) root = p;
	else if (x.key < q->data.key) {
		q->LeftChild = p;
	}
	else {
		q->RightChild = p;
	}

	if (this->root->LeftSize >= 5 || this->root->RightSize >= 5) {
		mid = findUnbalancedNode(this->root);
		cout << "Key: " << mid->data.key << endl;
	}

	if (mid != nullptr) {
		BST leftTree, rightTree;
		Element element;
		Element* midElem = this->Split(mid->data.key, leftTree, rightTree, element);
		if (midElem != nullptr) {
			BST* joinTree;
			joinTree = this->ThreeWayJoin(&leftTree, midElem, &rightTree);
			this->root = joinTree->root;
			recalculateWeight(this->root);
		}
	}
	return true;
}

bool BST::DeleteLargestElement(Element& outElement) {
	BstNode* deletedNode = nullptr;
	if (!root) return false;

	if (!root->RightChild) {//the tree does not have right sub-tree
		deletedNode = root;
		root = root->LeftChild;
	}
	else {
		BstNode* parentNode = root, * currNode = root;
		while (currNode->RightChild) {
			parentNode = currNode;
			currNode = currNode->RightChild;
		}
		if (currNode->LeftChild) {//the largest node has left child
			parentNode->RightChild = currNode->LeftChild;
			deletedNode = currNode;
		}
		else {//the larget node is a leaf node.
			deletedNode = currNode;
			parentNode->RightChild = nullptr;
		}
	}
	outElement = deletedNode->data;
	delete deletedNode;
	deletedNode = nullptr;
	return true;
}

BST* BST::ThreeWayJoin(BST* A, Element* x, BST* B) {
	//To be implemented
	BstNode* newNode = new BstNode;
	newNode->data = *x;
	newNode->LeftChild = A->root;
	newNode->RightChild = B->root;

	BST* newTree = new BST;
	newTree->root = newNode;
	return newTree;
}

BST* BST::TwoWayJoin(BST* A, BST* B)
{
	if (!A) return B;
	if (!B) return A;

	Element midEle;
	A->DeleteLargestElement(midEle);

	return ThreeWayJoin(A, &midEle, B);
}

