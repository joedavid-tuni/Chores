/* Name: Joe David
 * Emal: joe.david@student.tut.fi
 * Student Ref: 267598 */

#ifndef CHORES_H
#define CHORES_H

#include "priorityqueue.h"
#include <cstdlib>

class Chores
{
private:
    PriorityQueue pq;
    string prompt;
    bool initialized;

    // Members used by the commands for various purpose
    string args;
    string base;
    string command;
    int number;
    bool numberfound;
    bool argsfound;

public:
    // Constructs Chores class with default prompt string
    Chores();

    // Prompts the user to create Priority Queues
    // Available methods "init", "add", "erase", "next" and "quit"
    // Takes no arguments, returns nothing
    void loop();

    // Reads the whole input command, splits them into numbers
    // and arguments for sub-commands
    void parse_command();

    // Executes the commands in sub modules
    void do_init();
    void do_add();
    void do_print();
    void do_next();
    void do_erase();
};

#endif // CHORES_H
