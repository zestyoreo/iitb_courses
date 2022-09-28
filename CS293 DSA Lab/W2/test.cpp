#include<iostream>
using namespace std;
#define ARRAY_SIZE (1<<6)

/*struct Entry {
  char *key;
};

int main(){
struct Entry *A;
A = new Entry[10];
(A+5)->key = new char[32];
cin>>*((A+5)->key);
cout<<*((A+5)->key);
}
*/

int main(){
char *s1;
char *s2;
s1 = new char[32];
s2 = new char[32];
cin>>s1;
cin>>s2;
cout<<s1<<" "<<s2<<endl;
int i=0;
cout<<strlen(s1)<<endl;
*(s1+strlen(s1)) = '\0';
cout<<s1<<endl;
if(strcmp(s1,s2))
{
	cout<<"different";
}
else
	cout<<"same";
}    
