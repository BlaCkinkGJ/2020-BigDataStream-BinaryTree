#include "pch.h"
#include "BstNode.h"

void BstNode::display(vector<CString>& v, int i)
{
	CString str;
	str.Format(_T("Postion %d: data.key %d"), i, data.key);
	v.push_back(str);
	if (LeftChild) LeftChild->display(v, 2 * i);
	if (RightChild) RightChild->display(v, 2 * i + 1);
};



void BstNode::treeprint(map<int, pair<int, int>>& keys, int l, int& h)
{
	if (this) {
		(this->RightChild)->treeprint(keys, l + 1, h);
		h += 1;
		for (int i = 1; i <= l; i++) cout << "   ";
		cout << this->data.key << "(" << l << "," << h << ")" << "\n";
		keys.insert(make_pair<>(this->data.key, make_pair<>(l, h)));
		keys.at(this->data.key) = make_pair<>(l, h);
		(this->LeftChild)->treeprint(keys, l + 1, h);
	};
};

