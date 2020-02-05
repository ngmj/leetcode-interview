#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

void split( char *pSrc, const char c, vector<char*> &rstVec )
{
    if ( NULL == pSrc )
    {
        return;
    }

    char *p = pSrc;
    while ( *p != '\0' )
    {
        while ( c == *p && '\0' != *p )
        {
            p++;
        }

        if ( '\0' == *p )
        {
            break;
        } else // c != *p
        {
            rstVec.push_back( p );
            p++;
        }

        while ( c != *p && '\0' != *p )
        {
            p++;
        }

        if ( '\0' == *p )
        {
            break;
        } else // c == *p
        {
            *p = '\0';
            p++;
        }
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
