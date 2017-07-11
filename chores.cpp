/* Name: Joe David
 * Emal: joe.david@student.tut.fi
 * Student Ref: 267598 */

#include "chores.h"

// Remove leading and trailing spaces from any string
// Takes a reference to a string object
// Returns the trimmed string
string trim(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Constructor for Chores class
// initializes the prompt string
// Sets list initialized flag to false
Chores::Chores()
{
    prompt = "chores> ";
    initialized = false;
}

void Chores::loop()
{
    while (true) {
        // print the prompt
        cout << prompt;

        // Take a line into the command string and trim it
        command = "";
        getline(cin, command);
        trim(command);

        // Clear input buffer
        cin.clear();

        // Extract the first word of the line
        base = command.substr(0, command.find(" "));

        // We will store arguments and number found in every command
        args = "";
        number = 0;
        numberfound = false;
        argsfound = false;

        parse_command();

        if (base == "init")
            do_init();
        else if (base == "add")
            do_add();
        else if (base == "print")
            do_print();
        else if (base == "next")
            do_next();
        else if (base == "erase")
            do_erase();
        else if (base == "quit")
            break;

        // In case the input command is non of init, add, next, print, erase or quit
        // Warn about the invalid command.
        else if (base.size() > 1) {
            cout << "Error: no such command." << endl;
            base.clear();
        }
    }
}

void Chores::parse_command()
{
    // Check if there is any other arguments in the line
    // The number of spaces denotes the number of words in a line
    if (command.find(" ") != string::npos) {
        // If more than 1 spaces are found, it indicates that some arguments are found
        args = command.substr(command.find(" ") + 1, command.length());
        argsfound = true;

        // Try to extract number from the line
        // strtol function converts string to long numberrs using base 10
        char *end;
        string num = args.substr(0, args.find(" "));
        number = strtol(num.c_str(), &end, 10);

        // While extracting number, strtoul returns error if no valid number is found
        // Otherwise
        if (end != num.c_str()) {
            numberfound = true;

            // Find more arguments after any number is found
            if (args.find(" ") == string::npos) {
                args.clear();
                argsfound = false;
            } else {
                args = args.substr(args.find(" ") + 1, args.length());
                argsfound = true;
            }
        }
    }
}

void Chores::do_init()
{
    if (numberfound) {
        // Show error when no valid nonzero number is given to init command
        if (number <= 0)
            cout << "Error: it is not possible to create a priority list with 0 or less levels." << endl;
        // Clear any existing list and initialize new list with priority number
        else {
            cout << "New priority list with levels 1-" << number << " initialized." << endl;
            pq.clear();
            pq.set_max_priority(number);
            initialized = true;
        }
    } else {
        // Show error if init command is issued with no arguments
        if (!argsfound)
            cout << "Error: the number of priority levels is missing." << endl;
        else
            cout << "Error: the number of priority levels must be an integer larger than 0." << endl;
    }
    base.clear();
}

void Chores::do_add()
{
    // Do not add anything to the list if not initialized
    if (!initialized) {
        cout << "Error: initialize priority list first." << endl;
    } else if (numberfound) {
        // Check if priority with add command is lower or equal to max_priority
        if (number <= 0 or number > pq.get_max_priority())
            cout << "Error: priority level must be an integer between 1-" << pq.get_max_priority() << "." << endl;
        // If a valid priority is given along with add command, add it to list
        else {
            if (argsfound) {
                pq.push(number, args);
                cout << "New chore added to priority level " << number << "." << endl;
            } else {
                cout << "Error: chore description is missing." << endl;
            }
        }
    }
    // When provided invalid or nonzero numbers with add command, show error
    else if (argsfound) {
        cout << "Error: priority level must be an integer between 1-" << pq.get_max_priority() << "." << endl;
    } else {
        cout << "Error: priority level and chore description are missing." << endl;
    }
    base.clear();
}

void Chores::do_print()
{
    // Do not print anything if not initialized
    if (!initialized) {
        cout << "Error: initialize priority list first." << endl;
    }
    // Check if print command is given with extra arguments, show error
    else if (argsfound or numberfound) {
        cout << "Error: extra text after print command." << endl;
    } else
        cout << pq;

    base.clear();
}

void Chores::do_next()
{
    // Do not erase anything from the task if not initialized
    if (!initialized) {
        cout << "Error: initialize priority list first." << endl;
    } else if (argsfound or numberfound) {
        cout << "Error: extra text after next command." << endl;
    } else {
        // If list is empty, show that there is no chores left
        if (pq.top() == NULL) {
            cout << "--- no chores left ---" << endl;
        }
        // If list is initialized, show the top most chore name
        else {
            cout << pq.top()->data << endl;
            pq.pop();
        }
    }

    base.clear();
}

void Chores::do_erase()
{
    // Do not erase anything from the task if not initialized
    if (!initialized) {
        cout << "Error: initialize priority list first." << endl;
    } else if (numberfound) {
        // When erasing anything, check if running number is non zero
        if (number <= 0)
            cout << "Error: the running number must be larger than 0." << endl;
        // Otherwise allow erasing
        else {
            if (!pq.erase(number))
                cout << "Error: there is no such chore." << endl;
        }
    }
    // When erasing anything, check if running number is non zero
    else {
        if (!argsfound)
            cout << "Error: the running number is missing." << endl;
        else
            cout << "Error: the running number must be larger than 0." << endl;
    }

    base.clear();
}


