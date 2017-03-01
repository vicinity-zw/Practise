#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;


struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
 };


class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        
        ListNode mergelist(-1);
        ListNode *p = &mergelist;		
        for (; l1 != NULL && l2 != NULL; p = p->next)	 
        {
        	if (l1->val > l2->val)
        	{
        	    p->next = l2;
        	    l2 = l2->next;
        	}
        	else
        	{
        	    p->next = l1;
        	    l1 = l1->next;
        	}
        }

        if (l1 != NULL)	
            p->next =l1;
        else 
            p->next = l2;

		
        return mergelist.next;		
    }

    ListNode* mergeKLists(vector<ListNode*>& lists){
		int i = 0;
		ListNode *p = NULL;
		if (lists.size() < 1)
			return NULL;
		
		p = lists[0];
		for (i = 1; i < lists.size(); i++)
		{
			p = mergeTwoLists(p, lists[i]);
		}

		return p;
    }
    ListNode* sortList(ListNode* head)	
    {
        ListNode  *slow, *fast;
        ListNode  *front, *back;				

        if (NULL == head || NULL == head->next)
            return head;

        slow = fast = head;		
        while (NULL != fast->next && NULL != fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        fast = slow;
        slow  = slow->next;
        fast->next = NULL;

        front = sortList(head);
        back  = sortList(slow);
        return mergeTwoLists(front, back);
	 
    }

    ListNode* insertionSortList(ListNode* head) {
        ListNode  *pPrev = NULL;	
        ListNode  *pCur = NULL;	
        ListNode  *pTmp = NULL;	
        ListNode  *pSel = NULL;	
        int  Min = 0;		

        pTmp = head;
        while (pTmp) 	
        {
            pSel = NULL;
            Min = pTmp->val;
            pCur = pTmp->next;
            while (pCur)
            {
                if (pCur->val < Min)
                {
                    Min = pCur->val;
                    pSel = pCur;
                }
                pCur = pCur->next;
            }	
			
            if (pSel)
            {
                pSel->val = pTmp->val;
                pTmp->val = Min;
            }		 
            pTmp = pTmp->next;	
        }
        return head;	
    }

    void sortColors(vector<int>& nums) {
        int i = 0;
        int pos0 = -1;
        int pos1 = -1;
        int tmp = 0;	
        for (i = 0; i < nums.size(); i++)	 	
        {
        	tmp = nums[i];
        	nums[i] = 2;	
        	if (tmp == 0)
        	{
        	    nums[++pos1] = 1;        	       
        	    nums[++pos0] = 0;
        	}
        	else if (tmp == 1)	
        	{
        	    nums[++pos1] = 1;        	       
        	}
        }
    }

    int firstMissingPositive(vector<int>& nums) {
        int i = 0;
        int length = nums.size();
        int tmp = 0;	
        int pos = 0;	
        for (i = 0; i < length; i++)	 	
        {
            while (nums[i] != i+1)	
            {
                if (nums[i] > length || nums[i] < 0 || nums[i] == nums[nums[i] - 1])            	
                    break;
				
                tmp = nums[i];
		  nums[i] = nums[tmp - 1];
		  nums[tmp - 1] = tmp;
            }
        }
		
        for (i = 0; i < length; i++)  
        {
        	if (nums[i] != i+1)
        	    return i+1;
        }
        return length + 1;	
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        int left, right, mid;
        vector<int>  result(2, -1);

        left = 0;
        right = nums.size() -1;		
        while (left <= right)	
        {
            mid = left + (right - left)/2;
            if (nums[mid] < target)
            {
                left = mid + 1;
            }
            else if (nums[mid] > target)
            {
                right = mid - 1;
            }
            else
            {
                left = mid;
                right = mid;
                while (left >0  && nums[left - 1] == target)
                {
                    left--;
                }
                result[0] = left;
					  
                while (right < (nums.size() - 1)  && nums[right + 1] == target)
                {
                    right++;
                }
                result[1] = right;

                return result;
            }
        }

        return result;	 
    }

    vector<vector<int> > subsets(vector<int>& nums){
        int i, j, cnt, idx;
        cnt = 1<<nums.size();	 	
        vector<vector<int> >  result;	
        for (i = 0; i < cnt; i++)
        {
            vector<int>  tmp;
            j = i;
            idx = 0;	 
            while (j > 0)	 
            {
                if (j&1)
                {
                    tmp.push_back(nums[idx]);
                }
                idx++;	 
                j = j>>1;	     	
            }
	     sort(tmp.begin(), tmp.end());		
            result.push_back(tmp);		 
        }
        return result;	 	
    }

    void  dfs(vector<int>& nums, vector<int>&  tmp, int start){
        allset.push_back(tmp);
        cnt++;
        for (int i = start; i < nums.size(); i++)
        {
        	if (i != start && nums[i] == nums[i -1])
        	    continue;
        	tmp.push_back(nums[i]);	
        	dfs(nums, tmp, i + 1);
        	tmp.pop_back();		
        }
    }
    vector<vector<int>  > subsetsWithDup(vector<int>& nums){
        vector<int>  tmp;
	 cnt = 0;	
        if (nums.size() < 1)		
            return allset;
	 sort(nums.begin(), nums.end());	
        dfs(nums, tmp, 0);
        cout<<"number:"<<cnt<<endl;
        return allset;
    }

    int searchInsert(vector<int>& nums, int target) {
        int  low, high, length, mid;
        low = 0;
        high = length = nums.size() - 1;
        while (low <= high)
        {
            mid = low + ((high - low)>>1);
            if (nums[mid] == target)
            {
                return mid;
            }
            else if (nums[mid] < target)
            {
                low = mid + 1;
            }	
            else if (nums[mid] > target)
            {
                high = mid - 1;
            }				
        }

        if (high < 0)
            return 0;
        if (low >= length + 1)	
            return length + 1;

        return low;
    }
    //int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList){
    //}

    void  explore(vector<vector<char> >& board, int x, int y)
    {
        int mv_x, mv_y;    
        typedef pair<int,int> point;  
        queue<point> q;
	 point tmp;	
        q.push(point(x, y));

        board[x][y] = 'Y';
        while (!q.empty())
        {
            tmp = q.front();
            q.pop();
            mv_x = tmp.first;
            mv_y = tmp.second;
            if (mv_x > 0 && board[mv_x - 1][mv_y] == 'O')
            {
                q.push(point(mv_x - 1, mv_y));
                board[mv_x - 1][mv_y] = 'Y';		
            }
			
            if (mv_x < rows -1 && board[mv_x + 1][mv_y] == 'O')
            {
                q.push(point(mv_x + 1, mv_y));
                board[mv_x + 1][mv_y] = 'Y';		
            }

            if (mv_y > 0 && board[mv_x][mv_y - 1] == 'O')
            {
                q.push(point(mv_x, mv_y - 1));
                board[mv_x][mv_y - 1] = 'Y';		
            }

            if (mv_y < cols -1 && board[mv_x ][mv_y + 1] == 'O')
            {
                q.push(point(mv_x, mv_y + 1));
                board[mv_x][mv_y + 1] = 'Y';		
            }
        }
    }
    void solve(vector<vector<char> >& board)
    {
        int i, j;
        rows = board.size();
        if (rows == 0)		
            return;			
        cols  = board[0].size();

        for (i = 0; i < cols; i++)
        {
            if (board[0][i] == 'O')
            {
                explore(board, 0, i);
            }
            if (board[rows - 1][i] == 'O')
            {
                explore(board, rows - 1, i);	
            }
        }

        for (i = 0; i < rows; i++)
        {
            if (board[i][0] == 'O')
            {
                explore(board, i, 0);
            }

            if (board[i][cols - 1] == 'O')
            {
                explore(board, i, cols - 1);
            }               
        }

        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < cols; j++)
            {
                if (board[i][j] == 'Y')
                {
                	board[i][j] = 'O';
                }
                else if (board[i][j] == 'O')
                {
                	board[i][j] = 'X';
                }				
            }
        }
    }


    void  next(vector<int>& nums, int cur)
    {
    	 int tmp;
        if (cur == nums.size())
        {
            result.push_back(nums);        		
            return;
        }
        for (int idx = cur; idx < nums.size(); idx++)    
        {
            tmp = nums[cur];
            nums[cur] = nums[idx];
            nums[idx] = tmp;

	     next(nums, cur + 1);		

            tmp = nums[cur];
            nums[cur] = nums[idx];
            nums[idx] = tmp;		 
        }
    }
	
  /*
    vector<vector<int> > permute(vector<int>& nums){
        if (nums.size() == 0)
        {
            return result;         	
        }

	 next(nums, 0);
	 return result;
    }
    */


    vector<vector<int> > permute(vector<int>& nums){
        if (nums.size() == 0)
        {
            return result;         	
        }
        sort(nums.begin(), nums.end());
        do{
            result.push_back(nums);
        }while(nextpermute(nums));

        return result;
    }

    bool nextpermute(vector<int>& nums){
        vector<int>::iterator pivot, itr, tmp;
        for (pivot = nums.end(); pivot != nums.begin(); pivot--)
        {
            if (*pivot > *(pivot - 1))
            {
                break;
            }
        }

        if (pivot == nums.begin())
        {
            return false;
        }

        pivot = pivot - 1;
        for (itr = nums.end(); itr != pivot; itr--)	
        {
            if (*itr > *pivot)
            {
                iter_swap(itr, pivot);
                break;
            }
        }
		
        reverse(pivot + 1, nums.end());
        return true;		
    }

    void select(vector<int> &vec, int idx, int number, int k, vector<int> &suit)
    {
    	int tmp;
    	if (number == k)	 
    	{
    	    result.push_back(suit);
	    return;
    	}
		
    	for (int i = idx; i < vec.size(); i++)
    	{	
    	    if (vec[i] == 0)
    	    {
    	       vec[i] = 1;
    	       suit[number] = i + 1;

		select(vec, i + 1, number + 1, k, suit);
		
    	       vec[i] = 0;		
    	    }
    	}
    }
    vector<vector<int> > combine(int n, int k){
        vector<int> vec(n, 0);
        vector<int> suit(k, 0);

        if (n <= 0)
            return result;
	 
        select(vec, 0, 0, k, suit);
		
        return result;
    }

   /*
    const vector<string> keyboard { " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
    void dfsletter(string digits, int idx, string str, vector<string>& result)
    {
        if (idx == digits.size())
        {
            result.push_back(str);
            return;
        }

        for (auto c : keyboard[digits[idx] - '0'])
        {
            dfsletter(digits, idx + 1, str + c, result);
        }
    }
    vector<string> letterCombinations(string digits)
    {
        vector<string>  vec;
        if (digits.size() == 0)
            return vec;
        
        dfsletter(digits, 0, "", vec);	 

        return vec;		  
    }
    */
    bool  palindrome(const string &s, int beg, int end)
    {
        while (beg <= end)
        {
            if (s[beg] != s[end])
            {
                return false;
            }
            beg++;
            end--;
        }
        return true;
    }
    void truncate(vector<string>& front, int idx, const string& s)
    {
        string str;
        if (idx == s.size())
        {
            groups.push_back(front);
            return;
        }
       
        for (string::size_type last = idx;  last < s.size(); last++)
        {
                if (palindrome(s, idx, last))
                {
                    str = s.substr(idx, last - idx + 1);
                    front.push_back(str);
                    truncate(front, last + 1, s);
                    front.pop_back();
                }
        }
    }
    vector<vector<string> > partition(string s) {
        vector<string> front;
        if (s.size() == 0)
            return groups;
        truncate(front, 0, s);

        return groups;
    }

    int uniquePaths(int m, int n){
        if (m < 1 || n < 1) 
            return 0; // 终止条件
        if (m == 1 && n == 1) 
            return 1; // 收敛条件

        return uniquePaths(m - 1, n) + uniquePaths(m, n - 1);
    }

    /*
    int uniquePaths(int m, int n){
        int i = 0;
        int j = 0;
        int Min = 0;
        int **paths = NULL;
        paths = new int*[m];
        for (i = 0; i < m; i++)
        {
            paths[i] = new int[n];
        }

        Min = (m < n) ? m:n;
        for (i = 0; i < m; i++)
        {
            paths[i][0] = 1;
        }
        
        for (i = 0; i < n; i++)
        {
            paths[0][i] = 1;
        }
        
        for (i = 1; i < Min; i++)
        {
            for (j = i; j < n;j++)
            {
                paths[i][j] = paths[i - 1][j] + paths[i][j -1];
            }
            
            for (j = i; j < m;j++)
            {
                paths[j][i] = paths[j - 1][i] + paths[j][i -1];
            }
        }

        if (m > n)
        {
            for (i = Min ; i < m; i++)
            {
                for (j = i; j < n;j++)
                {
                    paths[i][j] = paths[i - 1][j] + paths[i][j -1];
                }
            }
        }
        else
        {
            for (i = Min ; i < n; i++)
            {
                for (j = i; j < m;j++)
                {
                    paths[j][i] = paths[j - 1][i] + paths[j][i -1];
                }
            }
        }

        return paths[m - 1][n -1];
    }
    */

    int uniquePathsWithObstacles(vector<vector<int> >& obstacleGrid) {
        int i, j;

        int **paths = NULL;
        
        int cols, rows;
        if (obstacleGrid.size() < 1)
            return 0;
        
        rows = obstacleGrid.size();
        cols = obstacleGrid[0].size();

        paths = new int*[rows];
        for (i = 0; i < rows; i++)
        {
            paths[i] = new int[cols];
        }


        if (obstacleGrid[0][0] == 1)
        {
            paths[0][0] = 0;
        }
        else 
        {
            paths[0][0] = 1;
        }

        
        for (i = 1; i < rows; i++)
        {
            if (obstacleGrid[i][0] == 1)
            {
                paths[i][0] = 0;
            }
            else
            {
                paths[i][0] = paths[i - 1][0];
            }
        }
        
        for (i = 1; i < cols; i++)
        {
            if (obstacleGrid[0][i] == 1)
            {
                paths[0][i] = 0;
            }
            else
            {
                paths[0][i] = paths[0][i - 1];
            }
        }
        
        for (i = 1; i < rows; i++)
        {
            for (j = 1; j < cols; j++)
            {
                if (obstacleGrid[i][j] == 1)
                {
                    paths[i][j] = 0;
                }
                else
                {
                    paths[i][j] = paths[i - 1][j] + paths[i][j -1];
                }
                
            }
        }

        return paths[rows - 1][cols -1];
    }

    void dfs_next(const string& s, int beg, int step, string prev, vector<string> &addrs)
    {
        int val = 0;
        
        if (beg == s.size() && step == 4)
        {
            prev.resize(prev.size() - 1);
            addrs.push_back(prev);
            return;
        }
        
        if (s.size() - beg > (4 - step)*3)
        {
            return;
        }
        
        if (s.size() - beg < (4 - step))
        {
            return;
        }
        
        
        for (int i = beg; i < beg + 3 ; i++)
        {  
            val = val*10 + (s[i] - '0');

            if (val <= 255)
            {
                prev += s[i];
                dfs_next(s, i + 1, step + 1, prev + '.', addrs);
            }

            if (val == 0)
            {
                break;
            }
        }
    }
    vector<string> restoreIpAddresses(string s){
        vector<string> addrs;
        string str;

        dfs_next(s, 0, 0, str, addrs);

        return addrs;
    }

    void dfs_comb(vector<int>& candidates, vector<int>& res, int index, int remain, vector<vector<int> > &combs)
    {
        int i = 0;
        int next = 0;
        int size =  candidates.size();

        if (0 == remain)
        {
            combs.push_back(res);
            return;            
        }
    
        for (i = index; i < size; i++)
        {
            if (remain < candidates[i])
                return;
            
            res.push_back(candidates[i]);
            dfs_comb(candidates, res, i, remain - candidates[i], combs);
            res.pop_back();
        }
        
    }
    vector<vector<int> > combinationSum(vector<int>& candidates, int target) {
        vector<vector<int> > combs;
        vector<int> res;
        sort(candidates.begin(), candidates.end());
        dfs_comb(candidates, res, 0, target, combs);
        return combs;
    }

    void dfs_comb2(vector<int>& candidates, vector<int>& contain, int start, int remain, vector<vector<int> > &combs)
    {
        int index = 0;
        int prev = numeric_limits<int>::min();

        if (0 == remain)
        {
            combs.push_back(contain);
            return;            
        }

        for (index = start; index < candidates.size(); index++)
        {
            if (remain < candidates[index])
                return;

            if (prev == candidates[index])
                continue;

            prev = candidates[index];
            
            contain.push_back(candidates[index]);
            dfs_comb2(candidates, contain, index + 1, remain - candidates[index], combs);
            contain.pop_back();
        }
        
    }
    vector<vector<int> > combinationSum2(vector<int>& candidates, int target){
        vector<vector<int> > combs;
        vector<int>  vec;
        
        sort(candidates.begin(), candidates.end());
        
        for (int i = 0; i < candidates.size(); i++)
        {
		cout<<candidates[i]<<" ";
        }
        cout<<endl;

        dfs_comb2(candidates, vec, 0, target, combs);

        return combs;
    }

    void dfs_parenthesis(vector<string> &result, string str, int left, int right)
    {
        if (left == 0 && right == 0)
        {
            result.push_back(str);
            return;
        }
        else if (left < 0 || right < 0)
        {
            return;
        }

        if (left > right)
            return;
        
        if (left > 0)
        {
            dfs_parenthesis(result, str + "(", left - 1, right);
        }

        if (left < right)
        {
            dfs_parenthesis(result, str + ")", left, right - 1);
        }
    }
    vector<string> generateParenthesis(int n){
           string str;
           vector<string> legals;
           dfs_parenthesis(legals, str, n, n);

           return legals;
    }

    
    bool search(vector<vector<char> >& board, const string &word, int idx, int curx, int cury, vector<vector<bool> > &visited)
    {
        int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int chgx = 0;
        int chgy = 0;
        bool  ret = false;

        if (true == visited[curx][cury] || word[idx] != board[curx][cury])
        {
            return false;
        }

        if (idx == word.size() - 1)
        {
            return true;
        }


        visited[curx][cury] = true;

        for (int cnt = 0; cnt < 4; cnt++)
        {
            chgx = curx + offset[cnt][0];
            chgy = cury + offset[cnt][1];
            if (0 <= chgx && chgx < board.size() && 0 <= chgy && chgy < board[0].size())            
            {
                ret =  search(board, word, idx + 1, chgx, chgy, visited);
                if (ret == true)
                {
                    return ret;
                }
            }
        }
        visited[curx][cury] = false;

        return ret;
    }
    bool exist(vector<vector<char> >& board, string word) {
        int rows = board.size();
        int cols = board[0].size();

        vector<vector<bool> >   visited(rows, vector<bool>(cols, false));

        if (board.size() < 1 || board[0].size() < 1)
        {
            return false;
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (search(board, word, 0, i, j, visited))
                {
                    return true;
                }
            }
        }

        return false;
    }


    bool isValidNum(vector<vector<char> >& board, int x, int y){
        int begx = 0;
        int begy = 0;
        int idx;
        char c = board[x][y];
        for (idx = 0; idx < 9; idx++)
        {
            if (board[idx][y] == c && idx != x)
                return false;
        }

        for (idx = 0; idx < 9; idx++)
        {
            if (board[x][idx] == c && idx != y)
                return false;
        }

        begx = (x/3)*3;
        begy = (y/3)*3;
        for (int i = begx; i < begx + 3; i++)
        {
            for (int j = begy; j < begy + 3; j++)
            {
                if (board[i][j] == c && (i != x && j != y))
                {
                    return false;
                }
            }
        }

        return true;
    }
    bool seek(vector<vector<char> >& board, int pos)
    {
        int x = 0;
        int y = 0;
        bool ret;

        x = pos/9;
        y = pos%9;
        while (pos < 81)
        {
            if (board[x][y] == '.')
            {
                break;
            }
            
            pos++;
            if (y + 1 == 9)
            {
                y = 0;
                x += 1;
            }
            else
            {
                y += 1;
            }
        }

        if (pos >= 81)
        {
             /*
            for (int i = 0; i < board.size(); i++)
            {
                for (int j = 0; j < board[0].size(); j++)
                {
                    cout<<board[i][j]<<" ";
                }
                cout<<endl;
            }
            */
            return true;
        }
        
        for (int idx = 0; idx < 9; idx++)
        {
            board[x][y] = '1' + idx;
            if (isValidNum(board, x, y))
            {
                ret = seek(board, pos + 1);
                if (ret == true)
                {
                    return ret;
                }
            }
            board[x][y] = '.';
        }

        return false;
    }
    void solveSudoku(vector<vector<char> >& board){
        int rows = board.size();
        int cols = board[0].size();
        bool ret;
        
        if (9 != rows || 9 != cols)
        {
            return;
        }

        ret = seek(board, 0);      
    }
    bool canJump(vector<int>& nums) {
        int maxstep = 0;
        
        if (nums.size() < 2)
        {
            return true;
        }

        maxstep = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            if (maxstep > 0)
            {
                maxstep--;
                maxstep = max(maxstep, nums[i]);
            }
            else
            {
                return false;
            }
        }
    }

    int jump(vector<int>& nums){
        int ret = 0;
        int curfar = 0;
        int currch = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            if (currch < i)
            {
                ret++;
                currch = curfar;
            }

            curfar = max(curfar, nums[i] + i);
        }
    
        return ret;
    }
    /*
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        int trough = 0;
        if (prices.size() < 2)
            return 0;
        
        trough =  prices[0];
        for (int i = 0; i < prices.size(); i++)
        {
            profit = max(profit, prices[i] - trough);
            trough = min(prices[i], trough);
        }

        return profit;
    }
    */

    int maxProfit(vector<int>& prices) {
        int profit = 0;
        int gap = 0;        
        for (int i = 1; i < prices.size(); i++)
        {
            gap = prices[i] -prices[i - 1];
            if (gap > 0)
                profit += gap;
        }

        return profit;
    }

    int lengthOfLongestSubstring(string s){
        const int LETTERS = 256;
        int locs[LETTERS];
        int start = -1;
        int maxlen = 0;
        int offset = 0;

        fill(locs, locs + 256, -1);

        for (int idx = 0; idx < s.size(); idx++)
        {
            offset = s[idx] - 'a'; 
            if (locs[offset] >= start)
            {
                start = locs[offset];
            }
            
            maxlen = max((idx -start), maxlen);

            locs[offset] = idx;
        }

        return maxlen;
    }
    int maxArea(vector<int>& height){
        int left = 0;
        int right = height.size() - 1;
        int area = 0;
        int ret = 0;

        while (left < right)
        {
            area = min(height[left], height[right]) * (right - left);
            ret = max(area, ret);

            if (height[left] <= height[right])
            {
                left++;
            }
            else
            {
                right--;
            }
        }

        return ret;
    }
    int minimumTotal(vector<vector<int> >& triangle){    
            for (int i = triangle.size() - 2; i >= 0; i--)
            {
                for (int j = 0; j < triangle[i].size(); j++)
                {
                    triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
                }
            }

            return triangle[0][0];
    }

    int maxSubArray(vector<int>& nums) {
        int ret = numeric_limits<int>::min();
        int sum = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            ret = max(sum, ret);
            if (sum < 0)
            {
                sum = 0;
            }
        }

        return ret;
    }
    
    int minCut(string s){
        int n = s.size();
        if (n < 1)
            return 0;
        vector<vector<bool> > tag(n, vector<bool>(n, false));
        vector<int> cuts(n+1, -1);
        for (int i = 0; i < n; i++)
        {
            tag[i][i] = true;
        }

        for (int i = s.size() - 1; i >=0; i--)
        {
            cuts[i] = cuts[i+1] + 1;
            for (int j = i+1; j < n; j++)
            {
                if (s[i] == s[j] && (j - i == 1 ||tag[i + 1][j - 1]))
                {
                    tag[i][j] = true;
                    if (j == n -1)
                    {
                        cuts[i] = 0;
                    }
                    else if (cuts[i] > cuts[j+1] + 1)
                    {
                        cuts[i] = cuts[j+1] + 1;
                    }
                }
            }
        }

        return cuts[0];
    }

    bool isInterleave(string s1, string s2, string s3){
        int len1 = s1.length();
        int len2 = s2.length();
        if ((len1 + len2) != s3.length())
        {
            return false;
        }
        
        vector<vector<bool> >   record(len1 + 1, vector<bool>(len2 + 1, true));

        for (int i = 1; i <= len1; i++)
        {
            record[i][0] = record[i - 1][0] && (s1[i - 1] == s3[i - 1]);
        }

        for (int i = 1; i <= len2; i++)
        {
            record[0][i] = record[0][i - 1] && (s2[i - 1] == s3[i - 1]);
        }

        for (int i = 1; i <= len1; i++)
        {
            for (int j = 1; j <= len2; j++)
            {
                record[i][j] = (record[i - 1][j] && (s3[i+j - 1] == s1[i - 1])) ||
                                    (record[i][j - 1] && (s3[i+j - 1] == s2[j - 1]));
            }
        }

        return record[len1][len2];
    }


    //result[k][i][j]表示s1[i...i+k]是否可以由s2[j...j+k]变化得来
    bool isScramble(string s1, string s2){
        int len = 0;
        if (s1.length() != s2.length())
            return false;

        len = s1.length();
        if (0 == len)
            return true;


        bool result[len][len][len];
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
            {
                result[0][i][j] = (s1[i] == s2[j]);
            }
        }

        for (int k = 2; k <= len; k++)
        {
            for (int i = len - k; i >=0; i--)
            {
                for (int j = len - k; j >= 0; j--)
                {
                    bool  tmp = false;
                    for (int n = 1; n < k && !tmp; n++)
                    {
                         tmp= (result[n-1][i][j] && result[k-n-1][i+n][j+n]) || 
                                 (result[n-1][i][j+k-n] && result[k-n-1][i+n][j]);
                    }
                    result[k - 1][i][j] = tmp; 
                }
            }
        }

        return result[len-1][0][0];
    }

    int minPathSum(vector<vector<int> >& grid){
        const int rows = grid.size();
        const int cols  = grid[0].size();

        int f[cols];
        fill(f, f + cols, numeric_limits<int>::max());
        f[0] = 0;

        for (int i = 0; i < rows; i++)
        {
            f[0] = grid[i][0];
            for (int j = 1; j < cols; j++)
            {
                f[j] = min(f[j - 1], f[j]) + grid[i][j];
            }
        }

        return f[cols - 1];
    }

    int numDecodings(string s){
        int len = s.length();
        int idx = 0;

        if (len == 0)
        {
            return 0;
        }
        
        if (s[0] == '0')
        {
            return 0;
        }
        int f[len + 1];
        fill(f, f + len + 1, 0);

        f[0] = f[1] = 1;        
        
        for (int i = 1; i < len; i++)
        {
            idx = i + 1;
            if (s[i] == '0')
            {
                if (s[i - 1] == '1' || s[i - 1] == '2')
                {
                    f[idx] = f[idx - 2];
                }
                else
                {
                    return 0;
                }
            }
            else if (s[i - 1] == '0')
            {
                f[idx] = f[idx - 1];
            }
            else if ((s[i] <= '6' && s[i - 1] == '2') || s[i - 1] == '1')
            {
                f[idx] = f[idx - 2] + f[idx - 1];
            }
            else
            {
                f[idx] = f[idx - 1];
            }
        }

        return f[len];
    }
