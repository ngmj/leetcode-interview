class Solution {
public:
    int trap(vector<int>& height) {
        size_t num = height.size();
        if ( num < 3 )
        {
            return 0;
        }

        int curTotal = 0;
        int total = 0;

        int cursorL = 0;
        int cursorR = num - 1;

        int i = cursorL + 1;
        int j = cursorR - 1;

        while ( cursorL < cursorR )
        {
            while ( i <= cursorR && height[i] < height[cursorL] )
            {
                curTotal += height[i];
                i++;
            }

            if ( i <= cursorR )
            {
                total += height[cursorL] * ( i - cursorL - 1 ) - curTotal;
                cursorL = i;
                i++;
            }

            curTotal = 0;
            while ( cursorL <= j && height[j] < height[cursorR] )
            {
                curTotal += height[j];
                j--;
            }

            if ( cursorL <= j )
            {
                total += height[cursorR] * ( cursorR - j - 1 ) - curTotal;
                cursorR = j;
                j--;
            }
            curTotal = 0;
        }
        return total;
    }
};
