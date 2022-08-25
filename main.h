#pragma once

#include"graph.h"
#include<iostream>
#include"vertex.h"
#include"my_priority_queue.h"

//-----------------------------------------------------------------------------------------------------------------------------
void bfs(int s, graph& gr, int n, std::vector<float>& d, std::vector<int>& p);
float min(float d, int c);
void Greedy_Method(int s, graph& gr, int n, std::vector<float>& d, std::vector<int>& p);
int findMin(graph& GF, std::vector<int>& p, int t);
void updateCapacity(graph& GF, std::vector<int>& p, int t, int update);
void updateFlow(graph& G, std::vector<int>& p, int t, int update);
void updatePath(graph& GF, graph& G, std::vector<int>& p, int t);
void fordfulkerson(graph& G, graph& GF, int t, int s, int n, bool flage);
void printOutPut(graph& G, graph& GF, int s, int t, int vertexs, bool flage);
//-----------------------------------------------------------------------------------------------------------------------------