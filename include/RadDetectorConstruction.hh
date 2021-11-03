#ifndef RadDetectorConstruction_H
#define RadDetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"

#define AL_SHIELD     100
#define SI_ACTIVE_TOP 200
#define SI_ACTIVE_BOT 300
#define PB_ABS        400
#define NO_MATERIAL   500

class RadDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    RadDetectorConstruction();
    ~RadDetectorConstruction();

    G4VPhysicalVolume* Construct();
  
    G4int CheckInteractionVol(G4String&);

//  private:

};

#endif

