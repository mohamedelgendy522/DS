#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>
using namespace std;

class ExpressionEvaluator
{
private:
    stack<int> st;
    int result;
    int num;
    int sign; // +1 or -1

    // Helper to process operator
    void applyOperator()
    {
        result += sign * num;
        num = 0;
    }

    // Check unary operator
    bool isUnary(const string& s, int i)
    {
        int j = i - 1;
        while (j >= 0 && s[j] == ' ')
            j--;

        return (j < 0 || s[j] == '(');
    }

public:
    ExpressionEvaluator()
    {
        reset();
    }

    void reset()
    {
        while (!st.empty()) st.pop();
        result = 0;
        num = 0;
        sign = 1;
    }

    int evaluate(const string& s)
    {
        reset();

        for (int i = 0; i < s.length(); i++)
        {
            char c = s[i];

            if (c == ' ')
                continue;

            if (isdigit(c))
                num = num * 10 + (c - '0');

            else if (c == '+' || c == '-')
            {
                if (c == '+')
                {
                    if (isUnary(s, i))
                        throw invalid_argument("Unary + is not allowed");

                    applyOperator();
                    sign = 1;
                }

                else if (c == '-')
                {
                    if (isUnary(s, i))
                    {
                        sign = -1;
                        continue;
                    }

                    applyOperator();
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
                applyOperator();

                result *= st.top(); st.pop();
                result += st.top(); st.pop();
            }
        }

        return result + sign * num;
    }
};

int main()
{
    ExpressionEvaluator evaluator;
    string s;

    while (true)
    {
        cout << "Enter expression: ";
        getline(cin, s);

        try
        {
            int result = evaluator.evaluate(s);
            cout << "Result = " << result << endl << endl;
        }
        catch (exception& e)
        {
            cout << e.what() << endl << endl;
        }
    }

    return 0;
}