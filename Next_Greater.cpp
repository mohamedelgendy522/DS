#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

vector<int> circular_arr(int arr[], int n) {
    vector<int> res(n, -1);
    stack<pair<int,int>> st;
    for(int i = 0; i < 2 * n; i++) {
        int idx = i % n;
        while (!st.empty() && st.top().first < arr[idx]) {
            res[st.top().second] = arr[idx];
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
    cout<<"please input the size of array: ";
    cin>>n;
    int arr[n];
    cout<<"please input the elements of array: ";
    for(int i = 0;i < n;i++) {
        cin>>arr[i];
    }
    vector<int> ans = circular_arr(arr,n);
    cout<<"display answer: ";
    for(int i = 0;i < n;i++) {
        cout<<ans[i]<<" ";
    }
}
