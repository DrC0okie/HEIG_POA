#include <utility>
#include "ShipList.hpp"

struct ShipList::Node {
    Ship* ship;
    Node* next;
};

ShipList::Iterator::Iterator(Node* head) {
    this->current = head;
}

[[nodiscard]] bool ShipList::Iterator::hasNext() const {
    return current != nullptr;
}

Ship* ShipList::Iterator::next() {
    if (current == nullptr) {
        throw std::out_of_range("Iterator has reached the end");
    }

    Node* tmp = current;
    current = current->next;
    return tmp->ship;
}

void ShipList::swap(ShipList& other) noexcept {
    // enable ADL (not necessary in our case, but good practice)
    using std::swap;

    swap(head, other.head);
    swap(tail, other.tail);
}

ShipList& ShipList::operator=(ShipList other) {
    swap(other);
    return *this;
}

ShipList::ShipList() : head(nullptr), tail(nullptr) {}

ShipList::ShipList(const ShipList& other) : head(nullptr), tail(nullptr) {
    for (Node* current = other.head; current != nullptr; current = current->next) {
        add(current->ship);
    }
}

ShipList::ShipList(ShipList&& other) noexcept
        : head(std::exchange(other.head, nullptr)), tail(std::exchange(other.tail, nullptr)) {}

ShipList::~ShipList() {
    clear();
}

Ship* ShipList::get(std::size_t index) const {
    if (head == nullptr) {
        throw std::out_of_range("The list is empty");
    }

    Node* current = head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
        if (current == nullptr) {
            throw std::out_of_range("Index out of range");
        }
    }
    return current->ship;
}

void ShipList::add(Ship* ship) {
    if (ship == nullptr) {
        throw std::invalid_argument("Cannot add a null ship to the list.");
    }

    Node* newNode = new Node{ship, nullptr};
    if (head == nullptr) {
        head = newNode;
    } else {
        tail->next = newNode;
    }
    tail = newNode;
}

bool ShipList::remove(Ship* ship) {
    if (ship == nullptr) {
        throw std::invalid_argument("The given ship to remove is null.");
    }

    Node* previous = nullptr;
    Node* current = head;

    while (current != nullptr) {
        if (current->ship == ship) {
            if (current == head) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            // Update tail to the previous node, which can be nullptr if the list becomes empty.
            if (current == tail) {
                tail = previous;
            }

            delete current;
            return true;
        }
        previous = current;
        current = current->next;
    }

    return false;
}

void ShipList::clear() {
    Node* current = head;
    Node* next;

    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}

bool ShipList::contains(const Ship* ship) const {
    if (ship == nullptr) {
        throw std::invalid_argument("Cannot check if the lists contains a null ship");
    }
    Node* current = head;
    while (current != nullptr) {
        if (current->ship == ship) {
            return true;
        }
        current = current->next;
    }
    return false;
}

ShipList::Iterator ShipList::getIterator() const {
    return Iterator(head);
}
