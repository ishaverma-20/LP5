#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>
using namespace std;

vector<int> createArr(int size)
{
    vector<int> array;
    for(int i = 0; i<size; i++)
        array.push_back(rand() % 1000);
    return array;
}

void display(vector<int> array)
{
    for(auto i:array)
        cout<<i<<", ";
    cout<<endl;
}

vector<int> bubbleSort(vector<int> array)
{
    int n = array.size();
    for(int i=0; i<n-2; i++)
        for(int j = i; j<n-1; j++)
            if(array[j] > array[j+1])
                swap(array[j], array[j+1]);
    return array;
}

vector<int> parBubbleSort(vector<int> array)
{
    int n = array.size();
    for(int i=0; i<n-2; i++)
    #pragma omp parallel for
        for(int j = i; j<n-1; j++)
            if(array[j] > array[j+1])
            #pragma omp critical
            {
                swap(array[j], array[j+1]);
            }
    return array;
}

void merge(vector<int> &array, int start, int end, int mid)
{
    vector<int> L(array.begin() + start, array.begin() + mid + 1);
    vector<int> R(array.begin() + mid + 1, array.begin() + end + 1);

    int i = 0, j = 0, k = start;

    while(i<L.size() && j<R.size())
    {
        if(L[i] <= R[j])
            array[k++] = L[i++];
        else
            array[k++] = R[j++];
    }

    while(i<L.size())
        array[k++] = L[i++];

    while(j<R.size())
        array[k++] = R[j++];
}

void mergeSort(vector<int> &array, int start, int end)
{
    if (start < end) 
    {
        int mid = (start + end) / 2;
        mergeSort(array, start, mid);
        mergeSort(array, mid + 1, end);
        merge(array, start, end, mid);
    }
}

void parMergeSort(vector<int> &array, int start, int end)
{
    if(start<end)
    {
        int mid = (start + end)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            parMergeSort(array, start, mid);
            #pragma omp section
            parMergeSort(array, mid+1, end);
        }
        merge(array, start, end, mid);
    }
}

int main()
{
    int size, choice = -1;
    cout<<"Enter size of array: ";
    cin>>size;
    vector<int> sortedArray, array = createArr(size);
    while(choice != 0)
    {
        cout<<"1. Display original array"<<endl;
        cout<<"2. Bubble Sort"<<endl;
        cout<<"3. Parallel Bubble Sort"<<endl;
        cout<<"4. Merge Sort"<<endl;
        cout<<"5. Parallel Merge Sort"<<endl;
        cout<<"6. Display Sorted array"<<endl;
        cout<<"Press 0 to exit"<<endl;
        cout<<"Enter choice: ";
        cin>> choice;
        int startTime = omp_get_wtime();
        if(choice == 1)
            display(array);
        else if(choice == 2)
            sortedArray = bubbleSort(array);
        else if(choice == 3)
            sortedArray = parBubbleSort(array);
        else if(choice == 4)
        {
            sortedArray = array;
            mergeSort(sortedArray, 0, sortedArray.size() - 1);
        }
        else if(choice == 5)
        {
            sortedArray = array;
            parMergeSort(sortedArray, 0, sortedArray.size() - 1);
        }
        else if(choice == 6)
            display(sortedArray);
        else if(choice == 0)
            return 0;
        else
            cout<<"Invalid choice"<<endl;
        int endTime = omp_get_wtime();
        cout<<"Time: "<<(endTime - startTime) * 1000<<" ms"<<endl;

    }
    return 0;
}