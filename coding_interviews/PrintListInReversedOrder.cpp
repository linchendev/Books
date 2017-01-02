#include "List.h"
#include <stdio.h>
#include <iostream>
#include <stack>

//面试题5：从尾到头打印链表
//思路一：压栈，不修改原数据结构
void PrintListReversingly_Iteratively(ListNode* pHead)
{
	std::stack<ListNode*> nodes;

	ListNode* pNode = pHead;
	while(pNode != NULL)
	{
		nodes.push(pNode);
		pNode = pNode->m_pNext;
	}

	while(!nodes.empty())
	{
		pNode = nodes.top();
		printf("%d\n", pNode->m_nValue);
		nodes.pop();
	}
}

//思路二：递归
void PrintListReversingly_Recursively(ListNode* pHead)
{
	if(pHead != NULL)
	{
		if(pHead->m_pNext != NULL)
		{
			PrintListReversingly_Recursively(pHead->m_pNext);
		}
		printf("%d\n", pHead->m_nValue);		
	}
}

int main()
{
	ListNode* pHead = NULL;
	AddToTail(&pHead, 1);
	AddToTail(&pHead, 2);
	AddToTail(&pHead, 3);
	AddToTail(&pHead, 4);
	AddToTail(&pHead, 5);

	PrintListReversingly_Recursively(pHead);
	std::cout << "==================" << std::endl;
	PrintListReversingly_Iteratively(pHead);

	DestroyList(pHead);
	
	return 0;
}
