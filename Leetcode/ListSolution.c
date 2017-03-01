#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

struct ListNode {
      int val;
      struct ListNode *next;
};

 struct RandomListNode {
       int label;
       struct RandomListNode *next;
       struct RandomListNode *random;
 };

//typedef struct ListNode struct ListNode
	
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
	struct ListNode   *ptrL1 = NULL;
	struct ListNode   *ptrL2 = NULL;
	struct ListNode   *ptr = NULL;
	struct ListNode   *pCur = NULL;
	struct ListNode   *pList = NULL;
	int   iVal = 0;
	int   iCarry = 0;
	

	ptrL1 = l1;
	ptrL2 = l2;

	if (NULL == l1 && l2 == NULL)
		return NULL;

	if (NULL == l1)
		return l2;
	if (NULL == l2)
		return l1;

	while (ptrL1 != NULL && ptrL2 != NULL)
	{
		ptr = (struct ListNode *)malloc(sizeof(struct ListNode)); 
		if (ptr == NULL)
		{
			return NULL;
		}
		
		iVal = ptrL1->val + ptrL2->val + iCarry;
		ptr->val = iVal%10;
		iCarry = iVal/10;
		ptr->next = NULL;
		printf("%d  ", ptr->val);

		if (!pList)
		{
			pList =  ptr;
			pCur = ptr;
		}
		else
		{
			pCur->next = ptr;
			pCur = ptr;
		}
	

		ptrL1 = ptrL1->next;
		ptrL2 = ptrL2->next;
	}

	while (ptrL1)
	{
		ptr = (struct ListNode *)malloc(sizeof(struct ListNode)); 
		if (ptr == NULL)
		{
			return NULL;
		}
		iVal = ptrL1->val + iCarry;
		ptr->val = iVal%10;
		iCarry = iVal/10;

		pCur->next = ptr;
		pCur = ptr;

		ptrL1 = ptrL1->next;
	}
	
	while (ptrL2)
	{
		ptr = (struct ListNode *)malloc(sizeof(struct ListNode)); 
		if (ptr == NULL)
		{
			return NULL;
		}
		iVal = ptrL2->val + iCarry;
		ptr->val = iVal%10;
		iCarry = iVal/10;
		
		pCur->next = ptr;
		pCur = ptr;

		ptrL2= ptrL2->next;		
	}

	if (iCarry)
	{
		ptr = (struct ListNode *)malloc(sizeof(struct ListNode));
		if (NULL == ptr)
		{
			return NULL;
		}
		ptr->val = iCarry;
		ptr->next = NULL;
		
		pCur->next = ptr;
	}

	return pList;
}

void PrintList(struct ListNode *pHead)
{
	struct ListNode *pTmp = pHead;
	printf("List:");
	while(pTmp)
	{
		printf("%d ->", pTmp->val);
		pTmp = pTmp->next;
	}
	printf("\n");
}

void FreeList(struct ListNode *pHead)
{
	struct ListNode *pTmp = pHead;
	printf("List:");
	while (pHead)
	{
		pTmp = pHead->next;
		free(pHead);
		pHead = pTmp;
		
	}
	printf("\n");
}

void PrintRandomList(struct RandomListNode *pHead)
{
	struct RandomListNode *pTmp = pHead;
	printf("RandomList:");
	while(pTmp)
	{
		printf("%d ", pTmp->label);
		if (pTmp->random)
		{
			printf("(Random:%d) ->", pTmp->random->label);
		}
		else
		{
			printf("  ->");
		}
		pTmp = pTmp->next;
	}
	printf("\n");
}

void FreeRandomList(struct RandomListNode *pHead)
{
	struct RandomListNode *pTmp = pHead;
	printf("RandomList:");
	while (pHead)
	{
		pTmp = pHead->next;
		free(pHead);
		pHead = pTmp;
		
	}
	printf("\n");
}

struct ListNode* partition(struct ListNode* head, int x) 
{
	struct  ListNode*  pLeftNode = NULL;
	struct  ListNode*  pRightNode = NULL;
	struct  ListNode*  pLeftHead = NULL;
	struct  ListNode*  pRightHead = NULL;
	
	struct  ListNode*  pCur = NULL;

