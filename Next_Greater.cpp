#include <iostream>
using namespace std;

class Stack {
private:
    int* data;
    int top;
    int capacity;

    void resize() {
        capacity *= 2;
        int* newData = new int[capacity];
        for (int i = 0; i <= top; i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
    }

public:
    Stack(int cap = 10) : top(-1), capacity(cap) {
        data = new int[capacity];
    }

    ~Stack() {
        delete[] data;
    }

    void push(int val) {
        if (top + 1 == capacity)
            resize();
        data[++top] = val;
    }

    void pop() {
        if (!empty()) top--;
    }

    int peek() {
        return data[top];
    }

    bool empty() {
        return top == -1;
    }
};

struct Pair {
    int val, idx;
};

int* circular_arr(int arr[], int n) {
    int* res = new int[n];
    for (int i = 0; i < n; i++) res[i] = -1;

    Stack<Pair> st(n);

    for (int i = 0; i < 2 * n; i++) {
        int idx = i % n;
        while (!st.empty() && st.peek().val < arr[idx]) {
            res[st.peek().idx] = arr[idx];
            st.pop();
        }
        if (i < n) {
            st.push({arr[idx], idx});
        }
    }

    return res;
}

int main() {
    
    int n;
    cout << "please input the size of array: ";
    cin >> n;

    int* arr = new int[n];
    cout << "please input the elements of array: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int* ans = circular_arr(arr, n);

    cout << "display answer: ";
    for (int i = 0; i < n; i++)
        cout << ans[i] << " ";
    cout << endl;

    delete[] arr;
    delete[] ans;

    return 0;
}
