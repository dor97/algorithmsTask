#include"my_priority_queue.h"
//-----------------------------------------------------------------------------------------------------------------------------
void my_priority_queue::push(vertex v)
{
	std::priority_queue<vertex>::push(v);
	++size;
}
//-----------------------------------------------------------------------------------------------------------------------------
//creat an update indexes vector with each node in the priority queue index
void my_priority_queue::update()
{
	for (int i = 0; i < size; ++i)
		indexes[c[i].getV() - 1] = i;
}
//-----------------------------------------------------------------------------------------------------------------------------
//The function return the indexe of the bigger key
int max(vertex x, vertex y, int ind1, int ind2)
{
	if (x > y)
		return ind1;
	return ind2;
}
//-----------------------------------------------------------------------------------------------------------------------------
//The function pop the head of the priority queue and update the indexes
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
		indexes[c[temp].getV() - 1] = ind;
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
	indexes[c[size - 1].getV() - 1] = ind;
	indexes[std::priority_queue<vertex>::top().getV() - 1] = -1;

	std::priority_queue<vertex>::pop();
	--size;
}
//-----------------------------------------------------------------------------------------------------------------------------
//return the left child of the node
int my_priority_queue::Left(int node) { return (2 * node + 1); }
//-----------------------------------------------------------------------------------------------------------------------------
//return the rigtht child of the node
int my_priority_queue::Right(int node) { return (2 * node + 2); }
//-----------------------------------------------------------------------------------------------------------------------------
//return the parent of the node
int my_priority_queue::Parent(int node) { return (node - 1) / 2; }
//-----------------------------------------------------------------------------------------------------------------------------
//the function update the key(max flow) of a vertex in the priority queue, fix it and update the indexes
void my_priority_queue::fixHeap(vertex v, int newC)
{

	int i = indexes[v.getV() - 1];

	if (i == -1)
		return;


	v.setC(newC);
	

	while (i > 0 && (c[Parent(i)].getC() < newC))
	{
		indexes[c[Parent(i)].getV() - 1] = i;
		c[i] = c[Parent(i)];
		i = Parent(i);
	}
	indexes[v.getV() - 1] = i;
	c[i] = v;
}
//-----------------------------------------------------------------------------------------------------------------------------
