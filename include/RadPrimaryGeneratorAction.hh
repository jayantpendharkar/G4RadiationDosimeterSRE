#ifndef RadPrimaryGeneratorAction_h
#define RadPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4GeneralParticleSource;
class G4Event;

class RadPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    RadPrimaryGeneratorAction();
    ~RadPrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* anEvent);

  private:

    G4GeneralParticleSource* particleGun;
};

#endif
