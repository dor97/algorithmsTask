#include"main.h"
//-----------------------------------------------------------------------------------------------------------------------------
int main()
{
	float vertexs, edges, s, t;
	try {
		std::cin >> vertexs >> edges >> s >> t;
		if (vertexs < 2 || vertexs != floor(vertexs) || edges < 0 || edges != floor(edges) || s < 1 || s > vertexs || s != floor(s) || t < 1 || t > vertexs || t != floor(t))
			throw(0);
		graph G1(vertexs), GF1(vertexs), G2(vertexs), GF2(vertexs);

		for (int i = 0; i < edges; ++i)
		{
			float v, u, c;
			std::cin >> v >> u >> c;
			if (v < 1 || v > vertexs || v != floor(v) || u < 1 || u > vertexs || u != floor(u) || c < 0 || c != floor(c))
				throw(0);
			G1.AddEdge(v, u, c);
		}


		GF1 = G1;
		G2 = G1;
		GF2 = G1;


		std::cout << "BFS Method:\n";
		printOutPut(G1, GF1, s, t, vertexs, true);
		std::cout << "Greedy Method:\n";
		printOutPut(G2, GF2, s, t, vertexs, false);

		std::cout << "\n\n";
		G1.print();
		std::cout << "\n\n";
		GF1.print();

		std::cout << "\n\n\n";
		G2.print();
		std::cout << "\n\n";
		GF2.print();

	}
	catch (...)
	{
		std::cout << "invalid input";
		return 0;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------------------------
void bfs(int s, graph& gr, int n, std::vector<float>& d, std::vector<int>& p)
{
	std::queue<int> q;
	q.push(s);
	for (int i = 0; i < n; ++i)
	{
		d.push_back(std::numeric_limits<float>::infinity());
		p.push_back(-1);
	}
	d[s - 1] = 0;
	
	while (!q.empty())
	{
			for (auto e : gr.GetAdjList(q.front()))
			{
				if (d[e.getVertex() - 1] > d[q.front() - 1] + 1)
				{
					p[e.getVertex() - 1] = q.front();
					d[e.getVertex() - 1] = d[q.front() - 1] + 1;
					q.push(e.getVertex());
				}
			}
			q.pop();
	}
}
//-----------------------------------------------------------------------------------------------------------------------------
float min(float d, int c)
{
	if (d > c)
		return c;
	return d;
}
//-----------------------------------------------------------------------------------------------------------------------------
//The function find the path with the max flow that can be add
void Greedy_Method(int s, graph& gr, int n, std::vector<float>& d, std::vector<int>& p)
{
	my_priority_queue q(n);
	q.push(vertex(s, std::numeric_limits<float>::infinity()));
	
	for (int i = 0; i < n; ++i)
	{
		d.push_back(0);
		if (i + 1 != s)
			q.push(vertex(i + 1, 0));
		p.push_back(-1);
	}

	q.update();

	d[s - 1] = std::numeric_limits<float>::infinity();

	while (!q.empty())
	{
		for (auto e : gr.GetAdjList(q.top().getV()))
		{
			if (d[e.getVertex() - 1] < min(d[q.top().getV() - 1], e.getCapacity()))
			{
				p[e.getVertex() - 1] = q.top().getV();
				d[e.getVertex() - 1] = min(d[q.top().getV() - 1], e.getCapacity());
				q.fixHeap(vertex(e.getVertex(), (float)e.getCapacity()) , d[e.getVertex() - 1]);
			}
		}
		q.pop();
	}
}
//-----------------------------------------------------------------------------------------------------------------------------
//The function return the min flow in a path from s to t
int findMin(graph& GF, std::vector<int>& p, int t)
{
	int min = -1;
	int i = t;
	while (p[i - 1] != -1)
	{
		std::list<edge>& l = GF.GetAdjList(p[i - 1]);
		for (auto& v : l)
		{
			if (v == i)
			{
				if (min > v.getCapacity() - v.getFlow() || min == -1)
					min = v.getCapacity() - v.getFlow();
				break;
			}
		}
		i = p[i - 1];
	}
	return min;
}
//-----------------------------------------------------------------------------------------------------------------------------
//The function updates the capacity in the graph after adding flow(to the GF graph)
void updateCapacity(graph& GF, std::vector<int>& p, int t, int update)
{
	int i = t;
	while (p[i - 1] != -1)
	{
		std::list<edge>& lp = GF.GetAdjList(p[i - 1]);
		for (auto& v : lp)
		{
			if (v == i)
			{
				v.addCapacity(-1 * update);
				if (v.getCapacity() == 0)
					GF.RemoveEdge(p[i - 1], i);
				break;
			}
		}
		std::list<edge>& lc = GF.GetAdjList(i);
		GF.AddEdge(i, p[i - 1], 0);
		for (auto& v : lc)
		{
			if (v == p[i - 1])
			{
				v.addCapacity(update);
				break;
			}
		}
		i = p[i - 1];
	}
}
//-----------------------------------------------------------------------------------------------------------------------------
//The function update the flow in the graph, adding a flow in a path from s to t
void updateFlow(graph& G, std::vector<int>& p, int t, int update)
{
	int i = t;
	while (p[i - 1] != -1)
	{
		std::list<edge>& lp = G.GetAdjList(p[i - 1]);
		for (auto& v : lp)
		{
			if (v == i)
			{
				v.addFlow(update);
				break;
			}
		}
		std::list<edge>& lc = G.GetAdjList(i);
		G.AddEdge(i, p[i - 1], 0);
		for (auto& v : lc)
		{
			if (v == p[i - 1])
			{
				v.addFlow(-1 * update);
				break;
			}
		}
		i = p[i - 1];
	}
}
//-----------------------------------------------------------------------------------------------------------------------------
//The function update a path from s to t, adding to it the max amount of flow that can be add
void updatePath(graph& GF, graph& G, std::vector<int>& p, int t)
{
	int min = findMin(GF, p, t);
	updateCapacity(GF, p, t, min);
	updateFlow(G, p, t, min);
}
//-----------------------------------------------------------------------------------------------------------------------------
void fordfulkerson(graph& G, graph& GF, int t, int s, int n, bool flage)
{
	std::vector<int> p;
	std::vector<float> d;
	if(flage)	//ones run the algorithm with bfs and ones with the greedy method 
		bfs(s, GF, n, d, p);
	else
		Greedy_Method(s, GF, n, d, p);
	while (p[t - 1] != -1)
	{
		updatePath(GF, G, p, t);
		p.clear();
		d.clear();
		if (flage)	//ones run the algorithm with bfs and ones with the greedy method
			bfs(s, GF, n, d, p);
		else
			Greedy_Method(s, GF, n, d, p);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------
void printOutPut(graph& G, graph& GF, int s, int t, int vertexs, bool flage)
{
	fordfulkerson(G, GF, t, s, vertexs, flage);
	int flow = 0;
	for (auto v : G.GetAdjList(s))
		flow += v.getFlow();	//sum flow in edges going out from s
	std::cout << "Max flow: " << flow << std::endl;

	std::vector<float> d;
	std::vector<int> p;

	bfs(s, GF, vertexs, d, p);
	std::cout << "Min cut : S = " << s;	//print accessible to s in GF
	for (int i = 0; i < p.size(); ++i)	
		if (p[i] != -1)
			std::cout << ", " << i + 1;
	std::cout << ".";

	std::cout << " T = ";
	int temp = -1;
	for (int i = 0; i < p.size(); ++i)	//print not accessible to s in GF
		if (p[i] == -1 && i != (s - 1))
		{
			if (temp != -1)
				std::cout << temp << ", ";
			temp = i + 1;
		}
	if (temp != -1)
		std::cout << temp << std::endl;
}
//-----------------------------------------------------------------------------------------------------------------------------

/*
G.AddEdge(1, 2, 16);
G.AddEdge(1, 3, 13);
G.AddEdge(2, 3, 10);
G.AddEdge(3, 2, 4);
G.AddEdge(2, 4, 12);
G.AddEdge(4, 3, 9);
G.AddEdge(3, 5, 14);
G.AddEdge(5, 4, 7);
G.AddEdge(4, 6, 20);
G.AddEdge(5, 6, 4);
*/