#include "includes.h"

#define TASK_STK_SIZE 512
#define MAX_TITLE_LENGTH 50
#define MAX_AUTHOR_LENGTH 50
#define MAX_BOOKS 100

// Stack memory for Task
OS_STK Task1Stk[TASK_STK_SIZE];
OS_STK Task2Stk[TASK_STK_SIZE];
OS_STK Task3Stk[TASK_STK_SIZE];
OS_STK Task4Stk[TASK_STK_SIZE];
OS_STK Task5Stk[TASK_STK_SIZE];

OS_EVENT* Semaphore; // Semaphore variable declaration
OS_EVENT* MessageQueue; // Message queue variable declaration
void* QueueMem[10];

void Task1(void* pdata); // User interface task
void Task2(void* pdata); // Book borrowing task
void Task3(void* pdata); // Book returning task
void Task4(void* pdata); // Book search task
void Task5(void* pdata); // Book reservation task

void DisplayMenu(void); // Function to display the menu
void InitializeLibrary(); // Function to initialize the library

typedef struct
{
    char title[MAX_TITLE_LENGTH]; // Title of the book
    char author[MAX_AUTHOR_LENGTH]; // Author of the book
    char shelf; // Shelf where the book is located
    int is_borrowed; // Flag indicating whether the book is borrowed or not
    INT32U return_due; // Due date for book return
} Book;

Book library[MAX_BOOKS]; // Array to store all books in the library
char bookTitle[MAX_TITLE_LENGTH]; // Variable to store the title of the book to be borrowed

int main(void)
{
    OSInit(); // Initialize the real-time operating system

    InitializeLibrary(); // Initialize the library

    Semaphore = OSSemCreate(1); // Create a semaphore

    MessageQueue = OSQCreate(QueueMem, 10); // Create a message queue

    OSTaskCreate(Task1, (void*)0, &Task1Stk[TASK_STK_SIZE - 1], 1); // Create tasks
    OSTaskCreate(Task2, (void*)0, &Task2Stk[TASK_STK_SIZE - 1], 2);
    OSTaskCreate(Task3, (void*)0, &Task3Stk[TASK_STK_SIZE - 1], 3);
    OSTaskCreate(Task4, (void*)0, &Task4Stk[TASK_STK_SIZE - 1], 4);
    OSTaskCreate(Task5, (void*)0, &Task5Stk[TASK_STK_SIZE - 1], 5);

    OSStart(); // Start multitasking

    return 0;
}

void DisplayMenu(void)
{
    printf("\n--- Library System ---\n");
    printf("1. Search for a book\n");
    printf("2. Reserve a book\n");
    printf("3. Borrow a book\n");
    printf("4. Return a book\n");
    printf("5. Exit\n");
    printf("Select an option: ");
}

void Task1(void* pdata)
{
    INT16U i;
    char choice;

    // Loop indefinitely to display the menu and handle user input
    for (i = 0; ; i++)
    {
        DisplayMenu();

        while (!kbhit())
        {
            OSTimeDly(5); // Wait for user input with a delay
        }

        choice = getch(); // Read the user input

        switch (choice)
        {
        case '1':
            printf("You selected book search.\n"); // task 4
            OSTaskResume(4);
            break;
        case '2':
            printf("You selected book reservation.\n"); // task 5
            OSTaskResume(5);
            break;
        case '3':
            printf("You selected book borrowing.\n"); // task 2
            OSTaskResume(2);
            printf("Enter the title of the book to borrow: ");
            scanf(" %[^\n]", bookTitle);
            bookTitle[strcspn(bookTitle, "\n")] = 0;
            break;
        case '4':
            printf("You selected book returning.\n"); // task 3
            OSTaskResume(3);
            break;
        case '5':
            printf("Exiting the menu...\n");
            return;
        default:
            printf("Invalid input. Please select again.\n");
            break;
        }
        OSTimeDly(2); // Delay to avoid rapid menu display
    }
}

// Initialize the library with some sample books
void InitializeLibrary()
{
    strcpy(library[0].title, "Demian");
    strcpy(library[0].author, "Hermann Hesse");
    library[0].shelf = 'A';
    library[0].is_borrowed = 0;

    strcpy(library[1].title, "Animal Farm");
    strcpy(library[1].author, "George Orwell");
    library[1].shelf = 'B';
    library[1].is_borrowed = 0;

    strcpy(library[2].title, "1984");
    strcpy(library[2].author, "George Orwell");
    library[2].shelf = 'C';
    library[2].is_borrowed = 0;
}

