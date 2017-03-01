// leetcode.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <limits> 
#include <iomanip>
#include <algorithm>

using namespace std;

/*
class Solution {
public:
	bool isValid (string const& s) 
	{
		string left = "([{";
		string right = ")]}";
		stack<char> stk;
		std::size_t i = 0;
		std::size_t pos = 0;
		for (i = 0; i < s.size(); i++) 
		{
			if (left.find(s[i]) != std::string::npos)
			{
				stk.push(s[i]);
			}
			else
			{
				pos = right.find(s[i]);
			    if (pos == std::string::npos)
					continue;
				if (stk.empty() || stk.top() != left[pos])
					return false;
				else 
					stk.pop();
			}

		}
		return stk.empty();
	}
};
*/

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

struct Point {
        int x;
        int y;
        Point() : x(0), y(0) {}
        Point(int a, int b) : x(a), y(b) {}
};

class Solution {
public:
	int removeDuplicates(vector<int>& nums) 
	{
		vector<int>::iterator itr = nums.begin();
		int iPreNum = 0;
		while(itr != nums.end())
		{
			if (itr == nums.begin())
			{
				iPreNum = *itr;
			}
			else
			{
				if (*itr == iPreNum)
				{
					
				}
				else
				{
					iPreNum = *itr;
				}
			}
			itr++;
		}
	}
	vector<vector<string> > groupAnagrams(vector<string> &strs) 
	{
		map<string, vector<string> >::iterator  mul_itr;
		map<string, vector<string> > hash_map;
		vector<vector<string> >  iResult;
		vector<string>::iterator itr;
		string tmp;
		for (itr = strs.begin(); itr != strs.end(); itr++)
		{
			tmp = *itr;
			sort(tmp.begin(), tmp.end());
			hash_map[tmp].push_back(*itr);
		}

		for (mul_itr = hash_map.begin(); mul_itr != hash_map.end(); mul_itr++)
		{
			iResult.push_back(mul_itr->second);
		}

		return iResult;
	}

	int longestValidParentheses(string s)
	{
		int i = 0;
		int length = s.size();
		int max_len = 0;
		int last = -1;
		int cnt = 0;
		stack<int> st;

		for (i = 0; i < length; i++)
		{
			if (s[i] == '(')
			{
				st.push(i);
			}
			else 
			{
				if (st.empty())
				{
					last = i;					
				}
				else 
				{
					st.pop();	
					if (st.empty())
					{
						cnt = i - last;
						max_len = (max_len > cnt) ? max_len:cnt;
					}
					else
					{
						cnt = i - st.top();
						max_len = (max_len > cnt) ? max_len:cnt;											
					}
				}
			}
		}

		return max_len;
	}

        vector<Interval> insert(vector<Interval>& intervals, Interval newInterval)
        {
            vector<Interval>::iterator  itr = intervals.begin();
            while (itr != intervals.end())
            {
                if (newInterval.end < itr->start)
                {
                    intervals.insert(itr, newInterval);
                    return intervals;
                }
                else if (newInterval.start > itr->end)
                {
                    itr++;
                    continue;
                }
                else
                {
                    newInterval.start = min(newInterval.start, itr->start);
                    newInterval.end  =  max(newInterval.end, itr->end);
                    itr = intervals.erase(itr);
                }
            }
            intervals.insert(intervals.end(), newInterval);
            return intervals;
        }

        string minWindow(string s, string t){
            int begin = 0;
            int end = 0;
            int minbegin = 0;
            int minend = 0;
            int minsize= numeric_limits<int>::max();
            int count = t.size();
            int size = 0;
            string minstr = "";

            vector<int> needFind(128, 0);
            vector<int> Found(128, 0);
            for (size_t i = 0; i < t.size(); i++)
            {
                needFind[t[i]]++;
            }

            Found[s[0]]++;
            if (Found[s[0]] <= needFind[s[0]])
            {
                count--;
            }
            
            while (1)
            {
                if (0 == count)
                {
                    while (Found[s[begin]] > needFind[s[begin]])
                    {
                        Found[s[begin]]--;
                        begin++;
                    }

                    size = end - begin + 1;
                    if (size < minsize)
                    {
                        minbegin = begin;
                        minend   =  end;
                        minsize  =  size;
                    }
                }

                if (end < s.size())
                {
                    end++;
                    Found[s[end]]++;
                    if (needFind[s[end]] >= Found[s[end]])
                    {
                        count--;
                    }
                }
                else
                {
                    break;
                }
            }

            if (minsize != numeric_limits<int>::max())
            {
                minstr = s.substr(minbegin, minsize);
            }

            return minstr;
        }
    
