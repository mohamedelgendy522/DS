#include <iostream>
#include <stack>
#include <string>
using namespace std;

int evaluate(string s)
{
    stack<int> st;
    int result = 0;
    int num = 0;
    int sign = 1; // +1 or -1

    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];

        if (isdigit(c))
            num = num * 10 + (c - '0');

        else if (c == '+' || c == '-')
        {
            // find previous non-space character
            int j = i - 1;
            while (j >= 0 && s[j] == ' ') 
                j--;

            if (c == '+')
            {
                // unary plus is invalid
                if (j < 0 || s[j] == '(')
                {
                    cout << "Invalid expression: unary + is not allowed\n";
                    exit(0);
                }

                result += sign * num;
                num = 0;
                sign = 1;
            }

            else // c == '-'
            {
                // unary minus is allowed
                if (j < 0 || s[j] == '(')
                {
                    sign = -1;
                    continue;
                }

                result += sign * num;
                num = 0;
                sign = -1;
            }
        }

        else if (c == '(')
        {
            st.push(result);
            st.push(sign);

            result = 0;
            sign = 1;
        }

        else if (c == ')')
        {
            result += sign * num;
            num = 0;

            result *= st.top(); // sign before '('
            st.pop();

            result += st.top(); // previous result
            st.pop();
        }
    }

    return result + sign * num;
}

int main()
{
    string s;
    while (true)
    {
        cout << "Enter expression: ";
        getline(cin, s);

        cout << "Result = " << evaluate(s) << endl << endl;
    }

    return 0;
}