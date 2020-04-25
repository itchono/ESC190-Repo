class State:
    def __init__(self, p1, p2, turn):
        self.p1 = p1
        self.p2 = p2
        self.turn = turn # either 1 or 2
    def p1Sum(self):
        return self.p1[0] + self.p1[1]
    def p2Sum(self):
        return self.p2[0] + self.p2[1]
    def __str__(self):
        return str(self.p1) + str(self.p2)+ str(self.turn)

# player 1 positive
# player 2 negative


def utility(s):
    # determine who won
    if s.p1[0] > 4 or s.p1[1] > 4: return ((-1) * s.p2Sum()) # p2 wins
    else: return s.p1Sum() # p1 wins

def terminal(s):
    return s.p1[0] > 4 or s.p1[1] > 4 or s.p2[0] > 4 or s.p2[1] > 4

ACTIONS = ["s0", "s1", "00", "01", "10", "11"]
# s0 =  self attack 0 etc
# 00 =  self 0 attack opponent 0 (6 possible total moves)

def next_state(s, a):
    n = State(s.p1[:], s.p2[:], 2 if s.turn == 1 else 1) # clone ==> next state
    # add chopsticks
    if s.turn == 1:
        if a == "s0":
            n.p1[0] += s.p1[1]
        elif a == "s1":
            n.p1[1] += s.p1[0]
        else:
            n.p2[int(a[1])] += s.p1[int(a[0])]
    else:
        if a == "s0":
            n.p2[0] += s.p2[1]
        elif a == "s1":
            n.p2[1] += s.p2[0]
        else:
            n.p1[int(a[1])] += s.p2[int(a[0])]
    
    return n

def minimax(s):
    d = dict()
    for a in ACTIONS:
        d[a] = getMin(next_state(s, a))
    print(d)
    v=list(d.values())
    k=list(d.keys())
    return k[v.index(max(v))]
    # outputs an ACTION, which you will need to interpret.

def getMax(s):
    if terminal(s):
        return (utility(s))
    val = float("-inf")
    for a in ACTIONS:
        val = max(val, getMin(next_state(s, a)))
    return val

def getMin(s):
    if terminal(s):
        return (utility(s))
    val = float("inf")
    for a in ACTIONS:
        val = min(val, getMax(next_state(s, a)))
    return val

if __name__ == "__main__":
    g = State([1, 1], [1, 1], 1)
    print(minimax(g))