#include "Manager.h"

Manager::Manager() // Constructor
{
}
Manager::~Manager() // Destructor
{
}

void Manager::run(const char *command)
{
    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt");
    if (!fcmd)
    {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    // Run command
    char buffer[256];
    char *cmd;

    // Process commands from the command file line by line
    while (fcmd.getline(buffer, sizeof(buffer)))
    {
        cmd = strtok(buffer, " "); // Extract the command from the line

        // Check and execute the command based on its type
        if (strcmp(cmd, "LOAD") == 0)
        {
            if (!LOAD())
            {
                // Command executed successfull
            }
            else
            {
                PrintErrorCode(100); // Print an error code for the command
            }
        }
        else if (strcmp(cmd, "ADD") == 0)
        {
            char *name;
            int age = 0;
            char *date;
            char *termtype;
            name = strtok(NULL, " ");
            age = stoi(strtok(NULL, " "));
            date = strtok(NULL, " ");
            termtype = strtok(NULL, " ");

            // Check for missing or invalid arguments
            if (name == NULL || age == 0 || date == NULL || termtype == NULL)
            {
                PrintErrorCode(200); // Print an error code for the command
            }
            if (!ADD(name, age, date, termtype))
            {
                // Command executed successfull
            }
            else
            {
                PrintErrorCode(200); // Print an error code for the command
            }
        }
        else if (strcmp(cmd, "QPOP") == 0)
        {
            if (!QPOP())
            {
                PrintSuccess(cmd); // Command executed successfull
            }
            else
            {
                PrintErrorCode(300); // Print an error code for the command
            }
        }
        else if (strcmp(cmd, "SEARCH") == 0)
        {
            char *name;
            name = strtok(NULL, " ");
            if (!SEARCH(name))
            {
                // Command executed successfull
            }
            else
            {
                PrintErrorCode(400); // Print an error code for the command
            }
        }
        else if (strcmp(cmd, "PRINT") == 0)
        {
            char *data;
            data = strtok(NULL, " ");
            if (!PRINT(data, &flog))
            {
                // Command executed successfull
            }
            else
            {
                PrintErrorCode(500); // Print an error code for the command
            }
        }
        else if (strcmp(cmd, "DELETE") == 0)
        {
            char *deletebuffer = strtok(NULL, "\0");
            if (DELETE(deletebuffer))
            {
                PrintSuccess(cmd); // Command executed successfull
            }
            else
            {
                PrintErrorCode(600); // Print an error code for the command
            }
        }
        else if (strcmp(cmd, "EXIT") == 0)
        {
            PrintSuccess(cmd); // Command executed successfull
        }
        else
        {
            PrintErrorCode(1000); // Print an error code for an unknown command
        }
    }

    fcmd.close();
    flog.close();
    return;
}

void Manager::PrintSuccess(const char *cmd) // Function to print a success message for a command
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl
         << endl;
}

void Manager::PrintErrorCode(int num) // Function to print an error code for a command
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============" << endl
         << endl;
}

int Manager::LOAD()
{
    ifstream dataFile("data.txt"); // Open the data.txt file
    if (!dataFile)                 // Check if the file exists
    {
        flog << "Error: data.txt not found." << endl;
        PrintErrorCode(100); // Print an error code
        return 0;
    }

    if (memberQueue.full()) // Check if the Member_Queue is full
    {
        flog << "Error: Member_Queue is full." << endl;
        PrintErrorCode(100); // Print an error code
        dataFile.close();
        return 0;
    }

    char buffer[100];
    flog << "===== LOAD =====" << endl;

    // Read data from 'data.txt' line by line
    while (dataFile.getline(buffer, sizeof(buffer)))
    {
        char *token = strtok(buffer, "\n");

        // Extract member data from the line
        string name = strtok(token, " ");
        string age_str = strtok(NULL, " ");
        int age = stoi(age_str);
        string date = strtok(NULL, " ");
        string termtype = strtok(NULL, " ");

        bool valid = true;

        // Validate the member data
        if (name.length() > 20 || !islower(name[0]))
        {
            valid = false;
        }
        if (age < 10 || age > 99)
        {
            valid = false;
        }
        if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        {
            valid = false;
        }
        if (termtype.length() != 1 || !isupper(termtype[0]) || (termtype[0] != 'A' && termtype[0] != 'B' && termtype[0] != 'C' && termtype[0] != 'D'))
        {
            valid = false;
        }

        // Create a MemberQueueNode with the valid member data and push it into the Member_Queue
        MemberQueueNode member(name, age, date, termtype[0]);
        memberQueue.push(member);
        flog << member.getName() << "/" << member.getAge() << "/" << member.getDate() << "/" << member.getTermtype() << endl;
    }

    flog << "===============" << endl;
    dataFile.close(); // Close the data.txt file

    return 0; // Return 0 to indicate successful data loading
}

