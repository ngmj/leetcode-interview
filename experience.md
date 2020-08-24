# 递归求解模版
int recursion(level, param1, param2, ...):

    # recursion termination
    if level > MAX_LEVEL:
        print_result
        return

    # process data in current level
    process_data(level, data)

    # drill down
    self.recursion(level+1, p1, p2, ...)

    # reverse the current level if needed
    reverse_state(level)

# 分治法求解模版
def divid_conquer(problem, param1, param2, ...):
    
    # recursion termination
    if problem is None:
        print_result
        return

    # prepare data
    data = prepare_data(problem)
    subproblems = split_problem(problem, data)

    # conquer subproblems
    subresult1 = divid_conquer( subproblems[0], p1, ... )
    subresult2 = divid_conquer( subproblems[1], p1, ... )
    subresult3 = divid_conquer( subproblems[2], p1, ... )
    ...

    # process and generate the final result
    result = process_result(subresult1, subresult2, subresult3, ...)

# dfs & bfs
visisted[][]
int dfs(node, visisted, ...):
    # 退出条件，如isValid(node, ...)
    visisted.add(node)
    for n in node.children():
        if not n && !visisted(n):
            dfs(n, visisted, ...)

int bfs(graph, node):
    queue.push(node)
    visisted = set()
    while (!queue.empty()):
        node = queue.top()
        queue.pop()
        visisted.add(node)

        process(node)
        for n in node.children():
            if not n && !visisted(n):
                queue.push(n)
    # other processing work

# 二分处理模版
## 1、不确定target是否存在
def binary_search( array, target ):
    s, e = 0, len(array) - 1
    while s <= e:
        m = s + (e - s) / 2 # 下取整
        if array[m] == target:
            # find the target!!
            return True
        elif array[m] < target:
            s = m + 1
        else:
            e = m - 1
    // e是最后一个小于target的下标，s是首个大于target的下标
    // 走到这, 一定是这样data[e] < target < data[s]
    return False

## 1.2 不确定是否有符合条件的（查找首个比val大的元素位置）
def binary_search( array, target ):
    s, e = 0, len(array) - 1
    while s <= e:
        m = s + (e - s) / 2 # 下取整
        if array[m] <= target:
            s = m + 1
        else:
            e = m - 1
    // 只要还会==，那么s=m+1，s往后走，直到target < data[s] 或者s溢出
    // 只要还会>，那么e=m-1，e往前，直到data[e] <= target 或者 e溢出
    // 故走到这, 一定是这样data[e] <= target < data[s] 或者s e溢出范围
    return s # s可能大于len(array) - 1 

## 2. 确定target存在，求下标
def binary_search( array, target ):
    s, e = 0, len(array) - 1
    # NOTE: s < e 且 一次只挪动一个值
    while s < e: 
        m = s + (e - s) / 2 # 下取整
        # 因为m跟右边的比过来，没符合，所以可以s = m+1
        if array[m] < target:
            s = m + 1 # NOTE: 因为是下取整，所以一定要s+1，否则容易出现死循环，如s=0，e=1
        # m未跟左边比过，所以e=m
        else:
            e = m 
    return s # s == e

# 位运算常用算子
X & (X - 1) =》消掉X最后一位1，不管这个1在什么位置
X & -X =》得到最后一位1

# 买卖股票问题的通解
状态：dp[i][k][0 or 1]表示第i天，k次交易后，不持有或持有股票时收益
状态转移方程：
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i-1])
              max(前一天不持有,    前一天持有今天卖出     ) // 一次买卖才是一次交易，所以k可以理解为买的次数
dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i-1])
              max( 前一天持有  , 前一天不持有今天买入     )
初始状态
dp[0][k][0] = 0
dp[0][k][1] = MIN_INT
dp[i][0][0] = 0
dp[i][0][1] = MIN_INT

# 单调上升或下降栈

# 常见问题
## 调上升或下降栈
    适合求解前后数字下降或上升的规律题，如求解“下一个更大值”，“接雨水”等题
## 0/1背包问题
    dp[i][w]表示前i个物品，背包限制大小为w时最优解, dp[i][j] = max{dp[i-1][j], dp[i-1][j-cost[i]] + value[i]}
    完全背包问题（任意一个物品可以被无限放置）dp[i][j] = max{dp[i-1][j], dp[i][j-cost[i]] + value[i]}
    解释：
    1. 第i个物品放进背包一次，dp[i-1][j-cost[i]] + value[i] 表示前i-1个物品被放进j-cost[i]最优值，现在增加"一个"i物品的收益
    2. 第i个物品放进背包至少一次，dp[i][j-cost[i]] + value[i] ，dp[i][j-cost[i]]表示第i个物品放进j-cost[i]的背包最优值，此时i个物品是至少0次，+value[i] 表示"再放一个"i物品，即dp[i][j-cost[i]] + value[i]表示第i个物品至少放进背包一次的最优值
## 子串问题
    最长公共子序列，最长公共子串（子串是连续的）动态规划
    最长上升子序列(a、两层for循环 动态规划；b、dfs；c、dfs+状态记忆，pre为结尾+当前i元素判断的最优解；d、上升子序列+二分查找替换)
## 滑动窗口
    双指针，right往右得到可行解，左指针往右得到当前最优解
    如字符串中最长不重复字符数目之类的
    如最长上升子串（串是连续的）
## 前缀和（留意首个元素为0，长度=nums.size + 1）
一维前缀和 sum[j] - sum[i]
二维前缀和 sum[j]{1~26} - sum[i]{1~26} ==》动态规划？？？
    数组（非负数组）或类两值数组（如求数字和字母数组中最长的子数组，满足字母个数和数字个数相等）
    整数数组 和问题
    (连续的子数组问题，可以考虑前缀和、双指针、hash等方法)
## 蓄水池抽样算法
    每次只保留一个数，当遇到第 i 个数时，以 1/i的概率保留它，(i-1)/i的概率保留原来的数。
    while (phead){
      if (rand() % count++ == 0)
        val = phead->val;
      phead = phead->next;
    }
    return val

