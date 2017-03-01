#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <limits>
#include <limits.h>
#include <set>
#include <sstream>
#include <queue>
#include <math.h>

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

struct Interval {
        int start;
        int end;
        Interval() : start(0), end(0) {}
        Interval(int s, int e) : start(s), end(e) {}
};


struct Node{
    Node  *next[2];
    Node(){
        next[0] = NULL;
        next[1] = NULL;
    }
};

bool cmp_by_digit(const int &a, const int &b){
    long long ab = 0;
    long long ba = 0;
    long long basea = 10;
    long long baseb = 10;
        
    int tmp = a;
    while (tmp/10)
    {
        basea  *= 10;
        tmp = tmp/10;
    }
    
    tmp = b;
    while (tmp/10)
    {
        baseb  *= 10;
        tmp = tmp/10;
    }
    ab = a * baseb + b;
    ba = b * basea + a;
    return ab > ba;
}

class Solution {
public:

/*    
    //Word search ---Trie
    TriNode *root;
    
    void insert(string word) {
        TriNode *p = root;
        for (int n = 0; n < word.length(); n++) {
            char a = word[n];
            int i = a - 'a';
            if (p->ch[i] == NULL) 
                p->ch[i] = new TriNode();
            p = p->ch[i];
        }
        p->isWord = true;
    }
    
    bool isPrefix(string word) {
        TriNode *p = root;
        for (int n = 0; n < word.length(); n++) {
            char a = word[n];
            int i = a - 'a';
            if (p->ch[i] == NULL) 
                return false;
            
            p = p->ch[i];
        }
        return true;
    }
    
    bool isWord(string word) {
        TriNode *p = root;
        for (int n = 0; n < word.length(); n++) {
            char a = word[n];
            int i = a - 'a';
            if (p->ch[i] == NULL) 
                return false;
            
            p = p->ch[i];
        }
        return p->isWord;
    }

    bool isValid(vector<vector<char> > &board, vector<vector<bool> > &visit, int x, int y) {
        int m = board.size();
        int n = board[0].size();
        if (x < 0 || x >= m || y < 0 || y >= n || visit[x][y]) 
            return false;
        return true;
    }
    
    bool dfsword(vector<vector<char> > &board, vector<vector<bool> > &visit, set<string> &st, string &s, int x, int y) {
        int dx[4] = {1, 0, -1, 0};
        int dy[4] = {0, 1, 0, -1};
        int xx, yy;
        
        visit[x][y] = true;
        for (int i = 0; i < 4; ++i) {
            xx = x + dx[i]; 
            yy = y + dy[i];
            if (isValid(board, visit, xx, yy)) 
            {
                s.push_back(board[xx][yy]);
                if (isWord(s)) 
                    st.insert(s);
                if (isPrefix(s)) 
                    dfsword(board, visit, st, s, xx, yy);
                s.pop_back();
            }
        }
        visit[x][y] = false;
    }

    vector<string> findWords(vector<vector<char> >& board, vector<string>& words) {
        root = new TriNode();
        vector<string> res;
        int m = board.size();
        int n = board[0].size();

        
        if (board.empty() || board[0].empty() || words.empty()) 
            return res;
        
        for (int i = 0; i < words.size(); i++) 
            insert(words[i]);

        vector<vector<bool> > visit(m, vector<bool>(n, false));
        string s;
        set<string> st;
        for (int i = 0; i < m; ++i) 
        {
            for (int j = 0; j < n; ++j) 
            {
                s.push_back(board[i][j]);
                if (isWord(s)) 
                    st.insert(s);
                if (isPrefix(s)) 
                    dfsword(board, visit, st, s, i, j);
                s.pop_back();
            }
        }
        for (set<int>::iterator itr = st.begin(); itr != st.end(); itr++) 
            res.push_back(*itr);
        
        return res;
    }
    //Word search ---Trie
    */

    //if it is "10001011", then x^n = x^(1+2+8+128) = x^1 * x^2 * x^8 * x^128.
    double myPow(double x, int n){
        if (0 == n)
            return 1.0;
        if (INT_MIN == n)
            return 1.0/(myPow(x, INT_MAX)*x);
        if (n < 0)
            return 1.0/myPow(x, -n);

        double ret = 1.0;
        while (n > 0)
        {
            if (n&1 > 0)
                ret *= x;

            x *= x;
            n >>= 1;
        }
        return ret;
    }