private:
    vector<vector<int> >  result;
    vector<string>  addrs;
    vector<vector<string> >  groups;
    int rows, cols;	
    int cnt;	
    vector<vector<int> > allset;
};

void test_searchrange()
{
	int a[] = {1,3,3,4,5};
	Solution  s;
	vector<int>  vec(a, a + 5);
	vector<int>  res;
	vector<vector<int> >  allres;
	res = s.searchRange(vec, 3);
	cout<<res[0]<<","<<res[1]<<endl;
}

void test_insert()
{
    int res;
    int a[] = {1,3,5};
    Solution  s;
    vector<int>  vec(a, a + 3);

    res = s.searchInsert(vec, 5);
    cout<<"Position: "<<res<<endl;
}

void test_subsets()
{
	int a[] = {1,3,3};
	Solution  s;
	vector<int>  vec(a, a + 3);
	vector<vector<int> >  res;
	res = s.subsetsWithDup(vec);
       //cout<<"Size:"<<res.size()<<endl;
       //cout<<"Begin:"<<res[1][0]<<endl;	
}

void test_permute()
{
	int a[] = {1,2,3};
	vector<int>  vec(a, a + 3);	
	vector<vector<int> >  res;	
	vector<int>  tmp;
	Solution  s;

	res = s.permute(vec);

	for (int i = 0; i < res.size(); i++)
	{
		tmp = res[i];
		for (int j = 0; j < tmp.size(); j++)
		{
			cout<<tmp[j]<<" ";
		}
		cout<<endl;
	}
}

