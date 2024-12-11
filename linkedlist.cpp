#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int _data) {
        data = _data;
        next = nullptr;
        prev = nullptr;
    }

    ~Node() {}
};

class LinkedList {
    Node* head;
    Node* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    void addNode(int _data) {
        Node* newNode = new Node(_data);
        if (head == nullptr) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    void display() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << "\t";
            current = current->next;
        }
        cout << endl;
    }

    void Remove(int _data) {
        Node* node = GetNode(_data);
        if (node == nullptr) {
            cout << "Not Found " << endl;
            return;
        }

        if (head == node) {
            if (head == tail) {
                head = tail = nullptr;
            } else {
                head = head->next;
                head->prev = nullptr;
            }
        } else if (tail == node) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            Node* A = node->prev;
            Node* B = node->next;
            A->next = B;
            B->prev = A;
        }

        delete node;
    }

    // 1. Insert node after a given node
    void InsertAfter(int data, int afterData) {
        Node* current = GetNode(afterData);
        if (current == nullptr) {
            cout << "Node with data " << afterData << " not found." << endl;
            return;
        }

        Node* newNode = new Node(data);
        newNode->next = current->next;
        newNode->prev = current;

        if (current->next != nullptr) {
            current->next->prev = newNode;
        } else {
            tail = newNode;
        }

        current->next = newNode;
    }

    // 2. Insert node before a given node
    void InsertBefore(int data, int beforeData) {
        Node* current = GetNode(beforeData);
        if (current == nullptr) {
            cout << "Node with data " << beforeData << " not found." << endl;
            return;
        }

        Node* newNode = new Node(data);
        newNode->next = current;
        newNode->prev = current->prev;

        if (current->prev != nullptr) {
            current->prev->next = newNode;
        } else {
            head = newNode;
        }

        current->prev = newNode;
    }

    // 3. Get number of nodes
    int GetCount() {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    // 4. Get data at a given index
    int GetDataByIndex(int index) {
        if (index < 0) {
            cout << "Invalid index." << endl;
            return -1;
        }

        int currentIndex = 0;
        Node* current = head;
        while (current != nullptr) {
            if (currentIndex == index) {
                return current->data;
            }
            currentIndex++;
            current = current->next;
        }

        cout << "Index out of bounds." << endl;
        return -1;
    }

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

private:
    Node* GetNode(int _data) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == _data) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};

int main() {
    LinkedList l;

    l.addNode(5);
    l.addNode(10);
    l.addNode(15);

    cout << "Initial list: ";
    l.display();

    cout << "\nInserting 7 after 5..." << endl;
    l.InsertAfter(7, 5);
    l.display();

    cout << "\nInserting 12 before 15..." << endl;
    l.InsertBefore(12, 15);
    l.display();

    cout << "\nNumber of nodes: " << l.GetCount() << endl;

    cout << "\nData at index :2 " << l.GetDataByIndex(2) << endl;

    return 0;
}
