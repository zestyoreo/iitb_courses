int f(int x) {
    int a;
    if (x==0) return 1; 
        a = f(x-1);
        return(x * a); 
    
}