void test_next()
{
	int a[] = {1,3,2};
	vector<int>  vec(a, a + 3);	
	vector<int>  tmp;
	Solution  s;


	if (true == s.nextpermute(vec))
	{
		for (int i = 0; i < vec.size(); i++)
		{
			cout<<vec[i]<<" ";
		}
		cout<<endl;
	}
}
        
void test_combine()
{
	vector<vector<int> >  res;	
	vector<int>  tmp;
	Solution  s;

	res = s.combine(4, 4);

	for (int i = 0; i < res.size(); i++)
	{
		tmp = res[i];
		for (int j = 0; j < tmp.size(); j++)
		{
			cout<<tmp[j]<<" ";
		}
		cout<<endl;
	}
}


void test_partition()
{
       string str = "aab";
	vector<vector<string> >  res;	
	vector<string>  tmp;
	Solution  s;

	res = s.partition(str);

	for (int i = 0; i < res.size(); i++)
	{
		tmp = res[i];
		for (int j = 0; j < tmp.size(); j++)
		{
			cout<<tmp[j]<<" ";
		}
		cout<<endl;
	}
}

void test_paths()
{
    Solution  s;
    int res = 0;
    res = s.uniquePaths(23, 12);

    cout<<"Paths:"<<res<<endl;
}

void test_pathswithobstacles()
{
    Solution  s;
    int res = 0;
    int a1[] = {0,1,0};
    int a2[] = {1,0,0};
    int a3[] = {0,0,0};
    vector<vector<int> >  mappath;
    vector<int> vec1(a1, a1 + 3);
    vector<int> vec2(a2, a2 + 3);
    vector<int> vec3(a3, a3 + 3);

    mappath.push_back(vec1);
    mappath.push_back(vec2);
    mappath.push_back(vec3);

    res = s.uniquePathsWithObstacles(mappath);

    cout<<"Paths:"<<res<<endl;
}

