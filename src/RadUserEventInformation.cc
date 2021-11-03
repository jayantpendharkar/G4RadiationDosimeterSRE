#include "RadUserEventInformation.hh"

RadUserEventInformation::RadUserEventInformation()
{
   TotalSteps = 0;

   nStepsOverflow = 0;

   nShieldTotInt = 0;
   ShieldEleEscape = 0;
   ShieldEneDep = 0.0;
   ShieldIntPos.setX(0.0);
   ShieldIntPos.setY(0.0);
   ShieldIntPos.setZ(0.0);

   nActive_topTotInt = 0;
   Active_topEleEscape = 0;
   Active_topEneDep = 0.0;
   Active_topIntPos.setX(0.0);
   Active_topIntPos.setY(0.0);
   Active_topIntPos.setZ(0.0);

   nAbsorberTotInt = 0;
   AbsorberEleEscape = 0;
   AbsorberEneDep = 0.0;
   AbsorberIntPos.setX(0.0);
   AbsorberIntPos.setY(0.0);
   AbsorberIntPos.setZ(0.0);

   nActive_botTotInt = 0;
   Active_botEleEscape = 0;
   Active_botEneDep = 0.0;
   Active_botIntPos.setX(0.0);
   Active_botIntPos.setY(0.0);
   Active_botIntPos.setZ(0.0);

   nNoMaterial_TotInt = 0;
   NoMaterial_EleEscape = 0;
   NoMaterial_EneDep = 0.0;
   NoMaterial_IntPos.setX(0.0);
   NoMaterial_IntPos.setY(0.0);
   NoMaterial_IntPos.setZ(0.0);

G4int i;
for(i=0;i<MAX_STEPS;i++){
// G4cout << "Repeat" << G4endl;
   EvtStepInd[i].stepId = 99;
   EvtStepInd[i].trackId = 99;

   EvtStepInd[i].ProcName = "nullstr";
   EvtStepInd[i].ParticleName = "nullstr";

   EvtStepInd[i].preKinEne = 77.789;
   EvtStepInd[i].postKinEne = 77.789;
   EvtStepInd[i].stpEneDep = 77.789;

   EvtStepInd[i].preStepVol = "nullvol";
   EvtStepInd[i].postStepVol = "nullvol";

   EvtStepInd[i].preStepPos.setX(0.0);
   EvtStepInd[i].preStepPos.setY(0.0);
   EvtStepInd[i].preStepPos.setZ(0.0);
   EvtStepInd[i].postStepPos.setX(0.0);
   EvtStepInd[i].postStepPos.setY(0.0);
   EvtStepInd[i].postStepPos.setZ(0.0);

   EvtStepInd[i].mtmDir.setX(0.0);
   EvtStepInd[i].mtmDir.setY(0.0);
   EvtStepInd[i].mtmDir.setZ(0.0);
//G4cout << EvtStepInd[i].stepId << G4endl;
   }

}

RadUserEventInformation::~RadUserEventInformation()
{
}
