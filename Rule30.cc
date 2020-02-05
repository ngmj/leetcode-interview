#include <string.h>
#include <iostream>

using namespace std;

// array[0~n-1][0~2n-2]
void makeRule30Array( const size_t n,
                      bool         **array )
{
    // 第一行
    memset( array[0], 0, sizeof(bool) * (2*n-1) );
    array[0][n-1] = 1;
    // 第一列和最后一列
    for ( size_t j = 0; j < n - 1; j++ )
    {
        array[j][0] = 0;
        array[j][2*n-2] = 0;
    }
    array[n-1][0] = 1;
    array[n-1][2*n-2] = 1;
    // 剩余元素，j行i列
    for ( size_t j = 1; j < n; j++ )
    {
        for ( size_t i = 1; i < 2*n - 2; i++ )
        {
            bool a = array[j-1][i-1];
            bool b = array[j-1][i];
            bool c = array[j-1][i+1];
            if ( a && b && c ) // 111
            {
                array[j][i] = 0;
            } else if ( a && b && !c ) // 110
            {
                array[j][i] = 0;
            } else if ( a && !b && c ) // 101
            {
                array[j][i] = 0;
            } else if ( a && !b && !c ) // 100
            {
                array[j][i] = 1;
            } else if ( !a && b && c ) // 011
            {
                array[j][i] = 1;
            } else if ( !a && b && !c ) // 010
            {
                array[j][i] = 1;
            } else if ( !a && !b && c ) // 001
            {
                array[j][i] = 1;
            } else if ( !a && !b && !c ) // 000
            {
                array[j][i] = 0;
            }
        }
    }
    return;
}

// array[0~n-1][0~2n-2]
int minPath( bool         **array,
             const size_t n,
             const int lastJ,
             const int lastI,
             const int currJ,
             const int currI,
             const int targetJ,
             const int targetI )
{
    if ( currJ == targetJ && currI == targetI )
    {
        return 0;
    } 
    bool stillHasPath = false;
    size_t leftPath = 3*n - 1; // 矩形周长
    size_t rightPath = 3*n - 1;
    size_t downPath = 3*n - 1;
    size_t leftDownPath = 3*n - 1;
    size_t rightDownPath = 3*n - 1;
    // 向左走
    int nextJ = currJ;
    int nextI = currI - 1;
    if ( nextI >= 0 && array[nextJ][nextI] && nextI != lastI && nextJ != lastJ )
    {
        leftPath = 1 + minPath( array, n, currJ, currJ, nextJ, nextI, targetJ, targetI );
        stillHasPath = true;
    }
    
    // 向右走
    nextJ = currJ;
    nextI = currI + 1;
    if ( nextI <= 2*n-2 && array[nextJ][nextI] && nextI != lastI && nextJ != lastJ )
    {
        rightPath = 1 + minPath( array, n, currJ, currJ, nextJ, nextI, targetJ, targetI );
        stillHasPath = true;
    }

    // 向下走
    nextJ = currJ + 1;
    nextI = currI;
    if ( nextJ <= n-1 && array[nextJ][nextI] )
    {
        downPath = 1 + minPath( array, n, currJ, currJ, nextJ, nextI, targetJ, targetI );
        stillHasPath = true;
    }

    // 向左下走
    nextJ = currJ + 1;
    nextI = currI - 1;
    if ( nextJ <= n-1 && nextI >=0 && array[nextJ][nextI] )
    {
        leftDownPath = 2 + minPath( array, n, currJ, currJ, nextJ, nextI, targetJ, targetI );
        stillHasPath = true;
    }

    // 向右下走
    nextJ = currJ + 1;
    nextI = currI + 1;
    if ( nextJ <= n-1 && nextI <= 2*n - 2 && array[nextJ][nextI] )
    {
        rightDownPath = 2 + minPath( array, n, currJ, currJ, nextJ, nextI, targetJ, targetI );
        stillHasPath = true;
    }

    return min( min( min( min( leftPath, rightPath ), downPath), leftDownPath), rightDownPath);
}

int main()
{
    const size_t N = 102;
    bool *array[N];
    for ( size_t j = 0; j < N; j++ )
    {
        array[j] = new bool[2*N-1];
    }
    makeRule30Array( N, array );
    for ( size_t j = 0; j < N; j++ )
    {
        for ( size_t i = 0; i < 2*N-1; i++ )
        {
            cout << array[j][i] << "\t";
        }
        cout << endl;
    }
    size_t path = minPath( array, N, -1, -1, 0, N-1, N-1, N-1 );
    cout << "N: " << N << ", path: " << path << endl;
    for ( size_t j = 0; j < N; j++ )
    {
        delete []array[j];
    }
}