void testipaddress()
{
    Solution  s;
    string  str = "0000";
    vector<string> res;
    res = s.restoreIpAddresses(str);

    cout<<"Size:"<<res.size()<<endl;
    for (vector<string>::size_type i = 0; i < res.size(); i++)
    {
        cout<<"IP:"<<res[i]<<endl;
    }
    
}


void test_combs()
{
	int a[] = {2,2,};
	vector<int>  vec(a, a + 2);	
	vector<vector<int> >  result;
        vector<int> tmp;
	Solution  s;

        result = s.combinationSum(vec, 4);
        
        cout<<"size:"<<result.size()<<endl;
        for (int i = 0; i < result.size(); i++)
        {
             tmp = result[i];
		for (int j = 0; j < tmp.size(); j++)
		{
			cout<<tmp[j]<<" ";
		}
		cout<<endl;
        }
}


void test_combs2()
{
	int a[] = {10,1,2,7,6,1,5};
	vector<int>  vec(a, a + 7);	
	vector<vector<int> >  result;
        vector<int> tmp;
	Solution  s;

        result = s.combinationSum2(vec, 8);
        
        cout<<"size:"<<result.size()<<endl;
        for (int i = 0; i < result.size(); i++)
        {
             tmp = result[i];
		for (int j = 0; j < tmp.size(); j++)
		{
			cout<<tmp[j]<<" ";
		}
		cout<<endl;
        }
}

