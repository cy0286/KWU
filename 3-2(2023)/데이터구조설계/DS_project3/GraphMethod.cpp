#include <iostream>
#include <vector>
#include "GraphMethod.h"
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <utility>

using namespace std;

bool BFS(Graph *graph, char option, int vertex, ofstream* fout)
{
    int n = graph->getSize();
    bool *visit = new bool[n]{0}; // visit allocation
    map<int, int>::iterator it;   // declare iterator
    map<int, int> near;           // declare map to find adjacent nodes
    visit[vertex] = true;
    queue<int> q;   // declare queue
    q.push(vertex); // push in q
    *fout << "startvertex: " << vertex + 1 << endl;
    while (!q.empty()) // until q is empty
    {
        vertex = q.front();
        q.pop();                                // queue pop
        if (option == 'Y')
        {   
            graph->getAdjacentEdges(vertex, &near); // get adjacent edges with direction
        }
        else if (option == 'N')
        {
            graph->getAdjacentEdges2(vertex, &near); // get adjacent edges without direction
        }
        for (it = near.begin(); it != near.end(); it++)
        {
            if (!visit[it->first])
            {
                q.push(it->first);
                visit[it->first] = true;
            }
        }
        if (q.empty()) // queue is empty
        {
            *fout << vertex + 1;
        }
        else
        {
            *fout << vertex + 1 << " -> ";
        }
    }
    *fout << endl
          << "=====================" << endl
          << endl;
    delete[] visit; // disallocation
    return true;
}

bool DFS(Graph *graph, char option, int vertex, ofstream* fout)
{
    int n = graph->getSize();
    bool *visit = new bool[n]{0};       // visit allocation
    map<int, int>::reverse_iterator it; // declare iterator
    map<int, int> near;                 // declare map to find adjacent nodes
    stack<int> s;                       // declare stack
    visit[vertex] = true;
    *fout << "startvertex: " << vertex + 1  << endl;
    s.push(vertex);
    while (!s.empty()) // until stack is empty
    {
        vertex = s.top();
        s.pop();
        if (option == 'Y')
        {   
            graph->getAdjacentEdges(vertex, &near); // get adjacent edges with direction
        }
        else if (option == 'N')
        {
            graph->getAdjacentEdges2(vertex, &near); // get adjacent edges without direction
        }
        for (it = near.rbegin(); it != near.rend(); it++)
        {
            if (!visit[it->first])
            {
                s.push(it->first);
                visit[it->first] = true;
            }
        }
        if (s.empty()) // stack is empty
        {
            *fout << vertex + 1;
        }
        else
        {
            *fout << vertex + 1 << " -> ";
        }
    }
    *fout << endl
          << "=====================" << endl
          << endl;
    delete[] visit; // disallocation
    return true;
}

