#include <iostream>
using namespace std;
  // This will deduce the binary tree given the pre_order and in_order traversals
  // The first N characters of each string pre_order and in_order are relevant (this will be convenient for a recursive call)
  // You are to return NULL if there is no tree possible with the given pre and in order traversals
enum TraversalType_e { PRE_ORDER, IN_ORDER, POST_ORDER };
int main()
{

    TraversalType_e tt;
    tt = PRE_ORDER;
    cout<<tt;
    if(tt == PRE_ORDER)
    {
        cout<<"pre-order"<<endl;
    }

}