        void wiggleSort(vector<int>& nums) {
            int len = nums.size();
            int tail = 0;
            int mid = (len + 1) >> 1;
            if(len <= 1) 
                return;

            sort(nums.begin(), nums.end());
            vector<int> tmp(len, 0);

            tail = len;
            for (int i = 0; i < len; i++)
            {
                tmp[i] = (i & 1) == 0 ? nums[--mid] : nums[--tail];
            }
            nums = tmp;
	}

        /*按照O(n) 复杂度实现, 题目中要求有顺序*/
        void wiggleSort2(vector < int > & nums)
        {
            for (int i = 1; i < nums.size(); i++)
            {
                if (((i & 1) == 0 && nums[i - 1] < nums[i]) ||
                    ((i & 1) != 0 && nums[i - 1] > nums[i]))
                {
                    int tmp = nums[i - 1];
                    nums[i - 1] = nums[i];
                    nums[i] = tmp;
                }
            }
        }

        
        string multiply1(string num1, string num2){
            int len1 = num1.length();
            int len2 = num2.length();
            vector<int>  vec(len1 + len2, 0);
            string tmp;
            int carry = 0;
            int num = 0;
            int i = 0;
            int j = 0;
            int size = 0;

            reverse(num1.begin(), num1.end());
            reverse(num2.begin(), num2.end());
            for (i = 0; i < len1; i++)
            {
                for (j = 0; j < len2; j++)
                {
                    num = (num1[i] - '0') * (num2[j] - '0') + vec[i + j];
                    carry = num/10;
                    num = num%10;

                    vec[i + j + 1] += carry;  
                    vec[i + j] = num;
                }
            }

            size = len1 + len2 - 1;
            while (vec[size] == 0 & size > 0)
            {
                size--;
            }

            if (size < 0)
            {
                return "0";
            }

            tmp.reserve(size + 1);
            for (i = 0; i <= size; i++)
            {
                tmp.push_back(vec[size - i] + '0');
            }
           
            return tmp;
        }
       
     


        typedef long long int_64;
        const static int MAX_LEN = 9;
        const static int MAX_INT = 1000000000;

        vector<int_64>  IntArray(string num){
            int cnt = num.size()/9 + 1;
            vector<int_64>  vec(cnt, 0);

            cnt = 0;
            for (int i = num.size(); i > 0; i -= MAX_LEN)
            {
                int tmp = 0;
                const int low = max(i - MAX_LEN, 0);
                for (int j = low; j < i; j++)
                {
                    tmp = tmp*10 + num[j] - '0';
                }
                vec[cnt++] = tmp;
            }       

            return vec;
        }
        vector<int_64>  LargeIntMul(const vector<int_64> &vec1, const vector<int_64> &vec2){
            vector<int_64> mul(vec1.size() + vec2.size(), 0);
            for (int i = 0; i < vec1.size(); i++)
            {
                for (int j = 0; j < vec2.size(); j++)
                {
                    mul[i + j ] += vec1[i]*vec2[j];

                    if (mul[i + j] > MAX_INT)
                    {
                        mul[i + j + 1] += mul[i + j]/MAX_INT;
                        mul[i + j] = mul[i + j]%MAX_INT;
                    }
                }
            }

            return mul;
        }

