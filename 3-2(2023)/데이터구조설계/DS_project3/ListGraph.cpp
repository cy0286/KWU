#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_Type = type;
	m_List = new map<int, int>[size]; //allocation
}

ListGraph::~ListGraph()
{
	delete[] m_List; //deallocation
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
	map<int, int>::iterator it; //declare iterator
	for(it = m_List[vertex].begin(); it != m_List[vertex].end(); it++)
	{
		m->insert({it->first, it->second}); //insert
	}
}

void ListGraph::getAdjacentEdges2(int vertex, map<int, int>* m) //no direct
{
	map<int, int>::iterator it; //declare itertaor
	for(it = m_List[vertex].begin(); it != m_List[vertex].end(); it++)
	{
		m->insert({it->first, it->second}); //insert
	}
	for(int i = 0; i < getSize(); i++) //as a size
	{
		if(i == vertex) //i is vertecx
		{
			continue;
		}
		for(it = m_List[i].begin(); it != m_List[i].end(); it++)
		{
			if(it->first == vertex)
			{
				m->insert({i,it->second});
			}
		}
	}
}

void ListGraph::insertEdge(int from, int to, int weight)
{	
	m_List[from].insert(make_pair(to, weight)); //insert
}

bool ListGraph::printGraph(ofstream* fout)
{
	*fout<<"Graph is ListGraph!"<<endl;
	*fout<<"======== PRINT ========"<<endl;
	for(int i=0; i<m_Size; i++)
	{	
		*fout<<"["<< i + 1 <<"]";

		for(auto it_=m_List[i].begin(); it_!=m_List[i].end() && *fout<<" -> "; it_++)
		{
			*fout<<"("<<it_->first+1<<","<<it_->second<<")";
		}
		*fout<<endl;
	}
	*fout<<"======================"<<endl;
	*fout<<endl;
	return 1;
}