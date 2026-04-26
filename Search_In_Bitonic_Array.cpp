#include<iostream>
using namespace std;

void bubbleSort(int arr[], int n , int &comparisons , int &swaps) {     //mt3dl 34an 2l comparison wl swaps
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

void selectionSort(int arr[], int n , int &comparisons , int &swaps) {

    int minidx;

    for (int i = 0; i < n - 1; i++) {                                                                   
        minidx = i;


        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] > arr[minidx]) {                     // mt3dl nfs 2l kalam w 2l comaprison m3koos 34an descending 
                minidx = j;
            }

        }


        swap(arr[minidx], arr[i]);
        swaps++;
    }
}

void print(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}



int main() {
    int inputsize , number , bitonicpoint = 0 , pointindex , comparisons = 0 , swaps = 0;
    cout << "Enter Array Size:";
    cin >> inputsize;
    int* inputarray = new int[inputsize];

    cout << "Enter array numbers:";
    for (int i = 0; i < inputsize; i++){                         //d5l 2l elements w hat 2l bitonic point
        cin >> number;
        inputarray[i] = number;
        if (number > bitonicpoint)
            bitonicpoint = number;

    }

   

    for (int i = 0; i < inputsize; i++){                          //4lna 2l bitonic point
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


    for (int i = 0 , j = 0; i < inputsize; i++){                 // 2sm 2l elements 3ala 2l arrays w lw odd 2l selection bya5od 2ktr 34an rgoola
        if (i < bubblesize) {
            bubblearray[i] = inputarray[i];
        }
        else if (i >= bubblesize) {
            selectionarray[j] = inputarray[i];
            j++;
        }
    }

    bubbleSort(bubblearray, bubblesize , comparisons ,swaps);

    selectionSort(selectionarray, selectionsize , comparisons ,swaps);



    inputsize++;                                            // gam3 2l array bubble -> bitonicpoint -> selection , w hat 2l index bta3 2l bitonic point
    int i = 0;
    for (; i < bubblesize; i++){
        inputarray[i] = bubblearray[i];
    }
    inputarray[i] = bitonicpoint;
    pointindex = i;
    i++;
    for (int j = 0; j < selectionsize; j++){
        inputarray[i] = selectionarray[j];
        i++;
    }



    cout << "array after Bitonic sort:";
    print(inputarray, inputsize);
    cout << "comparisons:" << comparisons << "\nswaps:" << swaps << "\n";
    
    int searchtarget;
    cout << "Insert search target:";
    cin >> searchtarget;


    bool found = false;
    for (int i = 0; i < inputsize; i++) {                                   //linear search by7dd 7asb 2l pointindex
        if (inputarray[i] == searchtarget) {
            if (i < pointindex) {
                cout << "Target in the left half(ascending portion).";
            }
            else if (i == pointindex) {
                cout << "Target at the bitonic point.";
            }
            else if (i > pointindex) {
                cout << "Target in the right half (descending portion).";
            }
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Target not present in the array.";
    }


    cout << "\n";

    delete[] inputarray;
    delete[] bubblearray;
    delete[] selectionarray;
    return 0;
}


