#ifndef VALLEY_INCLUDED
#define VALLEY_INCLUDED

typedef unsigned long ItemType;

#include <string>
#include "globals.h"

class EnergySource;
class Robot;

class Valley
{
  public:
        // Constructor/destructor
    Valley(int nr, int nc);
    ~Valley();

        // Accessors
    int    rows() const;
    int    cols() const;
    void   display() const;
    bool   energySourceAt(int r, int c) const;
    Robot* otherRobotAt(Robot* rp) const;
    Robot* getRobotByName(std::string name) const;

        // Mutators
    bool   addRobot(std::string name, int r, int c, int d);
    bool   addEnergySource(int r, int c);
    bool   step();

  private:
    int           m_rows;
    int           m_cols;
    Robot*        m_robots[MAXROBOTS];
    int           m_nRobots;
    EnergySource* m_sources[MAXSOURCES];
    int           m_nSources;
    int           m_nSteps;
};

#endif