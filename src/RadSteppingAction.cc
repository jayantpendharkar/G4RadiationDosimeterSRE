#include "RadSteppingAction.hh"

#include "RadDetectorConstruction.hh"
#include "RadEventAction.hh"
#include "RadUserEventInformation.hh"
#include "G4SteppingManager.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
//#include "G4Step.hh"

////#include "G4RunManager.hh"

class G4VProcess;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadSteppingAction::RadSteppingAction(RadDetectorConstruction* det,
                                         RadEventAction* evt)
:detector(det), eventaction(evt)					 
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadSteppingAction::~RadSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadSteppingAction::UserSteppingAction(const G4Step* aStep)
{

  RadUserEventInformation* eventInfo 
	= (RadUserEventInformation*)G4EventManager::GetEventManager()
	->GetConstCurrentEvent()->GetUserInformation();

  RadDetectorConstruction* det 
	= (RadDetectorConstruction*)G4RunManager::GetRunManager()
	->GetUserDetectorConstruction();

  //get step Id
  G4int stepId = aStep->GetTrack()->GetCurrentStepNumber();
  
  //get track Id
  G4int trackId = aStep->GetTrack()->GetTrackID();

 // G4int stepInd = trackId*(stepId + 1);  
  G4int stepInd = trackId*stepId;  

// get particle name
  G4String particle = "UNDEF";
   	particle = aStep->GetTrack()->GetDefinition()->GetParticleName();
 
// get process name
  G4String process = "UNDEF";
  if(aStep->GetPostStepPoint()->GetProcessDefinedStep() != 0){
	process = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    } else {
	process = "UserLimit";
    }

// get pre-step kinetic energy of particle  (pre-step is important for electron)
  G4double preStepKinEne = aStep->GetPreStepPoint()->GetKineticEnergy();
  G4double postStepKinEne = aStep->GetPostStepPoint()->GetKineticEnergy();

// get energy deposited in the step (for electrons this coming more then preKinEne???)
  G4double stpEneDep = aStep->GetTotalEnergyDeposit();

// get pre and post step positions
  G4ThreeVector preStepPos = aStep->GetPreStepPoint()->GetPosition();
  G4ThreeVector postStepPos = aStep->GetPostStepPoint()->GetPosition();

// get pre and post step volume

  G4String preStepVolName = "Unknown";
	preStepVolName = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName();
  G4String postStepVolName = "Unknown";

  if(aStep->GetPostStepPoint()->GetPhysicalVolume() != 0)
	postStepVolName = aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName();

  // get momentum direction 
  G4ThreeVector mtmDir = aStep->GetTrack()->GetMomentumDirection();

  // Reference direction
  G4ThreeVector refDir(0.0, -1.0, 0.0);
  G4ThreeVector X(1.0, 0.0, 0.0);

  eventInfo->IncTotalSteps();

if (stepInd < MAX_STEPS){	
  eventInfo->SetTrackId(stepInd, trackId);
  eventInfo->SetStepId(stepInd, stepId);
  eventInfo->SetParticleName(stepInd, particle);
  eventInfo->SetProcessName(stepInd, process);
  eventInfo->SetPreStepKinEne(stepInd, preStepKinEne);
  eventInfo->SetPostStepKinEne(stepInd, postStepKinEne);
  eventInfo->SetStepEneDep(stepInd, stpEneDep);
  eventInfo->SetPreStepPos(stepInd, preStepPos);
  eventInfo->SetPostStepPos(stepInd, postStepPos);
  eventInfo->SetPreStepVolName(stepInd, preStepVolName);
  eventInfo->SetPostStepVolName(stepInd, postStepVolName);
  eventInfo->SetStepMtmDir(stepInd, mtmDir);
} else {
	eventInfo->SetStepsOverflow(true);
}

G4int preStepVol = det->CheckInteractionVol(preStepVolName);
G4int postStepVol = det->CheckInteractionVol(postStepVolName);

G4cout << stepInd << "\t" << preStepVol << " Volume  " << postStepVol << G4endl;
  if (particle == "proton"){

//	if (postStepVol == NO_MATERIAL){
//	eventInfo->SetNoMat_IntPos(preStepPos);
//	eventInfo->AddNoMat_EneDep(preStepKinEne - postStepKinEne);
//G4cout << preStepPos << "In Vaccum" << postStepPos << G4endl;
//}

	if (preStepVol == AL_SHIELD){
	eventInfo->IncShieldTotInt();
	eventInfo->SetShieldIntPos(postStepPos);
	eventInfo->AddShieldEneDep(preStepKinEne - postStepKinEne);

} else if (preStepVol == SI_ACTIVE_TOP){

	eventInfo->IncActive_topTotInt();
	eventInfo->SetActive_topIntPos(postStepPos);
	eventInfo->AddActive_topEneDep(preStepKinEne - postStepKinEne);

} else	if (preStepVol == PB_ABS){

	eventInfo->IncAbsorberTotInt();
	eventInfo->SetAbsorberIntPos(postStepPos);
	eventInfo->AddAbsorberEneDep(preStepKinEne - postStepKinEne);

} else if (preStepVol == SI_ACTIVE_BOT){

	eventInfo->IncActive_botTotInt();
	eventInfo->SetActive_botIntPos(postStepPos);
	eventInfo->AddActive_botEneDep(preStepKinEne - postStepKinEne);
}

}

/*	if (stpEneDep > 0){
		postStepVol = SI_ACTIVE_1;
		preStepKinEne_Si = preStepKinEne - postStepKinEne;
G4cout << preStepKinEne << "\t"<< postStepKinEne << "\t" << preStepKinEne_Si << "In Silicon" << G4endl;
		eventInfo->IncActive_1TotInt();
		eventInfo->SetActive_1IntPos(preStepPos);
	eventInfo->AddActive_1EneDep(postStepKinEne - preStepKinEne_Si);} */
// G4cout << preStepKinEne_Si << "Look Here" << G4endl;	
/*	if (preStepVol == AL_SHIELD){
		eventInfo->IncShieldTotInt();
//		eventInfo->SetShieldIntPos(postStepPos);
		eventInfo->AddShieldEneDep(postStepKinEne);
		eventInfo->SetShieldIntPos(postStepPos);
		} else {
	eventInfo->SetShieldEleEscape(true);
	eventInfo->AddShieldEneDep(preStepKinEne - postStepKinEne);
		} 
*/
/*  if (preStepVol == AL_SHIELD){
	if(postStepVol == preStepVol){
		eventInfo->AddShieldEneDep(preStepKinEne);
		eventInfo->SetShieldIntPos(preStepPos);
	} else {
		eventInfo->AddShieldEneDep(preStepKinEne - postStepKinEne);
	}
  }*/
/*
    if (postStepVol == SI_ACTIVE_1){
//	if (postStepVol == preStepVol){
		eventInfo->IncActive_1TotInt();
	//	eventInfo->SetActive_1IntPos(postStepPos);
		eventInfo->AddActive_1EneDep(preStepKinEne);
		eventInfo->SetActive_1IntPos(postStepPos);
	} else {
		eventInfo->AddActive_1EneDep(preStepKinEne - postStepKinEne);
	}
  // } 
*/
/*   if (preStepVol == SI_ACTIVE_1){
	if(postStepVol == preStepVol){
		eventInfo->AddActive_1EneDep(preStepKinEne);
		eventInfo->SetActive_1IntPos(preStepPos);
	} else {
		eventInfo->AddActive_1EneDep(preStepKinEne - postStepKinEne);
	}
  } */

/*  if (preStepVol == PB_ABS){
	if(postStepVol == preStepVol){
		eventInfo->IncAbsTotInt();
		eventInfo->SetAbsIntPos(postStepPos);
		eventInfo->AddAbsEneDep(preStepKinEne);
		eventInfo->SetAbsIntPos(preStepPos);
	} else {
		eventInfo->AddAbsEneDep(preStepKinEne - postStepKinEne);
	}
  } */

/*  if (preStepVol == PB_ABS){
	if(postStepVol == preStepVol){
		eventInfo->AddAbsEneDep(preStepKinEne);
		eventInfo->SetAbsIntPos(preStepPos);
	} else {
		eventInfo->AddAbsEneDep(preStepKinEne - postStepKinEne);
	}
  } 

  if (preStepVol == SI_ACTIVE_2){
	if(postStepVol == preStepVol){
		eventInfo->AddActive_2EneDep(preStepKinEne);
		eventInfo->SetActive_2IntPos(preStepPos);
	} else {
		eventInfo->AddActive_2EneDep(preStepKinEne - postStepKinEne);
	}
  }
*/
//}
  /* else if (particle == "e-"){
        if (preStepVol == AL_SHIELD){
                if(postStepVol == preStepVol){
                        eventInfo->AddShieldEneDep(preStepKinEne);
                        eventInfo->SetShieldIntPos(preStepPos);
                } else {
                        eventInfo->SetShieldEleEscape(true);
                        eventInfo->AddShieldEneDep(preStepKinEne-postStepKinEne);
                }
        }

        if (preStepVol == SI_ACTIVE_1){
                if(postStepVol == preStepVol){
                        eventInfo->AddActive_1EneDep(preStepKinEne);
                        eventInfo->SetActive_1IntPos(preStepPos);
                } else {
                        eventInfo->SetActive_1EleEscape(true);
                        eventInfo->AddActive_1EneDep(preStepKinEne-postStepKinEne);
                }
        }
        if (preStepVol == PB_ABS){
                if(postStepVol == preStepVol){
                        eventInfo->AddAbsEneDep(preStepKinEne);
                        eventInfo->SetAbsIntPos(preStepPos);
                } else {
                        eventInfo->SetAbsEleEscape(true);
                        eventInfo->AddAbsEneDep(preStepKinEne-postStepKinEne);
                }
        }

        if (preStepVol == SI_ACTIVE_2){
                if(postStepVol == preStepVol){
                        eventInfo->AddActive_2EneDep(preStepKinEne);
                        eventInfo->SetActive_2IntPos(preStepPos);
                } else {
                        eventInfo->SetActive_2EleEscape(true);
                        eventInfo->AddActive_2EneDep(preStepKinEne-postStepKinEne);
                }
        }
} 

*/

/*
  // get volume of the current step
  G4VPhysicalVolume* volume 
  = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  
  // collect energy and track length step by step
  G4double edep = aStep->GetTotalEnergyDeposit();
  
  G4double stepl = 0.;
  if (aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
    stepl = aStep->GetStepLength();
      
//  if (volume == detector->GetShield()) eventaction->AddShield(edep,stepl);
//  if (volume == detector->GetActive_1()) eventaction->AddActive_1(edep,stepl);
  if (volume == detector->GetAbsorber()) eventaction->AddAbs(edep,stepl);
//  if (volume == detector->GetActive_2())      eventaction->AddActive_2(edep,stepl);
  
  //example of saving random number seed of this event, under condition
  //// if (condition) G4RunManager::GetRunManager()->rndmSaveThisEvent(); 
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
