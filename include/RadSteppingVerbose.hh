
class RadSteppingVerbose;

#ifndef RadSteppingVerbose_h
#define RadSteppingVerbose_h 1

#include "G4SteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RadSteppingVerbose : public G4SteppingVerbose
{
 public:   

   RadSteppingVerbose();
  ~RadSteppingVerbose();

   void StepInfo();
   void TrackingStarted();

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
