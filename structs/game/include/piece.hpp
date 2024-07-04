#pragma once
#include <vector>


class Piece {
public:
    Piece();
    ~Piece();
    
    void offset() const ;
    void rotate(int) const;
    std::vector<int> getCases();


    private:
    std::vector<int> cases;
}