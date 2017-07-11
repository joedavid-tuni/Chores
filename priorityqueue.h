/* Name: Joe David
 * Emal: joe.david@student.tut.fi
 * Student Ref: 267598 */

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <ostream>
#include <iostream>

#define INT_MAX 2147483647

using namespace std;

// Each node consists of the following item
// An integer denoting the priority
// An string instance containing the chore
// A pointer to the next node
struct Node {
    int priority;
    string data;
    Node *next;
};

class PriorityQueue
{
private:
    Node *head;
    int max_priority;

public:

    // Constructor of the PQ class
    // When maximum_priority is defined, no item greater than maximum_priority
    // will be added
    PriorityQueue(int maximum_priority = INT_MAX);

    // Automatically clears the queue items and frees the memory
    ~PriorityQueue();

    // Get and Set the maximum allowed priority of the queue
    int get_max_priority();
    void set_max_priority(int value);

    // Clear all items from the queue
    // Takes no argument
    void clear();

    // Address of the first element of the queue
    Node *top();

    // Adds an string item with priority to the linked list
    // Returns true if successfully added to the list
    // Returns false if priority exceeds maximum_priority
    bool push(const int priority, const string data);

    // Removes the item with maximum priority
    // Returns true if item was removed
    // Returns false if list was empty
    bool pop();

    // Erases tasks with running number
    // Takes an integer as running number
    bool erase(const int number);

    // Prints the list to console when used with cout
    friend ostream &operator << (ostream &out, const PriorityQueue &ll);
};

#endif // PRIORITYQUEUE_H
