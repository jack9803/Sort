#include <cstdio>
#include <cstdlib>
#include <math.h>

#define MAX 10
int data[MAX];

void dataView();
void selectionSort(int size);
void insertionSort(int size);
void bubbleSort(int size);
void quickSort(int left, int right, int size);
void merge(int begin, int leftSize, int rightSize);
void mergeSort(int begin, int size);
void heapify(int root, int size);
void heapSort(int size);
void swap();


int main() {
    //Initialization
    int i;
    for(i = 0; i < MAX; i++){
        data[i] = rand() % 100 + 1;
        printf(" %d", data[i]);
    }
    printf("\n");

    //Sort
    //selectionSort(MAX);
    //insertionSort(MAX);
    //bubbleSort(MAX);
    quickSort(0, (MAX-1), MAX);
    //mergeSort(0, MAX);
    //heapSort(MAX);

    //Result
    dataView();

    return 0;
}

void dataView(){
    int i;
    for(i = 0; i < MAX; i++){
        printf(" %d", data[i]);
    }
    printf("\n");
}

void swap(int &a, int &b){
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void selectionSort(int size){
    int min, i, j;
    for(i = 0; i < size; i++){
        min = i;
        for(j = i + 1; j < size; j++){
            if(data[j] < data[min]){
                min = j;
            }
        }
        swap(data[i], data[min]);
    }
}

void insertionSort(int size){
    int i, j;
    int temp;
    for(i = 1; i < size; i++){
        temp = data[i];
        for(j = i; j > 0 && temp < data[j-1]; j--){
                data[j] = data[j - 1];
        }
        data[j] = temp;
    }
}

void bubbleSort(int size){
    int i, j, k;
    bool flag = true;
    for(i = 0; i < size && flag; i++){
        flag = false;
        for(j = 0; j < size - i - 1; j++){
            if(data[j] > data[j + 1]){
                swap(data[j], data[j+1]);
                flag = true;
            }
        }
    }
}

/*select the first element as piviot*/
void quickSort(int left, int right, int size){
    int i, j;
    if(left < right){
        i = left;
        j = right + 1;
        while(true){
            while((i + 1 < size) && (data[++i] < data[left]));
            while((j - 1 > -1) && (data[--j] > data[left]));
            if(i >= j)
                break;
            swap(data[i], data[j]);
        }
        swap(data[left], data[j]); // move the piviot to the center
        quickSort(left, j-1, MAX);
        quickSort(j+1, right, MAX);
    }
}

void merge(int begin, int leftSize, int rightSize){
    int temp[leftSize + rightSize];
    int ptrL = 0, ptrR = 0;
    while(ptrL < leftSize || ptrR < rightSize){
        if((ptrL < leftSize) && ((data[begin + ptrL] <= data[begin + leftSize + ptrR]) || (ptrR == rightSize))){
            temp[ptrL + ptrR] = data[begin + ptrL];
            ptrL++;
        }
        else if((ptrR < rightSize) && ((data[begin + leftSize + ptrR] < data[begin + ptrL]) || (ptrL == leftSize))){
            temp[ptrL + ptrR] = data[begin + leftSize + ptrR];
            ptrR++;
        }
    }


    for(int i = 0; i < leftSize + rightSize; i++){
        data[begin + i] = temp[i];
    }
}

void mergeSort(int begin, int size){
    if(size == 1)
        return;
    int leftSize = size / 2;
    int rightSize = size - leftSize;
    mergeSort(begin, leftSize);
    mergeSort(begin + leftSize, rightSize);
    merge(begin, leftSize, rightSize);
}

void heapify(int root, int size){
    int leftChild = root*2 + 1;
    int rightChild = root*2 + 2;
    int maxNode;

    maxNode = root;
    if(leftChild < size && (data[leftChild] > data[root]))
        maxNode = leftChild;
    if(rightChild < size && (data[rightChild] > data[maxNode]))
        maxNode = rightChild;

    if(maxNode != root){
        swap(data[root], data[maxNode]);
        heapify(maxNode, size);
    }

}

void heapSort(int size){
    // Step 1 : transform to MAX heap
    // Heapify all node that have child
    // i < (size - 1)/2 : start node i = 
    int i; 
    for(i = ceil((size - 3)/2); i >= 0; i--){
        heapify(i, size);
    }

    dataView();

    //Step 2 : pop all element
    for(i = size - 1; i > 0; i--){
        swap(data[0], data[i]);
        heapify(0, i); // because pop one element : size - 1
    }

}