int Manager::ADD(char *name, int age, char *date, char *termtype)
{
    if (name == nullptr || age < 10 || age > 99 || date == nullptr || termtype == nullptr) // Check data exist
    {
        PrintErrorCode(200); // Print an error code
    }

    // Create local variables to store the input data
    char _name[100];
    char _date[100];
    char _termtype[10];

    // Copy the input data into local variables
    strcpy(_name, name);
    strcpy(_date, date);
    strcpy(_termtype, termtype);

    // Create a MemberQueueNode using the local variables and push it into the Member_Queue
    MemberQueueNode member(_name, age, _date, _termtype[0]);
    memberQueue.push(member);

    flog << "===== ADD =====" << endl;
    flog << _name << "/" << age << "/" << _date << "/" << _termtype << endl;
    flog << "===============" << endl;

    return 0;
}

int Manager::QPOP()
{
    if (memberQueue.empty()) // Check if the Member_Queue is empty
    {
        cout << "Error: Member_Queue is empty." << endl;
        PrintErrorCode(300); // Print an error code
        return 0;
    }

    while (!memberQueue.empty()) // Process all elements in the Member_Queue
    {
        MemberQueueNode data = memberQueue.front(); // Get the front data from the Member_Queue
        termList.insert(data);                      // Add data to the Terms_List
        nameBST.insert(data);                       // Add data to the Name_BST

        memberQueue.pop(); // Remove the front node from the queue
    }
    return 0;
}

int Manager::SEARCH(char *name)
{
    flog << "===== SEARCH =====" << endl;
    if (nameBST.search(name, &flog) == 0) // Search for the specified name in the Name_BST
    {
        PrintErrorCode(400); // Print an error code
    }
    flog << "===============" << endl;
    return 0;
}

int Manager::PRINT(char *data, ofstream *flog)
{
    if (strcmp(data, "NAME") == 0)
    {
        if (nameBST.getRoot() != NULL)
        {
            *flog << "===== PRINT =====" << endl;
            *flog << "NAME_BST" << endl;
            nameBST.print(flog); // Print the contents of the Name_BST
            *flog << "===============" << endl;
        }
        else
        {
            PrintErrorCode(500);
        }
    }
    else
    {
        if (termList.getHead() != NULL)
        {
            *flog << "===== PRINT =====" << endl;
            *flog << "Terms_BST " << data[0] << endl;
            termList.searchprint(data[0], flog); // Print the contents of the Terms_BST based on the specified term type
            *flog << "===============" << endl;
        }
        else
        {
            PrintErrorCode(500);
        }
    }
    return 0;
}

int Manager::DELETE(char *data)
{
    // Create local variables to store data for deletion
    char *Name_origin = new char[20];
    char *end_date_origin = new char[20];
    char *Name = new char[20];
    char *end_date = new char[20];
    char *deletedata = strtok(data, " ");
    int flag = 0;

    if (strcmp(deletedata, "DATE") == 0)
    {
        // Parse and extract end_date_origin from the input data
        end_date_origin = strtok(NULL, " ");

        while (termList.deletelist(end_date_origin, Name)) // Delete entries from Terms_LIST and Name_BST based on end_date
        {
            flag++;
            if (!nameBST.deletename(0, nameBST.getRoot(), end_date, Name))
            {
                PrintErrorCode(600); // Print an error code
            }
        }
    }
    else
    {
        Name_origin = strtok(NULL, " ");                                      // Parse and extract Name_origin from the input data
        if (!nameBST.deletename(0, nameBST.getRoot(), end_date, Name_origin)) // Delete entries from Name_BST and Terms_LIST based on name
        {
            PrintErrorCode(600); // Print an error code
        }
        else
        {
            flag = termList.deletelistname(Name_origin); // Update the flag based on the number of entries deleted from Terms_LIST
            if (flag == 0)
            {
                PrintErrorCode(600); // Print an error code
            }
        }
    }
    return flag; // Return the number of entries deleted
}