	if (NULL == head)
		return NULL;

	
	pCur = head;
	while (pCur)
	{

		if (pCur->val < x)
		{
			if (NULL == pLeftHead)
			{
				pLeftHead = pLeftNode = pCur;
			}
			else
			{
				if (NULL == pLeftNode->next)
				{
					printf("1  %d.\n", pLeftNode->val);
				}

				pLeftNode->next = pCur;
				pLeftNode = pCur;
			}
		}
		else
		{
			if (NULL == pRightHead)
			{
				pRightHead = pRightNode = pCur;
			}
			else
			{
				pRightNode->next = pCur;
				pRightNode = pCur;
			}
		}
		pCur = pCur->next;
	}

	if (pLeftNode)
		pLeftNode->next = pRightHead;

	if (pRightNode)
		pRightNode->next = NULL;

	if (pLeftHead)
		return pLeftHead;
	else
		return pRightHead;
}

/*
struct ListNode* deleteDuplicates(struct ListNode* head)
{
	struct ListNode  *pTmp = NULL;
	struct ListNode  *pNextNode = NULL;
	struct ListNode  *pNewNode = NULL;
	struct ListNode  *pListHead = NULL;
	struct ListNode  *pListTail = NULL;
	int iVal = 0;

	if (NULL == head)
		return NULL;

	iVal = head->val + 1;

	pTmp = head;
	while (pTmp)
	{
		if (iVal == pTmp->val)
		{
			pNextNode = pTmp;
			while (pNextNode)
			{
				if (pNextNode->val != iVal)
				{
					break;
				}
				pNextNode = pNextNode ->next;
			}
			pTmp = pNextNode;
		}
		else
		{
			pNewNode = (struct ListNode*)malloc(sizeof(struct ListNode));
			pNewNode->val = pTmp->val;
			pNewNode->next = NULL;

			if (NULL == pListHead)
			{
				pListHead = pListTail = pNewNode;
			}
			else
			{
				pListTail->next = pNewNode;
				pListTail = pNewNode;
			}
			
			iVal = pTmp->val;
			pTmp = pTmp->next;	
		}
	}

	return pListHead;
}
*/

struct ListNode* reverseBetween(struct ListNode* head, int m, int n)
{
	int i = 0;
	struct ListNode  *pTmp = NULL;
	struct ListNode  *pNextNode = NULL;
	struct ListNode  *pStartNode = NULL;
	struct ListNode  *pTailNode = NULL;
	struct ListNode  *pPrevNode = NULL;


	if (NULL == head)
		return NULL;
	if (m < 1 || m > n)
		return NULL;

	
	pTmp = head;
	for (i = 1; i < m; i++)
	{
		pPrevNode = pTmp;
		pTmp = pTmp->next;
	}
	pTailNode = pTmp;
	
	for (i = m; i <= n; i++)
	{
		pNextNode = pTmp->next;
		
		pTmp->next = pStartNode;
		pStartNode = pTmp;
		
		pTmp = pNextNode;
	}

	if (pPrevNode)
		pPrevNode->next = pStartNode;
	else
		head = pStartNode;
	
	pTailNode->next = pTmp;
	
	return head;
}

struct ListNode* deleteDuplicates(struct ListNode* head)
{
	int iVal = 0;
	struct ListNode  *pTmp = NULL;
	struct ListNode  *pNextNode = NULL;
	struct ListNode  *pDupStartNode = NULL;
	struct ListNode  *pFreeNode = NULL;
	struct ListNode  *pPrevNode = NULL;	

	pTmp = head;
	while (pTmp)
	{
		iVal = pTmp->val;
		pNextNode = pTmp->next;
		if (pNextNode && pNextNode->val == iVal)
		{
			pDupStartNode = pTmp;
			while (pTmp && pTmp->val == iVal)
			{
				pFreeNode = pTmp;
				pTmp = pTmp->next;
				free(pFreeNode);
			}
			pDupStartNode->next = pTmp;
			
			if (!pPrevNode)
			{
				head = pTmp;
			}
			else
			{
				pPrevNode->next = pTmp;
			}
		}
		else
		{
			pPrevNode = pTmp;
			pTmp = pTmp->next;
			
		}
	}

	return head;
}

struct ListNode* rotateRight(struct ListNode* head, int k) 
{
	struct ListNode  *pTmp = NULL;
	int iLen = 1;
	int i = 0;

