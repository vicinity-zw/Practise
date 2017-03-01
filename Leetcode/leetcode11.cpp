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


struct TriNode {
    TriNode *ch[26];
    bool isWord;
    TriNode() : isWord(false) {
        for (int i = 0; i < 26; i++) 
            ch[i] = NULL;
    }
};

struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class NumArray {
public:
    NumArray(vector<int> &nums) {
        c.resize(nums.size() + 1);
        m_nums = nums;
        for (int i = 0; i < nums.size(); i++)
        {
            add(i + 1, nums[i]);
        }
    }
    
    void update(int i, int val) {
        int ori = m_nums[i];
        int delta = val - ori;
        add(i + 1, delta);
    }

    int sumRange(int i, int j) {
        return sum(j + 1) - sum(i);
    }

    void add(int pos, int value)
    {
        while (pos < c.size())  
        {
            c[pos] += value;
            pos += lowbit(pos);
        }
    }
    
    int lowbit(int pos){
        return pos & (-pos);
    }

    int sum(int pos){
        int res = 0;
        while (pos > 0)
        {
            res += c[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
private:
    vector<int> m_nums;
    vector<int> c;    
};



class NumMatrix {
public:
    NumMatrix(vector<vector<int> > &matrix) {
        int rows = matrix.size() + 1;
        int cols = matrix[0].size() + 1;
        sums.resize(rows,  vector<int>(cols));

        for (int i = 0; i < rows; i++)
        {
            sums[i][0] = 0;
        }
        
        for (int i = 0; i < cols; i++)
        {
            sums[0][i] = 0;
        }
        
        for (int i = 1; i < rows; i++)
        {
            for (int j = 1; j < cols; j++)
            {
                sums[i][j] = sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1] + matrix[i - 1][j - 1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        int res = 0;
        int m = sums.size(), n = sums[0].size();
        if (row1 < 0 || row1 >= m || col1 < 0 || col1 >= n || row2<0 || row2 >= m ||
            col2<0 || col2 >= n || row1 >row2 || col1 > col2)
        {
            return 0;
        }
        res = sums[row1][col1] + sums[row2 + 1][col2 + 1] - sums[row2 + 1][col1] -
                sums[row1][col2 + 1];
        return res;
    }
    
private:
    vector<vector<int> >  sums;
};

/*
class AllOne {
public:
    // Initialize your data structure here. 
    AllOne() {}
    
    // Inserts a new key <Key> with value 1. Or increments an existing key by 1. 
    void inc(string key) {
        if (!m.count(key)) 
        {
            if (buckets.empty() || buckets.back().val != 1) 
            {
                auto newBucket = buckets.insert(buckets.end(), {1, {key}});
                m[key] = newBucket;
            } 
            else 
            {
                auto newBucket = --buckets.end();
                newBucket->keys.insert(key);
                m[key] = newBucket;
            }
        } 
        else 
        {
            auto curBucket = m[key], lastBucket = (--m[key]);
            if (lastBucket == buckets.end() || lastBucket->val != curBucket->val + 1) 
            {
                auto newBucket = buckets.insert(curBucket, {curBucket->val + 1, {key}});
                m[key] = newBucket;
            } 
            else 
            {
                lastBucket->keys.insert(key);
                m[key] = lastBucket;
            }
            curBucket->keys.erase(key);
            if (curBucket->keys.empty()) 
                buckets.erase(curBucket);
        }
    }
    
    // Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. 
    void dec(string key) {
        if (!m.count(key)) 
            return;
        auto curBucket = m[key];
        if (curBucket->val == 1) 
        {
            curBucket->keys.erase(key);
            if (curBucket->keys.empty()) 
                buckets.erase(curBucket);
            m.erase(key);
            return;
        }
        auto nextBucket = ++m[key];
        if (nextBucket == buckets.end() || nextBucket->val != curBucket->val - 1) 
        {
            auto newBucket = buckets.insert(nextBucket, {curBucket->val - 1, {key}});
            m[key] = newBucket;
        } 
        else 
        {
            nextBucket->keys.insert(key);
            m[key] = nextBucket;
        }
        curBucket->keys.erase(key);
        if (curBucket->keys.empty()) 
            buckets.erase(curBucket);
    }
    
    // Returns one of the keys with maximal value. 
    string getMaxKey() {
        return buckets.empty() ? "" : *(buckets.begin()->keys.begin());
    }
    
    // Returns one of the keys with Minimal value. 
    string getMinKey() {
        return buckets.empty() ? "" : *(buckets.rbegin()->keys.begin());
    }
private:
    struct Bucket { 
        int val; 
        unordered_set<string> keys;
    };
    list<Bucket> buckets;
    unordered_map<string, list<Bucket>::iterator> m;
};
*/

class Solution {
public:
    /*
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node){
        if (NULL == node)
            return NULL;
        
        unordered_set<UndirectedGraphNode *>  st;
        UndirectedGraphNode *pTmp = NULL;
        for (size_t i = 0; i < node.neighbors.size(); i++)
        {
              pTmp = node.neighbors[i];
        }
        

        return pTmp;
    }
    */

    bool isPalindrome(const string &s, int left, int right){
        while (left <= right)
        {
            if (s[left] != s[right])
                return false;
            left++;
            right--;
        }
        return true;
    }
    
    void  dfs(string s, vector<string> &vec, vector<vector<string> > &ans){
        if (s.size() < 1)
        {
            ans.push_back(vec);
            return;
        }

        for (int i = 0; i < s.size(); i++)
        {
            if (isPalindrome(s, 0, i))
            {
                vec.push_back(s.substr(0, i + 1));
                dfs(s.substr(i + 1), vec, ans);
                vec.pop_back();
            }
        }
    }
    
    vector<vector<string> > partition(string s){
        vector<vector<string> >  ans;
        vector<string>  vec;
        dfs(s, vec, ans);
        return ans;
    }

    void minheap(vector<ListNode*>  &heap, int i)
    {
        int lchild = 2*i + 1, rchild = lchild + 1;
        int length = heap.size();
        while (rchild < length)
        {
            if (heap[i]->val <= heap[lchild]->val && heap[i]->val <= heap[rchild]->val)
                return;

            if (heap[lchild]->val <= heap[rchild]->val)
            {
                swap(heap[lchild], heap[i]);
                i = lchild;
            }
            else
            {
                swap(heap[rchild], heap[i]);
                i = rchild;
            }
            lchild = 2*i + 1;
            rchild = lchild + 1;
        }

        if (lchild < length && heap[lchild]->val < heap[i]->val)
            swap(heap[lchild], heap[i]);

    }

    void makeheap(vector<ListNode*>  &heap)
    {
        for (int i = heap.size()/2 - 1; i >= 0; i--)
        {
            minheap(heap, i);
        }
    }
    
    ListNode* mergeKLists(vector<ListNode*>& lists){
        if (lists.empty())        
            return NULL;

        vector<ListNode *>  heap;
        for (int i = 0; i < lists.size(); i++)
        {
            if (lists[i])
                heap.push_back(lists[i]);
        }
        makeheap(heap);

        ListNode  head(-1);
        ListNode *p = &head;
        while (!heap.empty())
        {
            ListNode* pminNode = heap[0];

            if (heap[0]->next)
            {
                heap[0] = heap[0]->next;
            }
            else
            {
                swap(heap[0], heap[heap.size() - 1]);
                heap.pop_back();
            }
            p->next = pminNode;
            p = pminNode;

            minheap(heap, 0);
                
        }

        return head.next;
    }

    int maxProduct(vector<int>& nums) {
        
        if (nums.size() < 1)
            return 0;
        
        if (1 == nums.size())
            return nums[0];

        int min_local = nums[0];
        int max_local = nums[0];
        int res = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            int tmp = max_local;
            max_local = max(max(nums[i] * max_local, nums[i]), nums[i] * min_local);
            min_local = min(min(nums[i] * tmp, nums[i]), nums[i] * min_local);
            cout<<"Max: "<<max_local<<"   Min:"<<min_local<<endl;
            res = max(res, max_local);
        }

        return res;
    }


    vector<int> findRightInterval(vector<Interval>& intervals){
        map<int, int>  startmap;

        vector<int> res(intervals.size(), -1);
        for (int i = 0; i < intervals.size(); i++)
        {
            startmap.insert(pair<int, int>(intervals[i].start, i));
        }

        map<int, int>::iterator itr;
        for (int i = 0; i < intervals.size(); i++)
        {
            int pos = intervals[i].end;
            itr = startmap.lower_bound(pos);
            if (itr != startmap.end())
                res[i] = itr->second;
        }

        return res;
    }

    /*
    void   heapadjust(vector<int> &nums, int i){   
        int lchild = 2*i + 1, rchild = lchild + 1;
        int length = nums.size();
        while (rchild < length)
        {
            if (nums[i] >= nums[lchild] && nums[i] >= nums[rchild])
                return;

            if (nums[lchild] >= nums[rchild])
            {
                swap(nums[lchild], nums[i]);
                i = lchild;
            }
            else
            {
                swap(nums[rchild], nums[i]);
                i = rchild;
            }
            lchild = 2*i + 1;
            rchild = lchild + 1;
        }

        if (lchild < length && nums[lchild] > nums[i])
            swap(nums[lchild], nums[i]);

    }
    
    int findKthLargest(vector<int>& nums, int k) {
        int res = 0;
        for (int i = nums.size()/2 - 1; i >= 0; i--)
            heapadjust(nums, i);

        for (int i = 0; i < k; i++)
        {
            res = nums[0];
            swap(nums[0], nums[nums.size() - 1]);
            nums.pop_back();
            heapadjust(nums, 0);
        }
        return res;
    }
    */

    int findKthLargest(vector<int>& nums, int k) {
        int L = 0, R = nums.size() - 1;
        while (L < R) 
        {
            int left = L, right = R;
            int key = nums[left];
            while (left < right) 
            {
                while (left < right && nums[right] < key) 
                    --right;
                nums[left] = nums[right];
                    
                while (left < right && nums[left] >= key) 
                    ++left;
                nums[right] = nums[left];
            }
            
            nums[left] = key;
            if (left == k - 1) 
                return nums[k - 1];
            else if (left > k - 1) 
                R = left - 1;
            else 
                L = left + 1;
        }
        return nums[k - 1];
    }

    
    int maxProductII(vector<string>& words){
        int maxlen = 0;
        vector<int> mask(words.size(), 0);
        for (int i = 0; i < words.size(); i++)
        {
            for (int k = 0; k < words[i].length(); k++)
            {
                mask[i] |= 1<<(words[i][k] - 'a');
            }

            for (int j = 0; j < i; j++)
            {
                if (!(mask[i] & mask[j]))
                    maxlen = max(maxlen, int(words[i].length() * words[j].length()));
            }
        }
        
        return maxlen;
    }

    string longestPalindrome(string s){
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
            p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
            while (t[i + p[i]] == t[i - p[i]])
                ++p[i];

            if (mx < i + p[i])
            {
                mx = i + p[i];
                id = i;
            }

            if (res < p[i])
            {
                res    = p[i];
                resId = i;
            }
        }

        cout<<"Index: "<<((resId - res)/2)<<"Radius: "<<res<<endl;
        return s.substr((resId - res)/2, res - 1);
    }


    int findMin(vector<int>& nums){
        int left = 0;
        int right = nums.size() - 1;

        while (left < right && nums[left] >= nums[right])
        {
            int mid = left + (right - left)/2;

            if (nums[left] > nums[mid])
            {
                right = mid ;
            }
            else if (nums[left] == nums[mid])
            {
                left++;
            }
            else
            {
                left = mid + 1;
            }
        }
        return nums[left];
        
    }

    bool increasingTriplet(vector<int>& nums){
        int m1 = INT_MAX;
        int m2 = INT_MAX;
        
        for (int i = 0; i < nums.size(); i++)
        {
            if (m1 >= nums[i])
                m1 = nums[i];
            else if (m2 >= nums[i])
                m2 = nums[i];
            else
                return true;
        }

        return false;
    }

    int findDuplicate(vector<int>& nums){
        int slow = 0;
        int fast = 0;
        
        do{
            slow = nums[slow];
            fast = nums[nums[fast]];
        }while (slow != fast);

        int find = 0;
        while (find != slow)
        {
            find = nums[find];
            slow = nums[slow];
        }
        return find;
    }

    int rangeBitwiseAnd(int m, int n){
        int i = 0;
        while (m != n)
        {
            m >>= 1;
            n >>= 1;
            i++;
        }

        return (m<<i);
    }

    vector<string> summaryRanges(vector<int>& nums){
        vector<string> res;
        int i = 0, n = nums.size();
        while (i < n) {
            int j = 1;
            while (i + j < n && nums[i + j] - nums[i] == j) 
                ++j;
            //res.push_back(j <= 1 ? to_string(nums[i]) : to_string(nums[i]) + "->" + to_string(nums[i + j - 1]));
            i += j;
        }
        return res;
    }

    int integerReplacement(int n) {
        long long t = n;
        int cnt = 0;
        while (t > 1)
        {
            ++cnt;
            if (t & 1)
            {
                if ((t & 2) && (t != 3))
                    ++t;
                else
                    --t;
            }
            else
                t >>= 1;
        }
        return cnt;
    }


    int getMaxAmount(vector<vector<int> > &amounts, int from, int to){
        if (from >= to)
            return 0;

        if (amounts[from][to] > 0)
            return amounts[from][to];

        int min_amount = INT_MAX;
        for (int i = from; i <= to; i++)
        {
            int cost = i + max(getMaxAmount(amounts, from, i - 1), getMaxAmount(amounts, i + 1, to));
            min_amount = min(min_amount, cost);
        }
        amounts[from][to] = min_amount;
        
        return min_amount;
    }
    int getMoneyAmount(int n){
        vector<vector<int> >  amounts(n + 1, vector<int>(n + 1, 0));   
        return getMaxAmount(amounts, 1, n);        
    }

    int longestSubstring(string s, int k){
        int cnt[26] = {0};
        int qualified = 0;
        int flag[26] = {0};
        int unqualified = 0;
        for (int i = 0; i < s.length(); i++)
        {
            cnt[s[i] - 'a'] += 1;
        }

        for (int i = 0; i < 26; i++)
        {
            if (cnt[i] >= k)
            {
                qualified += cnt[i];
            }
            else
            {
                flag[i] = 1;
                unqualified += cnt[i];
            }
        }

        if (qualified == s.length())
            return s.length();

        if (unqualified == s.length())
            return 0;

        int res = 0;
        int beg = 0;
        for (int i = 0 ; i < s.length(); i++)
        {
            if (1 == flag[s[i] - 'a'])
            {
                if (i - beg >= k) 
                {
                    cout<<"String1: "<<s.substr(beg, i - beg)<<endl;
                    int tmp = longestSubstring(s.substr(beg, i - beg), k);
                    res = max(res, tmp);
                }
                beg = i + 1;
            }
        }

        if (beg < s.length())
        {
            cout<<"String2: "<<s.substr(beg)<<endl;
            res = max(res, longestSubstring(s.substr(beg), k));
        }

        return res;
        
    }

    vector<int> maxSlidingWindow(vector<int>& nums, int k){
        vector<int> res;
        deque<int>  q;

        for (int i = 0; i < nums.size(); i++)
        {
            if (!q.empty() && q.front() == i - k)
                q.pop_front();
            while (!q.empty() && nums[q.back()] < nums[i])
                q.pop_back();

            q.push_back(i);

            if (i >= k - 1)
                res.push_back(nums[q.front()]);
        }

        return res;
    }


    string fractionToDecimal(int numerator, int denominator){
        string res = "";
        if (0 == numerator)
            return "0";

        if (0 == denominator)
            return res;

        long long n = numerator;
        long long d = denominator;

        if ((n < 0 && d >0)  || (n > 0 && d < 0))
            res += "-";

        if (n < 0)
            n = -n;
        if (d < 0)
            d = -d;

       
        res += char(n/d);
        n = n%d;
        if (0 == n)
        {
            cout<<res<<endl;
            return res;
        }
        
        res += '.';


        int pos = res.size();
        map<long long, int> record;

        while (n != 0)
        {
            if (record.find(n) != record.end())
            {
                res.insert(res.begin() + record[n], '(');
                res += ')';
                return res;
            }

            record[n] = pos;
            res += char(n * 10/d + '0');
            pos++;
            n = (n * 10)%d;
        }
        
        return res;
    }    

    void gameOfLife(vector<vector<int> >& board){
        int m = board.size();
        int n = m ? board[0].size() : 0;
        int dx[8] = {-1, -1,  -1, 0, 0, 1, 1, 1};
        int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int cnt = 0;
                for (int k = 0; k < 8; k++)
                {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y <= n && (1 == board[x][y] || 2 == board[x][y]))
                    {
                        cnt++;
                    }
                }

                if (board[i][j] && (cnt < 2 || cnt > 3))
                {
                    board[i][j] = 2;
                }
                else if (!board[i][j] && cnt == 3)
                {
                    board[i][j] = 3;
                }
            }
        }


        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                board[i][j] &= 1;
            }
        }
    }

    bool frog_dfs(vector<int> &stones, int idx, int steps){
        if (idx == stones.size() - 1)
            return true;

        int pos[3] = {0};
        for (int i = 0; i < 3; i++)
        {
            pos[i] = stones[idx] + steps + i - 1;
        }

        bool flag[3] = {false, false, false};
        for (int i = idx + 1; i < stones.size(); i++)
        {
            if (stones[i] == pos[0])
                flag[0] = frog_dfs(stones, i, steps - 1);
            
            if (stones[i] == pos[1])
                flag[1] = frog_dfs(stones, i, steps);

            if (stones[i] == pos[2])
                flag[2] = frog_dfs(stones, i, steps + 1);
        }

        return flag[0] | flag[1] | flag[2];
    }
    bool canCross(vector<int>& stones){
        if (stones.size() < 1)
            return false;

        if (stones.size() > 2 && stones[1] != 1)
            return false;

        return frog_dfs(stones, 1, 1);        
    }

    int minSubArrayLen(int s, vector<int>& nums) {
        for (int k = 1; k <= nums.size(); k++)
        {
            int sum = 0;
            for (int i = 0; i < k; i++)
            {
                sum += nums[i];
            }

            if (sum >= s)
            {
                return k;
            }
            
            for (int j = k; j < nums.size(); j++)
            {
                sum += nums[j] - nums[j - k];
                if (sum >= s)
                {
                    return k;
                }
            }
        }

        return 0;
    }
    
};

