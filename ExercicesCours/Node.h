#pragma once

#include <iostream>
#include <map>

#include "MapGenerator.h"


struct Vector2
{
	int x;
	int y;

	bool operator<(const Vector2 &o)  const {
		return x < o.x || (x == o.x && y < o.y);
	}

	bool operator==(const Vector2 &o) {
		return x == o.x && y == o.y;
	}

};

class Node
{
	private:
		std::string src;
		std::map<Direction, Node*> adjacent_map;

		Vector2 posInGraph;

	public:
		Node(std::string mapPath);
		~Node();

		void AddAdjacent(Direction d, Node* n);
		void AddAdjacentNewNode(Direction d, Node * n);
		Node* GetNodeAdjacent(Direction d);
		void CheckMapAround();
		void SetMapLink();

		void AddMapAdjacent(Direction d, Node* n);

		inline std::string GetMapName() const { return src; }
		inline Vector2 GetPos() const { return posInGraph; }

		inline void SetGraphPos(Vector2 v) { posInGraph = v; }
};