	if (NULL == head)
		return NULL;
	
	pTmp = head;
	while (pTmp->next)
	{
		iLen += 1;
		pTmp = pTmp->next;
	}
	
	k = iLen - k%iLen;
	pTmp->next = head;
	for (i = 0; i < k; i++)
	{
		pTmp = pTmp->next;
	}
	head = pTmp->next;
	pTmp->next = NULL;
	
	return head;

}

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) 
{
	struct  ListNode *pNthNode = NULL;
	struct  ListNode *pTmp = NULL;
	struct  ListNode *pPrevNode = NULL;	
	int i = 0;
	if (NULL == head)
		return NULL;
	pTmp = head;
	while (pTmp)
	{	
		i += 1;
		if (i == n)
		{
			pNthNode = head;
		}
		else if (i > n)
		{
			pPrevNode = pNthNode;
			pNthNode = pNthNode->next;
		}
		pTmp = pTmp->next;
	}

	printf("value :%d\n", pNthNode->val);
	if (!pNthNode)
		return head;
	if (pPrevNode)
	{
		pPrevNode->next = pNthNode->next;
	}	
	else
	{
		head = pNthNode->next;
	}
	free(pNthNode);
	
	return head;
}

struct ListNode* swapPairs(struct ListNode* head)
{
	struct ListNode *pHead1 = NULL;
	struct ListNode *pHead2 = NULL;
	struct ListNode *pCur1 = NULL;
	struct ListNode *pCur2 = NULL;	
	struct ListNode *pTmp = NULL;
	struct ListNode *pTmp2 = NULL;
	struct ListNode *pNewHead = NULL;
	int i = 0;
	int iCnt = 0;

	if (NULL == head || head->next == NULL)
		return head;

	
	pTmp = head;
	while (pTmp)
	{
		if (iCnt%2)
		{
			if (NULL == pHead1)
			{
				pHead1 = pCur1 = pTmp;
			}
			else
			{
				pCur1->next = pTmp;
				pCur1 = pTmp;
			}
		}
		else
		{
			if (NULL == pHead2)
			{
				pHead2 = pCur2 = pTmp;
			}
			else
			{
				pCur2->next = pTmp;
				pCur2 = pTmp;
			}
		}
		pTmp = pTmp->next;
		iCnt++;
	}

	pCur1->next = NULL;
	pCur2->next = NULL;

	PrintList(pHead1);
	PrintList(pHead2);


	pCur1 = pHead1;
	pCur2 = pHead2;

	pNewHead = pHead1;
	iCnt = iCnt >> 1;
	for (i = 0; i < iCnt; i++)
	{	
		pTmp = pCur1->next;
		pTmp2 = pCur2->next;

		if (pCur1->next)
		{
			pCur2->next = pCur1->next;
		}
		pCur1->next = pCur2;
	
		pCur1 = pTmp;
		pCur2 = pTmp2;
	}
	
	return pNewHead;
}


struct ListNode* reverseKGroup(struct ListNode* head, int k)
{	
	struct ListNode  *pVisitNode = NULL;
	struct ListNode  *pTmp = NULL;
	struct ListNode  *pStartNode = NULL;
	struct ListNode  *pEndNode = NULL;
	struct ListNode  *pPrevNode = NULL;
	int iCnt = 0;
	int i = 0;
	int iExcess = 0;

	if (NULL == head || k == 0 || k == 1)
		return head;
	
	/*All  Node reverse*/
	pVisitNode = head;
	while (pVisitNode)
	{			
		//pPrevNode = pTmp;
		pTmp = pVisitNode->next;            
		pVisitNode->next = pPrevNode;  
		pPrevNode = pVisitNode;
		pVisitNode = pTmp;
		iCnt++;
	}
	head = pPrevNode;

	/*less than k  Node recovery*/
	iExcess = iCnt%k;
	
	pPrevNode = NULL;
	pVisitNode = head;
	for (i = 0; i < iExcess; i++)
	{
		pTmp = pVisitNode->next;            
		pVisitNode->next = pPrevNode;  
		pPrevNode = pVisitNode;
		pVisitNode = pTmp;
	}
	if (pPrevNode)
	{
		head->next = NULL;
		head  = pPrevNode;
	}


