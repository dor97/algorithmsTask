#pragma once
#include<queue>
#include"edge.h"
#include"vertex.h"
#include<vector>

class my_priority_queue : public std::priority_queue<vertex>
{
	std::vector<vertex*> pointrs;
	std::vector<int> vec;
	int size;

public:
	my_priority_queue(int n) { pointrs.resize(n);  vec.resize(n); }
	void push(vertex v);
	void pop();
	void fixHeap(vertex v, int newC);
	int Left(int node);
	int Right(int node);
	int Parent(int node);
	void updet();
};