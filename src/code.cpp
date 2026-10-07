// ============================================================
// CSCI 232 Assignment 05 – Evolution of Data Structures
// Student Implementation
// ============================================================
// Author: [Sebastian Cardullo]
// ============================================================

#include "code.hpp"
#include <iostream>
#include <format>

// ============================================================
// STAGE 0: Legacy C Union
// ============================================================

/// Converts a LegacyData union to a formatted string.
/// Format specs:
/// 'i' -> integer value as string (e.g., "42")
/// 'd' -> double value formatted to 2 decimal places (e.g., "3.14")
/// 'c' -> string pointer content (or "nullptr" if cPtr is null)
/// default -> "unknown"

std::string printLegacyData(LegacyData data, char type) {
    switch (type) {
        case 'i':
            return std::to_string(data.i);
        case 'd':
            return std::format("{:.2f}", data.d);
        case 'c':
            if (data.cPtr != nullptr) {
                return std::string(data.cPtr);
            } else {
                return "nullptr";
            }
        default:
            return "unknown";
    }
}

// ============================================================
// STAGE 1: C-Style Struct
// ============================================================

/// Initializes a structNode with value, type indicator, and nullptr nextPtr.
void initStructNode(structNode* nPtr, LegacyData val, char type) {
    if (nPtr == nullPtr){
        return;
    }
    
    nPtr->value = val;
    nPtr->typeData = type;
    nPtr->nextPtr = nullptr;
}

/// Dynamically allocates two structNodes.
/// Node 1: int 5 ('i')
/// Node 2: double 3.14 ('d')
/// Links Node 1 -> Node 2 -> nullptr
/// Returns pointer to Node 1.
structNode* createTwoStructNodes() {
    structNode *node1 = new structNode;
    structNode *node2 = new structNode;

    LegacyData val1;
    val1.i = 5;
    initStructNode (node1, val1, 'i');

    LegacyData val2;
    val2.d = 3.14;
    initStructNode (node2, val2, 'd');

    node1->nextPtr = node2;
    return node1;
}

// ============================================================
// STAGE 2: Early C++ Class (Classic Constructor)
// ============================================================

/// Constructor: Assign fields inside curly braces.
/// DO NOT use member initializer lists here!

// uncomment the following code to implement the classNode constructor

classNode::classNode(LegacyData val, char type) {
    value = val;
    typeData = type;
    nextPtr = nullptr;
}

/// Dynamically allocates two classNodes (int 5, double 3.14) and links them.
classNode* createTwoClassNodes() {
    LegacyData val1;
    val1.i = 5;
    classNode *node1 = new classNode(val1, 'i');

    LegacyData val2;
    val2.d = 3.14;
    classNode *node2 = new classNode(val2, 'd');

    node1->nextPtr = node2;
    return node1;
}

// ============================================================
// STAGE 3: C++98 Templates
// ============================================================

/// Dynamically allocates two classNodeT<int> objects (int 5, int 3) and links them.
classNodeT<int>* createTwoTemplateNodes() {
    classNodeT<int> *node1 = new classNodeT<int>(5);
    classNodeT<int> *node2 = new classNodeT<int>(3);

    node1->nextPtr = node2;
    return node1;

}

// ============================================================
// STAGE 4: C++17 Variant and LinkedList Manager
// ============================================================

// uncomment the following code to implement the LinkedList methods

LinkedList::LinkedList() {
    headPtr = nullPtr;
    counter = 0;
}

LinkedList::~LinkedList() {
    destroyList();
}
//uncoment the following code to implement the LinkedList methods

void LinkedList::destroyList() {
    classNodeVariant *current = headPtr;
    while (current != nullptr){
        classNodeVariant *temp = current;
        current = current->nextPtr;
        delete temp;
    }
    headPtr = nullptr;
    counter = 0;
}

int LinkedList::addFirst(classNodeVariant* newNodePtr) {
    if (newNodePtr == nullptr){
        return -1;
    }
    
    newNodePtr->nextPtr = headPtr;
    headPtr = newNodePtr;
    counter++;
    return 0;
}

int LinkedList::addLast(classNodeVariant* newNodePtr) {
    if (newNodePtr == nullptr) {
        return -1;
    }
    newNodePtr->nextPtr = nullptr;
    if (headPtr == nullptr) {
        headPtr = newNodePtr;
    } else {
        classNodeVariant* temp = headPtr;
        while (temp->nextPtr != nullptr) {
            temp = temp->nextPtr;
        }
        temp->nextPtr = newNodePtr;
    }
    counter++;
    return 0;
}
int LinkedList::deleteFirst() {
    if (headPtr == nullptr) {
        return -1;
    }
    classNodeVariant* temp = headPtr;
    headPtr = headPtr->nextPtr;
    delete temp;
    counter--;
    return 0;
}
int LinkedList::deleteLast() {
    if (headPtr == nullptr) {
        return -1;
    }
    if (headPtr->nextPtr == nullptr) {
        delete headPtr;
        headPtr = nullptr;
        counter--;
        return 0;
    }

    classNodeVariant *temp = headPtr;
    while (temp->nextPtr != nullptr){
        temp = temp->nextPtr;
    }
    delete temp->nextPtr;
    temp->nextPtr = nullptr;
    counter--;
    return 0;
}
int LinkedList::deleteValue(ModernData targetValue) {
    if (headPtr == nullptr) {
        return -1;
    }

    if (headPtr->value == targetValue) {
        classNodeVariant* temp = headPtr;
        headPtr = headPtr->nextPtr;
        delete temp;
        counter--;
        return 0;
    }

    classNodeVariant* current = headPtr;
    while (current->nextPtr != nullptr && current->nextPtr->value != targetValue) {
        current = current->nextPtr;
    }

    if (current->nextPtr != nullptr) {
        classNodeVariant* temp = current->nextPtr;
        current->nextPtr = temp->nextPtr;
        delete temp;
        counter--;
        return 0;
    }

    return -1;
}
int LinkedList::printList() {
    if (headPtr == nullptr) {
        return -1;
    }

    classNodeVariant* current = headPtr;
    while (current != nullptr) {
        if (std::holds_alternative<int>(current->value)) {
            std::cout << std::get<int>(current->value);
        } else if (std::holds_alternative<double>(current->value)) {
            std::cout << std::get<double>(current->value);
        } else if (std::holds_alternative<std::string>(current->value)) {
            std::cout << std::get<std::string>(current->value);
        }

        if (current->nextPtr != nullptr) {
            std::cout << " ";
        }
        current = current->nextPtr;
    }
    std::cout << std::endl;
    return 0;
}
int LinkedList::listLength() {
    return counter;
}