void test_parenthesis()
{
    vector<string>  result;
    Solution  s;

    result = s.generateParenthesis(3);

    for (int i  = 0; i < result.size(); i++)  
    {
        cout<<result[i]<<endl;
    }
}

void test_word()
{
    char a1[] = "ABCD";
    char a2[] = "SFCS";
    char a3[] = "ADED";
    
    vector<char> vec1(a1, a1 + 4);
    vector<char> vec2(a2, a2 + 4);
    vector<char> vec3(a3, a3 + 4);
    vector<vector<char> >  pannel;

    Solution  s;
    bool ret = false;

    cout<<"Initial: "<<ret<<endl;

    for (int i = 0; i < 3; i++)
    {
        pannel.push_back(vec1);
        pannel.push_back(vec2);
        pannel.push_back(vec3);
    }

    ret = s.exist(pannel, "ABCCED");

    cout<<"Result: "<<ret<<endl;
    
}

void test_sudoku()
{
    char a1[]  = "53..7.....";
    char a2[]  = "6..195...";
    char a3[]  = ".98....6.";
    char a4[]  = "8...6...3";
    char a5[]  = "4..8.3..1";
    char a6[]  = "7...2...6";
    char a7[]  = ".6....28.";
    char a8[]  = "...419..5";
    char a9[]  = "....8..79";

    Solution  s;
    vector<vector<char> >  pannel;
    pannel.push_back(vector<char>(a1, a1+9));
    pannel.push_back(vector<char>(a2, a2+9));
    pannel.push_back(vector<char>(a3, a3+9));
    pannel.push_back(vector<char>(a4, a4+9));
    pannel.push_back(vector<char>(a5, a5+9));
    pannel.push_back(vector<char>(a6, a6+9));
    pannel.push_back(vector<char>(a7, a7+9));
    pannel.push_back(vector<char>(a8, a8+9));
    pannel.push_back(vector<char>(a9, a9+9));

    s.solveSudoku(pannel);
    
    
}

