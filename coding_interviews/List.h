
//链表节点
struct ListNode
{
	int m_nValue;
	ListNode* m_pNext;
};

extern void DestroyList(ListNode* pHead);
extern void AddToTail(ListNode** pHead, int value);
extern bool RemoveNode(ListNode** pHead, int value);