    string str_add(string &str1, string &str2)
    {
        string sum;
        int len1 = str1.length() - 1;
        int len2 = str2.length() - 1;
        //int len = min(len1, len2) - 1;
        char tmp, digit1, digit2;
        char carry = 0;

        while (len1 >= 0 && len2 >= 0)
        {
            digit1 = str1[len1] - '0';
            digit2 = str2[len2] - '0';
            tmp = digit1 + digit2 + carry;
            if (tmp >= 10)
            {
                tmp -= 10;
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            sum.push_back(tmp+'0');
        }

        while (len1 >= 0)
        {
            digit1 = str1[len1] - '0';
            tmp = digit1 + carry;
            if (tmp >= 10)
            {
                tmp -= 10;
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            sum.push_back(tmp + '0');
        }

        while (len2 >= 0)
        {
            digit2 = str2[len2] - '0';
            tmp = digit2 + carry;
            if (tmp >= 10)
            {
                tmp -= 10;
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            sum.push_back(tmp + '0');
        }
    }
    bool  dfs_seq(string &num, int start, vector<string> &vec)
    {
        bool continued = false;
        if (start >= num.length() - 1)
        {
            if (vec.size() >= 3)
                return true;
            else
                return false;
        }

        if ('0' == num[start])
            return false;
        
        if (vec.size() < 3)
        {
  
            for (int i = start; i < num.length(); i++)
            {
                vec.push_back(num.substr(start, i - start + 1));
                if (dfs_seq(num, i + 1, vec));
                    return true;
                vec.pop_back();
            }
        }
        else
        {
            int i = 0;
            string tmp = str_add(vec[vec.size() - 1], vec[vec.size() - 2]);
            for (i = 0; i < tmp.length() && (start + i) < num.length(); i++)
            {
                if (tmp[i] != num[start + i])
                    return false;
            }
            if ((start + i ) >= num.length())
                return false;
            
            vec.push_back(tmp);
            continued = dfs_seq(num, start + i + 1, vec);
            vec.pop_back();
            return continued;
        }
    }

    /*
    bool isAdditiveNumber(string num){
        if (num.length() < 3)
        {
            return false;
        }
        vector<string>  vec;
        return dfs_seq(num, 0, vec);            
    }
    */
    bool isAdditiveNumber(string num){
        for (size_t i = 1; i < num.length(); i++)
        {
            for (size_t j = i + 1; j < num.length(); j++)
            {
                string str1 = num.substr(0, i);
                string str2 = num.substr(i, j - i);
                long long d1 = atoll(str1.c_str());
                long long d2 = atoll(str2.c_str());
                if ((str1.size() > 1 &&  '0' == str1[0] ) ||
                     (str2.size() > 1 && '0' == str2[0]))
                {
                    continue;
                }

                stringstream  ss;
                string tmp;
                
                long long next = d1 + d2;
                ss<<next;
                tmp = ss.str();
                string parts = str1 + str2 + tmp;

                while (parts.size() < num.size())
                {
                    d1 = d2;
                    d2 = next;
                    next = d1 + d2;

                    ss<<next;
                    tmp = ss.str();
                    parts = parts + tmp;
                }

                if (parts == num)
                    return true;
            }
        }
        return false;
    }

    bool canFinish(int numCourses, vector<pair<int, int> >& prerequisites){
        vector<vector<int> >  map(numCourses, vector<int>(0));
        vector<int>  indegree(numCourses, 0);
        
        vector<pair<int, int> >::iterator  itr;
        for (itr = prerequisites.begin(); itr != prerequisites.end(); itr++)
        {
            int id = itr->first;
            int pre = itr->second;

            map[pre].push_back(id);
            indegree[id]++;
        }

        queue<int>  que;
        for (int i = 0; i < numCourses; i++)
        {
            if (indegree[i] == 0)
            {
                que.push(i);
            }
        }

        while(!que.empty())
        {
            int node = que.front();
            que.pop();
            for (size_t i = 0; i < map[node].size(); i++)
            {
                int n = map[node][i];
                indegree[n]--;
                if (0 == indegree[n])
                    que.push(n);
            }
        }

        for (int i = 0; i < numCourses; i++)
        {
            if (indegree[i] != 0)
                return false;
        }

        return true;
    }


    int maxCoins(vector<int>& nums) {
        
        vector<int> arr(nums.size() + 2, 1);
        for (int i = 1; i <= nums.size(); i++)
            arr[i] = nums[i - 1];

        vector<vector<int> >  dp(nums.size() + 2, vector<int>(nums.size() + 2, 0));

        int n = nums.size() + 2;
        for (int k = 2; k < n; k++)
        {
            for (int left = 0; left < n - k; left++)
            {
                int right = left + k;
                for (int mid = left + 1; mid < right; mid++)
                {
                    dp[left][right] = max(dp[left][right], 
                                                  arr[left]*arr[mid]*arr[right] + dp[left][mid] + dp[mid][right]);
                }
            }
        }
        return dp[0][n - 1];
    }

    int combinationSum4(vector<int>& nums, int target){
        if (nums.size() == 0)
        {
            return 0;
        }
        vector<int>  dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= target; i++)
        {
            for (size_t j = 0; j < nums.size(); j++)
            {
                if (nums[j] <= i)
                    dp[i] += dp[i - nums[j]];
            }
        }
        
         return dp[target];
    }

    void dfs_sum3(vector<int> &vec, int remain, int k, vector<vector<int> > &ret){
        if (vec.size() > k || remain < 0)
            return;
            
        if (vec.size() == k && remain == 0)
            ret.push_back(vec);

        
        for (int num = vec[vec.size() - 1] + 1; num <= 9; num++)
        {
            vec.push_back(num);
            dfs_sum3(vec, remain - num, k, ret);
            vec.pop_back();
        }
    }

    
    vector<vector<int> > combinationSum3(int k, int n){
        vector<int> vec;
        vector<vector<int> > ret;
        for (int i = 1; i <= n/k; i++)
        {
            vec.push_back(i);
            dfs_sum3(vec, n - i, k, ret);
            vec.pop_back();
        }
        return ret;
    }

    int threeSumClosest(vector<int>& nums, int target){
        if (nums.size() < 3)
            return 0;
        
        int first, second, third, ret;

        bool inital = true;
        
        sort(nums.begin(), nums.end());

        for (first = 0; first < nums.size(); first++)        
        {
            second = first + 1;
            third  = nums.size() - 1;

            while (second < third)
            {
                int sum = nums[first] + nums[second] + nums[third];
                if (inital)
                {
                    ret = sum;
                    inital = false;
                }
                else
                {
                    if (abs(sum - target) < abs(ret - target))
                        ret = sum;
                }


                if (ret == target)
                    return ret;

                if (sum > target)
                    third--;
                else
                    second++;
            }
        }

        return ret;    
    }


    /*
    string decodeString(string s){
        string  left;        //左侧字符串
        string  mid;       //数字对应字符串
        string  right;     //右侧字符

        int beg, end;
        
        //查找数字起始位置
        for (beg = 0; beg < s.length(); beg++)        
        {
            if ('0' <= s[beg] && s[beg] <= '9')
            {
                break;
            }
        }

        if (beg == s.length())
            return s;

        //查找数字结束下一个位置
        for (end = beg; end < s.length(); end++)
        {
            if ( s[end] < '0' || s[end] > '9')
                break;
        }
        
        if (end == s.length())
            return s;

        if (s[end] != '[')
            return mid;



        if (beg > 0)
            left = s.substr(0, beg);

        string tmp = s.substr(beg, end - beg);
        int num = atoll(tmp.c_str());

        int cnt = 1;  //左中括号的计数
        int i = 0; 
        for (i = end + 1; i < s.length(); i++)
        {
            if (s[i] == ']')
            {
                cnt -= 1;
                if (0 == cnt)
                    break;
            }
            else if (s[i] == '[')
            {
                cnt += 1;
            }
        }

        if (s.length() == i)
            return left;

        string dupstr = decodeString(s.substr(end + 1, i - end - 1));

        for (int n = 0; n < num; n++)
        {
            mid += dupstr;
        }

        if (i < s.length() - 1)
            right = decodeString(s.substr(i + 1, s.length() - i - 1));

        return left + mid + right;
    }
    */

    string decodeString(string s){
        string res = "";
        string t = "";

        stack<int>  s_num;
        stack<string> s_str;

        int cnt = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                cnt = 10*cnt + (s[i] - '0');
            }
            else if ('[' == s[i])
            {
                s_num.push(cnt);
                s_str.push(t);

                cnt = 0;
                t.clear();
            }
            else if (']' == s[i])
            {
                int k = s_num.top();
                s_num.pop();
                
                for (int j = 0; j < k; j++)
                    s_str.top() += t;

                t = s_str.top();
                s_str.pop();
            }
            else
            {
                t += s[i];
            }
        }

        return s_str.empty() ? t: s_str.top();
    }

