#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;


 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

  struct TreeLinkNode {
      int val;
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
     TreeLinkNode(int x) : val(x), left(NULL), right(NULL) {}
 };

struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
 };


 class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode *> s;
        vector<int>  result;	
        TreeNode   *ptr;
        if (NULL != root)
        {
            s.push(root);
        }

        while (!s.empty())
        {
            ptr = s.top();
            s.pop();
            result.push_back(ptr->val);
            if (ptr->right)
                s.push(ptr->right);
            if (ptr->left)
                s.push(ptr->left);
        }

        return result;	
    }
    vector<int> inorderTraversal(TreeNode* root){
        stack<TreeNode *> s;
        vector<int>  result;	
        TreeNode   *ptr;
  	 ptr = root;	

        while (!s.empty() ||  ptr != NULL)
        {	
            if (ptr != NULL)
            {
                s.push(ptr);
	 	  ptr = ptr->left;		
            }
            else
            {
                ptr = s.top();
                s.pop();             
                result.push_back(ptr->val);
                ptr = ptr->right;
            }
         
        }

        return result;
    }

    vector<int> postorderTraversal(TreeNode* root){
        stack<TreeNode *> s;
        vector<int>  result;	
        TreeNode   *ptr, *q;
        ptr = root;	 

        do
        {	
            while (ptr)
            {
                 s.push(ptr);
                 ptr = ptr->left;				 
            }
            			
            q = NULL;
            while (!s.empty())
            {
                ptr = s.top();
                s.pop();

                if (ptr->right == q)
                {
                    result.push_back(ptr->val);
                    q = ptr;
                }
                else
                {
                    s.push(ptr);
                    ptr = ptr->right;
                    break;
                }
            }
        }while (!s.empty());

        return result;
    }

    vector<vector<int> > levelOrder(TreeNode* root){
        vector<vector<int> > result;
        vector<int> level;	
        stack<TreeNode *> cur, next;
        TreeNode *pTmp = NULL;	
        if (root)
        {
            cur.push(root);
        }
        while (!cur.empty())		
        {
            while(!cur.empty())
            {
                pTmp = cur.top();
                cur.pop();
                level.push_back(pTmp->val);
                if (pTmp->right)
                    next.push(pTmp->right);
                if (pTmp->left)
                    next.push(pTmp->left);		  		
            }
            result.push_back(level);		
            level.clear();
            swap(cur, next);	 
        }

	 return result;	
    }


    bool  isMirror(TreeNode* pLeft, TreeNode* pRight)
    {
        if (pLeft && pRight)          
        {
            return (pLeft->val == pRight->val) && isMirror(pLeft->left, pRight->right) && isMirror(pLeft->right, pRight->left);
        }
        else	if (NULL == pLeft && NULL == pRight)
        {
            return true;
        }
        else	
        {
            return false;        
        }
    }
    bool isSymmetric(TreeNode* root) {
        return root ? (isMirror(root->left, root->right)):true;
    }

    void compare(TreeNode* pPrev, TreeNode* pCur)	
    {
        if (pPrev != NULL && pPrev->val > pCur->val)        
        {
            if (pBeg == NULL)
            {
                pBeg = pPrev;
            }
            pEnd = pCur;		
        }  
    }
    void recoverTree(TreeNode* root)	
    {
        TreeNode  *pNode = NULL;
        TreeNode  *pPre = NULL;
        TreeNode  *pVisit = NULL;
        int  iIndex = 0;

        pNode = root;
        while (pNode)		
        {
            if (pNode->left == NULL)
            {
                cout<<pNode->val<<endl;
                compare(pVisit, pNode);
                pVisit = pNode;		
                pNode = pNode->right;
            }
            else
            {
                pPre = pNode->left;
                while (pPre->right != NULL && pPre->right != pNode)	  
                    pPre = pPre->right;

                if (pPre->right == NULL)
                {
                    pPre->right = pNode;
                    pNode = pNode->left;
                }
                else
                {
                    cout<<pNode->val<<endl;
                    compare(pVisit, pNode);
                    pVisit = pNode;		
                    pPre->right = NULL;			
                    pNode = pNode->right;
                }
            }
        }        
        swap(pBeg->val, pEnd->val);
    }

    int  Depth(TreeNode* pNode){
		int LeftDepth = 0;
		int RightDepth = 0;
		if (NULL == pNode)
			return 0;
		LeftDepth  =  Depth(pNode->left) ;
		RightDepth  =  Depth(pNode->right);			  
		if (LeftDepth < 0 || RightDepth < 0 || abs(LeftDepth - RightDepth) > 1)	  
			return -1;
		return max(LeftDepth, RightDepth) + 1;
    }
    bool isBalanced(TreeNode* root){
		return Depth(root) >= 0 ? true : false;
    }
	
    void flatten(TreeNode* root)
    {
        TreeNode*  pNode = NULL;
        if (NULL == root)
            return;
		
        flatten(root->left);	
        flatten(root->right);
	
        if (NULL == root->left)
            return;

        pNode = root->left;
        while (pNode->right)
            pNode = pNode->right;
	
        pNode->right = root->right;
        root->right = root->left;
        root->left = NULL;
    }
	
    void pointnext(TreeLinkNode *root, TreeLinkNode *sibling)
    {
        if (NULL == root)
            return ;
        else
            root->right = sibling;

        pointnext(root->left, root->right);	 
		
        if (sibling)	 
        {
            pointnext(root->right, sibling->left);
        }
        else
        {
            pointnext(root->right, NULL);
        }
    }
	
    void connect1(TreeLinkNode *root)
    {
        pointnext(root, NULL);
    }

	
    void connect(TreeLinkNode *root)	
    {
        TreeLinkNode   *pPre = NULL;
        TreeLinkNode   *pCur = NULL;
        TreeLinkNode   *pNext = NULL;
        if (!root)
            return;

        pCur = root;	
        while (pCur) 		
        {
            pPre = NULL;
            pNext = NULL;	   
            for (; pCur; pCur = pCur->next)
            {
                if (!pNext)
                    pNext = (pCur->left) ? pCur->left : pCur->right;

                if (pCur->left)	
                {
                    if (pPre)
                        pPre->next = pCur->left;

                    pPre = pCur->left;
                }
			
                if (pCur->right)	
                {
                    if (pPre)
                        pPre->next = pCur->right;

                    pPre = pCur->right;
                }
            }
		pCur = pNext;	
       	}
    }

    int numTrees(int n) {
        int *p  =  new int[n + 1];
        int   iRes = 0;	  
        int i = 0;
        int k = 0;

        if (n < 1)
            return 0;
		
        p[0] = 1;
        p[1] = 1;
        for (i = 2; i <= n; i++)
        {
            for (k = 0; k < i; k++)
                p[i] += p[k] * p[i - k - 1];
        }

        iRes = p[n];
        delete[] p;	  
		
        return 	iRes;
    }
	
    bool isValidBST(TreeNode* root)
    {
        if (NULL == root)
            return true;

        if (!isValidBST(root->left))
            return false;
		
        if (pPrev)
        {
            if (pPrev->val >= root->val)		
                return false;
        }
        pPrev = root;
	
        return isValidBST(root->right);
    }
    TreeNode*  PartArrayToBST(vector<int>& nums, int iStart, int iEnd)	
    {
        int iMid = 0;
        TreeNode *pNode = NULL;
        if (iStart > iEnd)
            return NULL;
		 
        pNode = new TreeNode(0);
        if (iStart == iEnd)    	
        {
            pNode->val = nums[iStart];
        }
        else if (iStart < iEnd)	
        {
            iMid = iStart + (iEnd - iStart)/2;
            pNode->val = nums[iMid];        	
            pNode->left = PartArrayToBST(nums, iStart, iMid - 1);
            pNode->right = PartArrayToBST(nums, iMid + 1, iEnd);
        }
        return pNode;
    }
	
    TreeNode* sortedArrayToBST(vector<int>& nums){
        TreeNode  *pRoot = NULL;
        pRoot = PartArrayToBST(nums, 0, nums.size() - 1);
        return pRoot;
    }

    TreeNode*  BuildBST(ListNode* pNode, int iStart, int iEnd)	
    {
        int iMid = 0;
        TreeNode *pParent = NULL;
        TreeNode *pLeft = NULL;
        if (iStart > iEnd)
            return NULL;

    	iMid = iStart + (iEnd - iStart)/2;
    	pLeft = BuildBST(pNode, iStart, iMid - 1);		 
    	pParent = new TreeNode(pCurrent->val);
    	pParent->left = pLeft;	
    	pCurrent = pCurrent->next;
    	pParent->right = BuildBST(pNode, iMid + 1, iEnd);

    	return pParent;
    }
	
    TreeNode* sortedListToBST(ListNode* head)
    {	
    	int iLen = 0;
    	ListNode  *pTmp = head;
    	pCurrent = head;
    	while (pTmp)	 
    	{
    	    iLen++;
    	    pTmp = pTmp->next;
    	}

    	return BuildBST(head, 0, iLen - 1);
    }

    vector<TreeNode *> generate(int iBeg, int iEnd)
    {
        int i = 0;
        int j = 0;  
        int k = 0;	  
        TreeNode  *proot = NULL;
        vector<TreeNode *> pLefts;
        vector<TreeNode *> pRights;
        vector<TreeNode *> pTree;
        if (iBeg > iEnd) 
        {
            pTree.push_back(NULL);
            return pTree;
        }
	
        for (k = iBeg; k <= iEnd; k++)
        {
            pLefts = generate(iBeg, k - 1);
            pRights = generate(k + 1, iEnd);
			
            for (i = 0; i < pLefts.size(); i++)
            {
                for (j = 0; j < pRights.size(); j++)
                {
                    proot = new TreeNode(k);
                    proot->left = pLefts[i];
                    proot->right = pRights[j];
                    pTree.push_back(proot);
                }
            }
        } 
        return pTree;		
    }
    vector<TreeNode*> generateTrees(int n)
    {
        vector<TreeNode*> vec;
        if (n != 0)
        {
            vec = generate(1, n);
        }
		
        return vec;
    }
	
    vector<vector<int> > zigzagLevelOrder(TreeNode* root)
    {
        TreeNode *pNode = NULL;
        vector<vector<int> >  result;
        vector<int> level;
        bool backward = false;	

        queue<TreeNode *>  q;

        if (NULL == root)
            return result;
	  
        q.push(root);
        q.push(NULL);
        while (!q.empty())
        {
            pNode = q.front();
            q.pop();
            if (pNode)
            {
                level.push_back(pNode->val);
                if (pNode->left)
                {
                    q.push(pNode->left);
                }
                if (pNode->right)
                {
                    q.push(pNode->right);
                }
            }
            else
            {
                if (backward)
                {
                    reverse(level.begin(), level.end());
                }
                result.push_back(level);
			
                backward = !backward;
                level.clear();
                if (q.size() > 0)
                    q.push(NULL);
            }
        }
	  
    }
    TreeNode*ConstructTree(vector<int>& preorder, int prebeg, vector<int>& inorder, int inbeg, int size)	
    {
        TreeNode *proot = NULL;
        int idx = 0;
        int num = 0;	   
        int val = 0;
		
        if (size < 1)		
        {
            return NULL;
        }
        val = preorder[prebeg];	
		
        for (idx = inbeg; idx < inbeg + size; idx++)
        {
            if (val == inorder[idx])
                break;
        }
        if (idx >= inbeg + size)
            return NULL;

        num = idx - inbeg; 
        proot = new TreeNode(val);		
        proot->left   = ConstructTree(preorder, prebeg + 1, inorder, inbeg, num);
		
        prebeg = prebeg + num + 1;	
        inbeg = inbeg + num + 1;
        num =  size - 1 - num;	
        proot->right = ConstructTree(preorder, prebeg , inorder, inbeg, num);
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)	
    {
        if (preorder.size() != inorder.size())   
            return NULL;
        return ConstructTree(preorder, 0, inorder, 0, inorder.size());
    }

    int ChildDepth(TreeNode *pNode, bool hasBrother)
    {
        int ldepth = 0;
        int rdepth = 0;
        if (!pNode)	 	
            return hasBrother? 65535:0;
		
        ldepth = ChildDepth(pNode->left, pNode->right != NULL);
        rdepth = ChildDepth(pNode->right, pNode->left != NULL);		

	return min(ldepth, rdepth) + 1;
    }
    	
    int minDepth(TreeNode* root) {
        ChildDepth(root, false);
    }
    int maxDepth(TreeNode* root){
        int ldepth = 0;
        int rdepth = 0;
        if (NULL == root)
            return 0;
		
        ldepth = maxDepth(root->left);
        rdepth = maxDepth(root->right);		

        return max(ldepth, rdepth) + 1;
    }

    bool hasPathSum(TreeNode* root, int sum) {
		if (NULL == root)
		{
			return false;
		}
		if (NULL == root->left && NULL == root->right)
		{
			return sum == root->val;
		}
		
		sum = sum - root->val;
		return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
    }

    void  dfs(TreeNode *root, int sum)
    {
        if (NULL == root)
            return;
		
        cur.push_back(root->val);
        if (NULL == root->left && NULL == root->right)	
        {
        	if (sum == root->val)
        	   result.push_back(cur);				
        }
		
        if (root->left)
        {
	 	pathSum(root->left, sum - root->val);
        }
	 
        if (root->right)
        {
	 	pathSum(root->right, sum - root->val);
        }
        cur.pop_back();
    }
    vector<vector<int> > pathSum(TreeNode* root, int sum){
        dfs(root, sum);
        return result;
    }
	
    int dfspathsum(TreeNode* root)
    {
    	  int Lsum = 0;
	  int Rsum = 0;
	  int Sum = 0;
	  int Val = 0;
	  if (NULL == root)
	      return 0;

	  Lsum =  dfspathsum(root->left);
	  Rsum = dfspathsum(root->right);

	  Sum += root->val;
	  if (Lsum > 0)
	  	Sum += Lsum;

	  if (Rsum > 0)
	  	Sum += Rsum;

	  if (Sum > MaxSum)
	  	MaxSum = Sum;

	  if (Lsum > Rsum)
	  {
	  	Val = (Lsum > 0) ? (root->val + Lsum) : root->val;
	  }
	  else
	  {
	  	Val = (Rsum > 0) ? (root->val + Rsum) : root->val;
	  }
	  return Val;
    }

    int maxPathSum(TreeNode* root)
    {
    	  MaxSum = numeric_limits<int>::min();
    	  dfspathsum(root);
    	  return MaxSum;
    }

    void dfsNumbers(TreeNode* root, int prefix)
    {
        if (root == NULL)	
        {
            return;
        }

        prefix = prefix*10 + root->val;
        if (NULL == root->left && NULL == root->right)	
        {
        	Numbers.push_back(prefix);
        	return;
        }	

        dfsNumbers(root->left, prefix);
        dfsNumbers(root->right, prefix);
    }
    int sumNumbers(TreeNode* root)
    {
       int i;
       int sum;   
       dfsNumbers(root, 0);
       for (i = 0; i < Numbers.size(); i++)	
       {
            sum += Numbers[i];
       }
       return sum;	 
    }

    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n){
		int cnt1 = m - 1;
		int cnt2 = n -1;
		int cnt = m + n -1;
		while (cnt1 >= 0 && cnt2 >= 0)
		{
		       nums1[cnt--] = (nums1[cnt1] >= nums2[cnt2]) ? nums1[cnt1--] : nums2[cnt2--];
		}

		while (cnt2 >= 0)
		{
			nums1[cnt--] = nums2[cnt2--];
		}
    }
