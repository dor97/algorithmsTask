#include"my_priority_queue.h"

void my_priority_queue::push(vertex v)
{
	std::priority_queue<vertex>::push(v);
	++size;

}

void my_priority_queue::updet()
{
	for (int i = 0; i < size; ++i)
		vec[c[i].getV() - 1] = i;
}

int max(vertex x, vertex y, int ind1, int ind2)
{
	if (x > y)
		return ind1;
	return ind2;
}

void my_priority_queue::pop()
{
	int ind = 0;
	int ind1, ind2;
	int temp;
	ind1 = Left(ind);
	ind2 = Right(ind);
	if (ind2 < size)
		temp = max(c[ind1], c[ind2], ind1, ind2);
	else
		if (ind1 < size)
			temp = ind1;
		else
			temp = size;

	while(temp < size && c[size - 1] < c[temp])
	{
		vec[c[temp].getV() - 1] = ind;
		ind = temp;
		ind1 = Left(ind);
		ind2 = Right(ind);
		if (ind2 < size)
			temp = max(c[ind1], c[ind2], ind1, ind2);
		else
			if (ind1 < size)
				temp = ind1;
			else
				temp = size;
	}
	vec[c[size - 1].getV() - 1] = ind;
	vec[std::priority_queue<vertex>::top().getV() - 1] = -1;

	std::priority_queue<vertex>::pop();
	--size;
}

int my_priority_queue::Left(int node) { return (2 * node + 1); }
int my_priority_queue::Right(int node) { return (2 * node + 2); }
int my_priority_queue::Parent(int node) { return (node - 1) / 2; }

void my_priority_queue::fixHeap(vertex v, int newC)
{

	int i = vec[v.getV() - 1];

	if (i == -1)
		return;


	v.setC(newC);
	

	while (i > 0 && (c[Parent(i)].getC() < newC))
	{
		vec[c[Parent(i)].getV() - 1] = i;
		c[i] = c[Parent(i)];
		i = Parent(i);
	}
	vec[v.getV() - 1] = i;
	c[i] = v;
}