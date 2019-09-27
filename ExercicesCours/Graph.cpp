#include "pch.h"
#include "Graph.h"


Graph::Graph()
{

}


Graph::~Graph()
{
}


void Graph::AddNode(int x, int y, Node * n) 
{
	Vector2 v;
	v.x = x;
	v.y = y;
	graphMap[v] = n;
	n->SetGraphPos(v);
	n->SetMapLink();
}

Node* Graph::GetNodeCoord(Vector2 v)
{
	if (graphMap[v]) {
		return graphMap[v];
	}
	return nullptr;
}