#pragma once
#include <string>

class InfoLine
{
public:
	std::string text;
	int color;

	InfoLine(std::string _text, int _color);
	~InfoLine();

	virtual void OnClick();
	virtual void OnHighlight();
	void OnLeaveHighlight();
};

