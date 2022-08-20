//
// Created by emery on 25/07/2022.
//
#include <cstdlib>
#include "iostream"
#include "sodoku.h"
#include "vector"
#include <ctime>
#include <algorithm>
#include <map>

using std::cout;
using std::endl;
using std::vector;
using std::map;

int Sodoku::generate() {
    cout << "generating" << endl;


    int select, number;
    int row = 0, col = 0;
    std::srand(std::time(nullptr));

    while (row < 9) {
        // << "row  : "  << row << " col : " << col <<endl;
        vector<int> tab{1,2,3,4,5,6,7,8,9};
        tab = this->col_select(tab, row, col);
        tab = this->check(tab, row, col);
        tab = this->rank(tab,row,col);
        if (tab.empty()){
            cout << "--------------- need to do this line again ---------------------" << endl;
            for (int i = 0; i < 9; ++i) {
                this->game_board[row][i] = -1;
            }
            col = 0;
            continue;
        }
        select = rand() % tab.size();
        number = tab[select];
        this->game_board[row][col] = number;
        if (col < 8){
            col += 1;
        }
        else if(col == 8){
            col = 0;
            row +=1;
        }

    }
    cout << "display matrice" << endl;
    for (int i=0; i < 9; i++) {
        for (int j = 0; j < 9 ; ++j) {
            bool cr = this ->check_row(i, j, this -> game_board[i][j]);
            bool cl = this ->check_col(i, j, this -> game_board[i][j]);
            if(!cr or !cl){
                cout << "NOON";
            }
            cout <<this -> game_board[i][j] << " " ;
            if (j == 8){
                cout << endl;
            }
        }
    }
    std::cout << "end generating \n";
    return 0;
}

std::vector<int> Sodoku::check(std::vector<int>& val, int row_index, int col_index) {
    int number;

    for (int i = 0; i < row_index; ++i) {
        number = this->game_board[i][col_index];
        if ( std::find(val.begin(), val.end(), number) != val.end() ){
            auto elem_to_remove = std::find(val.begin(), val.end(), number);
            if (elem_to_remove != val.end()) {
                val.erase(elem_to_remove);
            }
        }
    }

    for (int i = 0; i < col_index; ++i) {
        number = this->game_board[row_index][i];
        if ( std::find(val.begin(), val.end(), number) != val.end() ){
            auto elem_to_remove = std::find(val.begin(), val.end(), number);
            if (elem_to_remove != val.end()) {
                val.erase(elem_to_remove);
            }
        }
    }

    return val;
}

vector<int> Sodoku::rank(const std::vector<int>& tab, int row_index, int col_index) {
    std::map<int, int> dict;
    int lowest = 10;
    vector<int> final_tab;
    for (int i: tab) {
        int counter = 0;
        for (int j = col_index+1; j < 9; ++j) {
            if (this->check_col(row_index, j, i)){
                counter++;
            }
        }
        if( counter < lowest){
            lowest = counter;
        }
        dict[i]=counter;
    }
    for (auto &item : dict) {
        if (item.second == lowest){
            final_tab.push_back(item.first);
        }
    }
    return final_tab;
}

bool Sodoku::check_col(int row, int col, int number) {
    bool absent = true;
    for (int i = 0; i < row; ++i) {
        if (this->game_board[i][col] == number){
            absent = false;
            break;
        }
    }

    return absent;
}

bool Sodoku::check_row(int row, int col, int number) {
    bool absent = true;
    for (int i = 0; i < col; ++i) {
        if (this->game_board[row][i] == number){
            absent = false;
            break;
        }
    }

    return absent;
}

std::vector<int> Sodoku::col_select(vector<int> &tab, int row_index, int col_index) {
    vector<int> select;
    for (int i = col_index +1; i < 9; ++i) {
        int count = 0;
        for (int j: tab) {
            bool check = this->check_col(row_index, i, j);
            if (check){
                count++;
            }
        }
        if (count == 1){
            for (int j: tab) {
                bool check = this->check_col(row_index, i, j);
                if (check){
                    select.push_back(j);
                }
            }
        }
    }
    if(!select.empty()){
        for (int i :select) {
            auto elem_to_remove = std::find(tab.begin(), tab.end(), i);
            if (elem_to_remove != tab.end()) {
                tab.erase(elem_to_remove);
            }
        }
    }
    return tab;
}
