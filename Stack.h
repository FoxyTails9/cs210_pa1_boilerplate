#pragma once
#include <iostream>
#include "Node.h"

// A linked-list-backed stack. Reuses the same Node<T> the rest of the
// project already uses. Not a wrapper around List<T>: List<T> has no
// way to hand back the value it removed, or to look at the front
// without removing it, and a real stack needs both. So Stack<T> talks
// to Node<T> directly, the same way Queue<T> does.
//
// The one ownership rule that's different from everything else in this
// project: pop() hands the T* back to the caller. It only deletes the
// Node, not the T inside it. Whoever calls pop() now owns that pointer
// and is responsible for deleting it eventually. Nothing that's still
// sitting in the stack when it's destroyed gets that treatment, the
// destructor deletes both layers for anything nobody ever popped.

template <typename T>
class Stack {
public:
    Stack() : head_(nullptr), size_(0) {}

    void push(T* value) {
        Node<T>* fresh = new Node<T>(value);
        fresh->next = head_;
        head_ = fresh;
        ++size_;
    }

    T* pop() {
        if (head_ == nullptr) {
            std::cout << "Stack is empty." << std::endl;
            return nullptr;
        }
        Node<T>* doomed = head_;
        T* value = doomed->data;
        head_ = head_->next;
        delete doomed;
        --size_;
        return value;
    }

    T* peek() const {
        if (head_ == nullptr) return nullptr;
        return head_->data;
    }

    bool isEmpty() const {
        return head_ == nullptr;
    }

    int size() const {
        return size_;
    }

    void print() const {
        Node<T>* current = head_;
        while (current != nullptr) {
            std::cout << *current->data << ",";
            current = current->next;
        }
        std::cout << std::endl;
    }

    ~Stack() {
        while (head_ != nullptr) {
            Node<T>* doomed = head_;
            head_ = head_->next;
            delete doomed->data;
            delete doomed;
        }
    }

private:
    Node<T>* head_;
    int size_;
};
