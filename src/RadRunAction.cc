#include "RadRunAction.hh"
#include "RadUserEventInformation.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include <iomanip>
#include <fstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadRunAction::RadRunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadRunAction::~RadRunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadRunAction::BeginOfRunAction(const G4Run* aRun)
{ 
  G4cout << "### Starting a new Run " << aRun->GetRunID() << G4endl;

  outFile.open("Table_out.txt");
  ResetNumEvt();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadRunAction::WriteOutSteps(const G4Event* evt)
{
  RadUserEventInformation* eventInfo
        =(RadUserEventInformation*)evt->GetUserInformation();

  G4int evtNb = evt->GetEventID();
  
  G4int totSteps = eventInfo->GetTotalSteps();

  G4int stpN;

  for (stpN = 0;stpN<=totSteps;stpN++){
	
	outFile	<< evtNb << "\t"
		<< eventInfo->GetTrackId(stpN) << "\t"
		<< eventInfo->GetStepId(stpN) << "\t"
  		<< eventInfo->GetParticleName(stpN) << "\t"
  		<< eventInfo->GetProcessName(stpN) << "\t"
	  	<< eventInfo->GetPreStepKinEne(stpN)/keV << "\t"
	  	<< eventInfo->GetPostStepKinEne(stpN)/keV << "\t"
  		<< eventInfo->GetStepEneDep(stpN)/MeV << "\t"
	  	<< eventInfo->GetPreStepVolName(stpN) << "\t"
	  	<< eventInfo->GetPostStepVolName(stpN) << "\t"
	  	<< eventInfo->GetPreStepPos(stpN) << "\t"
	  	<< eventInfo->GetPostStepPos(stpN) << "\t"
	  	<< eventInfo->GetStepMtmDir(stpN) << "\t"
		<< G4endl;
	}

}

void RadRunAction::WriteOut(const G4Event* evt)
{
 
  RadUserEventInformation* eventInfo
        =(RadUserEventInformation*)evt->GetUserInformation();

  G4int evtNb = evt->GetEventID();
  
  G4int totSteps = eventInfo->GetTotalSteps();

  G4int nShieldTotInt = eventInfo->GetShieldTotInt();
  G4bool ShieldEleEscape = eventInfo->GetShieldEleEscape();
  G4double ShieldEneDep = eventInfo->GetShieldEneDep();
  G4ThreeVector& ShieldIntPos = eventInfo->GetShieldIntPos();

  G4int nActive_topTotInt = eventInfo->GetActive_topTotInt();
  G4bool Active_topEleEscape = eventInfo->GetActive_topEleEscape();
  G4double Active_topEneDep = eventInfo->GetActive_topEneDep();
  G4ThreeVector& Active_topIntPos = eventInfo->GetActive_topIntPos();

  G4int nAbsorberTotInt = eventInfo->GetAbsorberTotInt();
  G4bool AbsorberEleEscape = eventInfo->GetAbsorberEleEscape();
  G4double AbsorberEneDep = eventInfo->GetAbsorberEneDep();
  G4ThreeVector& AbsorberIntPos = eventInfo->GetAbsorberIntPos();

  G4int nActive_botTotInt = eventInfo->GetActive_botTotInt();
  G4bool Active_botEleEscape = eventInfo->GetActive_botEleEscape();
  G4double Active_botEneDep = eventInfo->GetActive_botEneDep();
  G4ThreeVector& Active_botIntPos = eventInfo->GetActive_botIntPos();

  G4int nNoMaterial_TotInt = eventInfo->GetNoMaterial_TotInt();
  G4bool NoMaterial_EleEscape = eventInfo->GetNoMaterial_EleEscape();
  G4double NoMaterial_EneDep = eventInfo->GetNoMaterial_EneDep();
  G4ThreeVector& NoMaterial_IntPos = eventInfo->GetNoMaterial_IntPos();

if (ShieldEneDep > 0. && Active_topEneDep > 0. && AbsorberEneDep > 0. && Active_botEneDep > 0.){
  outFile	<< std::fixed 	<< std::setprecision(2) 
		<< std::setw(8) << evtNb << "\t"
		<< std::setw(4) << totSteps << "\t"

		<< std::setw(4) << nShieldTotInt << "\t"
		<< std::setw(4) << ShieldEleEscape << "\t"
		<< std::setw(8) << ShieldIntPos.x() << "\t"
		<< std::setw(8) << ShieldIntPos.y() << "\t"
		<< std::setw(8) << ShieldIntPos.z() << "\t"

		<< std::setw(4) << nActive_topTotInt << "\t"
		<< std::setw(4) << Active_topEleEscape << "\t"
		<< std::setw(8) << Active_topIntPos.x() << "\t"
		<< std::setw(8) << Active_topIntPos.y() << "\t"
		<< std::setw(8) << Active_topIntPos.z() << "\t"

		<< std::setw(4) << nAbsorberTotInt << "\t"
		<< std::setw(4) << AbsorberEleEscape << "\t"
		<< std::setw(8) << AbsorberIntPos.x() << "\t"
		<< std::setw(8) << AbsorberIntPos.y() << "\t"
		<< std::setw(8) << AbsorberIntPos.z() << "\t"

		<< std::setw(4) << nActive_botTotInt << "\t"
		<< std::setw(4) << Active_botEleEscape << "\t"
		<< std::setw(8) << Active_botIntPos.x() << "\t"
		<< std::setw(8) << Active_botIntPos.y() << "\t"
		<< std::setw(8) << Active_botIntPos.z() << "\t"

		<< std::setprecision(4) 
		<< std::setw(8) << ShieldEneDep << "\t"
		<< std::setw(8) << Active_topEneDep << "\t"
		<< std::setw(8) << AbsorberEneDep << "\t"
		<< std::setw(8) << Active_botEneDep << "\t"

		<< G4endl;
}
}
void RadRunAction::EndOfRunAction(const G4Run* aRun)
{

  outFile.close();

  G4int nNumEvt = GetNumEvt();

  G4cout << "\n--------------------End of Run--------------------\n" << G4endl;
}

/*
void RadRunAction::fillPerEvent(G4double EShield, G4double EActive_top,
				G4double EAbsorber, G4double EActive_bot,
                                G4double LShield, G4double LActive_top,
				G4double LAbsorber, G4double LActive_bot)
{
  //accumulate statistic
  //
  sumEShield += EShield; sum2EShield += EShield*EShield;
  sumEActive_top += EActive_top; sum2EActive_top += EActive_top*EActive_top;
  sumEAbsorber += EAbsorber;  sum2EAbsorber += EAbsorber*EAbsorber;
  sumEActive_bot += EActive_bot;  sum2EActive_bot += EActive_bot*EActive_bot;
  
  sumLShield += LShield; sum2LShield += LShield*LShield;
  sumLActive_top += LActive_top; sum2LActive_top += LActive_top*LActive_top;
  sumLAbsorber += LAbsorber;  sum2LAbsorber += LAbsorber*LAbsorber;
  sumLActive_bot += LActive_bot;  sum2LActive_bot += LActive_bot*LActive_bot;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadRunAction::EndOfRunAction(const G4Run* aRun)
{

  outFile.close();

  G4int NbOfEvents = aRun->GetNumberOfEvent();
  if (NbOfEvents == 0) return;
  
  //compute statistics: mean and rms
  //
  sumEShield /= NbOfEvents; sum2EShield /= NbOfEvents;
  G4double rmsEShield = sum2EShield - sumEShield*sumEShield;
  if (rmsEShield > 0.) rmsEShield = std::sqrt(rmsEShield); else rmsEShield = 0.;

  sumEActive_top /= NbOfEvents; sum2EActive_top /= NbOfEvents;
  G4double rmsEActive_top = sum2EActive_top - sumEActive_top*sumEActive_top;
  if (rmsEActive_top > 0.) rmsEActive_top = std::sqrt(rmsEActive_top); else rmsEActive_top = 0.;

  sumEAbsorber /= NbOfEvents; sum2EAbsorber /= NbOfEvents;
  G4double rmsEAbsorber = sum2EAbsorber - sumEAbsorber*sumEAbsorber;
  if (rmsEAbsorber >0.) rmsEAbsorber = std::sqrt(rmsEAbsorber); else rmsEAbsorber = 0.;
  
  sumEActive_bot /= NbOfEvents; sum2EActive_bot /= NbOfEvents;
  G4double rmsEActive_bot = sum2EActive_bot - sumEActive_bot*sumEActive_bot;
  if (rmsEActive_bot > 0.) rmsEActive_bot = std::sqrt(rmsEActive_bot); else rmsEActive_bot = 0.;

  sumLShield /= NbOfEvents; sum2LShield /= NbOfEvents;
  G4double rmsLShield = sum2LShield - sumLShield*sumLShield;
  if (rmsLShield >0.) rmsLShield = std::sqrt(rmsLShield); else rmsLShield = 0.;

  sumLActive_top /= NbOfEvents; sum2LActive_top /= NbOfEvents;
  G4double rmsLActive_top = sum2LActive_top - sumLActive_top*sumLActive_top;
  if (rmsLActive_top >0.) rmsLActive_top = std::sqrt(rmsLActive_top); else rmsLActive_top = 0.;

  sumLAbsorber /= NbOfEvents; sum2LAbsorber /= NbOfEvents;
  G4double rmsLAbsorber = sum2LAbsorber - sumLAbsorber*sumLAbsorber;
  if (rmsLAbsorber >0.) rmsLAbsorber = std::sqrt(rmsLAbsorber); else rmsLAbsorber = 0.;
  
  sumLActive_bot /= NbOfEvents; sum2LActive_bot /= NbOfEvents;
  G4double rmsLActive_bot = sum2LActive_bot - sumLActive_bot*sumLActive_bot;
  if (rmsLActive_bot >0.) rmsLActive_bot = std::sqrt(rmsLActive_bot); else rmsLActive_bot = 0.;

  //print
  //
  G4cout
     << "\n--------------------End of Run------------------------------\n"
     << "\n mean Energy in Shield : " << G4BestUnit(sumEShield,"Energy")
     << " +- "                          << G4BestUnit(rmsEShield,"Energy")
     << "\n mean Energy in Active_top : " << G4BestUnit(sumEActive_top,"Energy")
     << " +- "                          << G4BestUnit(rmsEActive_top,"Energy")
     << "\n mean Energy in Absorberorber : " << G4BestUnit(sumEAbsorber,"Energy")
     << " +- "                          << G4BestUnit(rmsEAbsorber,"Energy")  
     << "\n mean Energy in Active_bot : " << G4BestUnit(sumEActive_bot,"Energy")
     << " +- "                          << G4BestUnit(rmsEActive_bot,"Energy")
     << G4endl;
     
  G4cout
     << "\n mean trackLength in Shield: " << G4BestUnit(sumLShield,"Length")
     << " +- "                            << G4BestUnit(rmsLShield,"Length")
     << "\n mean trackLength in Active_top: " << G4BestUnit(sumLActive_top,"Length")
     << " +- "                          << G4BestUnit(rmsLActive_top,"Length")
     << "\n mean trackLength in Absorberorber : " << G4BestUnit(sumLAbsorber,"Length")
     << " +- "                               << G4BestUnit(rmsLAbsorber,"Length")     << "\n mean trackLength in Active_bot: " << G4BestUnit(sumLActive_bot,"Length")
     << " +- "                          << G4BestUnit(rmsLActive_bot,"Length")
     << "\n------------------------------------------------------------\n"
     << G4endl;   
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
