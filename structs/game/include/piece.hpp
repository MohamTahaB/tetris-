#pragma once
#include <vector>


class Piece {
public:
    Piece();
    ~Piece();
    
    void offset(char) const ;
    void rotate(int) const;
    std::vector<pair<int,int>> getCases();


    private:
    std::vector<pair<int,int>> cases;
}