void test_partition()
{
    vector<vector<string> > res;

    string input = "aaa";
    Solution  s;
    res = s.partition(input);

    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
        {
            cout<<res[i][j]<<"   ";
        }
        cout<<endl;
    }
}

void test_product()
{
    int arr[] = {-3,-6,0,-4, -5};
    int n = sizeof(arr)/sizeof(int);
    vector<int>  vec(arr, arr + n);
    int  ret;
    Solution s;
    ret = s.maxProduct(vec);
    cout<<"result:"<<ret<<endl;     
}

void test_KthLargest()
{
    int arr[] = {-3,-6,0,-4, -5};
    int n = sizeof(arr)/sizeof(int);
    vector<int>  vec(arr, arr + n);
    int  ret;
    Solution s;
    ret = s.findKthLargest(vec, 2);
    cout<<"result:"<<ret<<endl;   
}

void test_maxProductII()
{
    string arr[] = {"a", "aa", "aaa", "aaaa"};
    vector<string>  vec(arr, arr + 4);
    int  ret;
    Solution s;
    ret = s.maxProductII(vec);
    cout<<"result:"<<ret<<endl;   
}

void test_longestPalindrome()
{
    string input = "babad";
    Solution  s;
    string res;
    res = s.longestPalindrome(input);
    cout<<"Result: "<<res<<endl;
}

