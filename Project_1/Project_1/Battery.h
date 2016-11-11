#ifndef BATTERY_INCLUDED
#define BATTERY_INCLUDED

class Battery
{
	public:
		Battery(int initialLevel);
		int level() const;
		void decrease();
	private:
		int battery_Level;
};

#endif