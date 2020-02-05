#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

void split( char *pSrc, const char c, vector<char*> &rstVec )
{
    if ( NULL == pSrc )
    {
        return;
    }

    char *p = pSrc;
    int len = strlen( p );

    for ( size_t i = 0; i < len; i++ )
    {
        if ( c == *p )
        {
            *p = '\0';
        } else if ( 0 == i )
        {
            rstVec.push_back( p );
        } else
        {
            if ( '\0' == *( p - 1 ) )
            {
                rstVec.push_back( p );
            }
        }
        p++;
    }
    return;
}

int main()
{
    string st = "  Hello    World";
    vector<char*> vec;
    split( (char*)st.c_str(), 'l', vec );
    for ( size_t i = 0; i < vec.size(); i++ )
    {
        fprintf( stdout, "%s\n", vec[i] );
    }
}