void test_triplet()
{
    int arr[] = {5, 4, 3, 2, 1};
    int n = sizeof(arr)/sizeof(int);
    vector<int>  vec(arr, arr + n);
    bool  ret;
    Solution s;
    ret = s.increasingTriplet(vec);
    cout<<"result:"<<ret<<endl;   
}

void test_slice()
{
    int arr[] = {2, 4, 6, 8, 10};
    int n = sizeof(arr)/sizeof(int);
    vector<int>  vec(arr, arr + n);
    int  ret;
    Solution s;
    ret = s.findDuplicate(vec);
    cout<<"result:"<<ret<<endl;   
}

void test_duplicate()
{
    int arr[] = {1, 2, 3, 2, 4};
    int n = sizeof(arr)/sizeof(int);
    vector<int>  vec(arr, arr + n);
    int  ret;
    Solution s;
    ret = s.findDuplicate(vec);
    cout<<"result:"<<ret<<endl;       
}

void test_bitwise()
{
    int m = 3;
    int n = 4;
    int ret = 0;
    Solution s;
    ret = s.rangeBitwiseAnd(m, n);
    cout<<"result:"<<ret<<endl;       
}

void test_sumrange()
{
    int arr[] = {0,1,2,4,5,7};
    int n = sizeof(arr)/sizeof(int);
    vector<int>  vec(arr, arr + n);
    vector<string> ret;
    Solution s;
    ret = s.summaryRanges(vec);
    for (int i = 0; i < ret.size(); i++)
    {
        cout<<ret[i]<<endl;
    }
    
}

