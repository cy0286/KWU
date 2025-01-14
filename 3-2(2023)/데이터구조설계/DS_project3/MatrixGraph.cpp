#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
	m_Mat = new int*[size]; //allocation
	for(int i=0; i<size; i++) //initialize
	{
		m_Mat[i] = new int[size];
		memset(m_Mat[i], 0, sizeof(int)*size);
	}
}

MatrixGraph::~MatrixGraph()
{
	for(int i=0; i<getSize(); i++) //disallocation
	{
		delete[] m_Mat[i];
	}
	delete[] m_Mat;
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
	for(int i = 0; i < getSize(); i++)
	{
		if(m_Mat[vertex][i] != 0)
		{
			m->insert(make_pair(i,m_Mat[vertex][i])); //insert
		}
	}
}

void MatrixGraph::getAdjacentEdges2(int vertex, map<int, int>* m) //no direction
{
	for(int i = 0; i < getSize(); i++)
	{
		if(m_Mat[vertex][i] != 0)
		{
			m->insert({i,m_Mat[vertex][i]}); // insert
		}
	}
	for(int i = 0; i < getSize(); i++)
	{
		if(m_Mat[i][vertex] != 0)
		{
			m->insert({i,m_Mat[i][vertex]}); // insert
		}
	}
}

void MatrixGraph::insertEdge(int from, int to, int weight)
{
	m_Mat[from][to] = weight; //insert
}

bool MatrixGraph::printGraph(ofstream* fout)
{
	if( m_Size < 0 )
		return 0;

	*fout<<"Graph is MatrixGraph!"<<endl;

	*fout<<"=========================== PRINT ==========================="<<endl;
	*fout<<'\t';
	for(int i=0; i<m_Size; i++)
	{
		*fout<<"["<< i + 1 <<"]"<<'\t';
	}
	*fout<<endl;

	for(int i=0; i<m_Size; i++)
	{
		*fout<<"["<< i + 1 <<"]";
		for(int j=0; j<m_Size && *fout<<'\t'; j++)
		{
			*fout<<m_Mat[i][j];
		}
		*fout<<endl;
	}
	*fout<<"============================================================="<<endl;
	return 1;
}