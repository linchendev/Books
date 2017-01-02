#include "List.h"
#include <iostream>
using namespace std;

void DestroyList(ListNode* pHead)
{
	ListNode* pNode = pHead;
	while(pNode != NULL)
	{
		pHead = pHead->m_pNext;
		delete pNode;
		pNode = pHead;
	}
}

//添加链表节点
void AddToTail(ListNode** pHead, int value)
{
	ListNode* pNew = new ListNode;
	pNew->m_nValue = value;
	pNew->m_pNext = NULL;

	if(*pHead == NULL)
	{
		*pHead = pNew;
	}
	else
	{
		ListNode* pTail = *pHead;
		while(pTail->m_pNext != NULL)
			pTail = pTail->m_pNext;

		pTail->m_pNext = pNew;
	}
}

//删除链表节点
bool RemoveNode(ListNode** pHead, int value)
{
	if(pHead == NULL || *pHead == NULL)
		return false;

	ListNode* pDelete = NULL;
	if((*pHead)->m_nValue == value)
	{
		pDelete = *pHead;
		*pHead = (*pHead)->m_pNext;
	}
	else
	{
		//也可以用一个节点便利
		ListNode* pFront = *pHead;
		ListNode* pNode = (*pHead)->m_pNext;
		while(pNode != NULL && pNode->m_nValue != value)
		{
			pFront = pNode;
			pNode = pNode->m_pNext;
		}

		if(pNode != NULL)
		{
			pDelete = pNode;
			pFront->m_pNext = pNode->m_pNext;
		}
	}

	if(pDelete != NULL)
	{
		delete pDelete;
		pDelete = NULL;
		return true;
	}
	else
		return false;
}



