#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void seqMax(vector<int> array)
{
    int maximum = array[0];
    double startTime = omp_get_wtime();
    for(int i=0; i<array.size(); i++)
        maximum = max(maximum, array[i]);
        double endTime = omp_get_wtime();

    cout<<"Maximum: "<<maximum<<endl;
    cout<<"Time: "<<endTime-startTime<<endl;
}

void seqMin(vector<int> array)
{
    int minimum = array[0];
    double startTime = omp_get_wtime();
    for(int i=0; i<array.size(); i++)
        minimum = min(minimum, array[i]);
    double endTime = omp_get_wtime();

    cout<<"Minimum: "<<minimum<<endl;
    cout<<"Time: "<<endTime-startTime<<endl;
}

void seqSum(vector<int> array)
{
    long long sum = 0;
    double startTime = omp_get_wtime();
    for(int i=0; i<array.size(); i++)
        sum+=array[i];
    double endTime = omp_get_wtime();

    cout<<"Sum: "<<sum<<endl;
    cout<<"Time: "<<endTime-startTime<<endl;
}

void seqAvg(vector<int> array)
{
    long long sum = 0;
    double startTime = omp_get_wtime();
    for(int i=0; i<array.size(); i++)
        sum+=array[i];
    double endTime = omp_get_wtime();
    double avg = sum/array.size();

    cout<<"Average: "<<avg<<endl;
    cout<<"Time: "<<endTime-startTime<<endl;
}


void parMax(vector<int> array)
{
    int maximum = array[0];
    double startTime = omp_get_wtime();
    #pragma omp parallel for reduction(max : maximum)
    for(int i=0; i<array.size(); i++)
        maximum = max(maximum, array[i]);
        double endTime = omp_get_wtime();

    cout<<"Maximum: "<<maximum<<endl;
    cout<<"Time: "<<endTime-startTime<<endl;
}

void parMin(vector<int> array)
{
    int minimum = array[0];
    double startTime = omp_get_wtime();
    #pragma omp parallel for reduction(min : minimum) 
    for(int i=0; i<array.size(); i++)
        minimum = min(minimum, array[i]);
    double endTime = omp_get_wtime();

    cout<<"Minimum: "<<minimum<<endl;
    cout<<"Time: "<<endTime-startTime<<endl;
}

void parSum(vector<int> array)
{
    long long sum = 0;
    double startTime = omp_get_wtime();
    #pragma omp parallel for reduction(+ : sum)
    for(int i=0; i<array.size(); i++)
        sum+=array[i];
    double endTime = omp_get_wtime();

    cout<<"Sum: "<<sum<<endl;
    cout<<"Time: "<<endTime-startTime<<endl;
}

void parAvg(vector<int> array)
{
    long long sum = 0;
    double startTime = omp_get_wtime();
    #pragma omp parallel for reduction(+ : sum)
    for(int i=0; i<array.size(); i++)
        sum+=array[i];
    double endTime = omp_get_wtime();
    double avg = sum/array.size();

    cout<<"Average: "<<avg<<endl;
    cout<<"Time: "<<endTime-startTime<<endl;
}

int main()
{
    long long N = 90000000;
    vector<int> array = {1, 1000};
    for(int i=0; i<N; i++)
        array.push_back((rand() % 1000));
    
    cout<<"SEQUENTIAL"<<endl;
    seqMin(array);cout<<endl;
    seqMax(array);cout<<endl;
    seqSum(array);cout<<endl;
    seqAvg(array);cout<<endl;

    cout<<endl;
    cout<<endl;

    cout<<"PARALLEL"<<endl;
    parMin(array);cout<<endl;
    parMax(array);cout<<endl;
    parSum(array);cout<<endl;
    parAvg(array);cout<<endl;
    
    return 0;
}