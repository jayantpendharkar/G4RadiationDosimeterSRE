#ifndef RadRunAction_h
#define RadRunAction_h 1

#include "G4UserRunAction.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"
#include <fstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;

class RadRunAction : public G4UserRunAction
{
public:
  RadRunAction();
 ~RadRunAction();

  void BeginOfRunAction(const G4Run*);
  void   EndOfRunAction(const G4Run*);
    
//  void fillPerEvent(G4double, G4double, G4double, G4double, G4double, G4double, G4double, G4double); 

  void WriteOutOld(G4int,G4int,G4int,G4String,G4String,G4double,
		G4double,G4double,G4String,G4String,
		G4bool,G4bool,G4bool);

    void WriteOut(const G4Event*); 
    void WriteOutSteps(const G4Event*); 
    void IncNumEvt(void){nNumEvt++;}
    void ResetNumEvt(void){nNumEvt = 0;}
    G4int GetNumEvt(void){return nNumEvt;}

private:

  std::ofstream outFile;
  
  G4int nNumEvt;
/*
  G4double sumEShield, sum2EShield;
  G4double sumEActive_top, sum2EActive_top;
  G4double sumEAbsorber, sum2EAbsorber;
  G4double sumEActive_bot, sum2EActive_bot;
    
  G4double sumLShield, sum2LShield;
  G4double sumLActive_top, sum2LActive_top;
  G4double sumLAbsorber, sum2LAbsorber;
  G4double sumLActive_bot, sum2LActive_bot;    */
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