	i = 0;
	while (pVisitNode)
	{
		i += 1;
		pTmp = pVisitNode->next;
		if (i == 1)
		{
			pStartNode = pVisitNode;	
		}
		else if (i == k)
		{
			pEndNode = pVisitNode;
			pEndNode->next = pPrevNode;
			head = pStartNode; 
			pPrevNode = pStartNode;
			i = 0;
		}
		pVisitNode = pTmp;
	}

	return head;
}

struct RandomListNode *copyRandomList(struct RandomListNode *head) 
{
	struct RandomListNode *pTmp = NULL;
	struct RandomListNode *pCopy = NULL;
	struct RandomListNode *pNewHead = NULL;

	
	if (NULL == head)
		return NULL;

	pTmp = head;
	while (pTmp)
	{
		pCopy = (struct RandomListNode *)malloc(sizeof(struct RandomListNode));

		if (pNewHead == NULL)
		{
			pNewHead = pCopy;
		}
	
	 	pCopy->label = pTmp->label;
		pCopy->next = pTmp->next;
		pCopy->random = pTmp->random;

		pTmp->next = pCopy;

		pTmp = pCopy->next;
	}

	pTmp = head;
	while (pTmp)
	{
		if (pTmp->random)
		{
			pCopy = pTmp->next;
			pCopy->random = pTmp->random->next;
		}
		
		pTmp = pTmp->next->next;
	}

	pTmp = head;
	pCopy = pNewHead;
	while (pCopy->next)
	{
		pTmp->next = pTmp->next->next;
		pCopy->next = pCopy->next->next;

		pCopy = pCopy->next;
		pTmp = pTmp->next;
	}
	pTmp->next = NULL;
	pCopy->next = NULL;
	
	return pNewHead;
}

void reorderList(struct ListNode* head)
{
	struct  ListNode*  pFrontNode = NULL;
	struct  ListNode*  pBackNode = NULL;
	struct  ListNode*  pFrontHead = NULL;
	struct  ListNode*  pBackHead = NULL; 
	struct  ListNode*  pTmp = NULL;	
	struct  ListNode*  pPrevNode = NULL;	
	
	int iCnt = 0;
	int iFrontNum = 0;
	int iTotalNum = 0;

	if (NULL == head)
		return ;

	pTmp = head;
	while (pTmp)
	{
		iCnt++;
		pTmp = pTmp->next;
	}
	iTotalNum = iCnt;

	iFrontNum = (iCnt>>1) + iCnt%2;

	pTmp = head;
	iCnt = 0; 
	while (pTmp)
	{
		iCnt += 1;
		if (iCnt == iFrontNum)
		{
			break;
		} 

		pTmp = pTmp->next;
	}

	pBackHead = pTmp->next;
	pTmp->next = NULL;
	pFrontHead = head;

	/*后半部分链表反转*/
	pPrevNode = NULL;
	pBackNode = pBackHead;
	while (pBackNode)
	{
		pTmp = pBackNode->next;
		pBackNode->next = pPrevNode;
		pPrevNode = pBackNode;
		
		pBackNode = pTmp;
	}
	pBackHead = pPrevNode;

	pFrontNode = pFrontHead;
	pBackNode  = pBackHead;
	while (pFrontNode && pBackNode)
	{
		pTmp = pBackNode->next;

		pBackNode->next = pFrontNode->next;
		pFrontNode->next = pBackNode;

		pFrontNode = pBackNode->next;
		pBackNode  = pTmp;
	}
	head = pFrontHead;
}
	

#define true 0
#define false 1
int  hasCycle(struct ListNode *head) 
{
	struct ListNode *pSlow = head;
	struct ListNode *pFast =  head;

	if (NULL == head)
		return false;
	while (pFast && pFast->next)
	{
		pSlow = pSlow->next;
		pFast = pFast->next->next;

		if (pSlow == pFast)
		{
			return true;
		}
	}
	return false;
}


