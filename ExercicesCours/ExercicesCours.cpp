#include "pch.h"
#include "ScreenManager.h"

#include <iostream>

int main()
{
	ScreenManager sm;
	sm.Init();


	while (!sm.GetExitGame())
	{
		sm.SampleDisplay();
		sm.Update();
	}

}

