#pragma once
#include <iostream>
#include "List.h"

template <typename T>
class ArrayList : public List<T> {
public:
    ArrayList() : size_(0) {}

    void addFront(T* value) override {
        if (size_ >= CAPACITY) {
            std::cout << "ArrayList is full." << std::endl;
            return;
        }
        for (int i = size_; i > 0; --i) {
            data_[i] = data_[i - 1];
        }
        data_[0] = value;
        ++size_;
    }

    void addAnywhere(int position, T* value) override {
        if (position < 0 || position > size_) {
            std::cout << "Invalid position." << std::endl;
            return;
        }
        if (size_ >= CAPACITY) {
            std::cout << "ArrayList is full." << std::endl;
            return;
        }
        // Shift elements [position, size_) one slot to the right.
        // Must go from the back toward position, otherwise we'd overwrite
        // data_[i] before it's been copied to data_[i+1].
        for (int i = size_; i > position; --i) {
            data_[i] = data_[i - 1];
        }
        data_[position] = value;
        ++size_;
    }

    void addBack(T* value) override {
        if (size_ >= CAPACITY) {
            std::cout << "ArrayList is full." << std::endl;
            return;
        }
        data_[size_] = value;
        ++size_;
    }

    void deleteFront() override {
        if (size_ == 0) {
            std::cout << "ArrayList is empty." << std::endl;
            return;
        }
        delete data_[0];
        for (int i = 0; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        --size_;
    }

    void deleteAnywhere(int position) override {
        if (position < 0 || position >= size_) {
            std::cout << "Invalid position." << std::endl;
            return;
        }
        delete data_[position];
        // Shift elements [position+1, size_) one slot to the left.
        // Must go forward, otherwise we'd overwrite data_[i] before reading it.
        for (int i = position; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        --size_;
    }

    void reverse() override {
        int left = 0;
        int right = size_ - 1;
        while (left < right) {
            T* temp = data_[left];
            data_[left] = data_[right];
            data_[right] = temp;
            ++left;
            --right;
        }
    }

    void concat(List<T>* other) override {
        ArrayList<T>* otherArr = dynamic_cast<ArrayList<T>*>(other);
        if (otherArr == nullptr) {
            std::cout << "Representation mismatch." << std::endl;
            return;
        }
        if (size_ + otherArr->size_ > CAPACITY) {
            std::cout << "Not enough capacity." << std::endl;
            return;
        }
        for (int i = 0; i < otherArr->size_; ++i) {
            data_[size_ + i] = otherArr->data_[i];
        }
        size_ += otherArr->size_;
        otherArr->size_ = 0;   // ownership transferred; don't double-delete
    }

    T* getFront() const override {
        if (size_ == 0) return nullptr;
        return data_[0];
    }

    bool isEmpty() const override { return size_ == 0; }
    int size() const override { return size_; }

    bool search(T* value) const override {
        for (int i = 0; i < size_; ++i) {
            if (*data_[i] == *value) return true;
        }
        return false;
    }

    void print() const override {
        for (int i = 0; i < size_; ++i) {
            std::cout << *data_[i] << ",";
        }
        std::cout << std::endl;
    }

    ~ArrayList() override {
        for (int i = 0; i < size_; ++i) {
            delete data_[i];
        }
    }

private:
    static const int CAPACITY = 20;
    T* data_[CAPACITY];
    int size_;
};