void Test_addTwoNumbers()
{
	int a[] = {1,0,3,7,2,7,4,0,1,1};
	int b[] = {1,5,0,3,0,8,6,5,5,2};
	int i = 0;

	struct ListNode  *pList = NULL;
	struct ListNode  *pHead1 = NULL;
	struct ListNode  *pHead2 = NULL;
	struct ListNode  *pTmp = NULL;
	for (i = 0; i < sizeof(a)/sizeof(int); i++)
	{
		pList = (struct ListNode *)malloc(sizeof(struct ListNode));
		pList->val = a[i];
		pList->next = pHead1;
		
		pHead1 = pList;
	}
	
	for (i = 0; i < sizeof(b)/sizeof(int); i++)
	{
		pList = (struct ListNode *)malloc(sizeof(struct ListNode));
		pList->val = b[i];
		pList->next = pHead2;
		
		pHead2 = pList;
	}

	pTmp = addTwoNumbers(pHead1, pHead2);
	PrintList(pTmp);

	FreeList(pTmp);
	FreeList(pHead1);
	FreeList(pHead2);
}

void Test_partition()
{
	int a[] = {1,4,3,2,5,2};
	int i = 0;
	struct ListNode  *pList = NULL;
	struct ListNode  *pHead1 = NULL;
	struct ListNode  *pHead2 = NULL;
	
	for (i = sizeof(a)/sizeof(int) - 1; i >= 0; i--)
	{
		pList = (struct ListNode *)malloc(sizeof(struct ListNode));
		pList->val = a[i];
		pList->next = pHead1;
		
		pHead1 = pList;
	}
	PrintList(pHead1);

	pHead2 = partition(pHead1, 1);


	PrintList(pHead2);

	FreeList(pHead2);
}


void Test_duplicate()
{
	int a[] = {1,1,2};
	//int b[] = {1,5,0,3,0,8,6,5,5,2};
	int i = 0;

	struct ListNode  *pList = NULL;
	struct ListNode  *pHead1 = NULL;
	struct ListNode  *pHead2 = NULL;
	struct ListNode  *pTmp = NULL;
	for (i = sizeof(a)/sizeof(int) - 1; i >= 0 ; i--)
	{
		pList = (struct ListNode *)malloc(sizeof(struct ListNode));
		pList->val = a[i];
		pList->next = pHead1;
		
		pHead1 = pList;
	}
	PrintList(pHead1);

	pHead2 = deleteDuplicates(pHead1);
	PrintList(pHead2);

	FreeList(pHead1);
	FreeList(pHead2);
}	

void  Test_Reverse()
{
	int a[] = {1,2,3,4,5};
	int i = 0;
	struct ListNode  *pList = NULL;
	struct ListNode  *pHead1 = NULL;
	struct ListNode  *pHead2 = NULL;
	
	for (i = sizeof(a)/sizeof(int) - 1; i >= 0; i--)
	{
		pList = (struct ListNode *)malloc(sizeof(struct ListNode));
		pList->val = a[i];
		pList->next = pHead1;
		
		pHead1 = pList;
	}
	PrintList(pHead1);

	pHead2 = reverseBetween(pHead1, 3, 5);


	PrintList(pHead2);

	FreeList(pHead2);

}

void Test_delete_duplicate()
{
	//int a[] = {1,2,3,3,4,4,5};
	int a[] = {1, 1, 1, 2, 2, 3};
	int i = 0;

	struct ListNode  *pList = NULL;
	struct ListNode  *pHead1 = NULL;
	struct ListNode  *pHead2 = NULL;
	struct ListNode  *pTmp = NULL;
	for (i = sizeof(a)/sizeof(int) - 1; i >= 0 ; i--)
	{
		pList = (struct ListNode *)malloc(sizeof(struct ListNode));
		pList->val = a[i];
		pList->next = pHead1;
		
		pHead1 = pList;
	}
	PrintList(pHead1);

	pHead2 = deleteDuplicates(pHead1);
	PrintList(pHead2);

	FreeList(pHead2);
}

void Test_rotate()
{
	//int a[] = {1,2,3,3,4,4,5};
	int a[] = {1, 2, 3, 4, 5};
	int i = 0;

	struct ListNode  *pList = NULL;
	struct ListNode  *pHead1 = NULL;
	struct ListNode  *pHead2 = NULL;
	struct ListNode  *pTmp = NULL;
	for (i = sizeof(a)/sizeof(int) - 1; i >= 0 ; i--)
	{
		pList = (struct ListNode *)malloc(sizeof(struct ListNode));
		pList->val = a[i];
		pList->next = pHead1;
		
		pHead1 = pList;
	}
	PrintList(pHead1);

	pHead2 = rotateRight(pHead1, 2);
	PrintList(pHead2);

	FreeList(pHead2);
}

