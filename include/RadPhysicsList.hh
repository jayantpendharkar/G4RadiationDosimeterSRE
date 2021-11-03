//
////////////////////////////////////////////////////////////////
//                                                            //
//  Title:  Space Sciences Physics List                       //
//  Date:   20 March 2005                                     //
//  Author: D.H. Wright (SLAC)                                //
//                                                            //
////////////////////////////////////////////////////////////////
//

#ifndef RadPhysicsList_h
#define RadPhysicsList_h 1

#include "G4VModularPhysicsList.hh"


class RadPhysicsList: public G4VModularPhysicsList
{
public:
  RadPhysicsList();
  virtual ~RadPhysicsList();
  
  virtual void SetCuts();
};

#endif



