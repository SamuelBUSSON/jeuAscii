#pragma once

#ifndef DEF_INFOPANEL
#define DEF_INFOPANEL

#include <string>

class InfoPanel
{
private:
	std::string text;
	int textColor;

public:
	InfoPanel();
	~InfoPanel();


	inline void SetString(std::string str) { text = str; }

	inline std::string GetText() const { return text; }
	inline int GetTextColor() const { return textColor; }
};

#endif
