#include "RadPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"

RadPrimaryGeneratorAction::RadPrimaryGeneratorAction()
{
   particleGun = new G4GeneralParticleSource();
}

RadPrimaryGeneratorAction::~RadPrimaryGeneratorAction()
{
  delete particleGun;
}

void RadPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  particleGun->GeneratePrimaryVertex(anEvent) ;
}
