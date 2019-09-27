#include "pch.h"
#include "Node.h"

#include "Graph.h"
#include "GameManager.h"
#include <iostream>
#include <fstream>  
#include <string>  
#include <filesystem>  

#include <vector>

using namespace std;


void SetCharAtCoord2(int x, int y, std::string &s, char c)
{
	s[x + (y * (MAP_WIDTH + 1))] = c;
}

Node::Node(std::string mapPath) : src(mapPath)
{
}

Node::~Node()
{

}

void Node::AddAdjacent(Direction d, Node * n)
{
	adjacent_map[d] = n ;
	SetMapLink();
	AddAdjacentNewNode(d, n);
}

void Node::AddAdjacentNewNode(Direction d, Node * n)
{
	int i(d);
	Direction dF = static_cast<Direction>((i + 2) % 4);
	n->AddMapAdjacent( dF, this );

	n->SetMapLink();
}

void Node::AddMapAdjacent(Direction d, Node* n)
{
	adjacent_map[d] = n;
}

Node* Node::GetNodeAdjacent(Direction d)
{
	if (adjacent_map[d]) {
		return  adjacent_map[d];
	}
	return nullptr;
}


void Node::CheckMapAround() {
	Graph* mainGraph = GameManager::Instance().GetGraph();


	Vector2 v = posInGraph;
	v.x--;

	Node* nodeCoord = mainGraph->GetNodeCoord(v);
	if (nodeCoord != nullptr) {
		AddAdjacent(West, nodeCoord);
	}

	v.x += 2;
	nodeCoord = mainGraph->GetNodeCoord(v);
	if (nodeCoord != nullptr) {
		AddAdjacent(East, nodeCoord);
	}

	v = posInGraph;
	v.y++;
	nodeCoord = mainGraph->GetNodeCoord(v);
	if (nodeCoord != nullptr) {
		AddAdjacent(North, nodeCoord);
	}

	v.y -= 2;
	nodeCoord = mainGraph->GetNodeCoord(v);
	if (nodeCoord != nullptr) {
		AddAdjacent(South, nodeCoord);
	}
}

void Node::SetMapLink()
{
	ifstream inFile;
	inFile.open(src);
	string finalString;

	string line;
	std::getline(inFile, line);


	for (int i = 0; i < 4; i++)
	{
		if (adjacent_map[(Direction)i])
		{		
			finalString += adjacent_map[(Direction)i]->GetMapName();
		}
		finalString += " ,";
	}
	finalString += "x : " + to_string(posInGraph.x) + " y : " + to_string(posInGraph.y) + "\n";

	while (std::getline(inFile, line))
	{
			finalString += line + '\n';
	}

	inFile.close();

	ofstream outFile;
	outFile.open(src);

	outFile << finalString;

	outFile.close();
}
