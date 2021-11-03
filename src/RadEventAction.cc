#include "RadEventAction.hh"
#include "RadUserEventInformation.hh"
#include "RadRunAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4VTrajectory.hh"
#include "G4VVisManager.hh"
#include "G4UnitsTable.hh"

//#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadEventAction::RadEventAction(RadRunAction* run)
:runAct(run)
//,printModulo(1),eventMessenger(0)
{
//  eventMessenger = new RadEventActionMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadEventAction::~RadEventAction()
{
//  delete eventMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadEventAction::BeginOfEventAction(const G4Event* evt)
{
 G4EventManager::
   GetEventManager()->SetUserInformation(new RadUserEventInformation);  

 printModulo = 10000;
/*
 G4int evtNb = evt->GetEventID();
 if (evtNb%printModulo == 0) { 
   G4cout << "\n---> Begin of event: " << evtNb << G4endl;
   CLHEP::HepRandom::showEngineStatus();
 }
 
 // initialisation per event
 EnergyShield =  EnergyActive_top = EnergyAbsorber =  EnergyActive_bot = 0.;
 TrackLShield = TrackLActive_top = TrackLAbsorber = TrackLActive_bot = 0.;
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadEventAction::EndOfEventAction(const G4Event* evt)
{

  RadUserEventInformation* eventInfo 
	=(RadUserEventInformation*)evt->GetUserInformation();

  //accumulates statistic
  //
//  runAct->fillPerEvent(EnergyShield, EnergyActive_top, EnergyAbsorber, EnergyActive_bot, TrackLShield, TrackLActive_top, TrackLAbsorber, TrackLActive_bot);
  
  //print per event (modulo n)
  //
  G4int evtNb = evt->GetEventID();

  G4int totSteps = eventInfo->GetTotalSteps();

  runAct->WriteOut(evt);
  runAct->IncNumEvt();

  if (evtNb%printModulo == 0) {
     G4cout << "processed\t " << evtNb << "events..." << G4endl;
  }
/*
  if (evtNb%printModulo == 0) {
    G4cout << "---> End of event: " << evtNb << G4endl;	

    G4cout
       << "   Shield: total energy: " << std::setw(7)
                                        << G4BestUnit(EnergyShield,"Energy")
       << "       total track length: " << std::setw(7)
                                        << G4BestUnit(TrackLShield,"Length")
       << G4endl
       << "        Active 1: total energy: " << std::setw(7)
                                        << G4BestUnit(EnergyActive_top,"Energy")
       << "       total track length: " << std::setw(7)
                                        << G4BestUnit(TrackLActive_top,"Length")
       << "   Absorber: total energy: " << std::setw(7)
                                        << G4BestUnit(EnergyAbsorber,"Energy")
       << "       total track length: " << std::setw(7)
                                        << G4BestUnit(TrackLAbsorber,"Length")
       << G4endl
       << "        Active 2: total energy: " << std::setw(7)
                                        << G4BestUnit(EnergyActive_bot,"Energy")
       << "       total track length: " << std::setw(7)
                                        << G4BestUnit(TrackLActive_bot,"Length")
       << G4endl;
	  
  }*/  
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
