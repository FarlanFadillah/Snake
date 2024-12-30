#pragma once
#include "Vec2.hpp"
class Node
{
private:
    Vec2 data;
    std::shared_ptr<Node> prevNode;
    std::shared_ptr<Node> nextNode;

public:
    Node() : prevNode(nullptr), nextNode(nullptr) {}
    Node(Vec2 e, std::shared_ptr<Node> prev, std::shared_ptr<Node> next)
        : data(e), prevNode(prev), nextNode(next) {
    }

    Vec2& getElement() { return data; }


    std::shared_ptr<Node>& getNext() { return nextNode; }
    std::shared_ptr<Node>& getPrev() { return prevNode; }

    void setPrev(const std::shared_ptr<Node> node) { prevNode = node; }
    void setNext(const std::shared_ptr<Node> node) { nextNode = node; }
};