bool Kruskal(Graph *graph, ofstream *fout)
{
    int n = graph->getSize();
    int numEdges = n * n;
    map<int, int> near;
    map<int, int>::iterator it;
    int edgeWeights[n][n] = {0};
    int sortedWeights[numEdges] = {0};                          
    int setParent[n]; 
    int kruskalMST[n][n] = {0};                   
    int weightCount = 0; 
    int edgeCount = 0;   
    int totalCost = 0;   

    for (int i = 0; i < n; i++) // Initialize arrays and matrice
    {
        for (int j = 0; j < n; j++)
        {
            edgeWeights[i][j] = 0;
            kruskalMST[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) // Populate the edgeWeights matrix with the weights from the graph
    {
        graph->getAdjacentEdges2(i, &near);
        for (it = near.begin(); it != near.end(); it++)
        {
            edgeWeights[i][it->first] = it->second;
            if (edgeWeights[i][it->first] == edgeWeights[it->first][i])
            {
                edgeWeights[i][it->first] = 0;
                continue;
            }
            else if ((edgeWeights[i][it->first] < edgeWeights[it->first][i]) && (edgeWeights[it->first][i] != 0))
            {
                edgeWeights[it->first][i] = 0;
                continue;
            }
            else if ((edgeWeights[i][it->first] > edgeWeights[it->first][i]) && (edgeWeights[it->first][i] != 0))
            {
                edgeWeights[i][it->first] = 0;
                continue;
            }
        }
        near.clear();
    }

    for (int i = 0; i < n; i++) // Extract unique edge weights and store them in sortedWeights array
    {
        for (int j = 0; j < n; j++)
        {
            if (edgeWeights[i][j] != 0)
            {
                sortedWeights[weightCount++] = edgeWeights[i][j];
            }
        }
    }

    quicksort(sortedWeights, 0, (weightCount - 1)); // Sort the edge weights in non-decreasing order using quicksort

    for (int i = 0; i < n; i++) // Initialize the setParent array for disjoint-set data structure
    {
        setParent[i] = -1;
    }

    for (int i = 0; i < weightCount;) // Build the Minimum Spanning Tree
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (edgeWeights[j][k] == sortedWeights[i])
                {
                    edgeWeights[j][k] = 0;
                    int set1 = findset(j, setParent);
                    int set2 = findset(k, setParent);
                    if (set1 != set2) // Merge the sets and add the edge to the MST
                    {
                        unionset(set1, set2, setParent);
                        kruskalMST[j][k] = sortedWeights[i++];
                        totalCost += kruskalMST[j][k];
                        edgeCount++;
                    }
                    else
                    {
                        i++;
                    }
                    if (edgeCount == n - 1 || i == weightCount) // Check if the MST is complete or if all edges have been processed
                    {
                        break;
                    }
                }
            }
            if (edgeCount == n - 1 || i == weightCount)
            {
                break;
            }
        }
        if (edgeCount == n - 1 || i == weightCount)
        {
            break;
        }
    }
    if (edgeCount != n - 1) // Check if the MST is connected 
    {
        *fout << "The number of edges is less than n-1" << endl;
        return false;
    }

    for (int i = 0; i < n; i++) // Make the MST matrix symmetric
    {
        for (int j = 0; j < n; j++)
        {
            if (kruskalMST[i][j] != 0)
            {
                kruskalMST[j][i] = kruskalMST[i][j];
            }
        }
    }

    for (int i = 0; i < n; i++) // print
    {
        *fout << "[" << i + 1 << "]";
        for (int j = 0; j < n; j++)
        {
            if (kruskalMST[i][j] != 0)
            {
                *fout << " " << j + 1 << "(" << kruskalMST[i][j] << ")";
            }
        }
        *fout << endl;
    }
    *fout << "cost: " << totalCost << endl;

    return true;
}

bool Dijkstra(Graph *graph, char option, int vertex, ofstream *fout)
{
    if (vertex >= graph->getSize()) // Check if the given vertex is valid
    {
        *fout << "vertex is not exist in graph" << endl;
        return false;
    }
    *fout << "startvertex: " << vertex + 1 << endl;
    int n = graph->getSize();
    int shortestPaths[2][n]; // 2D array to store shortest paths and their predecessors
    bool set[n];
    map<int, int> near; 
    map<int, int>::iterator it;

    for (int i = 0; i < n; i++) // Initialize arrays and matrices
    {
        set[i] = false;
        shortestPaths[0][i] = MAX;
        shortestPaths[1][i] = MAX;
    }
    shortestPaths[0][vertex] = 0;
    
    for (int i = 0; i < n - 1; i++) // Main loop to find shortest paths
    {
        int currentVertex;
        for (currentVertex = 0; currentVertex < n; currentVertex++) // Find the unvisited vertex with the minimum distance
        {
            if (set[currentVertex] == false)
            {
                break;
            }
        }
        for (int j = currentVertex + 1; j < n; j++)
        {
            if (set[j] == false)
            {
                if (shortestPaths[0][j] <= shortestPaths[0][currentVertex])
                {
                    currentVertex = j;
                }
            }
        }

        set[currentVertex] = true;
        // Get adjacent edges based on the option
        if (option == 'Y')
        {
            graph->getAdjacentEdges(currentVertex, &near);
        }
        else if (option == 'N')
        {
            graph->getAdjacentEdges2(currentVertex, &near);
        }

        // Update shortest paths and predecessors
        for (it = near.begin(); it != near.end(); it++)
        {
            if (it->second < 0)
            {
                *fout << "negative weight" << endl;
                return false;
            }
            int temp = shortestPaths[0][it->first];
            if (set[it->first] == false)
            {
                shortestPaths[0][it->first] = min(shortestPaths[0][currentVertex] + (it->second), shortestPaths[0][it->first]);
            }
            if (shortestPaths[0][it->first] != temp)
            {
                shortestPaths[1][it->first] = currentVertex;
            }
        }
        near.clear();
    }

    for (int i = 0; i < n; i++) // print
    {
        *fout << "[" << i + 1 << "] ";
        if (shortestPaths[1][i] == MAX)
        {
            *fout << "x" << endl;
        }
        else
        {
            stack<int> a;
            int temp = i;
            while (temp != vertex)
            {
                a.push(temp);
                temp = shortestPaths[1][temp];
            }
            *fout << temp + 1;
            while (!a.empty())
            {
                *fout << "->" << a.top() + 1;
                a.pop();
            }
            *fout << "(" << shortestPaths[0][i] << ")" << endl;
        }
    }
    return true;
}

