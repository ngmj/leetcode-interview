#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

/*
 * (1234567^12345678901234567890)%999999997
 * */

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
LL MAX_LL = std::numeric_limits<LL>::max();;
int MAX_INT = std::numeric_limits<int>::max();;

int main()
{
    ULL times = 12345678901234567890ul;
    ULL base = 1234567;
    ULL mode = 999999997;
    // 2^63 = 9223372036854775808
    // 2^61 = 2305843009213693952
    // 2^59 = 576460752303423488
    // 2^57 = 144115188075855872

    /*
     * base^12345678901234567890ul = base^(2^63) * base^(12345678901234567890ul-2^63)
     * = base^(2^63) * base^(3122306864379792082)
     * = base^(2^63) * base^(2^61) * base^(3122306864379792082-2^61)
     * = base^(2^63) * base^(2^61) * base^(816463855166098130)
     * = base^(2^63) * base^(2^61) * base^(2^59) * base^(816463855166098130-2^59)
     * = base^(2^63) * base^(2^61) * base^(2^59) * base^(240003102862674642)
     * = base^(2^63) * base^(2^61) * base^(2^59) * base^(2^57) * base^(240003102862674642-2^57)
     * = base^(2^63) * base^(2^61) * base^(2^59) * base^(2^57) * base^(240003102862674642-2^57)
     * ....
     * */
    vector<pair<int, ULL> > power2 = { {1, 2}, {2, 4}, {3, 8}, {4, 16}, {5, 32}, {6, 64}, {7, 128}, {8, 256}, {9, 512}, {10, 1024}, {11, 2048}, {12, 4096}, {13, 8192}, {14, 16384}, {15, 32768}, {16, 65536}, {17, 131072}, {18, 262144}, {19, 524288}, {20, 1048576}, {21, 2097152}, {22, 4194304}, {23, 8388608}, {24, 16777216}, {25, 33554432}, {26, 67108864}, {27, 134217728}, {28, 268435456}, {29, 536870912}, {30, 1073741824}, {31, 2147483648}, {32, 4294967296}, {33, 8589934592}, {34, 17179869184}, {35, 34359738368}, {36, 68719476736}, {37, 137438953472}, {38, 274877906944}, {39, 549755813888}, {40, 1099511627776}, {41, 2199023255552}, {42, 4398046511104}, {43, 8796093022208}, {44, 17592186044416}, {45, 35184372088832}, {46, 70368744177664}, {47, 140737488355328}, {48, 281474976710656}, {49, 562949953421312}, {50, 1125899906842624}, {51, 2251799813685248}, {52, 4503599627370496}, {53, 9007199254740992}, {54, 18014398509481984}, {55, 36028797018963968}, {56, 72057594037927936}, {57, 144115188075855872}, {58, 288230376151711744}, {59, 576460752303423488}, {60, 1152921504606846976}, {61, 2305843009213693952}, {62, 4611686018427387904}, {63, 9223372036854775808} };
    ULL maxNeb = 0;
    vector<int> powTimes;
    for ( int i = power2.size() - 1; i >= 0; i-- )
    {
        maxNeb += power2[i].second;
        if ( maxNeb > times )
        {
            maxNeb -= power2[i].second;
            continue;
        }
        cout << i+1 << ", maxNeb " << maxNeb << endl;
        powTimes.push_back( i+1 );
    }
    ULL reservedTimes = times - maxNeb;

    /*
     * 最终计算base^12345678901234567890ul = base^(2^n1)*base^(2^n2)*...*base^reservedTimes
     * */

    // 计算 base^(2^n) % mode结果
    vector<ULL> eachPowerVec;
    for ( int i = 0; i < powTimes.size(); i++ )
    {
        ULL tmp = base;
        for ( int j = 0; j < powTimes[i]; j++ )
        {
            tmp = tmp*tmp % mode;
        }
        eachPowerVec.push_back( tmp );
    }

    // 累计计算base^(2^n1)*base^(2^n2)*...
    ULL basePower = 1;
    for ( int i = 0; i < eachPowerVec.size(); i++ )
    {
        basePower = basePower * eachPowerVec[i] % mode; 
    }  
    // 计算base^reservedTimes
    ULL reserved = 1;  
    for ( int i = 0; i < reservedTimes; i++ )
    {
        reserved = reserved * base % mode;
    }
    cout << ((basePower*reserved) % mode ) << endl;
}
