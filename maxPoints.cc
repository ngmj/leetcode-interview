#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

typedef vector<int> Point;

class Solution {
    struct Line
    {
        int X;
        int Y;
        int x;
        int y;
        int num;
    };
public:
    int maxPoints(vector<vector<int>>& points) 
    {
        vector<pair<Point, int> > dupPoints; // 每个点后面重复的点个数
        unordered_map<string, int> duoPIdx;
        dupPoints.reserve( points.size() );
        duoPIdx.reserve( points.size() );
        size_t idx = 0;
        for ( auto &p: points )
        {
            string tmp = to_string( p[0] ) + "^" + to_string( p[1] );
            auto iter = duoPIdx.find( tmp );
            if ( duoPIdx.end() != iter )
            {
                dupPoints[iter->second].second++;
            } else
            {
                dupPoints.push_back( make_pair( p, 1 ) );
                duoPIdx.insert( make_pair( std::move( tmp ), idx++ ) );
            }
        }

        if ( dupPoints.size() < 1 )
        {
            return 0;
        } else if ( dupPoints.size() < 2 )
        {
            return dupPoints[0].second;
        }

        vector<Line> lines;
        lines.reserve( dupPoints.size()*dupPoints.size() );
        lines.push_back( OneLine( dupPoints[0], dupPoints[1] ) );
        for ( size_t i = 2; i < dupPoints.size(); i++ )
        {
            bool bMatch = false;
            for ( size_t j = 0; j < lines.size(); j++ )
            {
                if ( IsMatch( dupPoints[i].first, lines[j] ) )
                {
                    lines[j].num += dupPoints[i].second;
                    bMatch = true;
                    break;
                }
            }

            if ( false == bMatch )
            {
                for ( size_t k = 0; k < i; k++ )
                {
                    lines.push_back( OneLine( dupPoints[k], dupPoints[i] ) );
                }
            }
        }
        int maxNum = 0;
        for ( auto &l: lines )
        {
            if ( l.num > maxNum )
            {
                maxNum = l.num;
            }
        }
        return maxNum;
    }

    Line OneLine( const pair<Point, int> &p1,
                  const pair<Point, int> &p2 ) const
    {
        Line l;
        l.X = p1.first[0] - p2.first[0];
        l.Y = p1.first[1] - p2.first[1];
        int tmp = gcd( l.X, l.Y );
        l.X = tmp == 0 ? l.X : l.X / tmp;
        l.Y = tmp == 0 ? l.Y : l.Y / tmp;
        l.x = p1.first[0];
        l.y = p1.first[1];
        l.num = p1.second + p2.second;
        return l;
    }
    
    bool IsMatch( const Point &p,
                  const Line  &l ) const
    {
        if ( long(l.x - p[0])*l.Y == long(l.y - p[1])*l.X )
        {
            return true;
        }
        return false;
    }

    int gcd( int X, int Y ) const
    {
        while ( Y )
        {
            int tmp = X % Y;
            X = Y;
            Y = tmp;
        }
        return X;
    }
};

string PointsToString( vector<vector<int> > &points )
{
    ostringstream str;
    for ( auto &p: points ) 
    {
        str << "(" << p[0] << "," << p[1] << ") ";
    }
    return str.str();
}

