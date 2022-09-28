/*
  Sort.cpp
  Data Structures and Algorithms Lab - CS293
  Author: P Balasubramanian
  Rollno: 200050103
*/  

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <time.h>
#include <fstream>
#include <cmath>
using namespace std::chrono;
using namespace std;

long partition (double a[100000], long start, long end,long long &elem_comparisons,long int &swaps) 
{ 
    double pivot = a[end]; // pivot 
    long i = (start - 1);
  
    for (long j = start; j <= end-1 ; j++) 
    { 
        // If current element is smaller than the pivot 
        elem_comparisons++;
        if (a[j] < pivot) 
        { 
            i++;
            double temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            swaps++; 
        } 
    } 
    double temp = a[i+1];
    a[i+1] = a[end];
    a[end] = temp;
    swaps++;
    return (i + 1); 
}
long partition1 (double a[100000], long start, long end,long long &elem_comparisons,long int &swaps) 
{ 
    double temp = a[start];
    a[start] = a[end];
    a[end] = temp;
    swaps++;
    return partition(a, start, end, elem_comparisons, swaps);
}  

long partition2 (double a[100000], long start, long end,long long &elem_comparisons,long int &swaps) 
{ 
    long x ;
    x = start + rand()%(end-start+1);
    double temp = a[x];
    a[x] = a[end];
    a[end] = temp;
    swaps++;
    return partition(a, start, end, elem_comparisons, swaps);
} 

// Quick Sort
void QSP1(double a[100000], long start, long end, long long &elem_comparisons,long int &swaps)
{
  /* a is the array to be sorted start is the starting index and end is the ending index. */

  if (start < end) 
    { 
        long part = partition1(a, start, end,elem_comparisons,swaps); 
        QSP1(a, start, part - 1,elem_comparisons,swaps); 
        QSP1(a, part + 1, end,elem_comparisons,swaps); 
    } 
}

void QSPR(double a[100000], long start, long end, long long &elem_comparisons,long int &swaps)
{
  /* a is the array to be sorted start is the starting index and end is the ending index. */

  if (start < end) 
    { 
        long part = partition2(a, start, end,elem_comparisons,swaps); 
        QSPR(a, start, part - 1,elem_comparisons,swaps); 
        QSPR(a, part + 1, end,elem_comparisons,swaps); 
    } 
}

// Bubble Sort
void BS(double a[100000], long n,long long &elem_comparisons, long &swaps)
{
  /* a is the array to be sorted 
     n is the number of elements in a */
  for (long i = 0; i < n-1; i++)     
  { 
    for (long j = 0; j < n-i-1; j++) 
      {
        elem_comparisons++;
        if (a[j] > a[j+1])
        { 
          double temp = a[j];
          a[j] = a[j+1];
          a[j+1] = a[j];
          swaps++;
        }   
      }  
  }

}

// Generating and returning a random array
void ran_array(double a[100000],double N)
{
  /* N is the number of elements in the array to be generated and returned */

  for(long i=0;i<N;i++)
      a[i]=rand()%100000;
}

// Generating and returning an almost sorted array
void almost_sorted_array(double a[100000],double n,bool rev =false)
{
  /* N is the number of elements in the array to be generated and returned */
  long long N = n;
  if(rev)
  {
    for(long i=0;i<N;i++)
      a[N-1-i]=i;
  }
  else
  {
    for(long i=0;i<N;i++)
      a[i]=i;
  }

  for(long i=0;i<(N*0.105);i++)
  {
    long x,y;
    x = rand()%N; 
    y = rand()%N;
    double temp = a[x];
    a[x] = a[y];
    a[y] = temp;  
  }
}

void copy(double a[100000],double b[100000],double N)
{
  /* N is the number of elements in the array */

  for(long i=0;i<N;i++)
      b[i]=a[i];
}

#define NUM_ITER 15000

