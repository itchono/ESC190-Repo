# use memoization technique

# adjustable given variables
M = 4 # number of rows --> vertical axis
N = 5 # number of columns --> horizontal axis

# part A
def maximum_score(treasuremap):
    return pathfind_treasure(treasuremap)[0]

# part B
def optimal_sequnce(treasuremap):
    trace = pathfind_treasure(treasuremap)[1]

    i, j = M-1, N-1

    sequence = []

    while (i, j) != (0, 0):
        sequence.append(trace[i][j])
        if trace[i][j] == 0: j -= 1
        else: i -= 1
        # reconstruct the path from its trace
    sequence.reverse()
    return (sequence)

def pathfind_treasure(treasuremap):
    # memoization approach

    def score(x, y):
        if cache[y][x] == -1: # Score is not found yet
            if (x == 0):
                cache[y][x] = treasuremap[y][x] + score(x,y-1) - 2
                trace[y][x] = 1 # going down
            elif (y == 0):
                cache[y][x] = treasuremap[y][x] + score(x-1, y) - 1
                trace[y][x] = 0 # going right
            else:
                cache[y][x] = treasuremap[y][x] + max(score(x, y-1) - 2, score(x-1, y) - 1) # get max of moving right or down, applying move cost
                trace[y][x] = (1 if score(x, y-1) - 2 > score(x-1, y) - 1 else 0)

        return cache[y][x]

    cache = [[-1 for i in range(N)] for i in range(M)] # memoization cache
    trace = [[-1 for i in range(N)] for i in range(M)] # trace of moves

    # fill in starting corner as base case; that's it
    cache[0][0] = treasuremap[0][0]

    return score(N-1, M-1), trace, cache

if __name__ == "__main__":
    treasuremap = [[2,3,6,1,2],
                   [5,0,3,5,2],
                   [2,1,7,4,3],
                   [9,3,8,2,6]]
    print("Max Score: {}".format(maximum_score(treasuremap)))

    print("Move Sequence: ")
    sequence = optimal_sequnce(treasuremap)
    for s in sequence:
        print("Right" if s == 0 else "Down")
    
