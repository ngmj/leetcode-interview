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

    char *tmp = pSrc;
    char* seq = tmp;
    while ( *tmp != '\0' )
    {
        if ( *tmp == c )
        {
            *tmp = '\0';
            if ( seq != tmp )
            {
                rstVec.push_back( seq );
            }
            seq = tmp + 1;
        }
        tmp++;
    }

    if ( seq != tmp )
    {
        rstVec.push_back( seq );
    }
    return;
}

int main()
{
    string st = "h W";
    vector<char*> vec;
    split( (char*)st.c_str(), ' ', vec );
    for ( size_t i = 0; i < vec.size(); i++ )
    {
        fprintf( stdout, "%s\n", vec[i] );
    }
}