    /*
    vector< vector<int> > res;
    void nextnum(vector<int>& box, int target, int level, vector<int> &nums, int start){
        if (0 == level)
        {
            if (0 == target)
            {
                res.push_back(box);
            }
            return;
        }

        if (start >= nums.size())
            return;

        
        for (int i = start; i < nums.size(); i++)
        {
            box.push_back(nums[i]);
            nextnum(box, target - nums[i], level - 1, nums, i + 1);
            box.pop_back();

            while (i < nums.size() && nums[i + 1] == nums[i])
                i++;
        }
    }
    vector<vector<int> > fourSum(vector<int>& nums, int target){
        vector<int>  tmp;
        
        sort(nums.begin(), nums.end());
        nextnum(tmp, target, 4, nums, 0);

        return res;
    }
    */

    vector<vector<int> > fourSum(vector<int>& nums, int target){
        vector<vector<int> >  res;
        vector<int>  tmp;

        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue;


                int k = j + 1;
                int t = nums.size() - 1;
                while (k < t)
                {
                    if (k > j + 1 && nums[k] == nums[k - 1])
                    {
                        k++;      
                        continue;
                    }

                    if (t < nums.size() - 1 && nums[t] == nums[t + 1])
                    {
                        t--;
                        continue;
                    }

                    int sum = nums[i] + nums[j] + nums[k] + nums[t];
                    if (sum == target)
                    {
                        vector<int>  tmp;
                        tmp.push_back(nums[i]);
                        tmp.push_back(nums[j]);
                        tmp.push_back(nums[k]);
                        tmp.push_back(nums[t]);
                        res.push_back(tmp);
                        k++;
                    }
                    else if (sum < target)
                    {
                        k++;
                    }
                    else
                    {
                        t--;
                    }
                }
            }

        }

        return res;
    }

    int robI(vector<int>& nums){

        /*
        int len = nums.size();
        if (0 == len)
            return 0;
        if (1 == len)
            return nums[0];
            
        vector<int> dp(len, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < len; i++)
        {
            dp[i] = max(dp[i - 1],  nums[i] + dp[i - 2]);
        }

        return dp[len - 1];
        */

        int pre = 0;
        int pre_pre = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            int n = pre;
            int m = pre_pre + nums[i];
            
            pre = max(m, pre); 
            pre_pre = n; //move 
        }

        return max(pre_pre, pre);
    }

    int robII(vector<int>& nums){
        int len = nums.size();
        if (0 == len)
            return 0;
        if (1 == len)
            return nums[0];
            
        vector<int> dp(len, 0);
        int tmp;
        
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < len - 1; i++)
        {
            dp[i] = max(dp[i - 1],  nums[i] + dp[i - 2]);
        }
        tmp = dp[len - 2];

        dp[1] = nums[1];
        dp[2] = max(nums[1], nums[2]);
        for (int i = 3; i < len; i++)
        {
            dp[i] = max(dp[i - 1],  nums[i] + dp[i - 2]);
        }

        return max(tmp, dp[len - 1]);
    }

    vector<int>  dfsrob(TreeNode* root){
        if (NULL == root)
            return vector<int>(2, 0);

        vector<int> lchild = dfsrob(root->left);
        vector<int> rchild = dfsrob(root->right);

        vector<int> res(2, 0);
        res[0] = max(lchild[0], lchild[1]) + max(rchild[0], rchild[1]);
        res[1] = lchild[0] + rchild[0] + root->val;

        return res;
    }
    int robIII(TreeNode* root){
        vector<int> res = dfsrob(root);
        return max(res[0], res[1]);
    }

    int hIndex(vector<int>& citations){
        int n = citations.size();
        vector<int> stats(n + 1, 0);
        for (size_t i = 0; i < citations.size(); i++)
        {
            if (citations[i] > n)
                stats[n] += 1;
            else
                stats[citations[i]] += 1;
        }

        int sum = 0;
        for (int i = n; i > 0; i--)
        {
            sum += stats[i];
            if (sum >= i)
                return i;
        }

        return 0;
    }


    int hIndexII(vector<int>& citations){
        int num = citations.size();
        int left = 0; 
        int right = num - 1;
        
        while (left <= right)
        {
            int mid = left + (right - left)/2;

            if (citations[mid] == num - mid)
            {
                cout<<"Find: "<<mid<<endl;
                return num - mid;
            }
            else if (citations[mid] < num - mid)
            {
                cout<<"shift left"<<endl;
                left = mid + 1;
            }
            else 
            {
                cout<<"shift right "<<endl;
                right = mid - 1;
            }
        }

        cout<<"Left: "<<left<<endl;
        return num - left;
    }

    /*
    #define     DESCENDING         0
    #define     ASCENDING           1
    int findConsecutiveNumber(int value, int order, unordered_set<int> &nums)
    {
        int cnt = 0;
      
        while (nums.find(value) != nums.end())
        {
            cnt++;
            nums.earse(value);

            if (DESCENDING == order)
            {
                value -= 1;
            }
            else
            {
                value += 1;
            }
        }

    }
    int longestConsecutive(vector<int>& nums){
        unordered_set<int> flags;
        int maxlen = 0;
        for (size_t i = 0; i < nums.size(); i++)
        {
            flags.insert(nums[i]);
        }

        for (int i = 0; i < nums.size(); i++)
        {
            int left = findConsecutiveNumber(nums[i] - 1, DESCENDING, flags);
            int right = findConsecutiveNumber(nums[i] + 1, ASCENDING, flags);

            int tmp = left + right + 1;
            if (tmp > maxlen)
            {
                maxlen = tmp;
            }
        }

        return maxlen;

    }
    */


    int countBattleships(vector<vector<char> > &board){
        int rows = board.size();
        if (0 == rows)
            return 0;
        
        int cols = board[0].size();
        int res = 0;

        vector<int>  prev(cols, 0);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (0 == prev[j])
                {
                    if (board[i][j] == 'X')
                    {
                        prev[j] = 1;
                        if (0 == j || board[i][j - 1] != 'X')
                            res++;
                    }
                    else
                    {
                        prev[j] = 0;
                    }
                }
                else
                {
                    if (board[i][j] == 'X')
                    {
                        prev[j] = 1;
                    }
                    else
                    {
                        prev[j] = 0;
                    }
                }
            }
        }

        return res;
    }

    int findXorNum(Node *root, int num) {
        int res = 0;
        Node *ptr = root;
        for (int i = 30; i >= 0; i--)
        {
            int bitnum = (num >> i) & 1;
            int xornum = 1 - bitnum;
            if (ptr->next[xornum] == NULL)
            {
                ptr = ptr->next[bitnum];
                res += bitnum <<  i;
            }
            else
            {
                ptr = ptr->next[xornum];
                res += xornum << i;
            }
        }

        return res;
    }
    
    void buildTreeNode(Node *root, int x){
        Node *ptr = root;
        for (int i = 30; i >= 0; i--)
        {
            int bitnum = (x >> i) & 1;
            if (NULL == ptr->next[bitnum])
            {
                ptr->next[bitnum] = new Node();
            }
            ptr = ptr->next[bitnum];
        }
    }
    
    int findMaximumXOR(vector<int>& nums) {
        Node  *pRoot = new Node();
        int res = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            buildTreeNode(pRoot, nums[i]);
        }

        for (int i = 0; i < nums.size(); i++)
        {
            int xornum = findXorNum(pRoot, nums[i]);
            res = max(res, xornum^nums[i]);
        }

        return res;
    }


    int countNumbersWithUniqueDigits(int n){
        if (0 == n)
            return 1;
        int res = 10;
        int cnt = 9;
        for (int i = 2; i < n; i++)
        {
            cnt *= (11 - i);
            res += cnt;
        }
        return res;
    }



    int remainPow(int remain, int n)
    {
        int tmp1 = 1;
        int tmp2 = 1;
        if (0 == n)
            return 1;
        else if (1 == n)
            return remain%1337;

        tmp1 = remainPow(remain, n/2);
        if (n%2)
            tmp2 = (tmp1 * (remain%1337))%1337;
        else 
            tmp2 = tmp1;
        
        return tmp1*tmp2%1337;
    }
    int superPow(int a, vector<int>& b){
        long long  res = 1;
        
        for (int i = 0; i < b.size(); i++)
        {
            res = remainPow(res, 10) * remainPow(a, b[i]) %1337;
        }

        return res;
    }


    vector<int> singleNumber(vector<int>& nums){
        vector<int> ans;
        int calc = 0;
        int flag = 0;
        int idx = 0;
        if (nums.size() < 2)
            return ans;

        calc = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            calc ^= nums[i];
        }

        
        
        for (idx = 0; idx < 32; idx++) 
        {
            if ((calc>>idx) & 1)
                break;
        }

        flag = 1<<idx;
        

        int tmp1 = 0;
        int first1 = 0;
        int tmp2 = 0;
        int first2 = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (flag & nums[i])
            {
                if (first1)
                {
                    tmp1 ^= nums[i];
                }
                else 
                {
                    tmp1 = nums[i];
                    first1 = 1;
                }
            }
            else
            {
                if (first2)
                {
                    tmp2 ^= nums[i];
                }
                else 
                {
                    tmp2 = nums[i];
                    first2 = 1;
                }
            }
        }        

        ans.push_back(tmp1);
        ans.push_back(tmp2);
        return ans;
    }

    string largestNumber(vector<int>& nums){
        string ans;
        stringstream ss;
        if (nums.size() == 0)
            return ans;

        sort(nums.begin(), nums.end(), cmp_by_digit);

        int flag = 0;
        for (size_t i = 0; i < nums.size(); i++)
        {
            if (flag == 1 || nums[i] != 0)
            {
                ss<<nums[i];
                flag = 1;
            }
        }    
        if (0 == flag)
            ans = "0";
        else
            ans = ss.str();

        return ans;
    }

    int missingNumber(vector<int>& nums){
        int n = nums.size();
        long long total = 0;

        total = (1 + n) * n /2;
        for (int i = 0; i < nums.size(); i++)
        {
            total -= nums[i];
        }

        return total;
    }


    void dfsisland(vector<vector<char> > &grid, vector<vector<int> > &flag, int x, int y){
        int rows = grid.size();
        int cols = grid[0].size();

        int id = flag[x][y];

        //left
        if (x > 0)
        {
            if (grid[x - 1][y] == '1' && flag[x - 1][y] == 0)
            {
                flag[x - 1][y] = id;
                dfsisland(grid, flag, x - 1, y);
            }
        }

        //right
        if (x < rows - 1)
        {
            if (grid[x + 1][y] == '1' && flag[x + 1][y] == 0)
            {
                flag[x + 1][y] = id;
                dfsisland(grid, flag, x + 1, y);
            }
        }

        //top
        if (y > 0)
        {
            if (grid[x][y - 1] == '1' && flag[x][y - 1] == 0)
            {
                flag[x][y - 1] = id;
                dfsisland(grid, flag, x, y - 1);
            }
        }

        //bottom
        if (y < cols - 1)
        {
            if (grid[x][y + 1] == '1' && flag[x][y + 1] == 0)
            {
                flag[x][y + 1] = id;
                dfsisland(grid, flag, x, y + 1);
            }
        }
    }
    int numIslands(vector<vector<char> >& grid){
        int cnt = 0;
        int rows = grid.size();
        if (0 == rows)
            return cnt;

        int cols = grid[0].size();
        if (0 == cols)
            return cnt;
        
        vector<vector<int> > flag(rows, vector<int>(cols, 0));
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (0 == flag[i][j] && grid[i][j] == '1')
                {
                    flag[i][j] = ++cnt;
                    dfsisland(grid, flag, i, j);
                }
            }
        }

        return cnt;
    }

    int majorityElement(vector<int>& nums){
        int n = 0;
        int cnt = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (0 == cnt)
            {
                n = nums[i];
                cnt = 1;
            }
            else
            {
                if (n == nums[i])
                    cnt++;
                else
                    cnt--;
            }
        }

        return n;
    }

    int numberOfArithmeticSlices(vector<int>& A){
        if (A.size() < 3)
            return 0;

        int ans = 0;
        int len = A.size();
        vector<int>  subs(len - 1, 0);
        int cnt = 1;

        for (int i = 1; i < len ; i++)
        {
            subs[i - 1] = A[i] - A[i - 1];
        }

        for (int i = 1; i < subs.size(); i++)
        {
            if (subs[i] == subs[i - 1])
            {
                cnt += 1;
            }
            else
            {
                ans += cnt * (cnt - 1)/2;
                cnt = 1;
            }

        }

        if (cnt > 1)
            ans += cnt * (cnt - 1)/2;

        return ans;
    }

    int lastRemaining(int n){
        int base = 1;
        int res = 1;
        while (base * 2 <= n)
        {
            res += base;
            base *= 2;

            if (base * 2 > n)
                break;

            if ((n/base)%2 == 1)
                res += base;

            base *= 2;
        }

        return res;
    }

    string removeKdigits(string num, int k){
        if (k >= num.length())
            return "0";

        int beg = 0;
        int flag = 1;
        int n = num.length() - k;
        string res;
        for (int i = n; i > 0; i--)
        {
            if (num.length() - beg ==  i)
            {
                res += num.substr(beg, num.length() - beg);
                break;
            }
            else
            {
                int pos = 0;
                char minnum = '9' + 1;
                int  end = num.length() - i + 1;
                for (int j = beg; j < end; j++)
                {
                    if (num[j] < minnum)
                    {
                        pos = j;
                        minnum = num[j];
                    }
                }
                beg = pos + 1;
                res += num[pos];
            }
        }

        for (beg = 0; beg < res.length(); beg++)
        {
            if (res[beg] != '0')
                break;
        }

        if (beg == res.length())
            res = "0";
        else
            res = res.substr(beg, res.length() - beg);
        
        return res;
            
    }

    string removeDuplicateLetters(string s){
        int lettercnt[26] = {0};
        int visited[26] = {0};
        int idx = 0;
        string res;
        
        for (int i = 0; i < s.length(); i++)
        {
            idx = s[i] - 'a';
            lettercnt[idx] += 1;
        }

        vector<char> ans(1, '0');
        for (int i = 0; i < s.length(); i++)
        {
            idx = s[i] - 'a';
            lettercnt[idx]--;

            if (visited[idx])
                continue;
            while (s[i] < ans.back() && lettercnt[ans.back() - 'a'])
            {
                visited[ans.back() - 'a'] = 0;
                ans.pop_back();
            }
            ans.push_back(s[i]);
            visited[idx] = 1;
        }

        for (int i = 1; i < ans.size(); i++)
        {
            res += ans[i];
        }
        return res;

    }

    /*
    int calculate(string s){
        vector<int>  sign(2, 1);
        int res = 0;

        int tmp = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                int num = 0;
                while (i < s.length() && (s[i] >= '0' && s[i] <= '9'))
                {
                    num = num*10 + (s[i] - '0');
                    i++;
                }
                res += sign.back() * num;
                sign.pop_back();
                --i;
            }
            else if (s[i] == ')')
            {
                sign.pop_back();
            }
            else if (s[i] == '-')
            {
                sign.push_back(0 - sign.back());
            }
            else if (s[i] != ' ')
            {
                sign.push_back( sign.back());
            }
        }

        return res;
    }
    */

    int calculate(string s){
        stack<int>  nums;
        stack<char>  op;
        int res = 0;

        if (s.length() < 1)
            return 0;

        op.push('+');
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                int val = 0;
                while (i < s.length() && (s[i] >= '0' && s[i] <= '9'))
                {
                    val = val*10 + (s[i] - '0');
                    i++;
                }
                
                if (!op.empty())
                {
                    if ('*' == op.top())
                    {
                        nums.top() = nums.top()*val;
                        op.pop();
                    }
                    else if ('/' == op.top())
                    {
                        nums.top() = nums.top()/val;
                        op.pop();
                    }
                    else
                    {
                        nums.push(val);
                    }
                }
                else
                {
                    nums.push(val);
                }
                --i;
            }
            else if (' ' != s[i])
            {
                op.push(s[i]);
            }
        }


        while (!op.empty())
        {
            int tmp = nums.top();

            if ('-' == op.top())
            {
                tmp = - tmp;
            }

            res += tmp;
            op.pop();
            nums.pop();
        }

        return res;
    }

    int lengthOfLongestSubstring(string s){
        vector<int> pos(256, -1);
        int cnt = 0;
        int ans = 0;
        int beg = 0;

        for (int i = 0; i < s.length(); i++)
        {
            if (-1 == pos[s[i]])
            {
                pos[s[i]] = i;
                cnt++;  
            }
            else
            {
                ans = max(ans, cnt);
                if (beg < pos[s[i]])
                {
                    int tmp = pos[s[i]];
                    for (int j = beg; j <= pos[s[i]]; j++)
                    {
                        pos[s[j]] = -1;
                    }
                    beg = tmp + 1;
                    cnt = i - tmp;
                }
                else
                {
                    beg = beg + 1;
                }
                pos[s[i]] = i;
            }    
        }
        ans = max(ans, cnt);
        
        return ans;
    }


    bool  firstWillWin(vector<int> values)
    {
        int len = values.size();
        vector<int> sum(len + 1, 0);
        vector<int> dp(len, 0);

        sum[0] = 0;
        for (int i = 0; i <= len; i++)
        {
            sum[i] = sum[i - 1] + values[i - 1];
        }

        for (int i = 0; i < len; i++)
        {
            dp[i] = values[i];
        }

        int tmp = 0;
        for (int k = 1; k < len; k++)
        {
            tmp = dp[len - k];
            for (int i = len - k - 1; i >= 0; i--)
            {
                int tmp1 = dp[i];
                dp[i] = max(values[i] + (sum[i + k + 1] - sum[i + 1]) - tmp, 
                                 values[i + k] + (sum[i + k] - sum[i]) - dp[i]);
                tmp = tmp1;
            }
        }

        if (dp[0]*2 > sum[len])
            return true;
        else
            return false;
    }

    static bool cmp(const Interval &a, const Interval &b)
    {
        return a.start < b.start;
    }
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval>    ans;
        if (intervals.empty())
            return ans;
        sort(intervals.begin(), intervals.end(), cmp);
        ans.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++)
        {
            if (ans.back().end >= intervals[i].start)
            {
                ans.back().end = max(ans.back().end, intervals[i].end);
            }
            else
            {
                ans.push_back(intervals[i]);
            }
        }

        return ans;
    }


    string simplifyPath(string path){
        stack<string>  stk;
        string tmp;
        string res= "";
        for (int i = 0; i < path.length(); i++)
        {
            if (path[i] != '/')
            {
                tmp += path[i];
            }
            else
            {
                if (tmp.length() > 0)
                {
                    if (tmp != ".")
                    {
                        if (".." == tmp)
                        {
                            if (!stk.empty())
                                stk.pop();
                        }
                        else
                        {
                            stk.push(tmp);      
                        }
                    }
                }
                tmp = "";
            }
        }

        if (tmp.length() > 0)
        {
            if (tmp != ".")
            {
                if (".." == tmp)
                {
                    if (!stk.empty())
                        stk.pop();
                }
                else
                {
                    stk.push(tmp);      
                }
            }
        }

        if (stk.empty())
            return "/";

        while(!stk.empty())
        {
            res = "/" + stk.top() + res;
            stk.pop();
        }

        return res;
    }

    int minDistance(string word1, string word2){
        int len1 = word1.length() + 1;
        int len2 = word2.length() + 1;
        vector<vector<int> >    dp(len1, vector<int>(len2, 0));

        for (int i = 0; i < len1; i++)
            dp[i][0] = i;

        for (int i = 0; i < len2; i++)
            dp[0][i] = i;

        for (int i = 1; i < len1; i++)
        {
            for (int j = 1; j < len2; j++)
            {
                if (word1[i] == word2[j])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
            }
        }

        return dp[len1 - 1][len2 - 1];
    }
};