private:
    TreeNode  *pPrev;
    ListNode  *pCurrent;
	
    TreeNode  *pBeg;
    TreeNode  *pEnd;

    vector<int>  cur;
    vector<vector<int> >  result;

    int MaxSum;
    vector<int>  Numbers;
};

void test()
{
	TreeNode *pRoot  = new TreeNode(1); 
	TreeNode *pLeftChild  = new TreeNode(2);
	TreeNode *pRightChild  = new TreeNode(3);

	Solution  s;

	pRoot->left = pLeftChild;
	pRoot->right = pRightChild;

	s.recoverTree(pRoot);

	cout<<"Root:"<<pRoot->val<<endl;
	cout<<"Left Child:"<<pLeftChild->val<<endl;	
	cout<<"Right Child:"<<pRightChild->val<<endl;	
}

void  test_BTS()
{

	vector<int>  vec(3, 0);
	TreeNode  *pRoot = NULL;
	Solution  s;
	vec[0] = 3;
	vec[1] = 5;
	vec[2] = 8;
	pRoot = s.sortedArrayToBST(vec);
	cout<<"Number:"<<pRoot->val<<endl;
}

int main()
{
	Solution  sol;
	vector<int>  vec1;
	vector<int>  vec2;

	vec1.push_back(1);
	vec1.push_back(2);

	vec2.push_back(3);
	vec2.push_back(4);

	sol.merge(vec1, 2, vec2, 2);

	cout<<vec1[0]<<";"<<vec1[1]<<endl; 

	return 1;
}