void Test_Remove()
{
	//int a[] = {1,2,3,3,4,4,5};
	int a[] = {1, 2, 3, 4, 5};
	int i = 0;

	struct ListNode  *pList = NULL;
	struct ListNode  *pHead1 = NULL;
	struct ListNode  *pHead2 = NULL;
	struct ListNode  *pTmp = NULL;
	for (i = sizeof(a)/sizeof(int) - 1; i >= 0 ; i--)
	{
		pList = (struct ListNode *)malloc(sizeof(struct ListNode));
		pList->val = a[i];
		pList->next = pHead1;
		
		pHead1 = pList;
	}
	PrintList(pHead1);

	pHead2 = removeNthFromEnd(pHead1, 1);
	PrintList(pHead2);

	FreeList(pHead2);
}

void Test_Swap()
{
	//int a[] = {1,2,3,3,4,4,5};
	int a[] = {1,2,3,4};
	int i = 0;

	struct ListNode  *pList = NULL;
	struct ListNode  *pHead1 = NULL;
	struct ListNode  *pHead2 = NULL;
	struct ListNode  *pTmp = NULL;
	for (i = sizeof(a)/sizeof(int) - 1; i >= 0 ; i--)
	{
		pList = (struct ListNode *)malloc(sizeof(struct ListNode));
		pList->val = a[i];
		pList->next = pHead1;
		
		pHead1 = pList;
	}
	PrintList(pHead1);

	pHead2 = swapPairs(pHead1);
	PrintList(pHead2);

	FreeList(pHead2);
}


void Test_ReverseK()
{
	int a[] = {1,2,3,4,5,6};
	int i = 0;

	struct ListNode  *pList = NULL;
	struct ListNode  *pHead1 = NULL;
	struct ListNode  *pHead2 = NULL;
	struct ListNode  *pTmp = NULL;
	for (i = sizeof(a)/sizeof(int) - 1; i >= 0 ; i--)
	{
		pList = (struct ListNode *)malloc(sizeof(struct ListNode));
		pList->val = a[i];
		pList->next = pHead1;
		
		pHead1 = pList;
	}
	PrintList(pHead1);

	pHead2 = reverseKGroup(pHead1, 4);
	PrintList(pHead2);

	FreeList(pHead2);
}

void Test_CopyRandomList()
{
	int a[] = {1,2,3,4,5,6};
	int i = 0;

	struct RandomListNode  *pList = NULL;
	struct RandomListNode  *pHead1 = NULL;
	struct RandomListNode  *pHead2 = NULL;
	struct RandomListNode  *pTmp = NULL;
	for (i = sizeof(a)/sizeof(int) - 1; i >= 0 ; i--)
	{
		pList = (struct RandomListNode *)malloc(sizeof(struct RandomListNode));
		pList->label= a[i];
		pList->next = pHead1;
		
		pHead1 = pList;
	}
	pTmp = pHead1->next;
	pTmp->random = pTmp->next->next;
	
	PrintRandomList(pHead1);

	pHead2 = copyRandomList(pHead1);
	FreeRandomList(pHead1);
	
	PrintRandomList(pHead2);

	FreeRandomList(pHead2);
}

void Test_Reorder()
{
	int a[] = {1,2,3,4,5};
	int i = 0;

	struct ListNode  *pList = NULL;
	struct ListNode  *pHead1 = NULL;
	struct ListNode  *pHead2 = NULL;
	struct ListNode  *pTmp = NULL;
	for (i = sizeof(a)/sizeof(int) - 1; i >= 0 ; i--)
	{
		pList = (struct ListNode *)malloc(sizeof(struct ListNode));
		pList->val = a[i];
		pList->next = pHead1;
		
		pHead1 = pList;
	}
	PrintList(pHead1);

	reorderList(pHead1);
	PrintList(pHead1);

	FreeList(pHead1);
}
int main()
{
	//Test_partition();
	//Test_duplicate();
	//Test_Reverse();
	//Test_rotate();
	//Test_Remove();
	//Test_Swap();
	//Test_ReverseK();
	//Test_CopyRandomList();
	Test_Reorder();
	return 1;
}


