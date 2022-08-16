//
// Created by emery on 25/07/2022.
//

#ifndef SODOKU_SODOKU_H
#define SODOKU_SODOKU_H


class Sodoku {
public:
    int generate();
    bool check_col(int row_index, int col_index, int val);
private:
    int game_board[9][9];
};


#endif //SODOKU_SODOKU_H
