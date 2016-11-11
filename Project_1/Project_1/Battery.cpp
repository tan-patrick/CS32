#include "Battery.h"
#include <iostream>
using namespace std;

Battery::Battery(int initialLevel)
{
	battery_Level = initialLevel;
}

int Battery::level() const
{
	return battery_Level;
}

void Battery::decrease()
{
	if(battery_Level > 0)
		battery_Level--;
}