void test_jump()
{
    bool ret;
    int a[] = {3,2,1,0,4};
    vector<int>  vec(a, a + 5);
    Solution  s;
    ret = s.canJump(vec);

    cout<<"Jump:"<<ret<<endl;
}

void test_jump2()
{
    int ret;
    int a[] = {2,3,1,1,4};
    vector<int>  vec(a, a + 5);
    Solution  s;
    ret = s.jump(vec);

    cout<<"Jump:"<<ret<<endl;
}

void test_maxProfit()
{
    int ret;
    int a[] = {2,3,1,1,4};
    vector<int>  vec(a, a + 5);
    Solution  s;
    ret = s.maxProfit(vec);

    cout<<"Profit: "<<ret<<endl;
}

void test_longestsubstr()
{
    int ret;
    string str = "abcd";
    Solution  s;
    
    ret = s.lengthOfLongestSubstring(str);

    cout<<"Length: "<<ret<<endl;
}

void test_maxSubArray()
{
    int ret;
    int a[] = {-2,-1,-3,-4,-1,-2,-1,5,-4};
    vector<int>  vec(a, a + 9);
    Solution  s;
    ret = s.maxSubArray(vec);

    cout<<"Max:"<<ret<<endl;    
}

void test_cut()
{
    int ret;
    string str = "aaab";
    Solution  s;
    ret = s.minCut(str);

    cout<<"Min Cut:"<<ret<<endl;        
}

void test_interleave()
{
    int ret;
    Solution  s;
    ret = s.isInterleave("aabcc", "dbbca", "aadbbbaccc");    

    cout<<"Result : "<<ret<<endl;
}



void test_decode()
{
    int ret = 0;
    string str = "1212";
    Solution s;

    ret = s.numDecodings(str);

    cout<<"Number: "<<ret<<endl;
}


int main()
{
       //test_insert();
       //test_permute();
       //test_next();
       //test_combine();
       //test_partition();
       //test_paths();
       //test_pathswithobstacles();
       //testipaddress();
       //test_combs2();
       //test_parenthesis();
       //test_word();
       //test_sudoku();
       //test_jump();
       //test_jump2();
       //test_longestsubstr();
       //test_maxSubArray();
       //test_cut();
       //test_interleave();
       test_decode();
	return 1;
}