bool Bellmanford(Graph *graph, char option, int s_vertex, int e_vertex, ofstream *fout)
{
    if (s_vertex >= graph->getSize() || e_vertex >= graph->getSize())
    {
        *fout << "vertex is not exist in graph" << endl;
        return false;
    }
    int n = graph->getSize();
    int shortestPaths[2][n]; // 2D array to store shortest paths and their predecessors
    map<int, int> near;
    map<int, int>::iterator it;

    // Initialize arrays for shortest paths and predecessors
    for (int i = 0; i < n; i++) 
    {
        if (i == s_vertex)
        {
            shortestPaths[0][i] = 0; 
            shortestPaths[1][i] = MAX;
        }
        else
        {
            shortestPaths[0][i] = MAX;
            shortestPaths[1][i] = MAX;
        }
    }

    // Get initial adjacent edges from the source vertex
    if (option == 'Y')
    {
        graph->getAdjacentEdges(s_vertex, &near); 
    }
    else if (option == 'N')
    {
        graph->getAdjacentEdges2(s_vertex, &near); 
    }

    for (it = near.begin(); it != near.end(); it++) // Update shortest paths based on initial adjacent edges
    {
        shortestPaths[0][it->first] = it->second;
        shortestPaths[1][it->first] = s_vertex;
    }

    for (int iteration = 2; iteration < n + 1; iteration++) // Perform Bellman-Ford iterations
    {
        for (int current_vertex = 0; current_vertex < n; current_vertex++) 
        {
            if (current_vertex == s_vertex)
            {
                continue;
            }
            for (int incoming_vertex = 0; incoming_vertex < n; incoming_vertex++)
            {
                near.clear();
                if (option == 'Y')
                {
                    graph->getAdjacentEdges(incoming_vertex, &near); // get adjacent edges with direction
                }
                else if (option == 'N')
                {
                    graph->getAdjacentEdges2(incoming_vertex, &near); // get adjacent edges without direction
                }
                it = near.find(current_vertex);
                if (it == near.end())
                {
                    continue;
                }
                else
                {
                    int temp = shortestPaths[0][current_vertex];
                    shortestPaths[0][current_vertex] = min(shortestPaths[0][current_vertex], (shortestPaths[0][incoming_vertex] + it->second));
                    if (shortestPaths[0][current_vertex] != temp)
                    {
                        // Update predecessor if the distance is reduced
                        if (iteration == n)
                        {
                            *fout << "negative cycle" << endl;
                            return false;
                        }
                        shortestPaths[1][current_vertex] = incoming_vertex;
                    }
                }
            }
        }
    }

    // print
    stack<int> s;
    int temp = e_vertex;
    if (shortestPaths[1][temp] == MAX)
    {
        *fout << "x" << endl;
        return true;
    }
    while (temp != s_vertex)
    {
        if (shortestPaths[1][temp] == MAX)
        {
            *fout << "x" << endl;
            return true;
        }
        s.push(temp);
        temp = shortestPaths[1][temp];
    }
    *fout << temp + 1;
    while (!s.empty())
    {
        *fout << "->" << s.top() + 1;
        s.pop();
    }
    *fout << endl;
    *fout << "cost: " << shortestPaths[0][e_vertex] << endl;
    return true;
}

bool FLOYD(Graph *graph, char option, ofstream *fout)
{
    int i, j, k;
    int n = graph->getSize();
    int matrix[n][n];           // save graph
    map<int, int>::iterator it; // declare iterator
    map<int, int> near;         // declare map to find adjacent nodes

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i != j) // when i and j are not same
            {
                matrix[i][j] = MAX;
                continue;
            }
            matrix[i][j] = 0; // i = j, i and j are same
        }
    }

    for (i = 0; i < n; i++)
    {
        if (option == 'Y')
        {   
            graph->getAdjacentEdges(i, &near); // get adjacent edges with direction
        }
        else if (option == 'N')
        {
            graph->getAdjacentEdges2(i, &near); // get adjacent edges without direction
        }
        for (it = near.begin(); it != near.end(); it++)
        {
            matrix[i][it->first] = it->second;
        }
        near.clear();
    }

    // print matrix code
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                matrix[i][j] = min(matrix[i][j], (matrix[i][k] + matrix[k][j]));
            }
        }
    }

    *fout << '\t';
    for (int i = 0; i < n; i++)
    {
        *fout << "[" << i + 1 << "]" << '\t';
    }
    *fout << endl;

    for (int i = 0; i < n; i++)
    {
        *fout << "[" << i + 1 << "]";
        for (int j = 0; j < n && *fout << '\t'; j++)
        {
            if (matrix[i][j] >= 500000)
            {
                *fout << "x";
                continue;
            }
            *fout << matrix[i][j];
        }
        *fout << endl;
    }
    *fout << "======================" << endl;
    return true;
}

