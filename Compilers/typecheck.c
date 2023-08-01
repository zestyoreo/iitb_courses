#include <stdio.h>
// Basic type int, float, char, enum, void */
// Constructed types: pointers
// Constructed types: arrays
// Constructed type: structs

/* ------------------------------------------------ */

/* 1.   Any numeric  type is  compatible with  any other  numeric type (there is an implicit coercion).   Similarly, an enumerated type is compatible with any other numeric type and two enumerated types are compatible with  each other. This  is because enumerated  types are considered to  be ints.   When numeric  types are  converted to each other through an implicit cast. */

// typedef enum {sun, mon, tue, wed, thu, fri, sat} days;
// typedef enum {true, false} boolean;

// int main ()
// {
//    float i; boolean k; days j;
//   j = i;
//   k = j;
// }

//-------------------------------------------------

// 2. A  void type  is not  compatible with  any other  type. Variables cannot have the  void type. void* is compatible  with any pointer type.

// int main ()
// {
//   void* i;
//   int* j;
//   float* k;

//   i =j;
//   k = i;
// }

/* ------------------------------------------------- */

// 3. In  the case  of pointers  to numeric types,  two types  are the  compatible, if they point to  the same types.  
// This is interesting: numeric  types are  freely  assignable to  each  other, pointer  to numeric types are  not. 
// There is an interesting reason  why this is so.

// typedef int *t;
// typedef int *s;
// typedef float *r;

// int main()
// {
//    t i;
//    s j;
//    r k;
//    int *l;
//    l = i;
//    j = i;
//    j = k;
//    k = j;
// }

// Pointers to  non-numeric types s and  t are compatible, if  s and t are by themselves compatible.

// struct types are compatible if they are declared in the same declaration

// typedef struct
// {
//    int i;
// } s, t;
// typedef struct
// {
//    int i;
// } r;

// int main()
// {
//    t i;
//    s j;
//    r k;
//    struct
//    {
//       int i;
//    } l;
//    j = i;
//    j = k;
//    l = k;
// }

// typedef struct {int i;} s, t;
// typedef struct {int i;} r;

// int main ()
// {
//   t*  i;
//   s*  j;
//   r*  k;
//   struct {int i;} *l;
//   j = i;    //ok, s, t are compatible types, see below.
//   j = k;    //not ok, r and s are not compatible types.
//   l = k;    // not ok.
// }
//----------------------------------------------------------
/*
Basic facts about arrays:

1. An array a declared as int [i][j], is also of the type int (* const) [j]. It cannot be assigned to.

2. If p is of the type int (*) [j], one can assign to p. For example, p = a;

3. If p is of the type int (*) [j], then p[i] is *(p + i), where adding i advances the pointer p by i*sizeof(int)*j bytes.  Thus p[0] = *p. elementsize depends on
sizeof(int) and j.
*/

// void fun(int p[2][2][2])
// {
//   int e[2][2][2] = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
//   p = e;
//   printf("%d\n", p[0][0][1]);
// }

// int main()
// {
//   int e[2][2][2] = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
//   int(*p)[2][2] = e;
//   *p[0][1] = 7;
//   (*p[0])[1] = 7;
//   fun(e);
// }

// ---------------------------------------------------------

// typedef int a[7][8];

// void f(int (*i)[8]) 
// {
// }

// int main ()
// {
//   a j;      // essentially int (*.)[8]

//   f(j);     // therefore ok.

//   int ** p;

//   int  (*i)[5], *k[5]; 
//   i = j;   
//   i = k;
//   p = i; 
//   int l = p[1][2];
// }

/* ----------------------------------------------------- */
/* Whole arrays can be passed to functions. */

// typedef int arr[7][8][9];

// void f(int(*i)[9])
// {
//   i[3][6] = 455;
// }
// int main ()
// {
//   arr j;
//   f(j[1]);     //   passing int(*.)[9]
// }

// Case that specially applies to the lab assignment

// struct a{int x;};

// struct b{int x;};

// int main ()
// {
//   struct a i, j;
//   struct b k;
//   i = j;
//   i = k;    // incompatible types when assigning to type
//             // {struct a} from type {struct b}
// }

/* ----------------------------------------------------- */

// There are  two names  for the  first struct  below.  "struct  a" and "cell". Similarly there are two  names for the second struct "struct b" and "cell1".

// typedef struct a
// {
//   int val;
//   struct a* next;
// } cell;

// typedef struct b
// {
//   int val;
//   struct a* next;
// } cell1;

// main ()
// {
//   cell p; cell1 q;
//   struct a r;
//   p = q;       // Not equal
//   p = r;       // Equal
// }

/* ------------------------------------------------ */

// main()
// {
//    struct
//    {
//       int val
//    } p;
//    struct
//    {
//       int val
//    } q;
//    p = q; // Not equal
// }
/*--------------------------------------------------*/
/* This type fails because each occurrence of 

struct
{
   char c;
   char b;
} 
defines a new type. Therefor s and t are different types.However s and q are of the same type.*/

// typedef struct
// {
//    char c;
//    char b;
// } s, q;

// typedef struct
// {
//    char c;
//    char b;
// } t;

// void f(s a)
// {
// }

// main()
// {
//    t b;
//    f(b);
// }

/*------------------------------------------ */

// typedef struct a
// {
//    int val;
//    struct a *next;
// } cell;

// typedef struct b
// {
//    int val;
//    struct a *next;
// } cell1;

// int main()
// {
//    cell **p;
//    cell1 **q;
//    struct a **r;
//    p = q; // Not equal
//    p = r; // Equal
// }

/* -------------------------------------------- */

/*
Two types t1 and t2 are structurally equivalent if, any one of the following conditions hold:
1. t1 and t2 are eqivalent basic types or the same type name.
2. t1 and t2 are constructed by applying the same constructor on structurally equivalent types.
3. One of t1 or t2 is a name and the other is the type denoted by this name.

Two types t1 and t2 are name equivalent if,
any one of the following conditions hold:

1. t1 and t2 are equivalent basic types or the same type name.
2. t1 and t2 are constructed by applying the same constructor on name equivalent types.
*/