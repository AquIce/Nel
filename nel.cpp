#include <iostream>
#include <array>
#include <vector>

namespace NEL
{
    class Nel {
    private:
        // 1 -> X
        // -1 -> O
        // 0 -> Empty
        std::array<std::array<int, 3>, 3> board = {{
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
        }};
    public:
        Nel() {}

        bool is_engine_to_move(int player) {
            return player % 2 == 0;
        }

        std::string get_player_name(int player) {
            if(player == 1)
                return "X";
            else if(player == -1)
                return "O";
            else
                return " ";
        }

        void printBoard(std::array<std::array<int, 3>, 3> brd) {
            std::cout << "o - - - o" << std::endl;
            for (int i = 0; i < 3; i++) {
                std::cout << "| ";
                for (int j = 0; j < 2; j++) {
                    std::cout << get_player_name(brd[i][j]) << " ";
                }
                std::cout << get_player_name(brd[i][2]) << " |" << std::endl;
            }
            std::cout << "o - - - o" << std::endl;
        }

        void play(int x, int y, int player) {
            this->board[x][y] = player;
        }

        std::vector<std::array<int, 2>> getEmptyCells(std::array<std::array<int, 3>, 3> brd) {
            std::vector<std::array<int, 2>> emptyCells;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (brd[i][j] == 0) {
                        emptyCells.push_back({i, j});
                    }
                }
            }
            return emptyCells;
        }

        int status(std::array<std::array<int, 3>, 3> brd) {
            // Check rows
            for (int i = 0; i < 3; i++) {
                if (brd[i][0] == brd[i][1] && brd[i][1] == brd[i][2]) {
                    return brd[i][0];
                }
            }

            // Check columns
            for (int i = 0; i < 3; i++) {
                if (brd[0][i] == brd[1][i] && brd[1][i] == brd[2][i]) {
                    return brd[0][i];
                }
            }

            // Check diagonals
            if (brd[0][0] == brd[1][1] && brd[1][1] == brd[2][2]) {
                return brd[0][0];
            }
            if (brd[0][2] == brd[1][1] && brd[1][1] == brd[2][0]) {
                return brd[0][2];
            }

            // Check if board is full
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (brd[i][j] == 0) {
                        return 0;
                    }
                }
            }

            // Draw
            return 2;
        }

        std::vector<std::vector<std::pair<std::array<int, 2>, int>>> calculate(std::array<std::array<int, 3>, 3> brd, int player, std::vector<std::vector<std::pair<std::array<int, 2>, int>>> moves = {}) {
            for(auto move : getEmptyCells(brd)) {
                brd[move[0]][move[1]] = player;
                if(status(brd) == 0) {
                    std::vector<std::pair<std::array<int, 2>, int>> mvs = calculate(brd, -player, moves);
                    moves.insert(moves.end(), mvs.begin(), mvs.end());
                } else {
                    moves.push_back({move, status(brd)});
                }
                brd[move[0]][move[1]] = 0;
            }
            return moves;
        }

        std::array<int, 2> predict(std::vector<std::pair<std::array<int, 2>, int>> moves, int player) {
            std::array<int, 2> bestMove = {-1, -1};
            int bestScore = -2;
            for(auto move : moves) {
                if(move.second == player) {
                    return move.first;
                } else if(move.second == 0) {
                    if(bestScore < 1) {
                        bestScore = 1;
                        bestMove = move.first;
                    }
                } else if(move.second == 2) {
                    if(bestScore < 0) {
                        bestScore = 0;
                        bestMove = move.first;
                    }
                }
            }
            return bestMove;
        }

        void mainLoop() {
            int player = 1;
            while (true) {
                int x = 0, y = 0;
                printBoard(this->board);
                if(is_engine_to_move(player)) {
                    std::array<int, 2> move = predict(this->board, player);
                    if(move == std::array<int, 2>{-1, -1})
                        throw std::runtime_error("No move found");
                    x = move[0];
                    y = move[1];
                } else {
                    while(x < 1 || x > 3 || y < 1 || y > 3) {
                        std::cout << "Enter x and y: ";
                        std::cin >> x >> y;
                    }
                    x = 3 - x;
                    y -= 1;
                }
                this->play(x, y, is_engine_to_move(player) ? -1 : 1);
                if(status(this->board) != 0) {
                    printBoard(this->board);
                    std::cout << "Player " << get_player_name(player) << " won!" << std::endl;
                    break;
                }
                player++;
            }
        }
    };
} // namespace nel