void Task2(void* pdata)
{
    INT16U i;
    INT8U err;

    while (1)
    {
        OSTaskSuspend(OS_PRIO_SELF);  // Suspend the current task
        OSSemPend(Semaphore, 0, &err); // Obtain the semaphore
        if (err == OS_NO_ERR)
        {
            int found = 0;  // Variable to track if the book is found

            // Iterate through the library books
            for (int j = 0; j < MAX_BOOKS; j++)
            {
                // Check if the book matches the requested title and is not borrowed
                if (strcmp(library[j].title, bookTitle) == 0 && !library[j].is_borrowed)
                {
                    library[j].return_due = 0;
                    SetReturnDueDate(&(library[j].return_due)); // Set return due date
                    library[j].is_borrowed = 1;  // Mark the book as borrowed
                    printf("Borrowing book: %s\n", bookTitle);
                    found = 1;
                    WriteLoanRecord(bookTitle, "borrowed"); // Record borrowing information
                    break;
                }
            }

            // If book is not found or already borrowed
            if (!found)
            {
                printf("Book '%s' is not available for borrowing or already borrowed.\n", bookTitle);

                char* msg = (char*)malloc(100); // Allocate memory for message
                strcpy(msg, "Book not available for borrowing or already borrowed");
                OSQPost(MessageQueue, (void*)msg); // Post message to Task5
                printf("Reservation complete.\n");
                OSTaskResume(5);
            }
        }
        else
        {
            printf("Error: Semaphore pend failed in Task2.\n");
        }
        OSSemPost(Semaphore); // Release the semaphore
    }
}

void Task3(void* pdata)
{
    INT16U i;
    INT8U err;
   
    while (1)
    {
        OSTaskSuspend(OS_PRIO_SELF); // Suspend the current task
        OSSemPend(Semaphore, 0, &err); // Obtain the semaphore
        if (err == OS_NO_ERR)
        {
            char returnTitle[MAX_TITLE_LENGTH]; // Variable to store the title of the book to return
            printf("Enter the title of the book to return: ");
            scanf(" %[^\n]", returnTitle);
            bookTitle[strcspn(returnTitle, "\n")] = 0;


            int found = 0; // Variable to track if the book is found
            int wasBorrowed = 0; // Variable to track if the book was borrowed
            for (int j = 0; j < MAX_BOOKS; j++)
            {
                // Check if the book exists in the library
                if (strcmp(library[j].title, returnTitle) == 0)
                {
                    found = 1;
                    if (library[j].is_borrowed)
                    {
                        // Check if the book was returned on time
                        if (OSTimeGet() > library[j].return_due)
                        {
                            printf("Book '%s' was not returned on time.\n", returnTitle); // Print overdue message
                        }
                        library[j].is_borrowed = 0; 
                        printf("Returning book: %s\n", returnTitle); // Record return information 
                        wasBorrowed = 1; 
                        WriteLoanRecord(returnTitle, "Returned");
                    }
                    break;
                }
            }
            if (!found) // Check if the book was found
            {
                printf("Book '%s' does not exist in the library.\n", returnTitle);
            }
            else if (!wasBorrowed)
            {
                printf("Book '%s' is not currently borrowed.\n", returnTitle);
            }
            else // If the book was borrowed and returned, send a message 
            {
                char* msg = (char*)malloc(100);
                strcpy(msg, "Book returned");
                OSQPost(MessageQueue, (void*)msg); // Post message to Task5
                OSTaskResume(5);
            }
        }
        else
        {
            printf("Error: Semaphore pend failed in Task3.\n");
        }
        OSSemPost(Semaphore); // Release the semaphore
    }
}

void Task4(void* pdata)
{
    INT16U i;
    INT8U err;
    while (1)
    {
        OSTaskSuspend(OS_PRIO_SELF); // Suspend the current task
        OSSemPend(Semaphore, 0, &err); // Obtain the semaphore

        printf("Enter the title of the book to search: ");
        scanf(" %[^\n]", bookTitle);
        bookTitle[strcspn(bookTitle, "\n")] = 0;

        int found = 0; // Variable to track if the book is found

        for (int j = 0; j < MAX_BOOKS; j++)
        {
            // Check if the book exists in the libraryㄴ
            if (strcmp(library[j].title, bookTitle) == 0)
            {
                found = 1;
                printf("Book found!\n");
                printf("Title: %s\n", library[j].title);
                printf("Author: %s\n", library[j].author);
                printf("Shelf: %c\n", library[j].shelf);
                printf("Borrowed: %s\n", library[j].is_borrowed ? "Yes" : "No");

                if (library[j].is_borrowed) // If the book is borrowed, send a message
                {
                    char* msg = (char*)malloc(100);
                    strcpy(msg, "Reservation complete.\n");
                    OSQPost(MessageQueue, (void*)msg); // Post message to Task5
                    OSTaskResume(5);
                }
                else // If the book is not borrowed
                {
                    
                    OSTaskResume(2); 
                }
                break;
            }
        }
        if (!found) // If the book is not found
        {
            printf("Book not found.\n");
        }
        OSSemPost(Semaphore); // Release the semaphore
    }
}

void Task5(void* pdata)
{
    INT16U i;
    char* msg;

    while (1)
    {
        OSTaskSuspend(OS_PRIO_SELF); // Suspend the current task

        msg = (char*)OSQAccept(MessageQueue); // Receive a message from the queue
        if (msg != 0)
        {
            printf("Alert: %s\n", msg);
            free(msg); // Free the allocated memory for the message
        }
        else
        {
            printf("Error: Message queue pend failed in Task5.\n");
        }
    }
}