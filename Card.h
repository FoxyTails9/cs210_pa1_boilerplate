#pragma once
#include <ostream>
#include <string>

class Card {
public:
    Card(const std::string& color, const std::string& rank)
        : color_(color), rank_(rank) {}

    bool operator==(const Card& other) const {
        return color_ == other.color_ && rank_ == other.rank_;
    }

    friend std::ostream& operator<<(std::ostream& out, const Card& c) {
        return out << c.color_ << " " << c.rank_;
    }

private:
    std::string color_;
    std::string rank_;
};