void test_pow()
{
    double ret = 0;
    Solution s;
    ret =  s.myPow(8.88023, 3);
    cout<<"result:"<<ret<<endl;
}

void test_AdditiveNumber()
{
    string str = "112358";
    bool  ret;
    Solution s;
    ret =s.isAdditiveNumber(str);
    cout<<"result:"<<ret<<endl;    
}


void  test_topo()
{
    vector<pair<int, int> > vec;
    
    bool  ret;
    Solution s;

    vec.push_back(make_pair(1, 0));
    
    ret =s.canFinish(2, vec);
    cout<<"result:"<<ret<<endl;    
    
    vec.push_back(make_pair(0, 1));
    
    ret =s.canFinish(2, vec);
    cout<<"result:"<<ret<<endl;    
    
}

void test_coins()
{
    int arr[] = {1,5,8};
    int n = sizeof(arr)/sizeof(int);
    vector<int>  vec(arr, arr + n);
    int  ret;
    Solution s;
    ret = s.maxCoins(vec);
    cout<<"result:"<<ret<<endl;     
}

void test_sum4()
{
    int arr[] = {1,2,3};
    int n = sizeof(arr)/sizeof(int);
    vector<int>  vec(arr, arr + n);
    int  ret;
    Solution s;
    ret = s.combinationSum4(vec, 4);
    cout<<"result:"<<ret<<endl;     
}

