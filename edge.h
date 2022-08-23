#pragma once
#include<iostream>
//std::pair<int, int>
class edge {

	int u, c, f;

public:
	edge(int u, int c) : u(u), c(c), f(0){}
	edge(int u) : u(u), c(0), f(0) {}
	//int operator[](size_t i) const { return u; }
	bool operator==(const edge& i) const { return this->u == i.u; }
	bool operator!=(const edge& i) const { return !operator==(i); }
	bool operator<(const edge& i) const { return u < i.u; }
	//bool operator==(int i) { return u == i; }
	friend std::ostream& operator<< (std::ostream& out, const edge& e) { return out << e.u << "," << e.c << "," << e.f; }
	int getVertex() { return u; }
	int getCapacity() { return c; }
	int getFlow() { return f; }
	void addCapacity(int capacity) { c = c + capacity; }
	void addFlow(int flow) { f += flow; }
};