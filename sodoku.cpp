//
// Created by emery on 25/07/2022.
//
#include "iostream"
#include "sodoku.h"
#include "vector"
#include <algorithm>
#include <map>
#include <random>

using std::cout;
using std::endl;
using std::vector;
using std::map;

constexpr int MIN = 0;
constexpr int MAX =10;

void Sodoku::generate() {
    cout << "generating" << endl;
    std::cout << "end generating \n";

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(MIN, MAX);

    int select, number;
    int row = 0, col = 0, restart = 0;

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
            if(restart == 20){
                cout << "--------------- RESTART !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ---------------------" << endl;
                for (auto & i : this->game_board) {
                    for (int & j : i) {
                        j = -1;

                    }
                }
                col = 0;
                row = 0;
                restart = 0;
                continue;
            }
            restart++;
            continue;
        }
        select = distr(eng) % (int)tab.size();
        number = tab[select];
        //cout << "number chosen : " << number << endl;
        this->game_board[row][col] = number;
        if (col < 8){
            col += 1;
        }
        else if(col == 8){
            col = 0;
            row +=1;
        }

    }
    bool success = true;
    cout << "Game board" << endl;
    for (int i=0; i < 9; i++) {
        for (int j = 0; j < 9 ; j++) {
            bool cr = this ->check_row(i, j, this -> game_board[i][j]);
            bool cl = this ->check_col(i, j, this -> game_board[i][j]);
            bool cg = this ->final_check_grid(i, j, this -> game_board[i][j]);
            if(!cr or !cl or !cg){
                success = false;
                cout << "N" ;
            }
            cout <<this -> game_board[i][j] << " " ;
            if (j == 8){
                cout << endl;
            }
        }
    }
    if (success){
        this ->display("facile");
    }

    cout << "display board" << endl;
    for (int i=0; i < 9; i++) {
        for (int j = 0; j < 9 ; j++) {
            cout <<this -> display_board[i][j] << " " ;
            if (j == 8){
                cout << endl;
            }
        }
    }

    std::cout << "end generating \n";
}

std::vector<int> Sodoku::check(std::vector<int>& val, int row_index, int col_index) {
    int number;
    std::vector<int> check_list;
    for (int i = 0; i < row_index; i++) {
        number = this->game_board[i][col_index];
        if ( std::find(val.begin(), val.end(), number) != val.end() ){
            auto elem_to_remove = std::find(val.begin(), val.end(), number);
            if (elem_to_remove != val.end()) {
                val.erase(elem_to_remove);
            }
        }
    }

    for (int i = 0; i < col_index; i++) {
        number = this->game_board[row_index][i];
        if ( std::find(val.begin(), val.end(), number) != val.end() ){
            auto elem_to_remove = std::find(val.begin(), val.end(), number);
            if (elem_to_remove != val.end()) {
                val.erase(elem_to_remove);
            }
        }
    }

    for (auto i: val){
        if(this ->check_grid(row_index, col_index, i)){
            check_list.push_back(i);
        }
    }

    return check_list;
}

