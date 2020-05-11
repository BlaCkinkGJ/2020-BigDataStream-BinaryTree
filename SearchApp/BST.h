#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "Element.h"
#include "BstNode.h"

using namespace std;

class BST {
public:
	BST(BstNode* init = 0) { root = init; };

	//   BST& operator=(const BST&);

	void recalculateWeight(BstNode* root);

	BstNode* findUnbalancedNode(BstNode* root);

	bool Insert(const Element& x);
	//bool Delete(const Element&);
	BstNode* Search(BstNode*, const Element&);
	BstNode* Search(const Element&);
	BstNode* IterSearch(const Element&);

	BST* ThreeWayJoin(BST* A, Element* x, BST* B);
	BST* TwoWayJoin(BST* A, BST* B);

	void getTreePoints(map<int, pair<int, int>>& keys) { int h = 0; cout << "\n"; root->treeprint(keys, 1, h); }

	void display(vector<CString>& v) {
		cout << "\n";
		if (root) root->display(v, 1);
		else cout << "0\n";
	};
	Element* Split(int i, BST& B, BST& C, Element& x);

	const int BALANCE_POINT = 5;
	BstNode* root;

private:
	bool DeleteLargestElement(Element& outElement);
};