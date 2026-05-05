#include<iostream>
using namespace std;

class BitonicArray {
private:
    int* inputarray;
    int inputsize;
    int bitonicpoint;
    int pointindex;
    int comparisons;
    int swaps;

    void bubbleSort(int arr[], int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {


                comparisons++;
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swaps++;
                }
            }
        }
    }

    void selectionSort(int arr[], int n) {

        int minidx;

        for (int i = 0; i < n - 1; i++) {
            minidx = i;


            for (int j = i + 1; j < n; j++) {
                comparisons++;
                if (arr[j] > arr[minidx]) {
                    minidx = j;
                }

            }

            if (minidx != i) {
                swap(arr[minidx], arr[i]);
                swaps++;
            }
        }
    }

public:
    BitonicArray(int n) {
        inputsize = n;
        inputarray = new int[inputsize];
        comparisons = 0;
        swaps = 0;
        bitonicpoint = 0;
        pointindex = 0;
    }

    void insert(int index , int value) {
        inputarray[index] = value;
        if (value > bitonicpoint)
            bitonicpoint = value;
    }

    void BuildBitonic() {

        for (int i = 0; i < inputsize; i++) {                          //4lna 2l bitonic point
            if (inputarray[i] == bitonicpoint) {
                swap(inputarray[i], inputarray[inputsize - 1]);
                inputsize--;
                break;
            }
        }


        int bubblesize = inputsize / 2;
        int selectionsize = inputsize - bubblesize;
        int* bubblearray = new int[bubblesize];
        int* selectionarray = new int[selectionsize];           //declarations ya 7ag



        for (int i = 0, j = 0; i < inputsize; i++) {                 // 2sm 2l elements 3ala 2l arrays w lw odd 2l selection bya5od 2ktr 34an rgoola
            if (i < bubblesize) {
                bubblearray[i] = inputarray[i];
            }
            else if (i >= bubblesize) {
                selectionarray[j] = inputarray[i];
                j++;
            }
        }


        bubbleSort(bubblearray, bubblesize);

        selectionSort(selectionarray, selectionsize);

        inputsize++;                                            // gam3 2l array bubble -> bitonicpoint -> selection , w hat 2l index bta3 2l bitonic point

        int i = 0;
        for (; i < bubblesize; i++) {
            inputarray[i] = bubblearray[i];
        }
        inputarray[i] = bitonicpoint;
        pointindex = i;
        i++;
        for (int j = 0; j < selectionsize; j++) {
            inputarray[i] = selectionarray[j];
            i++;
        }


        delete[] bubblearray;
        delete[] selectionarray;

    }

    void print() {
        cout << "Array after Bitonic sort: ";
        for (int i = 0; i < inputsize; i++)
            cout << inputarray[i] << " ";
        cout << "\n";
    }

    void stats() {
        cout << "comparisons: " << comparisons
            << "\nswaps: " << swaps << "\n";
    }

    void search(int searchtarget) {
        bool found = false;
        bool left = false, right = false, peak = false;

        for (int i = 0; i < inputsize; i++) {
            if (inputarray[i] == searchtarget) {
                found = true;

                if (i < pointindex) left = true;
                else if (i == pointindex) peak = true;
                else right = true;
            }
        }

        if (!found) {
            cout << "Target not present in the array.\n";
        }
        else {
            if (peak) cout << "Target found at the bitonic point.\n";
            if (left) cout << "Target exists in left half (ascending).\n";
            if (right) cout << "Target exists in right half (descending).\n";
        }
    }

    ~BitonicArray() {
        delete[] inputarray;
    }
};


int main() {


    cout << "=================== TEST CASE 1:Target at the bitonic point =====================\n\n";

    
    int arr1[] = { 4, 11, 7, 20, 3, 9 };
    BitonicArray test1(6);

    for (int i = 0; i < 6; i++) {
        test1.insert(i, arr1[i]);
    }

    test1.BuildBitonic();
    test1.print();
    test1.stats();

    cout << "Search Target: 20\n";
    test1.search(20);

   
    cout << "\n\n=================== TEST CASE 2:Target at the left =====================\n\n";


    int arr2[] = { 1, 3, 8, 12, 4, 2, 10 };
    BitonicArray test2(7);

    for (int i = 0; i < 7; i++) {
        test2.insert(i, arr2[i]);
    }

    test2.BuildBitonic();
    test2.print();
    test2.stats();

    cout << "Search Target: 3\n";
    test2.search(3);


    cout << "\n\n=================== TEST CASE 3:Target at the right =====================\n\n";


    int arr3[] = { 15, 6, 22, 9, 13, 5, 18, 2 };
    BitonicArray test3(8);

    for (int i = 0; i < 8; i++) {
        test3.insert(i, arr3[i]);
    }

    test3.BuildBitonic();
    test3.print();
    test3.stats();

    cout << "Search Target: 5\n";
    test3.search(5);

    
    cout << "\n\n=================== TEST CASE 4:Target Not present =====================\n\n";


    int arr4[] = { 30, 12, 25, 7, 19, 3 };
    BitonicArray test4(6);

    for (int i = 0; i < 6; i++) {
        test4.insert(i, arr4[i]);
    }

    test4.BuildBitonic();
    test4.print();
    test4.stats();

    cout << "Search Target: 100\n";
    test4.search(100);


    cout << "\n\n=================== TEST CASE 5:Array with duplicate elements =====================\n\n";


    int arr5[] = { 5, 8, 5, 14, 8, 2, 5 };
    BitonicArray test5(7);

    for (int i = 0; i < 7; i++) {
        test5.insert(i, arr5[i]);
    }

    test5.BuildBitonic();
    test5.print();
    test5.stats();

    cout << "Search Target: 5\n";
    test5.search(5);



    cout << "\n\n\n";
    return 0;
}


