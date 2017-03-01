#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <limits>
#include <limits.h>
#include <set>

using namespace std;

void test_map()
{
	string str1 = "Helol";
	string str2 = "lloHe";
	string str3 = "Heoll";
	string str;
	
	map<string, vector<string> > hash_map;
	map<string, vector<string> >::iterator hash_itr;
	string::size_type  strsize;
	vector<string>  vec;
	vector<string>  vectmp;
	vector<string>::iterator itr;

	str = str1;
	sort(str.begin(), str.end());
	hash_map[str].push_back(str1);

	str = str2;
	sort(str.begin(), str.end());
	hash_map[str].push_back(str2);

	str = str3;
	sort(str.begin(), str.end());
	hash_map[str].push_back(str3);
	
	//hash_map.insert(map<string, vector<string> >::value_type("Hello", vec));
	vectmp = hash_map["Hello"];

	for (itr = vectmp.begin(); itr != vectmp.end(); itr++)
	{
		cout<<*itr<<endl;
	}
	//cout<<"size:"<<strsize<<endl;
}

struct SegmentTreeNode{
    int L, R;
    int cnt;
    SegmentTreeNode *pLeft, *pRight;
    SegmentTreeNode(int l, int r):L(l), R(r), cnt(0), pLeft(NULL), pRight(NULL){}
};



class SegmentTree{
public:
    SegmentTreeNode  *root;
    
    SegmentTreeNode  *buildTree(vector<int>& nums, int L, int R)
    {
        if (L > R)
            return NULL;
        SegmentTreeNode *root = new SegmentTreeNode(nums[L], nums[R]);
        if (L == R)
            return root;
        int mid = L + (R - L)/2;
        root->pLeft = buildTree(nums, L, mid);
        root->pRight = buildTree(nums, mid + 1, R);
    }


    void update(SegmentTreeNode *root, int val)
    {
        if (root && root->L <= val && val <= root->R)
        {
            root->cnt++;
            update(root->pLeft, val);
            update(root->pRight, val);
        }
    }

    int sum(SegmentTreeNode *root, int L, int R)
    {
        if (!root || root->R < L || R < root->L)
            return 0;
        if (L <= root->L &&  root->R <= R)
            return root->cnt;

        return sum(root->pLeft, L, R) + sum(root->pRight, L, R);
    }

    SegmentTree(vector<int> &nums, int L, int R)
    {
        root = buildTree(nums, L, R);
    }

    int sum(int L, int R)
    {
        return sum(root, L, R);
    }

    void update(int val)
    {
        update(root, val);
    }
};


class Solution {
public:
 
    int integerBreak(int n){
        int tmp  = 1;
        int res = 1; 
        int two_product = 1;    /*2的个数*/
        int three_cnt = 0;  /*3的个数*/

        if (n < 4)
            return n - 1;
        
        three_cnt = n/3;
        tmp = n%3;
        if (1 == tmp)
        {
            three_cnt -= 1;
            two_product = 4;
        }
        else if (0 == tmp)
        {
            two_product = 1;
        }
        else
        {
            two_product = 2;
        }


        for (int i = 0; i < three_cnt; i++)
        {
            res *= 3;
        }
        res *=  two_product;

        return res;
           
    }

    string simplifyPath(string path){
        vector<string>  vec;
        string tmp = path;
        string res;
        size_t offset = 0;
        size_t pre_pos = 0;
        if (path[0] != '/')
        {
            return res;
        }

        pre_pos = 0;
        while (path[pre_pos] == '/')
        {
            pre_pos++;
        }

        pre_pos -= 1;
        for (size_t i = pre_pos + 1; i < path.length(); i++)
        {
            if (path[i] == '/')
            {
                offset = 0;
                while (path[i + offset] == '/' && (i + offset) < path.length())
                {
                    offset++;                   
                }
                
                tmp = path.substr(pre_pos, i - pre_pos); //截断
                if (tmp != "/.")
                {
                    if (tmp == "/..")
                    {
                        if (!vec.empty())
                            vec.pop_back();
                    }
                    else
                    {
                        vec.push_back(tmp);
                    }
                }

                i = i + offset - 1;
                pre_pos = i; 
                    
            }
           
        }

        if (!vec.empty())
        {
            for (size_t idx = 0; idx < vec.size(); idx++)
            {
                res.append(vec[idx]);
            }
        }

        return res;
    }

