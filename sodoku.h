//
// Created by emery on 25/07/2022.
//

#ifndef SODOKU_SODOKU_H
#define SODOKU_SODOKU_H

#include <vector>
#include <map>

class Sodoku {
public:
    int generate();
    std::vector<int> check(std::vector<int>& tab, int row_index, int col_index);
    std::vector<int> rank (const std::vector<int>& tab, int row_index, int col_index);
    std::vector<int> col_select(std::vector<int>& tab, int row_index, int col_index);
    bool check_col(int row, int col, int number);
    bool check_row(int row, int col, int number);
    bool check_grid(int row, int col, int number);
private:
    int game_board[9][9] = {-1};
};


#endif //SODOKU_SODOKU_H
