#include "pch.h"
#include "InfoLine.h"
#include "ScreenManager.h"


InfoLine::InfoLine(std::string _text, int _color)
	:text(_text), color(_color)
{
}


InfoLine::~InfoLine()
{
}

void InfoLine::OnClick()
{
}

void InfoLine::OnHighlight()
{
}

void InfoLine::OnLeaveHighlight()
{
	ScreenManager::Instance().SetDescription("");
}