
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
