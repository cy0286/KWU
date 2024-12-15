#include "Manager.h"
#include "GraphMethod.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

Manager::Manager()	
{
	graph = nullptr;	
	fout.open("log.txt", ios::app);
	load = 0;	//Anything is not loaded
}

Manager::~Manager()
{
	if(load)	//if graph is loaded, delete graph
		delete graph;	
	if(fout.is_open())	//if fout is opened, close file
		fout.close();	//close log.txt File
}

void Manager::run(const char *command_txt)
{
	ifstream fin;						 // Command File Input File Stream
	fin.open(command_txt, ios_base::in); // File open with read mode

	if (!fin)
	{ // If command File cannot be read, Print error
		fout << "command file open error" << endl;
		return; // Return
	}

	// variable declaration
	char *str = NULL;
	char *str2 = NULL;
	char *str3 = NULL;
	char buf[129] = {0};

	while (fin.getline(buf, 128)) // until end of file
	{
		str = strtok(buf, " ");
		if (strcmp(str, "LOAD") == 0) // LOAD command
		{
			str2 = strtok(NULL, " ");
			if (LOAD(str2))
			{
				fout << "======== LOAD ========" << endl;
				fout << "Success" << endl;
				fout << "======================" << endl
					 << endl;
			}
			else // LOAD failed
			{
				printErrorCode(100);
			}
		}
		else if (strcmp(str, "PRINT") == 0) // PRINT command
		{
			if (!PRINT())
			{
				printErrorCode(200); // PRINT failed
			}
		}
		else if (strcmp(str, "BFS") == 0) // BFS command
		{
			str2 = strtok(NULL, " ");
			str3 = strtok(NULL, " ");
			fout << "======== BFS ========" << endl;
			
			// Check if vertex is empty
			if (str3 == NULL)
			{
				printErrorCode(300);
			}
			else
			{
				int vertex = atoi(str3) - 1;

				// Check if the entered vertex is valid
				if (vertex < 0 || vertex > graph->getSize())
				{
					printErrorCode(300);
				}
				else
				{
					if (strcmp(str2, "Y") == 0)
					{
						fout << "Directed Graph BFS result" << endl;
					}
					if (strcmp(str2, "N") == 0)
					{
						fout << "Undirected Graph BFS result" << endl;
					}

					if (!mBFS(str2[0], vertex))
					{
						printErrorCode(300); // BFS failed
					}
				}
			}
		}
		else if (strcmp(str, "DFS") == 0) // DFS command
		{
			str2 = strtok(NULL, " ");
			str3 = strtok(NULL, " ");
			fout << "======== DFS ========" << endl;
			
			// Check if vertex is empty
			if (str3 == NULL)
			{
				printErrorCode(400);
			}
			else
			{
				int vertex = atoi(str3) -1;

				// Check if the entered vertex is valid
				if (vertex < 0 || vertex > graph->getSize())
				{
					printErrorCode(400);
				}
				else
				{
					if (strcmp(str2, "Y") == 0)
					{
						fout << "Directed Graph DFS result" << endl;
					}
					if (strcmp(str2, "N") == 0)
					{
						fout << "Undirected Graph DFS result" << endl;
					}

					if (!mDFS(str2[0], vertex))
					{
						printErrorCode(400); // DFS failed
					}
				}
			}
		}
		else if (strcmp(str, "KWANGWOON") == 0)
		{
			str2 = strtok(NULL, " ");
			fout << "======== KWANGWOON ========" << endl;
			if(!mKwoonWoon(atoi(str2) - 1))
			{
				printErrorCode(500);
			}
			fout << "======================" << endl;
		}
		else if (strcmp(str, "KRUSKAL") == 0) // KRUSKAL command
		{
			fout << "======== KRUSKAL ========" << endl;
			if (!mKRUSKAL())
			{
				printErrorCode(600); // If MST is not found, KRUSKAL is failed
			}
			fout << "======================" << endl;
		}
		else if (strcmp(str, "DIJSKSTRA") == 0) // DIJSKSTRA command
		{
			str2 = strtok(NULL, " ");
			str3 = strtok(NULL, " ");
			if (str3 == NULL)
			{
				printErrorCode(700); // Vertex not provided
				return;
			}
			int vertex = atoi(str3) - 1;
			fout << "======== DIJSKSTRA ========" << endl;
			if (strcmp(str2, "Y") == 0)
			{
				fout << "Directed Graph DIJSKSTRA result" << endl;
			}
			if (strcmp(str2, "N") == 0)
			{
				fout << "Undirected Graph DIJSKSTRA result" << endl;
			}
			if (!mDIJKSTRA(str2[0], vertex))
			{
				printErrorCode(700); // DIJKSTRA failed
			}
			fout << "======================" << endl;
		}
		else if (strcmp(str, "BELLMANFORD") == 0) // BELLMANFORD command
		{
			fout << "======== BELLMANFORD ========" << endl;

			str2 = strtok(NULL, " ");
			char *str3 = strtok(NULL, " ");
			char *str4 = strtok(NULL, " ");
			if (str3 == NULL)
			{
				printErrorCode(800); // Vertex not provided
				return;
			}
			int vertex1 = atoi(str3) - 1;
			int vertex2 = atoi(str4) - 1;
			if (strcmp(str2, "Y") == 0)
			{
				fout << "Directed Graph BELLMANFORD result" << endl;
			}
			if (strcmp(str2, "N") == 0)
			{
				fout << "Undirected Graph BELLMANFORD result" << endl;
			}
			if (!mBELLMANFORD(str2[0], vertex1, vertex2))
			{
				printErrorCode(800); // BELLMANFORD failed
			}
			fout << "======================" << endl;
		}
		else if (strcmp(str, "FLOYD") == 0) // FLOYD command
		{
			char tmp[5];
			str2 = strtok(NULL, " ");
			strcpy(tmp,str2);
			
			fout << "======== FLOYD ========" << endl;
			if (strcmp(tmp, "Y") == 0)
			{
				fout << "Directed Graph FLOYD result" << endl;
			}
			if (strcmp(tmp, "N") == 0)
			{
				fout << "Undirected Graph FLOYD result" << endl;
			}
			
			if (!mFLOYD(tmp[0]))
			{
				printErrorCode(900); // FLOYD failed
			}
		}
		else
		{
			return;
		}
		fout << endl;
	}

	fin.close();
	return;
}