int main(){

  ofstream f1,f2,f3;
  f1.open("QSP1.csv");
  f2.open("QSPR.csv");
  f3.open("BS.csv");

  srand(time(0));
  double ran_arr[100000],ran_arr1[100000],ran_arr2[100000];
  double al_sor_arr[100000],al_sor_arr2[100000],al_sor_arr1[100000];
  double al_sor_rev_arr[100000],al_sor_rev_arr1[100000],al_sor_rev_arr2[100000];

  auto start = high_resolution_clock::now();
  for(double i=100;i<NUM_ITER;i+=100)
  {
    long long elem_comparisons = 0;
    long int swaps = 0;
    // Getting the 3 diff arrays
    ran_array(ran_arr,i);
    copy(ran_arr, ran_arr1,i);
    copy(ran_arr, ran_arr2,i);
    almost_sorted_array(al_sor_arr,i);
    copy(al_sor_arr, al_sor_arr1,i);
    copy(al_sor_arr, al_sor_arr2,i);
    almost_sorted_array(al_sor_rev_arr,i,true);
    copy(al_sor_rev_arr, al_sor_rev_arr1,i);
    copy(al_sor_rev_arr, al_sor_rev_arr2,i);

    // QSP1 sorting
    // 1)random array
    auto start = high_resolution_clock::now();
    QSP1(ran_arr, 0, i-1,elem_comparisons,swaps);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    double tim = double(duration.count());
    f1<<i<<","<<tim<<","<<elem_comparisons<<","<<swaps<<",";
    elem_comparisons = 0;
    swaps = 0;
    // 2)almost sorted array
    start = high_resolution_clock::now();
    QSP1(al_sor_arr, 0, i-1,elem_comparisons,swaps);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    tim = double(duration.count());
    f1<<tim<<","<<elem_comparisons<<","<<swaps<<",";
    elem_comparisons = 0;
    swaps = 0;
    // 3)almost sorted array reverse
    start = high_resolution_clock::now();
    QSP1(al_sor_rev_arr, 0, i-1,elem_comparisons,swaps);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    tim = double(duration.count());
    f1<<tim<<","<<elem_comparisons<<","<<swaps<<endl;
    elem_comparisons = 0;
    swaps = 0;

    // QSPR sorting
    // 1)random array
    start = high_resolution_clock::now();
    QSPR(ran_arr1, 0, i-1,elem_comparisons,swaps);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    tim = double(duration.count());
    f2<<i<<","<<tim<<","<<elem_comparisons<<","<<swaps<<",";
    elem_comparisons = 0;
    swaps = 0;
    // 2)almost sorted array
    start = high_resolution_clock::now();
    QSPR(al_sor_arr1, 0, i-1,elem_comparisons,swaps);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    tim = double(duration.count());
    f2<<tim<<","<<elem_comparisons<<","<<swaps<<",";
    elem_comparisons = 0;
    swaps = 0;
    // 3)almost sorted array reverse
    start = high_resolution_clock::now();
    QSPR(al_sor_rev_arr1, 0, i-1,elem_comparisons,swaps);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    tim = double(duration.count());
    f2<<tim<<","<<elem_comparisons<<","<<swaps<<endl;
    elem_comparisons = 0;
    swaps = 0;

    // BS sorting
    long n = i;
    // 1)random array
    start = high_resolution_clock::now();
    BS(ran_arr2, n, elem_comparisons,swaps);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    tim = double(duration.count());
    f3<<i<<","<<tim<<","<<elem_comparisons<<","<<swaps<<",";
    elem_comparisons = 0;
    swaps = 0;
    // 2)almost sorted array
    start = high_resolution_clock::now();
    BS(al_sor_arr2, n, elem_comparisons,swaps);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    tim = double(duration.count());
    f3<<tim<<","<<elem_comparisons<<","<<swaps<<",";
    elem_comparisons = 0;
    swaps = 0;
    // 3)almost sorted array reverse
    start = high_resolution_clock::now();
    BS(al_sor_rev_arr2, n, elem_comparisons,swaps);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    tim = double(duration.count());
    f3<<tim<<","<<elem_comparisons<<","<<swaps<<endl;
    elem_comparisons = 0;
    swaps = 0;

  }
  f1.close();
  f2.close();
  f3.close();
}
