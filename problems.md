1、https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/
返回 A 的最短的非空连续子数组的长度，该子数组的和至少为 K 。
如果没有和至少为 K 的非空子数组，返回 -1 。
=》解法：前缀和+双端（递增）队列
=》分析：我们用 opt(y) 表示对于固定的 y，最大的满足 P[x] <= P[y] - K 的 x，这样所有 y - opt(y) 中的最小值即为答案。
         如序列：1,4,-2,4; 前缀和：1,5,3,7; 
         单调队列入的时候，3进入时，可以把5剔除了，因为5不可能与后面的值形成答案（有更小的且下标更大的3在）
                        7进入时，可以跟队列头比，只要差值<=k，就可以把头挪出去（因为7已经和这些头比过且都符合条件，后面的值即使有跟头还符合的，长度也比7要大）

2、https://leetcode-cn.com/problems/longest-palindromic-substring/
最长回文串
给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。
=》解法：定义二维数组，dp[i][j]表示i～j是否是回文，计算长度为1的回文dp[i][i]，计算长度为2的dp[i][i+1]，再一直继续长度为n的
         dp[i][j+n-1] = dp[i+1][j+n-2] && s[i] == s[i+len-1]

3、https://leetcode-cn.com/problems/generate-parentheses/
括号生成
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
输入：n = 3
输出：[
       "((()))",
       "(()())",
       "(())()",
       "()(())",
       "()()()"]
=》解法：dfs+提前剪枝，)数目一定要小于(数目

4、https://leetcode-cn.com/problems/longest-valid-parentheses/
最长有效括号
给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。
输入: "(()"
输出: 2
解释: 最长有效括号子串为 "()"
=》解法：动态规划，跳过'('，只处理')'

5、https://leetcode-cn.com/problems/next-greater-element-ii/
下一个更大元素 II
给定一个循环数组（最后一个元素的下一个元素是数组的第一个元素），输出每个元素的下一个更大元素。数字 x 的下一个更大的元素是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1。
输入: [1,2,1]
输出: [2,-1,2]
解释: 第一个 1 的下一个更大的数是 2；
数字 2 找不到下一个更大的数； 
第二个 1 的下一个最大的数需要循环搜索，结果也是 2。
=》解法：单调下降栈，同时栈内保存数组下标
         第一轮循环，边处理栈，讲出栈的下标值设置为待入栈值
         栈内剩余元素是需要循环数组头部的值，所以再来一轮循环遍历数组就行了
   优化点：保存一个最大值，如果第二轮循环时，到这个最大值还没有处理完栈内元素，就可以退出了

6、https://leetcode-cn.com/problems/largest-rectangle-in-histogram/
柱状图中最大的矩形
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
求在该柱状图中，能够勾勒出来的矩形的最大面积。
=》解法：以高度为准，求该高度左右各能走多远；
         单调栈来分别求解每个h的左右边界

7、https://leetcode-cn.com/problems/maximum-product-subarray/
乘积最大子数组
给你一个整数数组 nums ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。
输入: [2,3,-2,4]
输出: 6
解释: 子数组 [2,3] 有最大乘积 6。
=》解法1：dp做，维护两个dp（max、min），如果当前值时负数，更新max和min
   解法2：贪心做，从左扫描，挨个累乘*max，遇到0则从新开始（max=1）
                  从右再扫描，挨个累乘*max，遇到0则从新开始（max=1）
7.2、https://leetcode-cn.com/problems/maximum-subarray/
最大子序和
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
输入: [-2,1,-3,4,-1,2,1,-5,4]
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
=》解法1：dp[i]表示以i为结尾的最长子序列，dp[i] = max(dp[i-1] + val, val)，状态压缩sum = max(sum + val, val)
   解法2：分治法,维护[l, r)区间的4个值，m = l + (r - l)/ 2;
                sum  整个区间和 = sum[l, m) = sum[m, r)
                lrum 以l为左端点的最长和 = max(lrum[l, m), sum[l, m) + lrum[m, r))
                rsum 以r为右端点的最长和 同上
                msum 内部区间最长和 = max(不垮m的max(msum[l, m), msum[m, r)), 跨过m的rsum[l, m) + lrum[m, r)) 

8、https://leetcode-cn.com/problems/search-a-2d-matrix-ii/
搜索二维矩阵 II
编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target。该矩阵具有以下特性：
每行的元素从左到右升序排列。
每列的元素从上到下升序排列。
=》解法：反对角线搜索

9、https://leetcode-cn.com/problems/remove-invalid-parentheses/
删除无效的括号
删除最小数量的无效括号，使得输入的字符串有效，返回所有可能的结果。
说明: 输入可能包含了除 ( 和 ) 以外的字符。
=》解法：dfs+剪枝（每个括号都保留或删除）

10、https://leetcode-cn.com/problems/coin-change/
零钱兑换
给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。
输入: coins = [1, 2, 5], amount = 11
输出: 3 
解释: 11 = 5 + 5 + 1
=》解法1：dp[amout]表示用coins组成amout最少需要多少枚
   解法2：贪心+dfs

11、https://leetcode-cn.com/problems/counting-bits/
比特位计数
给定一个非负整数 num。对于 0 ≤ i ≤ num 范围中的每个数字 i ，计算其二进制数中的 1 的数目并将它们作为数组返回。
输入: 2
输出: [0,1,1]
=》解法：x&(x-1)去掉最后一位1；dp[i] = dp[i & (i-1)] + 1

12、https://leetcode-cn.com/problems/integer-break/
整数拆分（类似剪绳子）
给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积。
=》解法1：尽可能多的3+剩余值
   解法2：dp[i] = max{j*dp[i-j], (i-j)*j}, j=0~i
