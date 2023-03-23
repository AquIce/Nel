# Tic-Tac-Toe using Mini-Max Algorithm
# Vineet Joshi
def print_board(board):
    for i in range(0, 9):
        if i % 3 == 0:
            print()
        if (board[i] == 0):
            print('-', end='')
        if (board[i] == 1):
            print('o', end='')
        if (board[i] == -1):
            print('x', end='')
    print('\n\n')

def HumanTurn(board):
    pos = int(input('Enter x\'s position (0..9): '))
    if (board[pos] != 0):
        print('Wrong Move')
        exit(0)
    board[pos-1] = -1

def minimax(board, player):
    x = state(board)
    if (x != 0):
        return (x*player)
    pos = -1
    value = -2
    for i in range(0, 9):
        if (board[i] == 0):
            board[i] = player
            score = -minimax(board, (player*-1))
            if (score > value):
                value = score
                pos = i
            board[i] = 0

    if (pos == -1):
        return 0
    return value

def NelTurn(board):
    pos = -1
    value = -2
    for i in range(0, 9):
        if (board[i] == 0):
            board[i] = 1
            score = -minimax(board, -1)
            board[i] = 0
            if (score > value):
                value = score
                pos = i

    board[pos] = 1

def state(board):
    cb = [[0, 1, 2], [3, 4, 5], [6, 7, 8], [0, 3, 6], [1, 4, 7], [2, 5, 8], [0, 4, 8], [2, 4, 6]]

    for i in range(0, 8):
        if (board[cb[i][0]] != 0 and board[cb[i][0]] == board[cb[i][1]] and board[cb[i][0]] == board[cb[i][2]]):
            return board[cb[i][2]]
    return 0

def main():
    board = [0, 0, 0, 0, 0, 0, 0, 0, 0]
    print('Computer > o')
    print('You      > x')
    player = input('Enter to play 1(st) or 2(nd) :')
    player = int(player)
    for i in range(0, 9):
        if (state(board) != 0):
            break
        if ((i+player) % 2 == 0):
            NelTurn(board)
        else:
            print_board(board)
            HumanTurn(board)

    x = state(board)
    if (x == 0):
        print_board(board)
        print('Draw')
    if (x == -1):
        print_board(board)
        print('x wins')
    if (x == 1):
        print_board(board)
        print('y wins')

main()