vector<int> Sodoku::rank(const std::vector<int>& tab, int row_index, int col_index) {
    /*cout << " check tab : ";
    for (auto i:tab) {
        cout << i << " ";
    }
    cout << endl;*/
    std::map<int, int> dict;
    int lowest = 10;
    vector<int> final_tab;
    for (int i: tab) {
        int counter = 0;
        for (int j = col_index+1; j < 9; j++) {
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
    }/*
    cout << " final tab : ";
    for (auto i:final_tab) {
        cout << i << " ";
    }
    cout << endl;*/
    return final_tab;
}

bool Sodoku::check_col(int row, int col, int number) {
    bool absent = true;
    for (int i = 0; i < row; i++) {
        if (this->game_board[i][col] == number){
            absent = false;
            break;
        }
    }

    return absent;
}

bool Sodoku::check_row(int row, int col, int number) {
    bool absent = true;
    for (int i = 0; i < col; i++) {
        if (this->game_board[row][i] == number){
            absent = false;
            break;
        }
    }

    return absent;
}

std::vector<int> Sodoku::col_select(vector<int> &tab, int row_index, int col_index) {
    vector<int> select;
    for (int i = col_index +1; i < 9; i++) {
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
                    if (this ->check_grid(row_index, i, j)){
                        select.push_back(j);
                    }
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

bool Sodoku::final_check_grid(int row, int col, int number) {
    bool absent = true;
    if(row >= 0 and row <=2 and col >= 0 and col <= 2){
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if( i != row and j!=col){
                    if (this -> game_board[i][j] == number){
                        absent = false;
                    }
                }
            }
        }
    }
    else if(row >= 0 and row <=2 and col >= 3 and col <= 5){
        for (int i = 0; i < 3; ++i) {
            for (int j = 3; j < 6; ++j) {
                if( i != row and j!=col){
                    if (this -> game_board[i][j] == number){
                        absent = false;
                    }
                }
            }
        }
    }
    else if(row >= 0 and row <=2 and col >= 6 and col <= 8){
        for (int i = 0; i < 3; ++i) {
            for (int j = 6; j < 9; ++j) {
                if( i != row and j!=col){
                    if (this -> game_board[i][j] == number){
                        absent = false;
                    }
                }
            }
        }
    }
    else if(row >= 3 and row <=5 and col >= 0 and col <= 2){
        for (int i = 3; i < 6; ++i) {
            for (int j = 0; j < 3; ++j) {
                if( i != row and j!=col){
                    if (this -> game_board[i][j] == number){
                        absent = false;
                    }
                }
            }
        }
    }
    else if(row >= 3 and row <=5 and col >= 3 and col <= 5){
        for (int i = 3; i < 6; ++i) {
            for (int j = 3; j < 6; ++j) {
                if( i != row and j!=col){
                    if (this -> game_board[i][j] == number){
                        absent = false;
                    }
                }
            }
        }
    }
    else if(row >= 3 and row <=5 and col >= 6 and col <= 8){
        for (int i = 3; i < 6; ++i) {
            for (int j = 6; j < 9; ++j) {
                if( i != row and j!=col){
                    if (this -> game_board[i][j] == number){
                        absent = false;
                    }
                }
            }
        }
    }
    else if(row >= 6 and row <=8 and col >= 0 and col <= 2){
        for (int i = 6; i < 9; ++i) {
            for (int j = 0; j < 3; ++j) {
                if( i != row and j!=col){
                    if (this -> game_board[i][j] == number){
                        absent = false;
                    }
                }
            }
        }
    }
    else if(row >= 6 and row <=8 and col >= 3 and col <= 5){
        for (int i = 6; i < 9; ++i) {
            for (int j = 3; j < 6; ++j) {
                if( i != row and j!=col){
                    if (this -> game_board[i][j] == number){
                        absent = false;
                    }
                }
            }
        }
    }
    else if(row >= 6 and row <=8 and col >= 6 and col <= 8){
        for (int i = 6; i < 9; ++i) {
            for (int j = 6; j < 9; ++j) {
                if( i != row and j!=col){
                    if (this -> game_board[i][j] == number){
                        absent = false;
                    }
                }
            }
        }
    }
    return absent;
}

bool Sodoku::check_grid(int row, int col, int number) {
    bool absent = true;
    if(row >= 0 and row <=2 and col >= 0 and col <= 2){
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; j++) {
                if (this -> game_board[i][j] == number){
                    absent = false;
                }
            }
        }
    }
    else if(row >= 0 and row <=2 and col >= 3 and col <= 5){
        for (int i = 0; i < 3; i++) {
            for (int j = 3; j < 6; j++) {
                if (this -> game_board[i][j] == number){
                    absent = false;
                }
            }
        }
    }
    else if(row >= 0 and row <=2 and col >= 6 and col <= 8){
        for (int i = 0; i < 3; i++) {
            for (int j = 6; j < 9; j++) {
                if (this -> game_board[i][j] == number){
                    absent = false;
                }
            }
        }
    }
    else if(row >= 3 and row <=5 and col >= 0 and col <= 2){
        for (int i = 3; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                if (this -> game_board[i][j] == number){
                    absent = false;
                }
            }
        }
    }
    else if(row >= 3 and row <=5 and col >= 3 and col <= 5){
        for (int i = 3; i < 6; i++) {
            for (int j = 3; j < 6; j++) {
                if (this -> game_board[i][j] == number){
                    absent = false;
                }
            }
        }
    }
    else if(row >= 3 and row <=5 and col >= 6 and col <= 8){
        for (int i = 3; i < 6; i++) {
            for (int j = 6; j < 9; j++) {
                if (this -> game_board[i][j] == number){
                    absent = false;
                }
            }
        }
    }
    else if(row >= 6 and row <=8 and col >= 0 and col <= 2){
        for (int i = 6; i < 9; i++) {
            for (int j = 0; j < 3; j++) {
                if (this -> game_board[i][j] == number){
                    absent = false;
                }
            }
        }
    }
    else if(row >= 6 and row <=8 and col >= 3 and col <= 5){
        for (int i = 6; i < 9; i++) {
            for (int j = 3; j < 6; j++) {
                if (this -> game_board[i][j] == number){
                    absent = false;
                }
            }
        }
    }
    else if(row >= 6 and row <=8 and col >= 6 and col <= 8){
        for (int i = 6; i < 9; i++) {
            for (int j = 6; j < 9; j++) {
                if (this -> game_board[i][j] == number){
                    absent = false;
                }
            }
        }
    }
    return absent;
}

void Sodoku::display(const std::string& level){
    const int min = 0;
    const int max = 8;
    int row, col;
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(min, max);
    int masque = 0;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            this -> display_board[i][j] = this -> game_board[i][j];
        }
    }
    if (level == "facile"){
        cout << "mode facile !" << endl;
        masque = 35;
    }
    else if(level == "moyen"){
        masque =50;
    }else if(level == "difficile"){
        masque =70;
    }
    while (masque > 0){
        row = distr(eng);
        col = distr(eng);
        if (this -> display_board[row][col] != 0){
            this -> display_board[row][col] = 0;
            masque--;
        }
    }

}