void test_array2()
{
    int n = 5;
    int (*pNum)[5] = new int[5][5];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            pNum[i][j] = i * 5 + j;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout<<pNum[i][j]<<" ";
        }
        cout<<endl;
    }
    
    delete[] pNum;
}


void test_getMoney()
{
    int n = 20;
    int ret = 0;
    Solution s;
    ret = s.getMoneyAmount(n);
    cout<<"Result:: "<<ret<<endl;
}

void test_longestString()
{
    string input = "baaabcb";
    //string input = "acbabb";
    Solution  s;
    int res;
    res = s.longestSubstring(input, 3);
    cout<<"Result: "<<res<<endl;
}


void test_slidingwindow()
{
    int arr[] = {1,3,-1,-3,5,3,6,7};
    int n = sizeof(arr)/sizeof(int);
    vector<int>  vec(arr, arr + n);
    vector<int> ret;
    Solution s;
    ret = s.maxSlidingWindow(vec, 3);
    cout<<"Size: "<<ret.size()<<endl;
    for (int i = 0; i < ret.size(); i++)
    {
        cout<<ret[i]<<endl;
    } 
}

void test_fraction()
{
    Solution  s;
    string res;
    res = s.fractionToDecimal(500, 10);
    cout<<"Result: "<<res<<endl;
}

void test_cross()
{
    int arr[] = {0,1,3,5,6,8,12,17};
    int n = sizeof(arr)/sizeof(int);
    vector<int>  vec(arr, arr + n);
    Solution  s;
    bool res;
    res = s.canCross(vec);
    cout<<"Result: "<<res<<endl;
}


void test_minSub()
{
    int arr[] = {2,3,1,2,4,3};
    int n = sizeof(arr)/sizeof(int);
    vector<int>  vec(arr, arr + n);
    Solution  s;
    int res;
    res = s.minSubArrayLen(7, vec);
    cout<<"Result: "<<res<<endl;
}



int main()
{    
    //test_partition();
    //test_product();
    //test_KthLargest();
    //test_maxProductII();
    //test_longestPalindrome();
    //test_triplet();
    //test_slice();
    //test_duplicate();
    //test_bitwise();
    //test_sumrange();
    //test_getMoney();
    //test_longestString();
    //test_slidingwindow();
    //test_fraction();
    //test_cross();
    //test_minSub();
    test_longestPalindrome();
    return 1;
}




