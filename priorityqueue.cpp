/* Name: Joe David
 * Emal: joe.david@student.tut.fi
 * Student Ref: 267598 */

#include "priorityqueue.h"

// Constructor of the PQ class
// When maximum_priority is defined, no item greater than maximum_priority
// will be added
PriorityQueue::PriorityQueue(int maximum_priority)
{
    head = NULL;
    max_priority = maximum_priority;
}

// Automatically clears the queue items and frees the memory
PriorityQueue::~PriorityQueue()
{
    clear();
}

// Clear all items from the queue
// Takes no argument
void PriorityQueue::clear()
{
    // If head is NULL, no need to clean the tree
    if (head != NULL) {
        // Start from head
        Node *curr = head;
        Node *next;

        // Iterate through next nodes until NULL is found
        while (curr != NULL) {
            next = curr->next;
            delete curr; // NOTE: MEMORY FREED
            curr = next;
        }

        // After deleting all nodes, set head to NULL
        head = NULL;
    }
}

// Address of the first element of the queue
Node *PriorityQueue::top()
{
    return head;
}

// Adds an string item with priority to the linked list
// Returns true if successfully added to the list
// Returns false if priority exceeds maximum_priority
bool PriorityQueue::push(const int priority, const string data)
{
    if (priority > this->max_priority) {
        cout << "Error: priority level must be an integer between 1-" << this->max_priority << endl;
        return false;
    }
    // If the head is null, put the item on top
    else if (head == NULL) {
        // Allocare item using new keyword
        Node *item = new Node;
        item->priority = priority;
        item->data = data;
        item->next = NULL;
        head = item;
        return true;
    }
    // If the priority of the top element is lower than the new element, put it on top too
    else if (top()->priority < priority) {
        // Allocare item using new keyword
        Node *item = new Node;
        item->priority = priority;
        item->data = data;
        item->next = head;
        head = item;
        return true;
    }
    // For items with lower or equal priority
    else {
        // Allocare item using new keyword
        Node *item = new Node;
        item->priority = priority;
        item->data = data;
        item->next = NULL;

        Node *curr = head;
        Node *prev = NULL;

        // Iterate through next items
        while (curr != NULL) {
            // When an item with lower priority is found
            if (item->priority > curr->priority) {
                // Insert the new item in the middle of them
                item->next = curr;
                prev->next = item;
                return true;
            }

            // Else keep moving forward
            prev = curr;
            curr = curr->next;
        }

        prev->next = item;

        return true;
    }
}

// Removes the item with maximum priority
// Returns true if item was removed
// Returns false if list was empty
bool PriorityQueue::pop()
{
    if (head == NULL) {
        return false;
    } else {
        // Allocare item using new keyword
        Node *item = head->next;
        // Clear the top node
        delete head; // NOTE: MEMORY FREED
        // Update head
        head = item;
        return true;
    }
}

// Erases tasks with running number
// Takes an integer as running number
bool PriorityQueue::erase(const int number)
{

    Node *curr = head;
    Node *pre = NULL;
    int running_number = 0;

    // Loop through next items
    while (curr != NULL) {
        // Increment running number
        running_number++;

        // When an item with matching running number is found
        if (running_number == number) {
            // If the item is on top
            if (pre == NULL) {
                Node *item = NULL;
                item = curr->next;
                delete curr; // NOTE: MEMORY FREED
                head = item;
            }
            // If the item is in the middle of the list
            else {
                Node *item = NULL;
                item = curr->next;
                delete curr; // NOTE: MEMORY FREED
                pre->next = item;
            }
            return true;
        }
        pre = curr;
        curr = curr->next;
    }
    return false;
}

// Prints the list to console when used with cout
ostream &operator << (ostream &out, const PriorityQueue &pq)
{
    if (pq.head == NULL) {
        return out;
    } else {
        Node *curr = pq.head;

        int inuse = INT_MAX;
        int running_number = 1;

        // Loop through next items
        while (curr != NULL) {
            // Print level of priority only once
            if (inuse != curr->priority) {
                inuse = curr->priority;
                cout << "Priority level " << inuse << ":" << endl;
            }

            // Print the running number, chore description and new line
            out << "  " << running_number
                << ". " << curr->data
                << endl;

            curr = curr->next;
            running_number++;
        }

        return out;
    }
}

//returns the max_priority variable
int PriorityQueue::get_max_priority()
{
    return max_priority;
}

//sets the max priority variable
void PriorityQueue::set_max_priority(int value)
{
    max_priority = value;
}
