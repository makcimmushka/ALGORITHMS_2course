#include <iostream>
#include <algorithm>

using namespace std;

struct Pair {
    int value;
    bool key;
};


void stableCountingSort(Pair *arr, int n) //1 algorithm
{
    Pair *output = new Pair[n];

    int *count = new int[2];

    for (int i=0; i < 2; ++i)
        count[i] = 0;

    for (int i=0; i<n; ++i)
        count[arr[i].key]++;

    for (int i=1; i<=1; ++i)
        count[i] += count[i-1];

    for (int i = n-1; i>=0; i--)
    {
        output[count[arr[i].key]-1] = arr[i];
        count[arr[i].key]--;
    }

    for (int i = 0; i<n; ++i)
        arr[i] = output[i];
}


void fixSort(Pair *arr, int n) { // 2 algorithm
    int lp = 0;
    int rp = n-1;
    while (lp < rp) {
        while (arr[lp].key == 0) {
            lp++;
        }

        while (arr[rp].key == 1) {
            rp--;
        }

        if (lp < rp) {
            swap(arr[lp], arr[rp]);
        }
    }
}



void bubbleSort(Pair *arr, int n) // 3 algorithm
{
    int i, j;

    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (arr[j].key > arr[j+1].key)
                swap(arr[j], arr[j+1]);
}



void insertionSort(Pair *arr, int n) // 3 algorithm
{
    int i, key, j, value;
    for (i = 1; i < n; i++)
    {
        key = arr[i].key;
        value = arr[i].value;
        j = i - 1;

        while (j >= 0 && arr[j].key > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1].key = key;
        arr[j + 1].value = value;
    }
}


void cocktailSort(Pair *arr, int n) // 3 algorithm
{
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; ++i) {
            if (arr[i].key > arr[i + 1].key) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;

        swapped = false;

        end--;

        for (int i = end - 1; i >= start; --i) {
            if (arr[i].key > arr[i + 1].key) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        start++;
    }
}


void printArray(Pair *arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i].value << " " << arr[i].key << endl;
    }

    cout << endl;
}


void getValues(Pair *arr, Pair *temp, int size) {
    for (int i = 0; i < size; i++) {
        arr[i].key = temp[i].key;
        arr[i].value = temp[i].value;
    }
}


int main() {
    int size;

    cout << "Input size: " << endl;
    cin>>size;

    Pair *arr = new Pair [size];
    Pair *temp = new Pair [size];

    cout << "Input values: " << endl;

    for (int i = 0; i < size; i++) {
        cin>>arr[i].value;
    }

    cout << "Input keys: " << endl;

    for (int i = 0; i < size; i++) {
        cin>>arr[i].key;
    }

    getValues(temp, arr, size);
    cout << "Array is: " << endl;
    printArray(arr,size);


    stableCountingSort(arr, size);
    cout << "Result of 1 is:" << endl;
    printArray(arr, size);


    getValues(arr, temp, size);
    fixSort(arr, size);
    cout << "Result of 2 is:" << endl;
    printArray(arr, size);


    getValues(arr, temp, size);
    cocktailSort(arr, size);
    cout << "Result of 3 is:" << endl;
    printArray(arr, size);


    delete [] arr;
    return 0;
}