void test_sum3()
{
    vector<vector<int> >  vec;
    Solution s;
    vec = s.combinationSum3(3, 9);
    for (size_t i = 0; i < vec.size(); i++)
    {
        for (size_t j = 0; j < vec[i].size(); j++)
        {
            cout<<vec[i][j]<<"  ";
        }
        cout<<endl;
    }
}

void  test_3sumcloset()
{
    int arr[] = {-1, 2, 1, -4};
    int n = sizeof(arr)/sizeof(int);
    int ret = 0;
    vector<int> vec(arr, arr + n);
    Solution s;

    ret = s.threeSumClosest(vec, 1);

    cout<<"Result: "<<ret<<endl;
}

void test_decodestring()
{
    string str = "2[abc]3[cd]ef";
    string  ret;
    Solution s;
    ret =s.decodeString(str);
    cout<<"result:"<<ret<<endl;    
}

void test_foursum()
{
    int arr[] = {-3,-2,-1,0,0,1,2,3};
    int n = sizeof(arr)/sizeof(int);
    vector<int> vec(arr, arr + n);
    Solution s;
    vector<vector<int> > ret;

    ret = s.fourSum(vec, 0);

    for (int i = 0; i < ret.size(); i ++)
    {
        for (int j = 0; j < ret[i].size(); j++)
        {
            cout<<ret[i][j]<<"   ";
        }
        cout<<endl;
    }
}

