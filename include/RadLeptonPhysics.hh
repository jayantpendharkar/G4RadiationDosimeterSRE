//
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  Title:  Lepton Physics for Space Sciences Physics List                 //
//  Date:   22 March 2005                                                  //
//  Author: D.H. Wright (SLAC)                                             //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//

#ifndef RadLeptonPhysics_h
#define RadLeptonPhysics_h 1

#include "G4VPhysicsConstructor.hh"


class RadLeptonPhysics : public G4VPhysicsConstructor
{
  public: 
    RadLeptonPhysics(const G4String& name ="lepton");
    virtual ~RadLeptonPhysics();

    // This method will be invoked in the Construct() method. 
    // each particle type will be instantiated
    virtual void ConstructParticle();
 
    // This method will be invoked in the Construct() method.
    // each physics process will be instantiated and
    // registered to the process manager of each particle type 
    virtual void ConstructProcess();

};

#endif





