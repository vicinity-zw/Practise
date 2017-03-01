#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>

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


class Solution {
public:
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
	
    int largestRectangleArea(vector<int>& heights) {
        stack<int>  s;
        heights.push_back(0);
        int sum = 0;
        int i = 0;
        int tmp = 0;
        for (i = 0; i < heights.size(); i++)
        {
            if (s.empty() || heights[i] > heights[s.top()])
            {
                s.push(i);	
            }
            else
            {
                tmp = s.top();
                s.pop();
                sum = max(sum, heights[tmp]*(s.empty() ? i : i - s.top() - 1));		
		 cout<<"sum: "<<sum<<endl;		
                i--;				
            }
        }
	return sum;	
    }

    int evalRPN(vector<string>& tokens) {
	vector<string>::iterator  itr;
	stack<string>  s;
	int x = 0;
	int y = 0;
	for (itr = tokens.begin(); itr != tokens.end(); itr++)
	{
		if (is_operator(*itr))
              {
                    y = std::stoi(s.top());
                    s.pop();			 
                    x = stoi(s.top());
                    s.pop();
		     if (*itr == "+")
			 	x = +y;
		     else if (*itr == "-")
		         x = -y;			 
		     else if (*itr == "*")
                       x = *y;			 
		     else 
                       x = /y;			 

                    s.push(to_string(x));
	       }
		else
		{
			s.push(*itr);
		}
	}
	return (stoi(s.top()));
    }


private:
    bool is_operator(const string &str)
    {
    	 string ops = "+-*/";
        if (str.size() == 1 && ops.find(str) != string::npos) 	
        {
        	return true;
        }
	 return false;	
    }
	 
};

void  test_RPN()
{
	int  Result = 0;
	Solution s;
	string arry[] = {"2", "1", "+", "3", "*"};
	vector<string>  vec_str(arry, arry + 5);
	Result = s.evalRPN(vec_str);
	cout<<"Result :"<<Result<<endl;
}

void  test_rectangle()
{
	int  MaxRec = 0;
	Solution s;
	int arry[] = {5,4,5};
	vector<int>  vec_int(arry, arry + 3);
	MaxRec = s.largestRectangleArea(vec_int);
	cout<<"Max :"<<MaxRec<<endl;
}


int main()
{
	//test_RPN();
}


