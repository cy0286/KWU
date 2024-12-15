#include "Manager.h"

void Manager::run(const char* command) 
{
	// open the input file and log file
	fin.open(command);
	flog.open("log.txt", ios::app);
	if(!fin)
	{
		flog << "File Open Error" << endl;
		return;
	}
	
	while (fin.getline(cmd, 100)) // process commands from the input file
	{
		char *buf = strtok(cmd, "\t");
		if (strcmp(buf, "LOAD") == 0)
		{
			if (LOAD())
			{
				printSuccessCode();
			}
			else
			{
				printErrorCode(100);
			}
		}
		else if (strcmp(buf, "ADD") == 0)
		{
			LoanBookData *temp = new LoanBookData();

			char name[100];
			int code;
			char author[100];
			int year;

			// tokenize to extract book information
			char *token = strtok(NULL, "\t");
			if (token != NULL)
			{
				strcpy(name, token);
				token = strtok(NULL, "\t");
				if (token != NULL)
				{
					code = atoi(token);
					token = strtok(NULL, "\t");

					if (token != NULL)
					{
						strcpy(author, token);
						token = strtok(NULL, "\t");

						if (token != NULL)
						{
							year = atoi(token);
						}
					}
				}
			}
			// set the extracted information
			temp->setName(name);
			temp->setCode(code);
			temp->setAuthor(author);
			temp->setYear(year);
			temp->updateCount();

			if (ADD(temp))
			{
			}
			else
			{
				printErrorCode(200);
			}
		}
		else if (strcmp(buf, "SEARCH_BP") == 0)
		{
			char name[100];
			char startWord[100];
			char endWord[100];

			// tokenize to extract search parameters
			char *token1 = strtok(NULL, "\t");;
			char *token2 = strtok(NULL, "\t");;

			if (token2 == NULL) // if only one token is present
			{
				strcpy(name, token1);
				if (SEARCH_BP_BOOK(name))
				{
					
				}
				else
				{
					printErrorCode(300);
				}
			}
			else // if two tokens are present
			{
				strcpy(startWord, token1);
				strcpy(endWord, token2);

				if (SEARCH_BP_RANGE(startWord, endWord))
				{ 

				}
				else
				{
					printErrorCode(300);
				}
			}
		}
		else if (strcmp(buf, "PRINT_BP") == 0)
		{
			if (PRINT_BP())
			{
			}
			else
			{
				printErrorCode(400);
			}
		}
		else if (strcmp(buf, "PRINT_ST") == 0)
		{
			int code;
			char *token1 = strtok(NULL, "\t");
			char *token2 = strtok(NULL, "\t");
			LoanBookData *temp = new LoanBookData();
			if (token2 != NULL)
			{
				code = atoi(token2);
			}
			temp->getCode();
			if (PRINT_ST(temp))
			{
			}
			else
			{
				printErrorCode(500);
			}
		}
		else if (strcmp(buf, "DELETE") == 0)
		{
			if (DELETE())
			{
				printSuccessCode();
			}
			else
			{
				printErrorCode(600);
			}
		}
		else if (strcmp(buf, "EXIT") == 0)
		{
			flog << "========EXIT========" << endl;
			printSuccessCode();
		}
		else // an incorrect command
		{
			printErrorCode(700);
		}
	}
	// close the input file and log file
	fin.close();
	flog.close();
	return;
}

bool Manager::LOAD()
{
	flog << "========LOAD========" << endl;
	datafile.open("loan_book.txt"); // open the loan_book.txt file
	if(!datafile) // check if the file exists
	{
		flog << "Error: loan_book.txt not found." << endl;
		printErrorCode(100);
		return false;
	}

	char name[50];
    int code;
    char author[100];
    int year;
	int count;

	char line[200];
	while(datafile.getline(line, 200)) // read each line from the file
	{
		LoanBookData *temp = new LoanBookData();
		
		char* token = strtok(line, "\t");
		
		// extract and set book information
        if (token != NULL) 
		{
            strcpy(name, token);
            token = strtok(NULL, "\t");
            if (token != NULL) 
			{
                code = atoi(token);
                token = strtok(NULL, "\t");
                if (token != NULL) 
				{
                    strcpy(author, token);
                    token = strtok(NULL, "\t");
                    if (token != NULL) 
					{
                        year = atoi(token);
						token = strtok(NULL, "\t");
						if (token != NULL)
						{
							count = atoi(token);
							token = strtok(NULL, "\t");
							if (token != NULL)
							{
								count = atoi(token);
							}
							
						}
                    }
                }
            }
        }
		
		// set the extracted information
		temp->setName(name);
		temp->setCode(code);
		temp->setAuthor(author);
		temp->setYear(year);
		// update the count of the book
		for (int i = 0; i < count; i++)
		{
			temp->updateCount();
		}
		bptree->Insert(temp); // insert the book into the B+ tree
	}
	
	return true;
}

bool Manager::ADD(LoanBookData *temp)
{
	flog << "========ADD========" << endl;

	if(bptree->Insert(temp) == 3) // insert into the B+ tree
	{
		// if the return value is 3, (deleted)
		if (temp->getCode() <= 200)
		{
			for(int i = 0; i < 3; i++) // update the count of the book three times
			{
				temp->updateCount();
			}
			// insert the book into the heap and selection tree
			heap->Insert(temp);
			stree->Insert(heap->getRoot()->getBookData());
			//heap->heapifyUp(heap->getRoot());
		}
		else if (temp->getCode() <=400)
		{
			for(int i = 0; i < 4; i++)
			{
				temp->updateCount();
			}
			heap->Insert(temp);
		}
		else if (temp->getCode() <=700)
		{
			for(int i = 0; i < 2; i++)
			{
				temp->updateCount();
			}
			heap->Insert(temp);
		}
	}
	
	flog << temp->getName() << "/" << std::setw(3) << std::setfill('0') << temp->getCode() << "/" << temp->getAuthor() << "/" << temp->getYear() << endl;
	flog << "====================" << endl;
	
	return true;
}

bool Manager::SEARCH_BP_BOOK(string book) 
{
	flog << "========SEARCH_BP========" << endl;
	bptree->searchBook(book);
	flog << "==========================" << endl;
}

bool Manager::SEARCH_BP_RANGE(string s, string e) 
{
	flog << "========SEARCH_BP========" << endl;
	bptree->searchRange(s, e);
	flog << "==========================" << endl;
}

bool Manager::PRINT_BP()
{
	flog << "========PRINT_BP========" << endl;
	bptree->printBptree(bptree->getRoot());
	flog << "========================" << endl; 
}

bool Manager::PRINT_ST(LoanBookData *temp) 
{
	flog << "========PRINT_ST========" << endl;
	stree->printBookData(temp->getCode());
	flog << "=========================" << endl;
}

bool Manager::DELETE() 
{	
	flog << "========DELETE========" << endl;
	int code;
	stree->Delete(code);
	// heapifyDown
}

void Manager::printErrorCode(int n) //ERROR CODE PRINT
{	
	flog << "========ERROR========" << endl;	
	flog << n << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode() //SUCCESS CODE PRINT 
{
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
}