bool Manager::LOAD(const char *filename)
{
	ifstream fin;
	fin.open(filename);
	if (!fin) // fail to open file
	{
		printErrorCode(100);
		return false;
	}

	// Check if the file is empty
	if (fin.peek() == ifstream::traits_type::eof())
	{
		printErrorCode(100);
		fin.close();
		return false;
	}

	// variable declaration
	char *str2 = NULL;
	char buf2[129] = {0};
	fin.getline(buf2, 129);	  // read a line
	str2 = strtok(buf2, " "); // read in buf2
	
	if (strcmp(str2, "L") == 0) // list graph
	{
		if (load == 1) // graph information exists
		{
			delete graph; // delete existing graph
		}
		fin.getline(buf2, 129);
		str2 = strtok(buf2, " ");
		graph = new ListGraph(0, atoi(str2)); // make new list graph

		while (fin.getline(buf2, 129))
		{
			int start;		   // start vertax
			char *str3 = NULL; // start vertax
			char *str4 = NULL; // arrived vertax, weight
			str3 = strtok(buf2, " ");
			str4 = strtok(NULL, " ");
			if (str4 == NULL) // start vertex
			{
				start = atoi(str3) - 1; // str3 = start vertax
			}
			else
			{
				graph->insertEdge(start, atoi(str3) - 1, atoi(str4)); // listGraph insert
			}
		}
	}
	else if (strcmp(str2, "M") == 0) // matrix graph
	{
		if (load == 1) // graph information exists
		{
			delete graph; // delete existing graph
		}
		fin.getline(buf2, 129);
		str2 = strtok(buf2, " ");
		graph = new MatrixGraph(1, atoi(str2)); // make new matrix graph
		
		// to, from vertax
		int start = 0;
		int arrive = 0;
		while (fin.getline(buf2, 129))
		{
			char *str3 = NULL; // weight
			str3 = strtok(buf2, " ");
			while (str3 != NULL)
			{
				graph->insertEdge(start, arrive++, atoi(str3)); // matrixGraph insert
				str3 = strtok(NULL, " ");
			}
			arrive = 0;
			start++;
		}
	}
	else // exception
	{
		return false;
	}
	fin.close(); // file close
	return true;
}

bool Manager::PRINT()
{
	if (graph == NULL)
    {
        printErrorCode(200);
        return false;
    }

	if (graph->printGraph(&fout))
		return true;
	return false;
}

bool Manager::mBFS(char option, int vertex)
{
	if (!BFS(graph, option, vertex, &fout))
	{
		return false;
	}
	return true;
}

bool Manager::mDFS(char option, int vertex)
{
	if (!DFS(graph, option, vertex, &fout))
	{
		return false;
	}
	return true;
}

bool Manager::mDIJKSTRA(char option, int vertex)	
{
	if (!Dijkstra(graph, option, vertex, &fout))
	{
		return false;
	}
	return true;
}

bool Manager::mKRUSKAL()
{
 	if (!Kruskal(graph, &fout))
	{
		return false;
	}
	return true;
}

bool Manager::mBELLMANFORD(char option, int s_vertex, int e_vertex)
{
	if (!Bellmanford(graph, option, s_vertex, e_vertex, &fout))
	{
		return false;
	}
	return true;
}

bool Manager::mFLOYD(char option)
{
	if (!FLOYD(graph, option, &fout))
	{
		return false;
	}
	return true;
}

bool Manager::mKwoonWoon(int vertex) 
{
	if (!KWANGWOON(graph, vertex, &fout))
	{
		return false;
	}
	return true;
}

void Manager::printErrorCode(int n)
{
	fout<<"========ERROR======="<<endl;
	fout<<n<<endl;
	fout<<"===================="<<endl;
}


