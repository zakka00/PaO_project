#ifndef CONTAINER_H
#define CONTAINER_H

template <typename T>
class Container {
public:
    class Node {
    private:
        T data;
        Node* next;

    public:
        Node(T data, Node* next): data(data), next(next) {}
        ~Node()=default;
        T getData() const {return data;}
        Node& setData(T data) {this->data = data;return *this;}
        Node* getNext() const {return next;}
        Node& setNext(Node* next) {this->next = next;return *this;}
    };

    Container(): head(nullptr) {}
    ~Container() {clearAll();}

    unsigned int getSize() const {
        unsigned int size = 0;
        Node* n = head;
        while (n != nullptr) {
            n = n->getNext();
            size++;
        }
        return size;
    }

    Node* getHead() const {return head;}

    Container& add(T data) {
        Node* newNode = new Node(data, nullptr);
        if (!head) {
            head = newNode;
        }
        else{
            Node* current = head;
            while (current->getNext() != nullptr) {
                current = current->getNext();
            }
            current->setNext(newNode);
        }
        return *this;
    }

    Container& remove(T data) {
        Node* previous = nullptr;
        Node* current = head;
        while (current != nullptr) {
            if (current->getData() == data) {
                if (previous != nullptr) {
                    previous->setNext(current->getNext());
                }
                else {
                    head = current->getNext();
                }
                delete current->getData(); // elimino il product puntato sulla memoria
                delete current; // elimino il nodo che lo conteneva
                return *this;
            }
            previous = current;
            current = current->getNext();
        }
        return *this;
    }

    Container& clear() { // distrugge la lista, ma non gli oggetti puntati, quindi il data
        while (head != nullptr) {
            Node* next = head->getNext();
            delete head;
            head = next;
        }
        return *this;
    }

    Container& clearAll() { // distruzione completa, data compreso
        while (head != nullptr) {
            Node* next = head->getNext();
            delete head->getData(); // --> se usassi Int, Double ecc...si avrebbe UB, ma dato che uso sempre e solo
                                    // un puntatore a Product non c'è bisogno di fare un controllo in più ( std::is_pointer<T>::value )
            delete head;
            head = next;
        }
        return *this;
    }

private:
    Node* head;
};

#endif
