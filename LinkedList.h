#pragma once
#include <iostream>
#include "Node.h"
#include "List.h"

template <typename T>
class LinkedList : public List<T> {
public:
    LinkedList() : head_(nullptr), size_(0) {}

    void addFront(T* value) override {
        Node<T>* fresh = new Node<T>(value);
        fresh->next = head_;
        head_ = fresh;
        ++size_;
    }

    void addAnywhere(int position, T* value) override {
        if (position < 0 || position > size_) {
            std::cout << "Invalid position." << std::endl;
            return;
        }
        if (position == 0) {
            addFront(value);
            return;
        }
        // Go to the node just before position.
        Node<T>* prev = head_;
        for (int i = 0; i < position - 1; ++i) {
            prev = prev->next;
        }
        Node<T>* fresh = new Node<T>(value);
        fresh->next = prev->next;
        prev->next = fresh;
        ++size_;
    }

    void addBack(T* value) override {
        Node<T>* fresh = new Node<T>(value);
        if (head_ == nullptr) {
            head_ = fresh;
        } else {
            Node<T>* current = head_;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = fresh;
        }
        ++size_;
    }

    void deleteFront() override {
        if (head_ == nullptr) {
            std::cout << "LinkedList is empty." << std::endl;
            return;
        }
        Node<T>* doomed = head_;
        head_ = head_->next;
        delete doomed->data;
        delete doomed;
        --size_;
    }

    void deleteAnywhere(int position) override {
        if (position < 0 || position >= size_) {
            std::cout << "Invalid position." << std::endl;
            return;
        }
        if (position == 0) {
            deleteFront();
            return;
        }
        Node<T>* prev = head_;
        for (int i = 0; i < position - 1; ++i) {
            prev = prev->next;
        }
        Node<T>* doomed = prev->next;
        prev->next = doomed->next;
        delete doomed->data;
        delete doomed;
        --size_;
    }

    void reverse() override {
        Node<T>* prev = nullptr;
        Node<T>* current = head_;
        Node<T>* next = nullptr;
        while (current != nullptr) {
            next = current->next;   // save the rest of the list
            current->next = prev;   // flip the pointer
            prev = current;         // advance prev
            current = next;         // advance current
        }
        head_ = prev;
    }

    void concat(List<T>* other) override {
        LinkedList<T>* otherLL = dynamic_cast<LinkedList<T>*>(other);
        if (otherLL == nullptr) {
            std::cout << "Representation mismatch." << std::endl;
            return;
        }
        if (otherLL->head_ == nullptr) {
            return; // nothing to attach
        }
        if (head_ == nullptr) {
            head_ = otherLL->head_;
        } else {
            // Walk to the last node of *this
            Node<T>* current = head_;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = otherLL->head_;
        }
        size_ += otherLL->size_;
        otherLL->head_ = nullptr;
        otherLL->size_ = 0;
    }

    T* getFront() const override {
        if (head_ == nullptr) return nullptr;
        return head_->data;
    }

    bool isEmpty() const override { return head_ == nullptr; }
    int size() const override { return size_; }

    bool search(T* value) const override {
        Node<T>* current = head_;
        while (current != nullptr) {
            if (*current->data == *value) return true;
            current = current->next;
        }
        return false;
    }

    void print() const override {
        Node<T>* current = head_;
        while (current != nullptr) {
            std::cout << *current->data << ",";
            current = current->next;
        }
        std::cout << std::endl;
    }

    ~LinkedList() override {
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