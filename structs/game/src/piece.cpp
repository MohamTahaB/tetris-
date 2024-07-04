#include <piece.hpp>
#include <map>

std::vector<pair<int,int>> Piece::getCases() {
    return this->cases;
}

void Piece::offset(char c) {
    std::map<char, pair<int,int>> offsetVal = {
        {'u', {1, 0}}, 
        {'d', {-1, 0}},
        {'l', {0, -1}},
        {'r', {0, 1}}};

    for (pair<int,int> positions : this->cases ) {
        positions.first += offsetVal[c].first ;
        positions.second += offsetVal[c].second;
    }
    return ;
}