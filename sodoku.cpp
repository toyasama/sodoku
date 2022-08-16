//
// Created by emery on 25/07/2022.
//
#include <cstdlib>
#include "iostream"
#include "sodoku.h"
#include "vector"
#include <ctime>

using std::cout;
using std::endl;

int Sodoku::generate() {
    std::cout << "generating" << std::endl;
    std::vector<int> save_tab {1,2,3,4,5,6,7,8,9};
    std::vector<int> tab;
    tab = save_tab;


    int select, val;
    int row = 0, col = 0;
    std::srand(std::time(nullptr));

    while (row < 9) {
        cout << "this is the row  :"  << row << endl;
        tab = save_tab;
        while (!tab.empty()) {
            select = std::rand() % tab.size();
            val = tab[select];
            if (row == 0) {
                this->game_board[row][col] = val;
                auto elem_to_remove = tab.begin() + select;
                if (elem_to_remove != tab.end()) {
                    tab.erase(elem_to_remove);
                }

                if (col == 8) {
                    row += 1;
                    col = 0;
                } else {
                    col += 1;
                }
            }
            else {
                while (!tab.empty()) {
                    bool check = this->check_col(row, col, val);
                    if (check) {
                        this->game_board[row][col] = val;
                        auto elem_to_remove = tab.begin() + select;
                        if (elem_to_remove != tab.end()) {
                            tab.erase(elem_to_remove);
                        }

                        if (col == 8) {
                            row += 1;
                            col = 0;
                        } else {
                            col += 1;
                        }
                        break;
                    } else {
                        cout << "old value and select " << val << " and " << select <<  "and " << tab.size() << endl;
                        if (tab.size() == 1){
                            tab = save_tab;
                            col = 0;
                            select = std::rand() % tab.size();
                            val = tab[select];
                            cout << "restart " << val << " and " << select << endl;
                            break;
                        }
                        select += 1;
                        select = select % tab.size();
                        val = tab[select];
                        cout << "New value and select " << val << " and " << select << endl;
                    }
                }
            }
        }
        cout << "print row" << endl;
        for (int j = 0; j < 9 ; ++j) {
            cout <<this->game_board[row-1][j] << " " ;
            if (j == 8){
                cout << endl;
            }
        }
    }
    for (int i = 0 ; i < 9 ; i++) {
        for (int j = 0; j < 9 ; ++j) {
            cout <<this->game_board[i][j] << " " ;
            if (j == 8){
                cout << endl;
            }
        }
    }
    std::cout << "end generating \n";
    return 0;
}

bool Sodoku::check_col(int row_index, int col_index,  int val) {
    bool check = true;
    for (int i = 0; i < row_index; ++i) {
        if (this->game_board[i][col_index] == val){
            check = false;
            break;
        }

    }
    return check;
}
