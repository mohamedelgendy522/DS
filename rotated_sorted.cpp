#include <iostream>
#include <vector>
using namespace std;

int comparisons = 0;

// Best Case:  O(1)
// Average Case: O(log n)
// Worst Case: O(n)

bool rotated_sorted(int arr[], int target, int n) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        comparisons++;
        if (arr[mid] == target) {
            return true;
        }
        if (arr[l] == arr[mid] && arr[mid] == arr[r]) {
            l++;
            r--;
        } else if (arr[l] <= arr[mid]) {
            comparisons += 2;
            if (arr[l] <= target && target < arr[mid]) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        } else {
            comparisons += 2;
            if (arr[mid] <= target && target < arr[r]) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    return false;
}

int main() {
    int n, target;
    cout << "Please input the size of array: ";
    cin >> n;
    int arr[n];
    cout << "Please input the elements of array: ";
    for (int i = 0; i < n; i++) cin >> arr[i];
    cout << "Please input the target value: ";
    cin >> target;

    if (rotated_sorted(arr, target, n)) {
        cout << "Found" << endl;
    } else {
        cout << "Not found" << endl;
    }
    cout << "Number of comparisons: " << comparisons << endl;
}