void test_robI()
{
    int arr[] = {2, 9};
    int n = sizeof(arr)/sizeof(int);
    int ret = 0;
    vector<int> vec(arr, arr + n);
    Solution s;

    ret = s.robI(vec);

    cout<<"Result: "<<ret<<endl;
}

void test_robII()
{
    int arr[] = {12, 17, 11, 5, 3};
    int n = sizeof(arr)/sizeof(int);
    int ret = 0;
    vector<int> vec(arr, arr + n);
    Solution s;

    ret = s.robII(vec);

    cout<<"Result: "<<ret<<endl;
}

void test_hIndex()
{
   int arr[] = {0};
    int n = sizeof(arr)/sizeof(int);
    int ret = 0;
    vector<int> vec(arr, arr + n);
    Solution s;

    ret = s.hIndexII(vec);

    cout<<"Result: "<<ret<<endl;
}

void test_maxxor()
{
   int arr[] = {3, 10, 5, 25, 2, 8};
    int n = sizeof(arr)/sizeof(int);
    int ret = 0;
    vector<int> vec(arr, arr + n);
    Solution s;

    ret = s.findMaximumXOR(vec);

    cout<<"Result: "<<ret<<endl;
}


void test_superpow()
{
   int arr[] = {1,0,0};
    int n = sizeof(arr)/sizeof(int);
    int ret = 0;
    vector<int> vec(arr, arr + n);
    Solution s;

    ret = s.superPow(209253, vec);

    cout<<"Result: "<<ret<<endl;
}

