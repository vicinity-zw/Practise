#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <limits>
#include <limits.h>
#include <float.h>
#include <set>
#include <sstream>
#include <queue>
#include <math.h>
#include <string.h>

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class BSTIterator {
public:
    stack<TreeNode *>  stk;
    BSTIterator(TreeNode *root) {
        while (root)
        {
            stk.push(root);
            root = root->left;
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !stk.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode* cur = stk.top();
        stk.pop();

        if  (cur->right)
        {
            TreeNode *pTmp = cur->right;
            while (pTmp)
            {
                stk.push(pTmp);
                pTmp = pTmp->left;
            }
        }

        return cur->val;
    }
};
/*
class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		ostringstream output;
		queue<TreeNode*>q;
		if (root)
			q.push(root);

		while (!q.empty())
		{
			TreeNode *t = q.front();
			q.pop();	
			if (t)
			{
				output<<t->val<<" ";
				q.push(t->left);
				q.push(t->right);
			}
			else
			{
				output<<"# ";
			}
		}
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		if (data.length() < 1)
			return NULL;
		istringstream input(data);
		queue<TreeNode *> q;
		string val;
		input >> val;
		TreeNode *res = new TreeNode(stoi(val));
		TreeNode *cur = res;
		q.push(cur);

		while (!q.empty())
		{
			TreeNode *t = q.front();
			q.pop();

			if (!(input >> val))
				break;
			if (val != "#")
			{
				cur = new TreeNode(stoi(val));
				q.push(cur);
				t->left = cur;
			}

			if (!(input >> val))
				break;
			if (val != "#")
			{
				cur = new TreeNode(stoi(val));
				q.push(cur);
				t->right = cur;
			}

		}
            return res;
	}
};
*/


class Solution {
public:
    string shortestPalindrome(string s) {  
        string str = s;  
        reverse(str.begin(), str.end());  
        str = s + "#" + str;  
        int len1 = s.size(), len2 = str.size();  
        vector<int> vec(len2 + 1, 0);  

        int k = 0;
        for(int i = 1; i < len2; i++)  
        {  
            while(k > 0 && str[k] != str[i]) 
                k = vec[k];  
            if (str[i] == str[k])
                k++;
            vec[i + 1] = k;  
        }  

        return str.substr(len1 + 1, len1 - vec[len2]) + s;  
    }  

    /*
    string shortestPalindrome(string s){
        int pos = longestPalindrome(s);
        string res;
        res = s.substr(pos);
        reverse(res.begin(), res.end());
        return res + s;
    }

    int longestPalindrome(string &s) {
        string t = "$#";
        for (int i = 0; i < s.size(); i++)
        {
            t += s[i];
            t += '#';
        }

        vector<int>  p(t.size(), 0);
        int id = 0, mx = 0, resId = 0, res = 0;
        for (int i = 0; i < t.size(); i++)
        {
            int mx = id + p[id];
            p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
            while (t[i + p[i]] == t[i - p[i]])
                ++p[i];

            if (mx < i + p[i])
            {
                id = i;
            }

            if (p[i] == i)
                res = max(res, i);
        }

        return res - 1;
    }
    */

    vector<int> findOrder(int numCourses, vector<pair<int, int> > & prerequisites){
        vector<vector<int> >  arr(numCourses, vector<int>(numCourses, 0));
        vector<int>  indegree(numCourses, 0);
        //typedef vector<pair<int, int> >::iterator ITER
        for (vector<pair<int, int> >::iterator itr = prerequisites.begin(); itr != prerequisites.end(); itr++)
        {
            arr[itr->second][itr->first] = 1;
            indegree[itr->first] += 1;
        }

        vector<int> res;
        int cnt = 0;
        deque<int>  deq;
        for (int i = 0; i < indegree.size(); i++)
        {
            if (0 == indegree[i])
            {
                deq.push_back(i);
                cnt += 1;
                res.push_back(i);
            }
        }

        while (!deq.empty())
        {
            int course = deq.front();
            deq.pop_front();
            for (int i = 0; i < numCourses; i++)
            {
                if (1 == arr[course][i])
                {
                    indegree[i] -= 1;
                    if (0 == indegree[i])
                    {
                        deq.push_back(i);
                        res.push_back(i);
                        cnt += 1;
                    }
                }
            }
        }

        if (cnt < numCourses)
            res.clear();

        return res;
    }

    /*
    vector<pair<int, int> > getSkyline(vector<vector<int> >& buildings){
        vector<pair<int, int> > height;
        for (auto &b : buildings)
        {
            height.push_back({b[0], -b[2]});
            height.push_back({b[1], b[2]});
        }

        sort(height.begin(), height.end());
        multiset<int>   heap;
        heap.insert(0);
        vector<pair<int, int> > res;

        int pre = 0, cur = 0;
        for (auto &h : height)
        {
            if (h.second < 0)
            {
                heap.insert(-h.second);
            }
            else
            {
                heap.erase(heap.find(h.second));
            }

            cur = *heap.begin();
            if (cur != pre)
            {
                res.push_back({h.first, cur});
                pre = cur;
            }
        }

        return res;
    }
    */
    int countNodes(TreeNode* root) {
        if (NULL == root)
            return 0;

        int h = 0;
        TreeNode *lchild = root, *rchild = root;

        while (lchild && rchild)
        {
            lchild = lchild->left;
            rchild = rchild->right;
            h++;
        }

        if (lchild == rchild)
            return (1<<h) - 1;

        return 1 + countNodes(root->left) + countNodes(root->right);
    }

    int countDigitOne(int n){
        int ones = 0;
        for (long m = 1; m <= n; m *= 10)
        {
            long a = n/m;
            long b = n%m;

            ones += (a + 8)/10*m;
            if (a == 1)
                ones = b + 1;
        }

        return ones;
    }


    int numSquares(int n){
        vector<int> dp(n + 1, n);

        dp[0] = 0;
        for (int i = 0; i <= n; i++)
        {
            for (int j = 1; i + j * j <= n; j++)
            {
                dp[i + j * j] = min(dp[i + j * j], dp[i] + 1);
            }
        }
        
        return dp.back();
    }

    ListNode* oddEvenList(ListNode* head){
        if (NULL == head || NULL == head->next)
            return head;

        ListNode  *oddList = head;
        ListNode  *evenList = head->next;

        ListNode *tmp = head, *podd = head, *peven = head->next;
        int n = 1;

        
        tmp = tmp->next->next;
        while (tmp)
        {
            if (1 == n)
            {
                podd->next = tmp;
                podd = podd->next;
                n = 0;
            }
            else
            {
                peven->next = tmp;
                peven = peven->next;
                n = 1;
            }

            tmp = tmp->next;
        }

        podd->next = evenList;
        peven->next = NULL;

        return head;
    }

    /*
    vector<string>  res;
    void addOperatorsDFS(string num, int target, long long diff, long long curnum, string dummy)
    {
        if (num.size() == 0 && curnum == target)
        {
            res.push_back(dummy);
        }

        for (int i = 1; i <= num.length(); i++)
        {
            string cur = num.substr(0, i);
            if (cur.size() > 1 && cur[0] == '0')
                return;

            string next = num.substr(i);
            long long tmp = stoll(cur);
            if (dummy.size() > 0)
            {
                addOperatorsDFS(next, target, tmp, curnum + tmp,  dummy + "+" + cur);
                addOperatorsDFS(next, target, -tmp, curnum - tmp,  dummy + "-" + cur);
                addOperatorsDFS(next, target, diff * tmp, (curnum - diff) + diff * tmp,  dummy + "*" + cur);
            }
            else
            {
                addOperatorsDFS(next, target, tmp, tmp, cur);
            }
        }
    }
    vector<string> addOperators(string num, int target) {
        addOperatorsDFS(num, target, 0, 0, "");
        return res;
    }
    */

    int maxProfit(vector<int>& prices){
        int buy = INT_MIN, pre_buy = 0;
        int sell = 0, pre_sell = 0;
        for (int i = 0; i < prices.size(); i++)
        {
            int price = prices[i];
            pre_buy = buy;
            buy = max(pre_sell - price, pre_buy);
            pre_sell = sell;
            sell = max(pre_buy + price, pre_sell);
        }

        return sell;
    }

    vector<int> findMinHeightTrees(int n, vector<pair<int, int> >& edges){
        vector<vector<int> >  depths(n, vector<int>(n, INT_MAX));
        //typedef vector<pair<int, int> >::iterator   ITER
        for (vector<pair<int, int> >::iterator  itr = edges.begin(); itr != edges.end(); itr++)
        {
            depths[itr->first][itr->second] = 1;
            depths[itr->second][itr->first] = 1;
        }

        for (vector<pair<int, int> >::iterator  itr = edges.begin(); itr != edges.end(); itr++)
        {
            for (int i = 0; i < n; i++)
            {
                if (depths[i][itr->first] != 0)
                    depths[i][itr->second] = depths[i][itr->first] + 1;
                else if (depths[i][itr->second] != 0)
                    depths[i][itr->first] = depths[i][itr->second] + 1;    
            }
        }

        int minheight = 0;
        vector<int> heights(n, 0);
        for (int i = 0; i < n; i++)
        {
            int height = 0;
            for (int j = 0; j < n; i++)
            {
                height = max(height, depths[i][j]);
            }
            heights[i] = height;
            minheight = min(height, minheight);
        }

        vector<int>  res;
        for (int i = 0; i < n; i++)
        {
            if (heights[i] == minheight)
                res.push_back(i);
        }
        return res;
    }

    static bool envelope_cmp(const pair<int, int> &a, const pair<int, int> &b)
    {
        if (a.first == b.first)
            return a.second > b.second;
        return a.first < b.first;
    }
    
    int maxEnvelopes(vector<pair<int, int> >& envelopes){
        vector<int> dp;
        if (envelopes.size() < 1)
            return 0;
        
        sort(envelopes.begin(), envelopes.end(), envelope_cmp);

        dp.push_back(envelopes[0].second);
        for (int i = 1; i < envelopes.size(); i++)
        {
            int left = 0, right = dp.size() - 1;
            int t = envelopes[i].second;

            if (t > dp[right])
                dp.push_back(t);
            else
            {
                int mid = 0;
                while (left <= right)
                {  
                    mid = left + (right - left)/2;
                    if (dp[mid] < t)
                        left = mid + 1;
                    else if (dp[mid] > t)
                        right = mid - 1;
                    else
                        break;
                }

                if (left > right)
                    dp[left] = t;
            }
        }

        return dp.size();
    }

    int wiggleMaxLength(vector<int>& nums){
        int n = nums.size();
        int res;

        if (n == 0)
            return 0;
        
        vector<int> inc = vector<int>(n, 1);
        vector<int> dec = vector<int>(n, 1);
        for (int i = 1; i < n; i++)
        {
            if (nums[i] > nums[i - 1])
            {
                inc[i] = dec[i - 1] + 1;
                dec[i] = dec[i - 1];
            }
            else if (nums[i] < nums[i - 1])
            {
                dec[i] = inc[i - 1] + 1;
                inc[i] = inc[i - 1] ;
            }
            else
            {
                inc[i] = inc[i - 1];
                dec[i] = dec[i - 1];
            }    
        }

        return max(dec[n - 1], inc[n - 1]);
    }

    /*
    vector<int> lexicalOrder(int n){
        vector<int>  ans(n, 0);
        int top = 0;
        int bound = 0;
        int pos = 0;
        int tmp = n;
        
        if (n <= 0)
            return vector<int>();
        while (n)
        {
            top += 1;
            bound = n;
            n = n/10;
        }

        for (int first = 1; first < 10; first++)
        {
            int num = 0;
            int digit = (first > bound) ? (top - 1): top;
            
            while (num < digit)
            {
                int cnt = 0;
                int base = 0;
                if (first == bound && num == digit - 1)
                {
                    cnt = tmp - bound * pow(10, num) + 1;
                    base = pow(10, num) * bound;
                }
                else
                {
                    cnt = pow(10, num);
                    base = cnt * first;
                }

                
                for (int j = 0; j < cnt; j++)
                {
                    ans[pos++] = base + j;
                }

                num++;
            }
        }
        return ans;
    }
    */

    vector<int> lexicalOrder(int n){
        vector<int>  ans;
        
        if (n <= 0)
            return ans;

        for (int first = 1; first < 10; first++)
        {
            lexicaldfs(first, n, ans);
        }

        return ans;
    }
    
    void lexicaldfs(int cur, int n, vector<int> &res){
        if (cur > n)
            return;
        res.push_back(cur);
        for (int i = 0; i <= 9; i++)
        {
            int tmp = cur*10 + i;
            if (tmp <= n)
                lexicaldfs(tmp, n, res);
            else
                break;
        }
    }


    
    int findKthNumber(int n, int k){
        int cur = 1;
        k = k - 1;
        while (k > 0)
        {
            int steps = calsteps(n , cur, cur + 1);
            if (steps <= k)
            {
                cur += 1;
                k -= steps;
            }
            else
            {
                cur *= 10;
                k -= 1;
            }
        }

        return cur;
    }

    int calsteps(int n, long n1, long n2)
    {
        int steps = 0;
        while (n1 <= n)
        {
            //steps += min(n + 1, n2) - n1;
            steps +=(n + 1, n2) - n1;
            n1 *= 10;
            n2 *= 10;
        }
        return steps;
    }

    bool canPartition(vector<int>& nums){
        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];    
        }

        if (sum & 1)
            return false;

        vector<int> dp(sum/2 + 1, 0);
        
        dp[0] = 1;
        for (int i = 1; i < nums.size(); i++)
        {
            for (int j = sum/2; j >= nums[i]; j--)
            {
                dp[j] = dp[j] || dp[j - nums[i]];
            }
        }

        return dp[sum/2];
    }

    int characterReplacement(string s, int k) {
        int res = 0;
        int maxcnt = 0;
        int start = 0;
        vector<int> counts(26, 0);
        for (int i = 0; i < s.length(); i++)
        {
            maxcnt = max(maxcnt, ++counts[s[i] - 'A']);
            while (i - start + 1 - maxcnt > k)
            {
                counts[s[start] - 'A'] -= 1;
                ++start;
            }
            res = max(res, i - start + 1);
        }

        return res;
    }

    bool find132pattern(vector<int>& nums) {
        int third = INT_MIN;
        stack<int>  s;
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            if (nums[i] < third)
            {
                return true;
            }
            else 
            {
                while (!s.empty() && nums[i] > s.top())
                {
                    third = s.top();
                    s.pop();
                }
            }

            s.push(nums[i]);
        }

        return false;
    }

    void wiggleSort(vector<int>& nums){
        int n = nums.size();
        if (n < 2)
            return;

        for (int i = 1; i < n; i++)
        {
            if ((i % 2 == 1) && nums[i] < nums[i - 1] ||
                (i % 2 == 0) && nums[i] > nums[i - 1])
                swap(nums[i - 1], nums[i]);
        }
            
    }
};


