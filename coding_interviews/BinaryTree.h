#pragma once

struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

extern void PrintTree(BinaryTreeNode* pRoot);
extern void DestroyTree(BinaryTreeNode* pRoot);
extern void PreOrder(BinaryTreeNode* pRoot);
extern void InOrder(BinaryTreeNode* pRoot);
extern void PostOrder(BinaryTreeNode* pRoot);

extern void PreOrder2(BinaryTreeNode* pRoot);
extern void InOrder2(BinaryTreeNode* pRoot);
extern void PostOrder2(BinaryTreeNode* pRoot);
