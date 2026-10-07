#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <sstream>
#include <iostream>

// ============================================================
// STAGE 0 Tests
// ============================================================

/// Create a LegacyData union with an int (42). Call printLegacyData.
/// Verify the returned string matches "42".
void test_printLegacyData_int(void) 
{
    LegacyData data;
    data.i = 42;
    std::string res = printLegacyData(data, 'i');
    TEST_ASSERT_EQUAL_STRING("42", res.c_str());
}

/// Create a LegacyData union with a double (3.14). Call printLegacyData.
/// Verify the returned string matches "3.14".
void test_printLegacyData_double(void) 
{
    LegacyData data;
    data.d = 3.14;
    std::string res = printLegacyData(data, 'd');
    TEST_ASSERT_EQUAL_STRING("3.14", res.c_str());
}

// ============================================================
// STAGE 1 Tests
// ============================================================

/// Call createTwoStructNodes().
/// Verify head->value contains int 5 with type 'i', and head->nextPtr->value contains double ~3.14 with type 'd'.
/// Clean up allocated memory.
void test_createTwoStructNodes_links_correctly(void) 
{
    structNode* head = createTwoStructNodes();
    TEST_ASSERT_EQUAL_CHAR('i', head->typeData);
    TEST_ASSERT_EQUAL_INT(5, head->value.i);

    TEST_ASSERT_EQUAL_CHAR('d', head->nextPtr->typeData);
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 3.14, head->nextPtr->value.d);

    delete head->nextPtr;
    delete head;
}

// ============================================================
// STAGE 2 Tests
// ============================================================

/// Call createTwoClassNodes().
/// Verify head->value contains int 5 with type 'i', and head->nextPtr->value contains double ~3.14 with type 'd'.
/// Clean up allocated memory.
void test_createTwoClassNodes_links_correctly(void) 
{
    classNode* head = createTwoClassNodes();
    TEST_ASSERT_EQUAL_CHAR('i', head->typeData);
    TEST_ASSERT_EQUAL_INT(5, head->value.i);

    TEST_ASSERT_EQUAL_CHAR('d', head->nextPtr->typeData);
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 3.14, head->nextPtr->value.d);

    delete head->nextPtr;
    delete head;
}

// ============================================================
// STAGE 3 Tests
// ============================================================

/// Call createTwoTemplateNodes().
/// Verify head->value is 5 and head->nextPtr->value is 3.
/// Clean up allocated memory.
void test_createTwoTemplateNodes_links_correctly(void) 
{
    classNodeT<int>* head = createTwoTemplateNodes();

    TEST_ASSERT_EQUAL_INT(5, head->value);
    TEST_ASSERT_EQUAL_INT(3, head->nextPtr->value);

    delete head->nextPtr;
    delete head;
}

// ============================================================
// STAGE 4: LinkedList Tests
// ============================================================

/// Create a LinkedList. Add two nodes using addFirst.
/// Verify listLength() returns 2 after insertions.
void test_linkedList_addFirst_updates_counter(void) 
{
    LinkedList list;

    list.addFirst(new classNodeVariant(1));
    list.addFirst(new classNodeVariant(2));

    TEST_ASSERT_EQUAL_INT(2, list.listLength());
}

/// Create a LinkedList. Add nodes (10, then 20) using addLast.
/// Capture std::cout and verify elements appear in order ("10" before "20").
void test_linkedList_addLast_places_at_end(void) 
{
    LinkedList list;
    
    classNodeVariant* node1 = new classNodeVariant(10);
    classNodeVariant* node2 = new classNodeVariant(20);

    list.addLast(node1);
    list.addLast(node2);

    /// Help from Gemini
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    list.printList();

    std::cout.rdbuf(oldCout);
    std::string output = buffer.str();

    TEST_ASSERT_TRUE(output.find("10") != std::string::npos);
    TEST_ASSERT_TRUE(output.find("20") != std::string::npos);
    TEST_ASSERT_TRUE(output.find("10") < output.find("20"));
}

/// Create a LinkedList with an int, double, and string.
/// Call deleteValue() with the double value (3.14).
/// Verify list length decreases to 2 and second call returns -1.
void test_linkedList_deleteValue_removes_variant(void) 
{
    LinkedList list;
    list.addLast(new classNodeVariant(10));
    list.addLast(new classNodeVariant(3.14));
    list.addLast(new classNodeVariant(std::string("hello")));

    int res = list.deleteValue(3.14);
    TEST_ASSERT_EQUAL_INT(2, list.listLength());
    TEST_ASSERT_EQUAL_INT(-1, res);
}

/// Create a LinkedList and insert three nodes.
/// Call destroyList().
/// Verify listLength() becomes 0.
void test_linkedList_destroyList_clears_all(void) 
{
    LinkedList list;
    list.addLast(new classNodeVariant(1));
    list.addLast(new classNodeVariant(2));
    list.addLast(new classNodeVariant(3));

    list.destroyList();
    TEST_ASSERT_EQUAL_INT(0, list.listLength());
}

/// Create a LinkedList with nodes (10, 20, 30).
/// Call deleteFirst().
/// Verify listLength() becomes 2 and operation returns 0.
void test_linkedList_deleteFirst(void) 
{
    LinkedList list;
    list.addLast(new classNodeVariant(10));
    list.addLast(new classNodeVariant(20));
    list.addLast(new classNodeVariant(30));

    int res = list.deleteFirst();
    TEST_ASSERT_EQUAL_INT(2, list.listLength());
    TEST_ASSERT_EQUAL_INT(0, res);
}

/// Create a LinkedList with nodes (10, 20, 30).
/// Call deleteLast().
/// Verify listLength() becomes 2 and operation returns 0.
void test_linkedList_deleteLast(void) 
{
    LinkedList list;
    list.addLast(new classNodeVariant(10));
    list.addLast(new classNodeVariant(20));
    list.addLast(new classNodeVariant(30));

    int res = list.deleteLast();
    TEST_ASSERT_EQUAL_INT(2, list.listLength());
    TEST_ASSERT_EQUAL_INT(0, res);
}

/// Create a LinkedList with nodes (1, 2.5, "test").
/// Redirect std::cout buffer and call printList().
/// Verify printed output contains "1", "2.5" (or "2.50"), and "test".
void test_linkedList_printList(void) 
{
    LinkedList list;
    list.addLast(new classNodeVariant(1));
    list.addLast(new classNodeVariant(2.5));
    list.addLast(new classNodeVariant(std::string("test")));

    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    int res = list.printList();
    std::cout.rdbuf(oldCout);
    std::string output = buffer.str();

    /// std::string::npos mean not found (Gemini)
    TEST_ASSERT_TRUE(output.find("1") != std::string::npos);
    TEST_ASSERT_TRUE(output.find("2.5") != std::string::npos);
    TEST_ASSERT_TRUE(output.find("test") != std::string::npos);
}