void test_shortestPalindrome()
{
    Solution s;
    string strs[5] = {"aaaabbaa", "aacecaaa", "abcd", "aaa", "a"};

    for (int i = 0; i < 5; i++)
    {
        string res = s.shortestPalindrome(strs[i]);
        cout<<strs[i]<<"  : "<<res<<endl;
    }
}

void test_square()
{
    Solution s;
    int arr[] = {12, 15, 18, 21};
    int n = sizeof(arr)/sizeof(int);

    for (int i = 0; i < n; i++)
    {
        int res = s.numSquares(arr[i]);
        cout<<arr[i]<<"  :  "<<res<<endl;
    }
}

void test_wiggleseq()
{
    Solution s;
    int arr[] = {1,7,4,9,2,5};
    int n = sizeof(arr)/sizeof(int);

    vector<int>  vec(arr, arr + n);
    int res = 0;

    res = s.wiggleMaxLength(vec);
    cout<<"Max Length: "<<res<<endl;
}


void test_lexicalOrder()
{
    Solution s;
    vector<int> ans;
    ans = s.lexicalOrder(123);

    for (int i = 0; i < ans.size(); i++)
    {
        cout<<ans[i]<<"  ";
    }
    cout<<endl;
}

void test_findKthNumber()
{
    Solution s;
    int ans;
    ans = s.findKthNumber(123, 2);

    cout<<"Result: "<<ans<<endl;
}


void test_canPartition()
{
    Solution s;
    int arr[] = {1,7,4,9,2,5};
    int n = sizeof(arr)/sizeof(int);
    vector<int> vec(arr, arr + n);
    
    bool res;
    res = s.canPartition(vec);
    cout<<"Result: "<<res<<endl;
}


int main()
{
    //test_shortestPalindrome();
    //test_square();
    //test_wiggleseq();
    //test_lexicalOrder();
    //test_findKthNumber();
    test_canPartition();
    return 1;
}


