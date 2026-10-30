#include <iostream>
#include "../h.files/DoublyList.h"

using namespace std;

void DoublyList::init() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void DoublyList::clear() {
    DoublyNode* curr = head;
    while (curr != nullptr) {
        DoublyNode* next_node = curr->next;
        delete curr;
        curr = next_node;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void DoublyList::push_head(const string& val) {
    DoublyNode* node = new DoublyNode;
    node->val = val;
    node->prev = nullptr;
    node->next = head;

    if (head != nullptr) {
        head->prev = node;
    } else {
        tail = node;
    }
    head = node;
    size++;
}

void DoublyList::push_tail(const string& val) {
    DoublyNode* node = new DoublyNode;
    node->val = val;
    node->next = nullptr;
    node->prev = tail;

    if (tail != nullptr) {
        tail->next = node;
    } else {
        head = node;
    }
    tail = node;
    size++;
}

bool DoublyList::insert_before(const string& target, const string& val) {
    DoublyNode* curr = head;
    while (curr != nullptr && curr->val != target) {
        curr = curr->next;
    }

    if (curr == nullptr) {
        return false;
    }

    if (curr == head) {
        push_head(val);
        return true;
    }

    DoublyNode* node = new DoublyNode;
    node->val = val;
    node->next = curr;
    node->prev = curr->prev;

    curr->prev->next = node;
    curr->prev = node;

    size++;
    return true;
}

bool DoublyList::insert_after(const string& target, const string& val) {
    DoublyNode* curr = head;
    while (curr != nullptr && curr->val != target) {
        curr = curr->next;
    }

    if (curr == nullptr) {
        return false;
    }

    if (curr == tail) {
        push_tail(val);
        return true;
    }

    DoublyNode* node = new DoublyNode;
    node->val = val;
    node->prev = curr;
    node->next = curr->next;

    curr->next->prev = node;
    curr->next = node;

    size++;
    return true;
}

string DoublyList::pop_head() {
    if (head == nullptr) {
        return "";
    }

    DoublyNode* temp = head;
    string val = temp->val;

    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }

    delete temp;
    size--;
    return val;
}

string DoublyList::pop_tail() {
    if (tail == nullptr) {
        return "";
    }

    DoublyNode* temp = tail;
    string val = temp->val;

    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }

    delete temp;
    size--;
    return val;
}

bool DoublyList::remove_val(const string& val) {
    DoublyNode* curr = head;
    while (curr != nullptr && curr->val != val) {
        curr = curr->next;
    }

    if (curr == nullptr) {
        return false;
    }

    if (curr == head) {
        pop_head();
        return true;
    }

    if (curr == tail) {
        pop_tail();
        return true;
    }

    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;

    delete curr;
    size--;
    return true;
}

bool DoublyList::find(const string& val) const {
    DoublyNode* curr = head;
    while (curr != nullptr) {
        if (curr->val == val) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

string DoublyList::get(int index) const {
    if (index < 0 || index >= size) {
        return "";
    }

    DoublyNode* curr = head;
    for (int i = 0; i < index; ++i) {
        curr = curr->next;
    }
    return curr->val;
}

void DoublyList::print() const {
    DoublyNode* curr = head;
    cout << "[";
    while (curr != nullptr) {
        cout << curr->val;
        if (curr->next != nullptr) {
            cout << " <-> ";
        }
        curr = curr->next;
    }
    cout << "]\n";
}