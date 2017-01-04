#pragma once

struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

extern void PrintTree(BinaryTreeNode* pRoot);
extern void DestroyTree(BinaryTreeNode* pRoot);
