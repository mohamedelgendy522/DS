#include <iostream>
#include <vector>

using namespace std;

class RotatedArraySearcher {
private:
    vector<int> data;
    int comparisons;

public:
    RotatedArraySearcher(const vector<int>& inputArray)
        : data(inputArray), comparisons(0) {}

    bool search(int target) {
        int left = 0;
        int right = data.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            comparisons++;

            if (data[mid] == target) {
                return true;
            }
            if (data[left] == data[mid] && data[mid] == data[right]) {
                left++;
                right--;
            }
            else if (data[left] <= data[mid]) {
                comparisons += 2;
                if (data[left] <= target && target < data[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            else {
                comparisons += 2;
                if (data[mid] <= target && target <= data[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return false;
    }

    int getComparisonCount() const {
        return comparisons;
    }
};

int main() {
    int size, target;

    cout << "Enter array size: ";
    cin >> size;

    vector<int> arr(size);
    cout << "Enter array elements: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    cout << "Enter target value: ";
    cin >> target;

    RotatedArraySearcher searcher(arr);

    if (searcher.search(target)) {
        cout << "Found\n";
    } else {
        cout << "Not Found\n";
    }

    cout << "Number of comparisons: "
         << searcher.getComparisonCount() << endl;

    return 0;
}
