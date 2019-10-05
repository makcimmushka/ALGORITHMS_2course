#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

void printArray(int nuts[], int bolts [], int size) {

    for (int i = 0; i < size; i++) {
        cout << nuts[i] << " " << bolts[i];
        cout << endl;
    }

    cout << endl;
}


int partition(int arr[], int low, int high, int pivot)
{
    int i = low;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }

        else if (arr[j] == pivot) {
            swap(arr[j], arr[high]);
            j--;
        }
    }

    swap(arr[i], arr[high]);

    return i;
}


void matchPairs(int nuts[], int bolts[], int low, int high) {

    if (low < high)
    {
        int pivot = partition(nuts, low, high, bolts[high]);

        partition(bolts, low, high, nuts[pivot]);

        matchPairs(nuts, bolts, low, pivot - 1);
        matchPairs(nuts, bolts, pivot + 1, high);
    }
}





    void shuffle_array(int arr1[], int arr2[], int n) {

        unsigned seed1 = rand() % 10;
        unsigned seed2;

        //unsigned seed2 = 2;

        shuffle(arr1, arr1 + n,
                default_random_engine(seed1));

        while(seed2==seed1) {
            seed2=rand() %10;
            shuffle(arr2, arr2 + n,
                    default_random_engine(seed2));
        }
    }


int main() {
    srand(time(NULL));
    int SIZE, temp;

    cout << "Input size of arrays: " << endl;
    cin >> SIZE;


    int nuts[SIZE];
    int bolts[SIZE];

    for(int i = 0; i < SIZE; i++)
    {
        nuts[i] = i;
        bolts[i] = i;
    }

    shuffle_array(nuts, bolts,  SIZE);

    matchPairs(nuts, bolts, 0, SIZE - 1);

    //printArray(nuts, bolts,  SIZE);


    return 0;
}