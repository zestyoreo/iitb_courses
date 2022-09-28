/*
	DynamicDequeue.cpp
	Data Structures and Algorithms Lab - CS293
	Author: P Balasubramanian
	Rollno: 200050103
*/	

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