void test_singlenumber()
{
    int arr[] = {1, 2, 1, 3, 2, 5};
    int n = sizeof(arr)/sizeof(int);
    vector<int> ret;
    vector<int> vec(arr, arr + n);
    Solution s;

    ret = s.singleNumber(vec);

    cout<<"Result"<<endl;
    for (int i = 0; i < ret.size(); i++)
        cout<<ret[i]<<"  "<<endl;
}

void test_largenumber()
{
    //int arr[] = {0,9,8,7,6,5,4,3,2,1};
    int arr[] = {0, 0};
    int n = sizeof(arr)/sizeof(int);
    string ret;
    vector<int> vec(arr, arr + n);
    Solution s;

    ret = s.largestNumber(vec);

    cout<<"Result : "<<ret<<endl;

}


void test_numisland()
{
    int ret = 0;
    string arr[] = {"11000","11000","00100","00011"};


    vector<vector<char> > vec(4, vector<char>(5, 0));
    Solution s;

    for (int i = 0; i < 4; i++)
    {
        string tmp = arr[i];
        for (int j = 0; j < 5; j++)
        {
            vec[i][j] = tmp[j];
        }
    }

    ret = s.numIslands(vec);
    
    cout<<"Result : "<<ret<<endl;

}

void test_slices()
{
    int arr[] = {7,7,7,7,7};
    int n = sizeof(arr)/sizeof(int);
    int ret;
    vector<int> vec(arr, arr + n);
    Solution s;

    ret = s.numberOfArithmeticSlices(vec);

    cout<<"Result: "<<ret<<endl;
}