    int search(vector<int>& nums, int target){
        int  left = 0;
        int  right = nums.size() - 1;
        
        while (left <= right)
        {
            int  mid  = (right - left) /2  + left;
            if (nums[mid] == target)
            {
                return mid;
            }
            
            if (nums[mid] > nums[right])  // mid 位于左半部分
            {
                if (target > nums[mid])
                {
                    left = mid + 1;    
                }
                else
                {
                    if (nums[left] <= target)
                    {
                        right = mid - 1;
                    }
                    else
                    {
                        left = mid + 1;
                    }
                }
            }
            else if (nums[mid] < nums[left])   // mid 位于右半部分
            {
                if (target > nums[mid])
                {
                    if (target <= nums[right])
                    {
                        left = mid + 1;
                    }
                    else
                    {
                        right = mid - 1;
                    }
                }
                else
                {
                    right = mid - 1;
                }
            }
            else  //mid 位于升序排列中
            {
                if (target > nums[mid])
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }

    bool isPerfectSquare(int num){
        int left = 1;
        int right = num;
        long mid = 0;
        long  square = 0;

        while (left <= right)
        {
            mid = (right - left)/2 + left;
            square = mid * mid;
            if (square == num)
            {
                return true;
            }
            else if (square < num)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        return false;
    }


    
    string unitToWord(int num, int level){
        string mapping[19] = {"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve ", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seveteen", "Eighteen", "Nineteen "};
        string related[8] = {"Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        string unit[3] = {"Thousand", "Million", "Billion"};
        
        string word;
        string right;
        int quota = 0;
        int remain = 0;
        int first_num = 0;
        int second_num = 0;
        int third_num = 0;


        if (0 == num)
        {
            return word;
        }

        quota = num/1000;
        remain = num%1000;
        if (quota > 0)
        {
            word = unitToWord(quota, level + 1);
        }

        if (0 != remain)        
        {
            first_num = remain/100;
            if (0 != first_num)
            {
                right += mapping[first_num - 1];
                right += " ";
                right += "Hundred";
            }

            second_num = remain%100;
            if (second_num == 0)
            {
                word = word + " " + right + " " + unit[level - 1];
                return word;
            }

            right += " ";
            if (second_num < 20)
            {
                third_num = 0;
                right += mapping[second_num - 1];
            }
            else
            {
                third_num = second_num%10;
                second_num = second_num/10;
               
                right += related[second_num - 2];
            }


            if (0 != third_num)
            {
                right += " ";
                right += mapping[third_num - 1];
            }

        
            if (word != "")
            {
                word = word + " ";
            }
            word = word + right;
            if (level > 0)
            {
                word = word + " " + unit[level - 1];
            }

        }
        
        return word;

    }
    string numberToWords(int num){
        string res;
        if (0 == num)
        {
            return "Zero";
        }
        res += unitToWord(num, 0);
        return res;
    }


    //(t length ~= 500,000) and  (s length <=100)
    bool isSubsequence(string s, string t){
        int pos = 0;

        if (0 == s.length())
        {
            return true;
        }
        
        for (int i = 0; i < s.length(); i++)
        {
            while (pos < t.length() && s[i] != t[pos])
                pos++;

            if (pos >= t.length())
            {
                return false;
            }
            
            pos++;
        }
        
        return true;
        
    }

    int binary_search(vector<int>& vec, int target){
        int left = 0;
        int right = vec.size();
        while (left <= right)
        {
            int mid = left + (right - left)/2;
            if (vec[mid] == target)
            {
                return mid;
            }
            else if (vec[mid] > target)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        return left;
    }
    int lengthOfLIS(vector<int>& nums) {
        vector<int>  vec;
        int idx = 0;
        if (0 == nums.size())
        {
            return 0;
        }
        vec.push_back(nums[0]);
        for (int i = 1; i < nums.size(); i++)
        {
            idx = vec.size() - 1;
            if (nums[i] > vec[idx])
            {
                vec.push_back(nums[i]);
            }
            else
            {
                idx = binary_search(vec, nums[i]);
                vec[idx] = nums[i];
            }
        }

        return vec.size();
    }

    int findPeakElement(vector<int>& nums){
        bool left = true;

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] > nums[i - 1])
            {
                left = true;
            }
            else if (left)
            {
                return i - 1;
            }
        }

        return nums.size() - 1;
    }


    /*
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t){
        int  win_beg = 0;
        int  win_end = 0;
        int  idx = 0;
        
        for (win_end = 0; win_end < nums.size(); win_end++)
        {
            if (win_end - win_beg >= k)
            {
                win_beg++;    
            }
            
            for (idx = win_beg; idx < win_end; idx++)
            {
                if (abs(nums[idx] - nums[win_end]) <= t)
                {
                    return true;
                }
            }
        }

        return false;
    }
    */

    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t){
        map<int, int>  m;
        map<int, int>::iterator   itr;
        int j = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            if (i - j > k && m[nums[j]] == j)
                m.erase(nums[j++]);
            itr = m.lower_bound(nums[i] - t);
            if (itr != m.end() && abs(itr->first - nums[i]) <= t)
                return true;

            m[nums[i]] = i;
        }

        return false;
    }

    vector<int> countBits(int num){
        if (num <= 0)
        {
            vector<int> tmp;
            return tmp;
        }
        vector<int> res(num+1, 0);
        for (size_t idx = 1; idx <= num; idx++)
        {
            if (idx%2)
                res[idx] = res[idx/2] + 1;
            else
                res[idx] = res[idx/2];
        }

        return res;
    }

    int candy(vector<int>& ratings) {
        int i = 0;
        int len = ratings.size();
        int tmp = 0;
        int sum = 0;
        vector<int> left(len, 1);
        vector<int> right(len, 1);

        for (i = 1; i < len; i++) 
        {
             if (ratings[i] > ratings[i - 1])
                left[i] = left[i - 1] + 1;
        }

        for (i = len - 2; i >= 0; i--) 
        {
             if (ratings[i] > ratings[i + 1])
                right[i] = right[i + 1] + 1;
        }


        for (i = 0; i < len; i++)
        {
            tmp = max(left[i], right[i]);
            sum += tmp;
        }

        return sum;
    }

    int collectvalue(vector<int>& coins, int amount){
        int min_cnt = numeric_limits<int>::max();
        int upper_bound = numeric_limits<int>::max();
        int tmp = 0;
        
        for (size_t i = 0; i < coins.size(); i++)
        {
            if (coins[i] < amount)
            {
                tmp = collectvalue(coins, amount - coins[i]);
                if (-1 == tmp)
                    continue;
            }
            else if (coins[i] == amount)
            {
                tmp = 0;
            }
            else
            {
                break;
            }

            if (tmp < min_cnt)
                min_cnt = tmp;
        }

        if (upper_bound == min_cnt)
            return -1;
        else
            return min_cnt + 1;
    }
    /*
    int coinChange(vector<int>& coins, int amount){
        int res = 0;
        sort(coins.begin(), coins.end());
        res = collectvalue(coins, amount);
        return res;
    }
    */
    int coinChange(vector<int>& coins, int amount){
        vector<int> dp(amount + 1, amount + 1);
        int tmp = 0;

        if (0 == amount)
        {
            return 0;
        }

        dp[0] = 0;
        sort(coins.begin(), coins.end());
        for (int i = 1; i <= amount; i++)
        {
            tmp = amount + 1;
            for (int j = 0; j < coins.size(); j++)
            {
                if (coins[j] <= i)
                {
                    tmp = min(dp[i - coins[j]] + 1, tmp);
                }
                else
                {
                    break;
                }
            }
            dp[i] = tmp;
        }

        if (dp[amount] == amount + 1)
            return -1;
        else
            return dp[amount];
         
    }


    int countRangeSum(vector<int>& nums, int lower, int upper){
        if (0 == nums.size())
            return 0;
        vector<int>  sum_array(nums.size(), 0);
        sum_array[0] = nums[0];
        for (int i = 0; i < sum_array.size(); i++)
        {
            sum_array[i] = nums[i] + sum_array[i - 1];
        }

        int sum = sum_array[sum_array.size() - 1];
        sort(sum_array.begin(), sum_array.end());

        vector<int>::iterator t;
        t = unique(sum_array.begin(), sum_array.end());
        SegmentTree  tree(sum_array, 0, t - sum_array.begin() - 1);
        int ans = 0;
        for (int i = nums.size(); i >= 0; i--)
        {
            tree.update(sum);
            sum -= nums[i];
            ans += tree.sum(lower + sum, upper + sum);
        }

        return ans;
    }
    
    int maximumGap(vector<int>& nums){
        int minnum = 0;
        int maxnum = 0;
        double interval = 0;
        int n = nums.size();
        int idx = 0;

        if (n < 2)
            return 0;
        
        minnum = *min_element(nums.begin(), nums.end());
        maxnum = *max_element(nums.begin(), nums.end());        
        interval = ((double)(maxnum - minnum))/(n - 1);

        //vector<int>  minval(n - 1, 0);
        //vector<int>  maxval(n - 1, 0);
        vector<int>  minval(n - 1, INT_MAX);
        vector<int>  maxval(n - 1, INT_MIN);

        for (int i = 0; i < n; i++)
        {
            if (nums[i] != maxnum)
            {
                idx = (int)((nums[i] - minnum)/interval);
                minval[idx] = min(minval[idx], nums[i]);
                maxval[idx] = max(maxval[idx], nums[i]);
            }
        }


        int ret = 0;
        int prevmax = maxval[0];
        for (int i = 1; i < n - 1; i++)
        {
            if (minval[i] != INT_MAX)
            {
                ret = max(ret, minval[i] - prevmax);
                prevmax = maxval[i];
            }
        }

        ret = max(ret, maxnum - prevmax);
        return ret;

        
    }

    int minof(int a, int b, int c)
    {
        int tmp = (a > b) ? b:a;
        return (tmp < c) ? tmp: c;
    }
    int nthUglyNumber(int n){
        vector<int> uglynum(n, 1);
        int index2, index3, index5;
        
        index2 = index3 = index5 = 0;
        for (int i = 1; i < n; i++)
        {
            int minnum = minof(2 * uglynum[index2], 3 * uglynum[index3], 5 * uglynum[index5]);

            uglynum[i] = minnum;
            if (2 * uglynum[index2] == minnum)
                index2 += 1;

            if (3 * uglynum[index3] == minnum)
                index3 += 1;
            
            if (5 * uglynum[index5] == minnum)
                index5 += 1;
        }

        return uglynum[n - 1];
    }

    int nthSuperUglyNumber(int n, vector<int>& primes){
        vector<int> idx(primes.size(), 0);
        vector<int> ugly(n, 1);
        for (int i = 1; i < n; i++)
        {
            ugly[i] = INT_MAX;
            for (int j = 0; j < primes.size(); j++)
            {
                ugly[i] = min(ugly[i], ugly[idx[j]] * primes[j]);
            }

            for (int j = 0; j < primes.size(); j++)
            {
                if (ugly[i] == ugly[idx[j]] * primes[j])
                {
                    idx[j] += 1;
                }
            }
        }
        return ugly[n - 1];
    }
  
private:
	 
};


void test_integerBreak()
{
	int  result = 0;
	Solution s;
	result = s.integerBreak(9);
	cout<<"Product :"<<result<<endl;
}


void test_simplepath()
{
    string input;
    string result;
    Solution s;
    
    cout<<"Please input string:"<<endl;
    cin>>input;
    result = s.simplifyPath(input);

    cout<<"Path:   "<<result<<endl;
}

void test_pivot()
{
    int idx = 0;
    int a[] = {4, 5, 6, 7, 0, 1, 2};
    vector<int>  vec(a, a + 7);
    Solution s;
    for (int i = 0; i < sizeof(a)/sizeof(int); i++)
    {
        idx = s.search(vec, a[i]);
        cout<<a[i]<<" position: "<<idx<<endl;    
    }
}

void test_numberword()
{
    string  res;
    Solution s;

    int a[] = {1010, 123, 1234567, 1000000000, 1018118, 0, 100};
    for (int i = 0; i < sizeof(a)/sizeof(int); i++)
    {
        res = s.numberToWords(a[i]);
        cout<<a[i]<<" :"<<endl;    
        cout<<res<<endl;
    }

}

void test_square()
{

    int idx = 0;
    Solution s;
    bool  res = false;
    for (int i = 0; i <= 100; i++)
    {
        res = s.isPerfectSquare(i);
        if (false == res)
        {
            cout<<i<<" : FALSE"<<endl;    
        }
        else
        {
            cout<<i<<" : TRUE"<<endl;    
        }
        
    }


    /*
    int left = 10;
    int right = 80;
    int num = 65538;
    long square = 0;
    square = (long)num * (long)num;
    cout<<"Square: "<<square<<endl;
    num = left + (right - left)>>1;
    cout<<"Number: "<<num<<endl;
    num = (right - left)>>1+left;
    cout<<"Number: "<<num<<endl;
    */
}

void test_subsequence()
{
    string child[5] = {"abcd", "bcd", "abc", "adc", "dcba"};
    string Parent = "abcd";
    Solution s;
    bool res = false;

    for (int i = 0; i < 5; i++)
    {
        res = s.isSubsequence(child[i], Parent);
        if (res)
        {
            cout<<child[i]<<"  belong to  "<<Parent<<endl;
        }
        else
        {
            cout<<child[i]<<"  don't belong to  "<<Parent<<endl;
        }
    }

}

void test_LIS()
{
    int a[] = {56, 6, 37, 73, 91, 82, 9, 72, 34, 76};
    int len = sizeof(a)/sizeof(int);
    vector<int> vec(a, a + len);
    int res = 0;
    Solution s;

    res = s.lengthOfLIS(vec);
    cout<<"Number: "<<res<<endl;
    
}

void test_countbits()
{
    int num = 20;
    Solution s;
    vector<int> count;
    count = s.countBits(num);

    cout<<"Size: "<<count.size()<<endl;
    for (size_t i = 0; i < count.size(); i++)
    {
        cout<<count[i]<<", ";
    }
    cout<<endl;
    
}

void test_neardup()
{
    int a[] = {56, 6, 37, 73, 91, 82, 9, 72, 34, 76};
    int len = sizeof(a)/sizeof(int);
    vector<int> vec(a, a + len);
    int res = 0;
    Solution s;

    res = s.lengthOfLIS(vec);
    cout<<"Number: "<<res<<endl;
}


void test_candy()
{
    int a[] = {4, 7, 22, 25, 9, 10, 24, 21, 28, 14};
    int len = sizeof(a)/sizeof(int);
    vector<int> vec(a, a + len);
    int res = 0;
    Solution s;

    res = s.candy(vec);
    cout<<"Candy: "<<res<<endl;    
}


void test_coin()
{
    int a[] = {2};
    int len = sizeof(a)/sizeof(int);
    vector<int> vec(a, a + len);
    
    int total = 3;
    Solution s;
    int res = 0;

    res = s.coinChange(vec, total);
    cout<<"Coin: "<<res<<endl;            
}

void test_uglynumber()
{
    Solution s;
    int res = 0;
    
    for (int i = 1; i < 20; i++)
    {
        res = s.nthUglyNumber(i);
        cout<<res<<endl;
    }
}

int main()
{

    //test_integerBreak();
    //test_simplepath();
    //test_pivot();
    //test_square();
    //test_numberword();

    //test_subsequence();
    //test_LIS();

    //test_countbits();
    //test_candy();
    //test_coin();
    test_uglynumber();
    return 1;
}


