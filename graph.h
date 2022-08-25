#pragma once
#include<vector>
#include<list>
#include"edge.h"
//-----------------------------------------------------------------------------------------------------------------------------
class graph {

	int size;
	std::vector<std::list<edge>> g;

	void makeEmptyGraph();
public:
	graph(int size);
	bool AddEdge(int v, int u, int c);
	void RemoveEdge(int v, int u);
	std::list<edge>& GetAdjList(int v);
	const std::vector<std::list<edge>>& getVector() { return g; }
	int getSize() { return size; }
	void print();
};
//-----------------------------------------------------------------------------------------------------------------------------