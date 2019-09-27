#pragma once

#include <vector>
#include <map>

#include "Node.h"


class Graph
{

	private:
		std::vector<Node*> v;
		Node* currentNode;
		std::map<Vector2, Node*> graphMap;

	public:
		Graph();
		~Graph();

		void AddNode(int x, int y, Node * n);

		Node* GetNodeCoord(Vector2 v);

		inline Node* GetCurrentNode() { return currentNode; }


};

