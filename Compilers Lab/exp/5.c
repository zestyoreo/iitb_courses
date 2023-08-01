void p(int &x) {
    int a;
    a = x + 1; 
}
int main() {
    int g;
    p(g);
    return 0;
}