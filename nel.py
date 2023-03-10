class Nel:
    board = [
        [0, 0, 0],
        [0, 0, 0],
        [0, 0, 0]
    ]

    def __init__(self):
        ...

    def print_board(self):
        for row in self.board:
            print(row)

    def move(self, x, y, player):
        self.board[x][y] = player

    def get_winner(self):
        if(self.board[0][0] == self.board[0][1] == self.board[0][2] != 0):
            return self.board[0][0]
        elif(self.board[1][0] == self.board[1][1] == self.board[1][2] != 0):
            return self.board[1][0]
        elif(self.board[2][0] == self.board[2][1] == self.board[2][2] != 0):
            return self.board[2][0]
        elif(self.board[0][0] == self.board[1][0] == self.board[2][0] != 0):
            return self.board[0][0]
        elif(self.board[0][1] == self.board[1][1] == self.board[2][1] != 0):
            return self.board[0][1]
        elif(self.board[0][2] == self.board[1][2] == self.board[2][2] != 0):
            return self.board[0][2]
        elif(self.board[0][0] == self.board[1][1] == self.board[2][2] != 0):
            return self.board[0][0]
        elif(self.board[0][2] == self.board[1][1] == self.board[2][0] != 0):
            return self.board[0][2]
        else:
            return 0
        
    def is_full(self):
        for row in self.board:
            for cell in row:
                if cell == 0:
                    return False
        return True