#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class D_Heap {
private:
    int max_dgr;
    vector <int> heap;

    void emersion(int index) { //всплытие :: log d (N)
        int prev = (index - 1) / this->max_dgr;
        while (index > 0 && this->heap[index] > this->heap[prev]) {
            swap(this->heap[prev], this->heap[index]);
            index = prev;
            prev = (index - 1) / this->max_dgr;
        }
    }


    int max_child(int index) { //поиск максимального значенния среди детей узла
        int bigger = index * this->max_dgr + 1;

        if (bigger >= (this->heap).size()) {
            return 0;
        }

        int max_key = this->heap[bigger];
        int last = (index + 1) * this->max_dgr;

        if (last >= (this->heap).size()) {
            last = (this->heap).size() - 1;
        }

        for (int i = bigger + 1; i < last + 1; i++) {
            if (this->heap[i] > max_key) {
                max_key = this->heap[i];
                bigger = i;
            }
        }

        return bigger;
    }


    void immersion(int index) { //погружение :: d * log d (N)
        int bigger = max_child(index);
        while (bigger != 0 && this->heap[index] < this->heap[bigger]) {
            swap(this->heap[bigger], this->heap[index]);
            index = bigger;
            bigger = max_child((index));
        }
    }


    void heapify() { //упорядочивание кучи
        for (int i = (this->heap).size(); i > -1; i--) {
            immersion(i);
        }
    }



public:
    D_Heap(int max_dgr) {
        this->max_dgr = max_dgr;
    }

    D_Heap(int max_dgr, vector <int> &heap) {
        this->max_dgr = max_dgr;
        this->heap = heap;
}


    int extract_max() {
        int max = this->heap[0];
        this->heap[0] = this->heap[(this->heap).size() - 1];
        (this->heap).pop_back();
        emersion(0);
        heapify();
        return max;
    }


    void insert(int key) {
        (this->heap).push_back(key);
        emersion((this->heap).size() - 1);
        //heapify();
    }


    void increase_key(int index, int value) {
        this->heap[index] += value;
        emersion(index);
        //heapify();
    }


    void printHeap() {
        heapify();

        for (int i = 0; i < (this->heap).size(); i++) {
            cout << heap[i] << " ";
        }

        cout << endl;
    }

};


int main() {
    srand(time(NULL));
    int max_dgr;
    int N;


    cout << "Input size of heap:" << endl;
    cin>>N;

    cout << "Input max deg of heap:" << endl;
    cin>>max_dgr;

    vector <int> vect(N);


    for (int i = 0; i < N; i++) {
        vect[i] = rand() % 15 + 1;
    }

    D_Heap heap(max_dgr, vect);

    //heap.printHeap();

    cout << endl << endl;

    for (int i = 0; i < N; i++) {
        cout << heap.extract_max() << endl;
    }


    /*heap.increase_key(1, 11);
    heap.printHeap();


    heap.insert(200);
    heap.printHeap();

    cout << heap.extract_max()<< " ";
    cout << endl;
    heap.printHeap();*/



    return 0;
}