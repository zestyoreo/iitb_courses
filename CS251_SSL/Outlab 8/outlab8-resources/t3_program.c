int bar(int i, int j)
{
    int e = i*i-j;
    return e;
}

int foo(int i, int j, int k)
{
    int x = i+3*j;
    int y = bar(j, k);
    return y+x;
}

int main(int argc, char *argv[])
{
    foo(1,2,3);
    return 0;
}
