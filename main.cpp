#include <iostream>
#include "List.h"
#include "Player.h"
#include "Card.h"

int main() {
    // ---- Part 1: required test ----
    std::cout << "== List<int>: addAnywhere / deleteAnywhere / reverse =="
              << std::endl;
    std::unique_ptr<List<int>> nums = makeList<int>();
    nums->addFront(new int(10));
    nums->addFront(new int(20));
    nums->addFront(new int(30));
    nums->print();
    nums->addAnywhere(1, new int(99));
    nums->print();
    nums->deleteAnywhere(2);
    nums->print();
    nums->reverse();
    nums->print();

    std::cout << std::endl << "== List<int>: concat ==" << std::endl;
    std::unique_ptr<List<int>> more = makeList<int>();
    more->addFront(new int(2));
    more->addFront(new int(1));
    more->print();
    nums->concat(more.get());
    nums->print();
    more->print();

    // ---- Part 2: your Uno scene ----

    std::cout << std::endl << "== Uno Turn Order ==" << std::endl;

    // Step 1: A table forms, players join the turn order.
    std::cout << "-- Table forms --" << std::endl;

    Player* p1 = new Player(1, "Alice");
    Player* p2 = new Player(2, "Bob");
    Player* p3 = new Player(3, "Carol");
    Player* p4 = new Player(4, "Dave");

    // Deal each player a starting hand.
    p1->hand()->push(new Card("Red", "7"));
    p1->hand()->push(new Card("Blue", "Skip"));
    p1->hand()->push(new Card("Green", "3"));

    p2->hand()->push(new Card("Yellow", "2"));
    p2->hand()->push(new Card("Red", "Reverse"));
    p2->hand()->push(new Card("Blue", "9"));

    p3->hand()->push(new Card("Green", "Draw Two"));
    p3->hand()->push(new Card("Yellow", "5"));
    p3->hand()->push(new Card("Red", "1"));

    p4->hand()->push(new Card("Blue", "4"));
    p4->hand()->push(new Card("Green", "Wild"));
    p4->hand()->push(new Card("Yellow", "8"));

    std::unique_ptr<List<Player>> table = makeList<Player>();
    table->addBack(p1);
    table->addBack(p2);
    table->addBack(p3);
    table->addBack(p4);
    table->print();

    // Step 2: A new player pulls up a chair mid-order.
    std::cout << "-- Eve joins mid-order --" << std::endl;
    Player* p5 = new Player(5, "Eve");
    p5->hand()->push(new Card("Red", "Draw Four"));
    p5->hand()->push(new Card("Blue", "6"));
    p5->hand()->push(new Card("Green", "Skip"));
    table->addAnywhere(2, p5);
    table->print();

    // Step 3: Reverse card played.
    std::cout << "-- Before Reverse --" << std::endl;
    table->print();
    table->reverse();
    std::cout << "-- After Reverse --" << std::endl;
    table->print();

    // Step 4: A player runs out of cards and leaves the match.
    std::cout << "-- Bob wins and leaves the match --" << std::endl;
    // After reverse, order is: Dave(4), Carol(3), Eve(5), Bob(2), Alice(1)
    // Bob is at position 3. Delete position 3.
    table->deleteAnywhere(3);
    table->print();

    // Extra Credit: a player plays a card.
    std::cout << "-- Alice plays a card --" << std::endl;
    Card* played = p1->hand()->pop();
    if (played != nullptr) {
        std::cout << "Alice plays: " << *played << std::endl;
        delete played;   // caller owns popped card
    }

    // Step 5: A second table merges in with concat.
    std::cout << "-- Second table forms --" << std::endl;
    std::unique_ptr<List<Player>> table2 = makeList<Player>();
    table2->addBack(new Player(6, "Frank"));
    table2->addBack(new Player(7, "Grace"));
    table2->print();

    std::cout << "-- Before concat --" << std::endl;
    std::cout << "Table 1: ";
    table->print();
    std::cout << "Table 2: ";
    table2->print();

    table->concat(table2.get());

    std::cout << "-- After concat --" << std::endl;
    std::cout << "Table 1: ";
    table->print();
    std::cout << "Table 2: ";
    table2->print();

    return 0;
}