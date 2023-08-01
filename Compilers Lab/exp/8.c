typedef struct {
    int data; struct rec* next;
} rec; 
void p () {
    rec x; rec *y;
    x.data = 5; x.next = y; 
}