bool KWANGWOON(Graph *graph, int vertex, ofstream *fout)
{
    int n = graph->getSize();
    bool *visit = new bool[n]{0}; // visit allocation
    map<int, int>::iterator it;   // declare iterator
    map<int, int> near;           // declare map to find adjacent nodes
    visit[vertex] = true;
    
    *fout << "startvertex: " << vertex + 1 << endl;
    graph->getAdjacentEdges2(vertex, &near); // get adjacent edges with direction
    *fout << vertex + 1;

    while (1) // Main loop for traversing the graph
    {
        int flag = 0;
        int path = 0;
        for (it = near.begin(); it != near.end(); it++) // Count the number of unvisited adjacent nodes
        {
            if (!visit[it->first])
            {
                path++;
            }
        }
        if (path % 2 == 0) // If the number of unvisited adjacent nodes is even
        {
            // Find the minimum unvisited adjacent node
            int min = 1000;
            for (it = near.begin(); it != near.end(); it++)
            {
                if (!visit[it->first] && it->first < min)
                {
                    min = it->first;
                    flag++;
                }
            }
            if(flag==0) // If no unvisited adjacent nodes are found
            {
                break; // break the loop
            }
            *fout << "->" << min + 1;
            visit[min] = true; // Mark the minimum adjacent node as visited
            near.clear();
            graph->getAdjacentEdges2(min, &near); // get adjacent edges with direction
            continue; 
        }
        else if (path % 2 == 1) // If the number of unvisited adjacent nodes is odd
        {
            // Find the maximum unvisited adjacent node
            int max = 0;
            for (it = near.begin(); it != near.end(); it++)
            {
                if (!visit[it->first] && it->first > max)
                {
                    max = it->first;
                    flag++;
                }
            }
            if(flag==0) // If no unvisited adjacent nodes are found
            {
                break; // break the loop
            }
            *fout << "->" << max + 1;
            visit[max] = true;
            near.clear();
            graph->getAdjacentEdges2(max, &near); // get adjacent edges with direction
            continue;
        }
    }
    *fout << endl;
    return true;
}

void quicksort(int array[], int leftIndex, int rightIndex)
{
    if (leftIndex < rightIndex) // Check if there are at least two elements in the subarray
    {
        if (rightIndex - leftIndex + 1 <= 6) // Converts to Insertion alignment if subarray size is small
        {
            insertionsort(array, leftIndex, rightIndex);
        }
        else 
        {
            int i = leftIndex;
            int j = rightIndex + 1;
            int pivot = array[leftIndex];

            // Partition the array into elements less than and greater than the pivot
            do
            {
                do
                {
                    i++;
                } while (array[i] < pivot);
                do
                {
                    j--;
                } while (array[j] > pivot);
                if (i < j)
                {
                    // Swap elements at positions i and j
                    int temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            } while (i < j);

            // Swap the pivot element into its correct position
            int temp = array[leftIndex];
            array[leftIndex] = array[j];
            array[j] = temp;

            // Recursively apply quicksort to the left and right partitions
            quicksort(array, leftIndex, j - 1);
            quicksort(array, j + 1, rightIndex);
        }
    }
}

void insertionsort(int array[], int startIndex, int endIndex)
{
    for (int i = (startIndex + 1); i <= endIndex; i++)
    {
        int currentValue = array[i];
        insertion(currentValue, array, i - 1); // Insert the current element into the sorted portion of the array
    }
}

void insertion(int element, int array[], int size)
{
    while (element < array[size]) // Move to the right until find the right location
    {
        array[size + 1] = array[size];
        size--;
        if (size < 0) // When reach the beginning of the array
        {
            break;
        }   
    }
    array[size + 1] = element;
}

void unionset(int vertexA, int vertexB, int parent[])
{
    int newWeight = parent[vertexA] + parent[vertexB]; // Combine the sizes of the sets
    // Merge
    if (parent[vertexA] > parent[vertexB])             
    {
        parent[vertexA] = vertexB;
        parent[vertexB] = newWeight;
    }
    else 
    {
        parent[vertexB] = vertexA;
        parent[vertexA] = newWeight;
    }
}

int findset(int vertex, int parent[])
{
    int root;
    for (root = vertex; parent[root] >= 0; root = parent[root]); // Find root

    while (vertex != root) // Update the parent pointers along the path to the root
    {
        int temp = parent[vertex];
        parent[vertex] = root;
        vertex = temp;
    }
    return root;
}
