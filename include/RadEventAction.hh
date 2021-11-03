#ifndef RadEventAction_h
#define RadEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class RadRunAction;
class RadEventActionMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RadEventAction : public G4UserEventAction
{
public:
  RadEventAction(RadRunAction*);
 ~RadEventAction();

  void  BeginOfEventAction(const G4Event*);
  void    EndOfEventAction(const G4Event*);

  void SetPrintModulo(G4int val) {printModulo = val;};
/*    
  void AddShield(G4double de, G4double dl) {EnergyShield += de; TrackLShield += dl;};

  void AddActive_top(G4double de, G4double dl) {EnergyActive_top += de; TrackLActive_top += dl;};

  void AddAbsorber(G4double de, G4double dl) {EnergyAbsorber += de; TrackLAbsorber += dl;};

  void AddActive_bot(G4double de, G4double dl) {EnergyActive_bot += de; TrackLActive_bot += dl;};
                     
  void SetPrintModulo(G4int    val)  {printModulo = val;};
*/    
private:
   RadRunAction*  runAct;
   
//   G4double  EnergyShield, EnergyActive_top, EnergyAbsorber, EnergyActive_bot;
//   G4double  TrackLShield, TrackLActive_top, TrackLAbsorber, TrackLActive_bot;
                     
   G4int     printModulo;
                             
//   RadEventActionMessenger*  eventMessenger;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
