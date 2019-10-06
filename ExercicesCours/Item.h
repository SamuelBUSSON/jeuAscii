#pragma once
#include <string>
class Item 
{
protected:
	std::string name;
	std::string description;

public:
	Item();
	~Item();

	virtual void OnUse();

	inline std::string const GetName() const { return name; }
	inline std::string const GetDescription() const { return description; }
};

