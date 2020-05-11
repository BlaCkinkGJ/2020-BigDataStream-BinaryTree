#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "Element.h"

using namespace std;

class BstNode {
	friend class BST;
public:
	void display(vector<CString>& v, int i);
	void treeprint(map<int, pair<int, int>>& keys, int l, int& h);
	int LeftSize;
	int RightSize;
	Element data;
	BstNode* LeftChild, * RightChild;
};

