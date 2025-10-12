#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string infixToPostfix(string infix) {
    stack<char> st;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop();
        } else {
            while (!st.empty() && precedence(c) <= precedence(st.top())) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

string infixToPrefix(string infix) {
    reverse(infix.begin(), infix.end());

    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] == '(') infix[i] = ')';
        else if (infix[i] == ')') infix[i] = '(';
    }

    string postfix = infixToPostfix(infix);
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

int main() {
    string infix;

    cout << "Enter infix expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);

    cout << "Postfix Expression: " << postfix << endl;
    cout << "Prefix Expression: " << prefix << endl;

    return 0;
}
