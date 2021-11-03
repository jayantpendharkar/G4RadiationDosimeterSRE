//
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  Title:  Space Sciences Physics List                                    //
//  Date:   20 March 2005                                                  //
//  Author: D.H. Wright (SLAC)                                             //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//

#include "RadPhysicsList.hh"

#include "RadDecayPhysics.hh"
#include "RadBosonPhysics.hh"
#include "RadLeptonPhysics.hh"
#include "RadNeutronPhysics.hh"
#include "RadHadronPhysics.hh"
#include "RadIonPhysics.hh"

RadPhysicsList::RadPhysicsList():  G4VModularPhysicsList()
{
  // default cut value  (1.0mm) 
  defaultCutValue = 1.0*mm;
  // SetVerboseLevel(1);

  // Particle decays
  RegisterPhysics( new RadDecayPhysics("decay"));

  // Bosons (gamma + geantinos)
  RegisterPhysics( new RadBosonPhysics("boson"));

  // Leptons
  RegisterPhysics( new RadLeptonPhysics("lepton"));

  // Neutron Physics
  RegisterPhysics( new RadNeutronPhysics("neutron"));

  // Hadron Physics
  RegisterPhysics( new RadHadronPhysics("hadron"));

  // Ion Physics
  RegisterPhysics( new RadIonPhysics("ion"));
}

RadPhysicsList::~RadPhysicsList()
{;}

void RadPhysicsList::SetCuts()
{
  // Use default cut values gamma and e processes
  SetCutsWithDefault();   
}
