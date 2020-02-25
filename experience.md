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

# dfs & bfs
visisted[][]
int dfs(node, visisted, ...):
    # 退出条件，如isValid(node, ...)
    visisted.add(node)
    for n in node.children():
        if not n || visisted(n):
            dfs(n, visisted, ...)

int bfs(graph, start, end):
    queue.push(start)
    while (!queue.empty()):
        node = queue.top()
        queue.pop()
        visisted.add(node)

        process(node)
        for n in node.children():
            queue.push(n)
    # other processing work

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

# 二分处理模版
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
    // e是下界首个小于target的下标，s是上界首个大于target的下标
    return False

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
适合求解前后数字下降或上升的规律题，如求解“下一个更大值”，“接雨水”等题

# 字串问题
最长公共子序列，最长公共子串（子串是连续的）动态规划
滑动窗口，双指针，right往右得到可行解，左指针往右得到当前最优解