int main()
{
    vector<vector<int> > points;
    Solution sol;

    points.clear();
    points.push_back( {40,-23});
    points.push_back( {9,138});
    points.push_back( {429,115});
    points.push_back( {50,-17});
    points.push_back( {-3,80});
    points.push_back( {-10,33});
    points.push_back( {5,-21});
    points.push_back( {-3,80});
    points.push_back( {-6,-65});
    points.push_back( {-18,26});
    points.push_back( {-6,-65});
    points.push_back( {5,72});
    points.push_back( {0,77});
    points.push_back( {-9,86});
    points.push_back( {10,-2});
    points.push_back( {-8,85});
    points.push_back( {21,130});
    points.push_back( {18,-6});
    points.push_back( {-18,26});
    points.push_back( {-1,-15});
    points.push_back( {10,-2});
    points.push_back( {8,69});
    points.push_back( {-4,63});
    points.push_back( {0,3});
    points.push_back( {-4,40});
    points.push_back( {-7,84});
    points.push_back( {-8,7});
    points.push_back( {30,154});
    points.push_back( {16,-5});
    points.push_back( {6,90});
    points.push_back( {18,-6});
    points.push_back( {5,77});
    points.push_back( {-4,77});
    points.push_back( {7,-13});
    points.push_back( {-1,-45});
    points.push_back( {16,-5});
    points.push_back( {-9,86});
    points.push_back( {-16,11});
    points.push_back( {-7,84});
    points.push_back( {1,76});
    points.push_back( {3,77});
    points.push_back( {10,67});
    points.push_back( {1,-37});
    points.push_back( {-10,-81});
    points.push_back( {4,-11});
    points.push_back( {-20,13});
    points.push_back( {-10,77});
    points.push_back( {6,-17});
    points.push_back( {-27,2});
    points.push_back( {-10,-81});
    points.push_back( {10,-1});
    points.push_back( {-9,1});
    points.push_back( {-8,43});
    points.push_back( {2,2});
    points.push_back( {2,-21});
    points.push_back( {3,82});
    points.push_back( {8,-1});
    points.push_back( {10,-1});
    points.push_back( {-9,1});
    points.push_back( {-12,42});
    points.push_back( {16,-5});
    points.push_back( {-5,-61});
    points.push_back( {20,-7});
    points.push_back( {9,-35});
    points.push_back( {10,6});
    points.push_back( {12,106});
    points.push_back( {5,-21});
    points.push_back( {-5,82});
    points.push_back( {6,71});
    points.push_back( {-15,34});
    points.push_back( {-10,87});
    points.push_back( {-14,-12});
    points.push_back( {12,106});
    points.push_back( {-5,82});
    points.push_back( {-46,-45});
    points.push_back( {-4,63});
    points.push_back( {16,-5});
    points.push_back( {4,1});
    points.push_back( {-3,-53});
    points.push_back( {0,-17});
    points.push_back( {9,98});
    points.push_back( {-18,26});
    points.push_back( {-9,86});
    points.push_back( {2,77});
    points.push_back( {-2,-49});
    points.push_back( {1,76});
    points.push_back( {-3,-38});
    points.push_back( {-8,7});
    points.push_back( {-17,-37});
    points.push_back( {5,72});
    points.push_back( {10,-37});
    points.push_back( {-4,-57});
    points.push_back( {-3,-53});
    points.push_back( {3,74});
    points.push_back( {-3,-11});
    points.push_back( {-8,7});
    points.push_back( {1,88});
    points.push_back( {-12,42});
    points.push_back( {1,-37});
    points.push_back( {2,77});
    points.push_back( {-6,77});
    points.push_back( {5,72});
    points.push_back( {-4,-57});
    points.push_back( {-18,-33});
    points.push_back( {-12,42});
    points.push_back( {-9,86});
    points.push_back( {2,77});
    points.push_back( {-8,77});
    points.push_back( {-3,77});
    points.push_back( {9,-42});
    points.push_back( {16,41});
    points.push_back( {-29,-37});
    points.push_back( {0,-41});
    points.push_back( {-21,18});
    points.push_back( {-27,-34});
    points.push_back( {0,77});
    points.push_back( {3,74});
    points.push_back( {-7,-69});
    points.push_back( {-21,18});
    points.push_back( {27,146});
    points.push_back( {-20,13});
    points.push_back( {21,130});
    points.push_back( {-6,-65});
    points.push_back( {14,-4});
    points.push_back( {0,3});
    points.push_back( {9,-5});
    points.push_back( {6,-29});
    points.push_back( {-2,73});
    points.push_back( {-1,-15});
    points.push_back( {1,76});
    points.push_back( {-4,77});
    points.push_back( {6,-29});
    cout << PointsToString( points ) << ( sol.maxPoints( points ) == 25 ) << endl;

    points.clear();
    points.push_back( vector<int>{ 1, 1 } );
    points.push_back( vector<int>{ 2, 2 } );
    points.push_back( vector<int>{ 3, 3 } );
    cout << PointsToString( points ) << ( sol.maxPoints( points ) == 3 ) << endl;

    points.clear();
    points.push_back( vector<int>{ 1, 1 } );
    points.push_back( vector<int>{ 3, 2 } );
    points.push_back( vector<int>{ 5, 3 } );
    points.push_back( vector<int>{ 4, 1 } );
    points.push_back( vector<int>{ 2, 3 } );
    points.push_back( vector<int>{ 1, 4 } );
    cout << PointsToString( points ) << ( sol.maxPoints( points ) == 4 ) << endl;
}
