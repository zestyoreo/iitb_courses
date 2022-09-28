#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

/**
 * @brief Builds and stores a vector with elements from the command line args
 * @param argc count of number of command line args
 * @param argv command line args (array elements 1:)
 */
int main(int argc, char *argv[])
{   
    assert (argc>=3);

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    assert (rows>0);
    assert (cols>0);

    int mat2d[rows][cols];

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++) 
            mat2d[i][j] = atoi(argv[i*cols + j + 3]);
    
GDBBREAKPOINT:
    
    return 0;
}
