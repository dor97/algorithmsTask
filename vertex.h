#pragma once
//-----------------------------------------------------------------------------------------------------------------------------
class vertex {

	int v;		//vertex
	float c;	//the max flow that can go through the vertex out of all the path from s to it
public:
	vertex() : v(0), c(0) { }
	vertex(int v, float c) : v(v), c(c) {}
	bool operator<(const vertex& u) const { if (c == u.c) return v < u.v; return c < u.c; }
	bool operator>(const vertex& u) const { if (c == u.c) return v > u.v; return c > u.c; }
	int getV() const { return v; }
	float getC() { return c; }
	void setC(float c) {this->c = c; }

};
//-----------------------------------------------------------------------------------------------------------------------------