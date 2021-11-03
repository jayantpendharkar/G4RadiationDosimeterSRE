//
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  Title:  Hadron Physics for Space Sciences Physics List                 //
//  Date:   20 March 2005                                                  //
//  Author: D.H. Wright (SLAC)                                             //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//

#ifndef RadHadronPhysics_h
#define RadHadronPhysics_h 1

#include "G4VPhysicsConstructor.hh"

class RadHadronPhysics : public G4VPhysicsConstructor
{
  public: 
    RadHadronPhysics(const G4String& name ="hadron");
    virtual ~RadHadronPhysics();

    // This method will be invoked in the Construct() method. 
    // each particle type will be instantiated
    virtual void ConstructParticle();
 
    // This method will be invoked in the Construct() method.
    // each physics process will be instantiated and
    // registered to the process manager of each particle type 
    virtual void ConstructProcess();

};

#endif





