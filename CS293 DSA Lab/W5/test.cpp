#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
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
void ran_array(double a[100000],double N)
{
  /* N is the number of elements in the array to be generated and returned */

  for(long i=0;i<N;i++)
      a[i]=rand()%100000;
}
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
int main()
{
  double ran_arr[100000],ran_arr1[100000],ran_arr2[100000];
  long long elem_comparisons = 0;
  long int swaps = 0;
  double i =100;
  long n = i;
    // Getting the 3 diff arrays
  ran_array(ran_arr,i);
  ran_array(ran_arr1,i);
  ran_array(ran_arr2,i);
  QSP1(ran_arr, 0, i-1,elem_comparisons,swaps);
  for(int j =0;j<i;j++)
  {
    cout<<ran_arr[j]<<" ";
  }
  cout<<endl;
  QSPR(ran_arr1, 0, i-1,elem_comparisons,swaps);
  for(int j =0;j<i;j++)
  {
    cout<<ran_arr1[j]<<" ";
  }
  BS(ran_arr2, n, elem_comparisons,swaps);
  for(int j =0;j<i;j++)
  {
    cout<<ran_arr2[j]<<" ";
  }
}