//!  Copyright [2017] <Copyright relldaXY>"
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! Class CircularList
/*!
 *  this is a circular list linked by reference. It's similar as linkedList, but 
 *  the main diferrence is that the last element point to first element
*/
class CircularList {
 public:
    CircularList() {
        head = nullptr;
        size_ = -1;
    }
    ~CircularList() {
        clear();
    }
    //! method clear
    /*!
        While the list is empty is false the elements go out from list
    */
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }
    //! method push back
    /*!
        Insert one element in the last position of circular list
    */
    void push_back(const T& data) {
        if (empty()) {
            head = new Node(data, NULL);
            size_ = 0;
        } else {
            Node *newNode = new Node(data);
            Node *aux = head;
            for (int i = 1 ; i <= size_; i++) {
                 aux = aux->next();
            }
            aux->next(newNode);
            newNode->next(head);
            size_++;
        }
    }
    //! method push front
    /*!
        insert one data in the first position in circular list
    */
    void push_front(const T& data) {
        if (empty()) {
            head = new Node(data);
            size_ = 0;
        } else {
            Node * newNode = new Node(data);
            newNode->next(head);
            head = newNode;
            size_++;
            Node * aux = head;
            for (int i = 1; i <= size_; i++) {
                aux = aux->next();
            }
            aux->next(head);
        }
    }
    //! method insert
    /*!
        Insert one data by index
    */
    void insert(const T& data, std::size_t index) {
        if (index > (size_+1)|| index < 0) {
            throw std::out_of_range("Invalid index");
        } else if (index == 0) {
            push_front(data);
        } else if (index == (size_+1)) {
            push_back(data);
        } else {
            Node *previous, *newNode;
            newNode = new Node(data, NULL);
            if (newNode == NULL) {
                throw std::out_of_range("Full memory");
            }
            previous = head;
            for (int i = 1; i < index; i++) {
                previous = previous->next();
            }
            newNode = new Node(data, NULL);
            newNode->next(previous->next());
            previous->next(newNode);
            size_++;
        }
    }
    //! method insert_sorted
    /*!
        Sort one element before insert into circular list 
    */
    void insert_sorted(const T& data) {
        Node *current;
        int pos = 0;
        if (empty()) {
            push_front(data);
        } else {
            current = head;
            while (data > current->data() && pos < size()) {
                pos++;
                current = current->next();
            }
            if (data < current->data()) {
                insert(data, pos);
            } else {
                push_back(data);
            }
        }
    }
    //! method at
    /*!
        return onde data by index
    */
    T& at(std::size_t index) {
        Node* indexNode;
        if (index < 0) {
            throw std::out_of_range("Invalid index");
        } else if (index == -1) {
            throw std::out_of_range("Invalid Index");
        } else if (empty()) {
            throw std::out_of_range("Empty List");
        } else {
            if (index == 0) {
                return head -> data();
            } else {
                indexNode = head;
            for (int i = 1; i <= index; i++) {
                indexNode = indexNode->next();
            }
            return indexNode->data();
            }
        }
    }
    //! method at
    /*!
        return onde data by index
    */
    const T& at(std::size_t index) const {
        Node* previousNode;
        if (index < 0) {
            throw std::out_of_range("Invalid index");
        } else if (index == -1) {
            throw std::out_of_range("Invalid Index");
        } else if (empty()) {
            throw std::out_of_range("Empty List");
        } else {
            if (index == 0) {
                return head -> data();
            } else {
                previousNode = head;
            for (int i = 1; i <= index; i++) {
                previousNode = previousNode->next();
            }
            return previousNode->data();
            }
        }
    }
    //! method pop
    /*!
        pop one element by index
    */
    T pop(std::size_t index) {
        Node* previousNode, *deleteNode;
        T data;
        if (index < 0 || index > size_) {
            throw std::out_of_range("Invalid index");
        } else {
        if (index == 0) {
            return pop_front();
        } else if (index == size_) {
            return pop_back();
        } else {
            previousNode = head;
            for (int i = 1; i < index; i++) {
                previousNode = previousNode -> next();
            }
            deleteNode = previousNode -> next();
            data = deleteNode -> data();
            previousNode -> next(deleteNode->next());
            size_--;
            delete deleteNode;
            return data;
        }
        }
    }
    //! method pop_back
    /*!
        remove the tail of circular list
    */
    T pop_back() {
        T data;
        if (empty()) {
            throw std::out_of_range("Empty List");
        } else if (size() == 1) {
            data = head->data();
            head = NULL;
            size_--;
            return data;
        } else {
            Node *lastNode;
            Node *deleteNode;
            lastNode = head;
            for (int i = 1; i < size_; i++) {
                lastNode = lastNode->next();
            }
            deleteNode = lastNode->next();
            data = deleteNode->data();
            lastNode->next(head);
            delete deleteNode;
            size_--;
            return data;
        }
    }
    //! method pop_front
    /*!
        remove the first data from circular list
    */
    T pop_front() {
        T data;
        if (empty()) {
            throw std::out_of_range("Empty List");
        } else if (size() == 1) {
            data = head->data();
            head = NULL;
            size_ = -1;
            return data;
        } else {
            Node* newHead;
            newHead = head->next();
            data = head->data();
            delete head;
            size_--;
            head = newHead;
            Node *aux = head;
            for (int i = 1; i <=size_ ; i++) {
                aux = aux->next();
            }
            aux->next(head);
            return data;
        }
    }
    //! method remove
    /*!
        remove one element by data from circular list
    */
    void remove(const T& data) {
        if (empty()) {
            throw std::out_of_range("Empty List");
        } else {
            pop(find(data));
        }
    }
    //! method empty
    /*!
        verify is one element is on circular list
    */
    bool empty() const {
        return size_ == -1;
    }
    //! method contains
    /*!
        verify if one element exist in circular list
    */
    bool contains(const T& data) const {
        Node *current;
        if (empty()) {
            throw std::out_of_range("Empty list");
        } else {
            current = head;
            for (int i = 1; i <= size_ ; i++) {
                if (current->data() == data) {
                    return true;
                } else {
                    current = current->next();
                }
            }
            return false;
        }
    }
    //! method find
    /*!
        return the index of one data that is on circular list
    */
    std::size_t find(const T& data) const {
        Node* dataNode;
        if (empty()) {
            throw std::out_of_range("Empty list");
        } else {
            dataNode = head;
            for (int i = 0; i <= size_ ; i++) {
                if (dataNode->data() == data) {
                    return i;
                } else {
                    dataNode = dataNode->next();
                }
            }
        }
        return size();
    }
    //! method size
    /*!
        return the size of circular list
    */
    std::size_t size() const {
        return (size_ + 1);
    }

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {   // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* head{nullptr};
    std::size_t size_{-1u};
};

}  // namespace structures

#endif