        string LargeIntToString(vector<int_64>  &vec){
            stringstream ss;
            vector<int_64>::reverse_iterator itr;  
            bool started = false;

            for (itr = vec.rbegin(); itr != vec.rend(); ++itr)
            {
                cout<<*itr<<endl;
                if (started)
                {
                    ss<<setw(MAX_LEN) << setfill('0')<<*itr;
                }
                else
                {
                    if (*itr != 0)
                    {
                        started = true;
                        ss<<*itr;
                    }
                }
            }
            
            if (!started)
            {
                return "0";
            }
            else
            {
                return ss.str();
            }
        }
        string multiply(string num1, string num2){
            vector<int_64>  vec1 = IntArray(num1);
            vector<int_64>  vec2 = IntArray(num2);
            vector<int_64>  vec;
            
            vec = LargeIntMul(vec1, vec2);

            return LargeIntToString(vec);
        }

        vector<int> findSubstring(string s, vector<string>& words) {
            int str_num = words.size();
            int str_len = 0;
            int i = 0;
            int j = 0;
            int end = 0;
            map<string, int>  word_cnt;
            map<string, int> match;
            vector<int>  idx_vec;
            
            if (str_num < 1)
            {
                return idx_vec;
            }

            str_len = words[0].length();
            for(i = 0; i < words.size(); i++)
            {
                word_cnt[words[i]] += 1;
            }

            end = s.length() - str_len * str_num;
            for (i = 0; i <= end; i++)
            {
                cout<<"Come in"<<endl;
                match.clear();
                for (j = 0; j < words.size(); j++)
                {
                    string word = s.substr(i + j * str_len, str_len);   
                    if (word_cnt.find(word) != word_cnt.end())
                    {
                        match[word]++;
                        if (match[word] > word_cnt[word])
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }

                if (words.size() == j)
                {
                    idx_vec.push_back(i);
                }
            }
            
            return idx_vec;
        }


        vector<int> spiralOrder(vector<vector<int> >& matrix){
            int start_x = 0, start_y = 0;
            int end_x, end_y;
            int i = 0;
            vector<int> result; 

            if (matrix.empty())
            {
                return result;
            }
            
            end_y = matrix.size() - 1;
            end_x = matrix[0].size() - 1;

            result.reserve((end_x + 1)*(end_y + 1)); //allocate 
            
            while (1)
            {
                //left to right
                for (i = start_x; i <= end_x; i++)
                {
                    result.push_back(matrix[start_y][i]);
                }
                if (++start_y > end_y)
                    break;

                //top to bottom
                for (i = start_y; i <= end_y; i++)
                {
                    result.push_back(matrix[i][end_x]);
                } 
                if (start_x > --end_x)
                    break;

                //righ to left 
                for (i = end_x; i >= start_x; i--)
                {
                    result.push_back(matrix[end_y][i]);
                }  
                if (start_y > --end_y)
                    break;

                //bottom to top
                for (i = end_y; i >= start_y; i--)
                {
                    result.push_back(matrix[i][start_x]);
                }  
                if (++start_x > end_x)
                    break;
            }
            return result;
        }

        vector<vector<int> > generateMatrix(int n){
            vector<vector<int> > flat(n, vector<int>(n));

            int num = 1;
            int i = 0;
            int start = 0, end = n -1;
            while (start <= end)
            {
                if (start == end)
                {
                    flat[start][end] = num++;
                    return flat;
                }
                
                //left to right
                for (i = start; i < end; i++)
                {
                    flat[start][i] = num++;
                }

                //top to bottom
                for (i = start; i < end; i++)
                {
                    flat[i][end] = num++;
                } 

                //righ to left 
                for (i = end; i > start; i--)
                {
                    flat[end][i] = num++;
                }  

                //bottom to top
                for (i = end; i > start; i--)
                {
                    flat [i][start] = num++;
                }  
                start++;
                end--;
            }

            return flat;
        }

        string convert(string s, int numRows){
            int i = 0;
            int block = numRows + numRows - 2;
            vector<string> array(numRows);
            vector<int> idx(block, 0);
            string zigstr;

            if (numRows <= 1 || s.size() <= 1)
            {
                return s;
            }
            
            for (i = 0; i < block; i++)
            {   
                if (i >= numRows)
                {
                    idx[i] = block - i;
                }
                else
                {
                    idx[i] = i;
                }
            }
            
            
            for (i = 0; i < s.length(); i++)
            {
                int offset = i%block;
                array[idx[offset]].push_back(s[i]);
            }

            for (i = 0; i < array.size(); i++)
            {
                zigstr += array[i];
            }

            return zigstr;
        }

        vector<string> fullJustify(vector<string>& words, int maxWidth){
            vector<string> lines;
            string tmp(maxWidth, 0);

            int i = 0;
            int j = 0;
            while (i < words.size())
            {
                int len = words[i].length();
                if (len > maxWidth)
                    return lines;

                int start =  i;
                int prev = 0;
                while (len <= maxWidth)
                {
                    prev = len;
                    len += words[++i].length() + 1;
                }
                int end = i - 1;
                int space = maxWidth - prev;
                int nelt = end - start;
                int idx = 0;
                if (nelt == 0)
                {
                    
                    tmp.replace(idx, words[start].length(), words[start]);
                    idx += words[start].length();
                    tmp.replace(idx, maxWidth - 1, maxWidth - idx, ' ');
                }
                else
                {
                    vector<int> pad(nelt, space/nelt);                
                    for (j = 0; j < space%nelt; j++)
                    {
                        pad[j] += 1;
                    }

                   
                    tmp.replace(0, words[start].length(), words[start]);
                    idx += words[start].length();
                    for (j = 0; j < nelt; j++)
                    {
                        tmp.replace(idx, idx + pad[j] - 1, pad[j], ' ');
                        idx += pad[j];
                        tmp.replace(idx, words[start + j + 1].length(), words[start + j + 1]);
                        idx += words[start + j + 1].length();
                    }
                }

                lines.push_back(tmp);
            }

            return lines;
        }


        int maxPoints(vector<Point>& points){
            unordered_map<double, int>  table;
            typedef  unordered_map<double, int>::iterator   POINT_ITER;
            double slope = 0;
            int max = 0;
            int repeats = 0;
            for (int i = 0; i < points.size(); i++)
            {
                table.clear();

                table[-1] = 0;  //one point or duplicate point
                repeats = 1;
                for (int j = 0; j < points.size(); j++)  //j为什么不等于i
                {
                    if (j == i)
                        continue;
                    
                    if (points[i].x == points[j].x && points[i].y == points[j].y)
                    {
                        repeats += 1;
                        continue;
                    }
                    else if (points[i].x == points[j].x)
                    {
                        slope = (double)numeric_limits<int>::max();
                    }
                    else
                    {
                        slope = (double)(points[i].y - points[j].y)/(points[i].x - points[j].x);
                    }

                    table[slope] += 1;
                }

                
                for (POINT_ITER itr = table.begin(); itr != table.end(); itr++)
                {
                    if (max < itr->second + repeats)
                    {
                        max = itr->second + repeats;  //重复节点
                    }
                }

            }

            return max;
        }

};


void test_insert()
{
    Interval  segments[2];
    Interval  addseg;

    segments[0].start = 1;
    segments[0].end = 7;
    segments[1].start = 6;
    segments[1].end = 9;
    
    addseg.start = 10;
    addseg.end  = 12;

    vector<Interval>  vec;
    vector<Interval>  res;
    int i = 0;
    Solution  sol;

    for (i = 0; i < 2; i++)
    {
        vec.push_back(segments[i]);
    }

    res = sol.insert(vec, addseg);
    
    for (i = 0; i < res.size(); i++)
    {
        cout<<"Start: "<<res[i].start<<",  End: "<<res[i].end<<endl;
    }
    

}


void  test_minwin()
{
    Solution  sol;
    string str1 = "ABCD";
    string str2 = "ABC";
    string res;

    res = sol.minWindow(str1, str2);
    
    cout<<"MinWindow: "<<res<<endl;

}

void test_wiggle()
{
    int a[6] = {1,5,1,1,6,4};
    vector<int> vec(a, a + 6);
    Solution  sol;
    sol.wiggleSort(vec);

    for (int i = 0; i < vec.size(); i++)
    {
        cout<<vec[i]<<",";
    }
    cout<<endl;
}

void test_multiply()
{
    string str1 = "725071900";
    string str2 = "6478"; //4789841874848784
    string str;
    Solution sol;
    str = sol.multiply(str1, str2);
    cout<<"result: "<<str<<endl;
}

void test()
{
    string str1 = "ABCD";
    string tmp;
    tmp.reserve(str1.size());

    for (int i = 0; i < str1.size(); i++)
    {
        tmp.push_back(str1[i]);
    }
    cout<<"test: "<<tmp <<endl;

    str1.erase();
    cout<<"Size: "<<str1.size()<<endl;
    cout<<"Length: "<<str1.length()<<endl;

    int dividend = 0; //numeric_limits<int>::min() + 1;
    int divisor = -1;
    int num = 0;
    num = dividend/divisor;

    cout<<"dividend: "<<dividend<<endl;
    cout<<"quotient: "<<num<<endl;

    dividend = 5;
    divisor = 2;
    double val = (double)dividend/divisor;

    cout<<"Value: "<<val<<endl;

    
}


void test_substring()
{
    string str1 = "barfoothefoobarman";
    string strs[2] = {"bar", "foo"}; 
    vector<string> vec_str(strs, strs + 2);
    vector<int>  vec;   
    Solution sol;
    vec = sol.findSubstring(str1, vec_str);

    cout<<"idices: ";
    for (vector<int>::iterator  itr = vec.begin(); itr != vec.end(); itr++)
    {
        cout<<*itr<<",";    
    }
    
}

void test_matrix()
{
    int a1[5] = {1, 2, 3, 4, 5};
    int a2[5] = {6, 7, 8, 9, 10};
    int a3[5] = {11, 12, 13, 14, 15};
    Solution sol;
    vector<int>  row;

    vector<int> vec1(a1, a1 + 5);
    vector<int> vec2(a2, a2 + 5);
    vector<int> vec3(a3, a3 + 5);

    vector<vector<int> > matrix;
    matrix.push_back(vec1);
    matrix.push_back(vec2);
    matrix.push_back(vec3);

    row = sol.spiralOrder(matrix);

    for (int i = 0; i < row.size(); i++)
    {
        cout<<row[i]<<",";
    }
    cout<<endl;
}

void test_genmatrix(int n)
{
    vector<vector<int> > result;
    Solution sol;
    result = sol.generateMatrix(n);

    for (int i = 0; i < result.size(); i++)
    {
        for (int j = 0; j < result[0].size(); j++)
        {
            cout<<result[i][j]<<" ";
        }
        cout<<endl;
    }
}

void test_convert()
{
    Solution sol;
    string str = "P";
    string cnvstr;

    cnvstr = sol.convert(str, 3);
    
    cout<<"ZigZag: "<<cnvstr<<endl;
}


void test_subwindow()
{
    Solution sol;
    vector<int> result;
    string str = "a";
    string w1 = "a";
    string w2 = "a";

    vector<string> dict;
    dict.push_back(w1);
    dict.push_back(w2);    

    result = sol.findSubstring(str, dict);

    for (size_t i = 0; i < result.size(); i++)
    {
        cout<<result[i]<<endl;
    }
}


void test_fullJustify()
{
    Solution sol;
    string str[7] = {"This", "is", "an", "example", "of", "text", "justification."};

    vector<string> words(str, str + 7);
    vector<string> result;

    result = sol.fullJustify(words, 10);
    for (size_t i = 0; i < result.size(); i++)
    {
        cout<<result[i]<<endl;
    }
}

int main(int argc, char* argv[])
{
    /*
    int Len = 0;
    string str = "()";
    Solution sol;

    Len = sol.longestValidParentheses(str);
    cout<<"Length : "<<Len<<endl;
    */

    //test_insert();
    //test_minwin();
    //test_wiggle();
    //test_multiply();
    test();
    //test_substring();
    //test_matrix();
    //test_genmatrix(0);
    //test_convert();
    //test_subwindow();
    //test_fullJustify();
    return 0;
}



