#include "BinaryTree.h"
#include <stdio.h>
#include <iostream>
#include <stack>
using namespace std;

void PrintTreeNode(BinaryTreeNode* pNode)
{
	if(pNode != NULL)
	{
		printf("value of this node is: %d\n", pNode->m_nValue);

		if(pNode->m_pLeft != NULL)
			printf("value of its left child is: %d.\n", pNode->m_pLeft->m_nValue);
		else
			printf("left child is null.\n");

		if(pNode->m_pRight != NULL)
			printf("value of its right child is: %d.\n", pNode->m_pRight->m_nValue);
		else
			printf("right child is null.\n");
	}
	else
	{
		printf("this node is null.\n");
	}

	printf("\n");
}

//前序遍历
void PrintTree(BinaryTreeNode* pRoot)
{
	PrintTreeNode(pRoot);

	if(pRoot != NULL)
	{
		if(pRoot->m_pLeft != NULL)
			PrintTree(pRoot->m_pLeft);

		if(pRoot->m_pRight != NULL)
			PrintTree(pRoot->m_pRight);
	}
}

//前序
void PreOrder(BinaryTreeNode* pRoot)
{
	if(pRoot == NULL)
		return;
	cout << pRoot->m_nValue << endl;
	PreOrder(pRoot->m_pLeft);
	PreOrder(pRoot->m_pRight);
}

void InOrder(BinaryTreeNode* pRoot)
{
	if(pRoot == NULL)
		return;

	InOrder(pRoot->m_pLeft);
	cout << pRoot->m_nValue << endl;
	InOrder(pRoot->m_pRight);
}

void PostOrder(BinaryTreeNode* pRoot)
{
	if(pRoot == NULL)
		return;

	PostOrder(pRoot->m_pLeft);
	PostOrder(pRoot->m_pRight);
	cout << pRoot->m_nValue << endl;
}

//非递归，栈遍历
//前序遍历
//将根结点入栈；
//每次从栈顶弹出一个结点，访问该结点；
//把当前结点的右孩子入栈；
//把当前结点的左孩子入栈。
void PreOrder2(BinaryTreeNode* pRoot)
{
	if(pRoot == NULL)
		return;

	stack<BinaryTreeNode *> stk;
	stk.push(pRoot);
	while(!stk.empty()) {
		BinaryTreeNode* pNode = stk.top();
		stk.pop();
		cout << pNode->m_nValue << endl;

		if(pNode->m_pRight != NULL)
			stk.push(pNode->m_pRight);
		if(pNode->m_pLeft != NULL)
			stk.push(pNode->m_pLeft);
	}
}

//中序遍历
//初始化一个二叉树结点pNode指向根结点；
//若pNode非空，那么就把pNode入栈，并把pNode变为其左孩子；（直到最左边的结点）
//若pNode为空，弹出栈顶的结点，并访问该结点，将pNode指向其右孩子（访问最左边的结点，并遍历其右子树）
void InOrder2(BinaryTreeNode* pRoot)
{
	if(pRoot == NULL)
		return;

	stack<BinaryTreeNode *> stk;
	BinaryTreeNode* pNode = pRoot;
	while(pNode != NULL || !stk.empty()) {
		if(pNode != NULL) {
			stk.push(pNode);
			pNode = pNode->m_pLeft;
		} else {
			pNode = stk.top();
			stk.pop();
			cout << pNode->m_nValue << endl;
			pNode = pNode->m_pRight;
		}
	}
}

//后序遍历
//设置两个栈stk, stk2；
//将根结点压入第一个栈stk；
//弹出stk栈顶的结点，并把该结点压入第二个栈stk2；
//将当前结点的左孩子和右孩子先后分别入栈stk；
//当所有元素都压入stk2后，依次弹出stk2的栈顶结点，并访问之。
void PostOrder2(BinaryTreeNode* pRoot)
{
	if(pRoot == NULL)
		return;

	stack<BinaryTreeNode *> stk1, stk2;
	stk1.push(pRoot);
	while(!stk1.empty()) {
		BinaryTreeNode* pNode = stk1.top();
		stk1.pop();
		stk2.push(pNode);
		if(pNode->m_pLeft != NULL)
			stk1.push(pNode->m_pLeft);
		if(pNode->m_pRight != NULL)
			stk1.push(pNode->m_pRight);
	}
	while(!stk2.empty()) {
		cout << stk2.top()->m_nValue << endl;
		stk2.pop();
	}
}

void DestroyTree(BinaryTreeNode* pRoot)
{
	if(pRoot != NULL)
	{
		BinaryTreeNode* pLeft = pRoot->m_pLeft;
		BinaryTreeNode* pRight = pRoot->m_pRight;

		delete pRoot;
		pRoot = NULL;

		DestroyTree(pLeft);
		DestroyTree(pRight);
	}
}
