//
#include "G4VUserEventInformation.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
//#include "G4Step.hh"
#include "G4VProcess.hh"

#ifndef RadUserEventInformation_h
#define RadUserEventInformation_h 1

#define MAX_STEPS 10

class RadUserEventInformation : public G4VUserEventInformation
{
public:
  RadUserEventInformation();
 ~RadUserEventInformation();
  
  inline void Print()const{};

  void IncTotalSteps(){TotalSteps++;}
  G4int GetTotalSteps(){return TotalSteps;}

  void SetStepsOverflow(G4bool val){nStepsOverflow = val;}
  G4bool GetStepsOverflow(){return nStepsOverflow;}

  void IncShieldTotInt(){nShieldTotInt++;}
  G4int GetShieldTotInt(){return nShieldTotInt;}

  void SetShieldEleEscape(G4bool val){ShieldEleEscape = val;}
  G4bool GetShieldEleEscape(){return ShieldEleEscape;}

  void AddShieldEneDep(G4double val){ShieldEneDep += val;}
  G4double GetShieldEneDep(){return ShieldEneDep;}

  void SetShieldIntPos(G4ThreeVector val){ShieldIntPos = val;}
  G4ThreeVector& GetShieldIntPos(){return ShieldIntPos;}

  void IncActive_topTotInt(){nActive_topTotInt++;}
  G4int GetActive_topTotInt(){return nActive_topTotInt;}

  void SetActive_topEleEscape(G4bool val){Active_topEleEscape = val;}
  G4bool GetActive_topEleEscape(){return Active_topEleEscape;}

  void AddActive_topEneDep(G4double val){Active_topEneDep += val;}
  G4double GetActive_topEneDep(){return Active_topEneDep;}

  void SetActive_topIntPos(G4ThreeVector val){Active_topIntPos = val;}
  G4ThreeVector& GetActive_topIntPos(){return Active_topIntPos;}

  void IncAbsorberTotInt(){nAbsorberTotInt++;}
  G4int GetAbsorberTotInt(){return nAbsorberTotInt;}

  void SetAbsorberEleEscape(G4bool val){AbsorberEleEscape = val;}
  G4bool GetAbsorberEleEscape(){return AbsorberEleEscape;}

  void AddAbsorberEneDep(G4double val){AbsorberEneDep += val;}
  G4double GetAbsorberEneDep(){return AbsorberEneDep;}

  void SetAbsorberIntPos(G4ThreeVector val){AbsorberIntPos = val;}
  G4ThreeVector& GetAbsorberIntPos(){return AbsorberIntPos;}

  void IncActive_botTotInt(){nActive_botTotInt++;}
  G4int GetActive_botTotInt(){return nActive_botTotInt;}

  void SetActive_botEleEscape(G4bool val){Active_botEleEscape = val;}
  G4bool GetActive_botEleEscape(){return Active_botEleEscape;}

  void AddActive_botEneDep(G4double val){Active_botEneDep += val;}
  G4double GetActive_botEneDep(){return Active_botEneDep;}

  void SetActive_botIntPos(G4ThreeVector val){Active_botIntPos = val;}
  G4ThreeVector& GetActive_botIntPos(){return Active_botIntPos;}

  void IncNoMaterial_TotInt(){nNoMaterial_TotInt++;}
  G4int GetNoMaterial_TotInt(){return nNoMaterial_TotInt;}

  void SetNoMaterial_EleEscape(G4bool val){NoMaterial_EleEscape = val;}
  G4bool GetNoMaterial_EleEscape(){return NoMaterial_EleEscape;}

  void AddNoMaterial_EneDep(G4double val){NoMaterial_EneDep += val;}
  G4double GetNoMaterial_EneDep(){return NoMaterial_EneDep;}

  void SetNoMaterial_IntPos(G4ThreeVector val){NoMaterial_IntPos = val;}
  G4ThreeVector& GetNoMaterial_IntPos(){return NoMaterial_IntPos;}

private:
   
