#ifndef RadSteppingAction_h
#define RadSteppingAction_h 1

#include "G4UserSteppingAction.hh"

class RadDetectorConstruction;
class RadEventAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RadSteppingAction : public G4UserSteppingAction
{
public:
  RadSteppingAction(RadDetectorConstruction*, RadEventAction*);
 ~RadSteppingAction();

  void UserSteppingAction(const G4Step*);
    
private:
  RadDetectorConstruction* detector;
  RadEventAction*          eventaction;  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
