#pragma once
#include <ostream>
#include <string>
#include "Stack.h"
#include "Card.h"

class Player {
public:
    Player(int id, const std::string& name) : id_(id), name_(name), hand_(new Stack<Card>()) {}

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    bool operator==(const Player& other) const {
        return id_ == other.id_;
    }

    friend std::ostream& operator<<(std::ostream& out, const Player& p) {
        return out << p.id_ << " " << p.name_;
    }

    Stack<Card>* hand() const { return hand_; }

    ~Player() {
        delete hand_;   // Stack<Card>'s destructor deletes its Cards
    }

private:
    int id_;
    std::string name_;
    Stack<Card>* hand_;
};