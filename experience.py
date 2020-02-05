
def recursion(level, param1, param2, ...):

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

def binary_search( array, target ):
    left, right = 0, len(array) - 1
    while left <= right:
        mid = ( left + right ) / 2
        if array[mid] == target:
            # find the target!!
            break or return result
        elif array[mid] < target:
            left = mid + 1
        else:
            right = mid - 1

// 位运算
X & (X - 1) =》消掉X最后一位1，不管这个1在什么位置
X & -X =》得到最后一位1