void test_remove()
{
    string input = "10200";
    int del = 1;
    Solution  s;

    string ans;
    ans = s.removeKdigits(input, del);

    cout<<"Result: "<<ans<<endl;
}

void test_calc()
{
    string input = " 3+5 / 2 ";
    Solution  s;

    int ans = 0;
    ans = s.calculate(input);

    cout<<"Result: "<<ans<<endl;
}

void test_removeletter()
{
    string input = "c";
    Solution  s;

    string ans;
    ans = s.removeDuplicateLetters(input);

    cout<<"Result: "<<ans<<endl;
}


void test_longsustr()
{
    string input1 = "abcabcbb";
    string input2 = "abcde";
    string input3 = "pwwkew";
    string input4 = "abba";
    string input5 = "tmmzuxt";
    Solution  s;

    int ans;
    ans = s.lengthOfLongestSubstring(input1);
    cout<<input1<<" : "<<ans<<endl;
    ans = s.lengthOfLongestSubstring(input2);
    cout<<input2<<" : "<<ans<<endl;
    ans = s.lengthOfLongestSubstring(input3);
    cout<<input3<<" : "<<ans<<endl;
    ans = s.lengthOfLongestSubstring(input4);
    cout<<input4<<" : "<<ans<<endl;
    ans = s.lengthOfLongestSubstring(input5);
    cout<<input5<<" : "<<ans<<endl;
}

void test_simplifyPath()
{
    string input = "/a/./b/../../c/";
    Solution  s;

    string ans;
    ans = s.simplifyPath(input);

    cout<<"Result: "<<ans<<endl;
}

void test_distance()
{
    string word1 = "a";
    string word2 = "bac";
    Solution  s;

    int ans;
    ans = s.minDistance(word1, word2);

    cout<<"Result: "<<ans<<endl;
}


int main()
{    
    //test_pow();
    //test_AdditiveNumber();
    //test_topo();
    //test_coins();
    //test_sum3();
    //test_3sumcloset();
    //test_decodestring();
    //test_foursum();
    //test_robI();
    //test_robII();
    //test_hIndex();
    //test_maxxor();
    //test_superpow();
    //test_singlenumber();
    //test_largenumber();
    //test_numisland();
    //test_slices();
    //test_remove();
    //test_removeletter();
    //test_longsustr();
    //test_simplifyPath();
    test_distance();
    return 1;
}

    
