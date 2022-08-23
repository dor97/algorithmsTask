#include"graph.h"

graph::graph(int size) : size(size)
{
	makeEmptyGraph();
}

void graph::makeEmptyGraph()
{
	for (int i = 0; i < size; ++i)
	{
		g.push_back(std::list<edge>{});
	}
}

bool graph::AddEdge(int v, int u, int c)
{
	for (auto e : g[v - 1])
		if (e == u)
			return false;
	g[v - 1].push_back(edge(u, c));
	return true;
}

void graph::RemoveEdge(int v, int u)
{
	g[v - 1].remove(u);
}

std::list<edge>& graph::GetAdjList(int v)
{
	g[v - 1].sort();
	return g[v - 1];
}

void graph::print()
{
	int i = 0;
	for (auto vertexList : g)
	{
		std::cout << i+1 << ":";
		for (auto vertex : vertexList)
		{
			std::cout << vertex << "  ";
		}
		++i;
		std::cout << "\n";
	}
}