   G4int TotalSteps;

   G4bool nStepsOverflow;

   G4int nShieldTotInt;  
   G4bool ShieldEleEscape;
   G4double ShieldEneDep;
   G4ThreeVector ShieldIntPos;

   G4int  nActive_topTotInt;
   G4bool Active_topEleEscape;
   G4double Active_topEneDep;
   G4ThreeVector Active_topIntPos;

   G4int  nAbsorberTotInt;
   G4bool AbsorberEleEscape;
   G4double AbsorberEneDep;
   G4ThreeVector AbsorberIntPos;

   G4int  nActive_botTotInt;
   G4bool Active_botEleEscape;
   G4double Active_botEneDep;
   G4ThreeVector Active_botIntPos;

   G4int  nNoMaterial_TotInt;
   G4bool NoMaterial_EleEscape;
   G4double NoMaterial_EneDep;
   G4ThreeVector NoMaterial_IntPos;

public:

  void SetTrackId(G4int num, G4int val){EvtStepInd[num].trackId = val;}
  G4int GetTrackId(G4int num){return EvtStepInd[num].trackId;}

  void SetStepId(G4int num, G4int val){EvtStepInd[num].stepId = val;}
  G4int GetStepId(G4int num){return EvtStepInd[num].stepId;}

  void SetProcessName(G4int num, G4String str){EvtStepInd[num].ProcName = str;}
  G4String& GetProcessName(G4int num){return EvtStepInd[num].ProcName;}
  void SetParticleName(G4int num, G4String str){EvtStepInd[num].ParticleName = str;}
  G4String& GetParticleName(G4int num){return EvtStepInd[num].ParticleName;}

  void SetPreStepKinEne(G4int num, G4double val){EvtStepInd[num].preKinEne = val;}
  G4double GetPreStepKinEne(G4int num){return EvtStepInd[num].preKinEne;}
  void SetPostStepKinEne(G4int num, G4double val){EvtStepInd[num].postKinEne = val;}
  G4double GetPostStepKinEne(G4int num){return EvtStepInd[num].postKinEne;}
  void SetStepEneDep(G4int num, G4double val){EvtStepInd[num].stpEneDep = val;}
  G4double GetStepEneDep(G4int num){return EvtStepInd[num].stpEneDep;}

  void SetPreStepVolName(G4int num, G4String val){EvtStepInd[num].preStepVol = val;}
  G4String& GetPreStepVolName(G4int num){return EvtStepInd[num].preStepVol;}
  void SetPostStepVolName(G4int num, G4String val){EvtStepInd[num].postStepVol = val;}
  G4String& GetPostStepVolName(G4int num){return EvtStepInd[num].postStepVol;}

  void SetPreStepPos(G4int num, G4ThreeVector val){EvtStepInd[num].preStepPos = val;}
  G4ThreeVector& GetPreStepPos(G4int num){return EvtStepInd[num].preStepPos;}
  void SetPostStepPos(G4int num, G4ThreeVector val){EvtStepInd[num].postStepPos = val;}
  G4ThreeVector& GetPostStepPos(G4int num){return EvtStepInd[num].postStepPos;}

  void SetStepMtmDir(G4int num, G4ThreeVector val){EvtStepInd[num].mtmDir = val;}
  G4ThreeVector& GetStepMtmDir(G4int num){return EvtStepInd[num].mtmDir;}


private:
   struct Rad_steps_info{

   G4int trackId;
   G4int stepId;

   G4String ParticleName;
   G4String ProcName;

   G4double preKinEne;
   G4double postKinEne;
   G4double stpEneDep;

   G4String preStepVol;
   G4String postStepVol;

   G4ThreeVector preStepPos;
   G4ThreeVector postStepPos;

   G4ThreeVector mtmDir;

   }EvtStepInd[MAX_STEPS];

};

#endif
