#ifndef DYNAMIC_DEQUEUE_H
#define DYNAMIC_DEQUEUE_H

// In this lab, you have to implement a dynamic dequeue of double values using an array
// When the array size is exceeded, you have to grow it (a) linearly, and (b) exponentially (i.e. doubling)
// You will compare the average run-time under both the above scenarios
// Your code for linear vs exponential growth should differ exactly in one function call: nextSizeLinear or nextSizeExponential
// Comparison graph: x-axis is number of elements inserted, y-axis run-time; two plots in same graph: one for linear size growth and one for exponential size growth
// Make sure to document your code properly using suitable comments

// FILES
// DO NOT MODIFY this file, submit as-is
// Write the CPP code for the specified header file below, in DynamicDequeue.cpp
// Write the main function in file main.cpp
// Submit graph as file runtime.png
// If you write any separate code for plotting the runtime, submit that too in plot.py

// While testing, you can change these constant values if you want
#define CONST_GROWTH 100
#define EXPO_GROWTH_FACTOR 2
#define INIT_SIZE 1000

class DynamicDequeue {
private:
  double *A; // the array used for implementing the dynamic dequeue
  unsigned int N; // the current size of array A
  unsigned int f; // index where first element of queue is present (if not empty)
  unsigned int r; // index where next element will be inserted
  unsigned int nextSizeLinear() { return N+CONST_GROWTH; }
  unsigned int nextSizeExponential() { return N*EXPO_GROWTH_FACTOR; }
public:
  DynamicDequeue(); // default constructor
  bool isEmpty(); // is the queue empty?
  bool isFull(); // is the queue full?
  void grow(); // grow the queue to its next size (linear or exponential)
  unsigned int size(); // return the current number of elements in the queue
  void insertFront(double x); // insert given value in front of the queue; grow array size as necessary
  void insertRear(double x); // insert given value in rear of the queue; grow array size as necessary
  bool removeFront(double *x); // remove the value in front of the queue and place it in *x; returns false if queue is empty, true otherwise
  bool removeRear(double *x); // remove the value in rear of the queue and place it in *x; returns false if queue is empty, true otherwise
  bool front(double *x); // place value in front of queue in *x; returns false if queue is empty, true otherwise
  bool rear(double *x); // place value in rear of queue in *x; returns false if queue is empty, true otherwise
};

DynamicDequeue::DynamicDequeue(){// default constructor
  N = INIT_SIZE;
  A = new double[N];
  f=-1;
  r=-1;

}
bool DynamicDequeue::isEmpty(){// is the queue empty?
  if(size() == 0)
    return true;
  else 
    return false;
}
bool DynamicDequeue::isFull(){// is the queue full?
  if(size() == N)
    return true;
  else 
    return false;
}
void DynamicDequeue::grow(){// grow the queue to its next size (linear or exponential) comment only one statement in the below function to get the time values
  N = nextSizeLinear();
  //N = nextSizeExponential();
}
unsigned int DynamicDequeue::size(){// return the current number of elements in the queue
  return r-f;
}
void DynamicDequeue::insertFront(double x){// insert given value in front of the queue; grow array size as necessary
  if(f==0){
    unsigned int n = N;
    grow();
    double *B ;
    B = new double[N];
    
    for(unsigned int i=1;i<=n;i++)
      *(B+N-i) = *(A+n-i);
    *(B+N-n-1)=x;
    r = N-n+r;
    f = N-n-1;
    delete[] A;
    A = B;
  }
  else if(f==-1){
    f=r=0;
    *(A+f) = x;
  }
  else{
    f--;
    *(A+f) = x;
  }
  
}
void DynamicDequeue::insertRear(double x){// insert given value in rear of the queue; grow array size as necessary
  if(r==N){
    grow();
    double *B;
    B = new double[N];
    for(unsigned int i=f;i<r;i++)
      { *(B+i) = *(A+i);}
    *(B+r) = x;
    delete[] A;
    A = B;
    r++;
  }
  else if(r==-1){
    f=r=0;
    *A = x;
  }
  else{
    *(A+r) = x;
    r++;
  }
  
}
bool DynamicDequeue::removeFront(double *x){// remove the value in front of the queue and place it in *x; returns false if queue is empty, true otherwise
  if(isEmpty())
    return false;
  else
  {  *x = *(A+f);
    if(f==r-1)
      f=r=-1;
    else
      f += 1;
    return true;
  }  
}
bool DynamicDequeue::removeRear(double *x){// remove the value in rear of the queue and place it in *x; returns false if queue is empty, true otherwise
  if(isEmpty())
    return false;
  else
  { *x = *(A+r-1);
    if(f==r-1)
      f=r=-1;
    else
      r -= 1;
    return true;
  }
}
bool DynamicDequeue::front(double *x){// place value in front of queue in *x; returns false if queue is empty, true otherwise
  if(isEmpty())
    return false;
  else
    {*x = *(A+f);
    return true;}
}
bool DynamicDequeue::rear(double *x){// place value in rear of queue in *x; returns false if queue is empty, true otherwise
  if(isEmpty())
    return false;
  else
    {*x = *(A+r-1);
    return true;}
}

#endif
