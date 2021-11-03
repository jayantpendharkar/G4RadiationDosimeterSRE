//
////////////////////////////////////////////////////////////////////////////
//                                                                        //
//  Title:  Ion Physics for Space Sciences Physics List                   //
//  Date:   22 March 2005                                                 //
//  Author: D.H. Wright (SLAC)                                            //
//                                                                        //
//  080430 Modified by T. Koi (SLAC)					  //
//  080916 Correct energy range definition                                //
//         for ionReaction and lightIonReaction_H  by T. Koi              //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
//

#include "RadIonPhysics.hh"

#include "G4ParticleTable.hh"
#include "G4ProcessManager.hh"
#include "G4IonConstructor.hh"

// processes
#include "G4MultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"
#include "G4HadronElasticProcess.hh"
#include "G4HadronInelasticProcess.hh"
#include "G4DeuteronInelasticProcess.hh"
#include "G4TritonInelasticProcess.hh"
#include "G4AlphaInelasticProcess.hh"

// models
#include "G4LElastic.hh"
#include "G4BinaryLightIonReaction.hh"
#include "G4QMDReaction.hh"

// cross sections
#include "G4TripathiLightCrossSection.hh"
#include "G4TripathiCrossSection.hh"
#include "G4IonsShenCrossSection.hh"
#include "G4IonsSihverCrossSection.hh"


RadIonPhysics::RadIonPhysics(const G4String& name)
               :  G4VPhysicsConstructor(name)
{;}


RadIonPhysics::~RadIonPhysics()
{;}


void RadIonPhysics::ConstructParticle()
{ 
  // Construct light ions (d, t, 3He, alpha, and generic ion)
  G4IonConstructor ionConstruct;
  ionConstruct.ConstructParticle();
}


void RadIonPhysics::ConstructProcess()
{
  // Hadronic Elastic Process and Model (for all ions except generic ion)

  G4HadronElasticProcess* elasticProcess = new G4HadronElasticProcess();
  G4LElastic* elasticModel = new G4LElastic();
  elasticProcess->RegisterMe(elasticModel);

  // Hadronic inelastic models

  G4BinaryLightIonReaction* lightIonReaction_L = new G4BinaryLightIonReaction();
  lightIonReaction_L->SetMinEnergy(0.*MeV);  
  lightIonReaction_L->SetMaxEnergy(50.*MeV);

  G4QMDReaction* ionReaction = new G4QMDReaction();
  ionReaction->SetMinEnergy(49.*MeV);  
  ionReaction->SetMaxEnergy(3001.*MeV);

  G4BinaryLightIonReaction* lightIonReaction_H = new G4BinaryLightIonReaction();
  lightIonReaction_H->SetMinEnergy(3.*GeV);  
  lightIonReaction_H->SetMaxEnergy(10.*GeV);

  G4TripathiLightCrossSection* tripLightCS = new G4TripathiLightCrossSection();
  G4TripathiCrossSection* tripCS = new G4TripathiCrossSection();
  G4IonsShenCrossSection* shenCS = new G4IonsShenCrossSection();
  G4IonsSihverCrossSection* sihverCS = new G4IonsSihverCrossSection();

  G4ProcessManager * pManager = 0;
  
  ///////////////////
  //               //
  //   Deuteron    //
  //               //
  ///////////////////

  pManager = G4Deuteron::Deuteron()->GetProcessManager();

  // EM processes
  pManager->AddProcess(new G4MultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4DeuteronInelasticProcess* dinelProc = new G4DeuteronInelasticProcess();
  dinelProc->RegisterMe(lightIonReaction_L);
  dinelProc->RegisterMe(ionReaction);
  dinelProc->RegisterMe(lightIonReaction_H);
  dinelProc->AddDataSet(sihverCS);
  dinelProc->AddDataSet(shenCS);
  dinelProc->AddDataSet(tripCS);
  dinelProc->AddDataSet(tripLightCS);
  pManager->AddDiscreteProcess(dinelProc);

  ///////////////////
  //               //
  //    Triton     //
  //               //
  ///////////////////

  pManager = G4Triton::Triton()->GetProcessManager(); 

  // EM processes
  pManager->AddProcess(new G4MultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4TritonInelasticProcess* tinelProc = new G4TritonInelasticProcess();
  tinelProc->RegisterMe(lightIonReaction_L);
  tinelProc->RegisterMe(ionReaction);
  tinelProc->RegisterMe(lightIonReaction_H);
  tinelProc->AddDataSet(sihverCS);
  tinelProc->AddDataSet(shenCS);
  tinelProc->AddDataSet(tripCS);
  tinelProc->AddDataSet(tripLightCS);
  pManager->AddDiscreteProcess(tinelProc);

  ///////////////////
  //               //
  //      3He      //
  //               //
  ///////////////////

  pManager = G4He3::He3()->GetProcessManager(); 

  // EM processes
  pManager->AddProcess(new G4MultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4ionIonisation(),      -1, 2, 2);

  // hadron inelastic
  G4HadronInelasticProcess* he3inelProc = 
    new G4HadronInelasticProcess("He3Inelastic",G4He3::He3());

  he3inelProc->RegisterMe(lightIonReaction_L);
  he3inelProc->RegisterMe(ionReaction);
  he3inelProc->RegisterMe(lightIonReaction_H);
  he3inelProc->AddDataSet(sihverCS);
  he3inelProc->AddDataSet(shenCS);
  he3inelProc->AddDataSet(tripCS);
  he3inelProc->AddDataSet(tripLightCS);
  pManager->AddDiscreteProcess(he3inelProc);

  ///////////////////
  //               //
  //     Alpha     //
  //               //
  ///////////////////

  pManager = G4Alpha::Alpha()->GetProcessManager(); 

  // EM processes
  pManager->AddProcess(new G4MultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4ionIonisation(),      -1, 2, 2);
  
  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4AlphaInelasticProcess* ainelProc = new G4AlphaInelasticProcess();
  ainelProc->RegisterMe(lightIonReaction_L);
  ainelProc->RegisterMe(ionReaction);
  ainelProc->RegisterMe(lightIonReaction_H);
  ainelProc->AddDataSet(sihverCS);
  ainelProc->AddDataSet(shenCS);
  ainelProc->AddDataSet(tripCS);
  ainelProc->AddDataSet(tripLightCS);
  pManager->AddDiscreteProcess(ainelProc);

  ///////////////////
  //               //
  //  generic ion  //
  //               //
  ///////////////////

  pManager = G4GenericIon::GenericIon()->GetProcessManager();

  // EM processes for generic ion
  pManager->AddProcess(new G4MultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4ionIonisation(),      -1, 2, 2);
 
  // hadron inelastic
  G4HadronInelasticProcess* genericIon = 
    new G4HadronInelasticProcess("ionInelastic",G4GenericIon::GenericIon());
  genericIon->RegisterMe(lightIonReaction_L);
  genericIon->RegisterMe(ionReaction);
  genericIon->RegisterMe(lightIonReaction_H);
  genericIon->AddDataSet(sihverCS);
  genericIon->AddDataSet(shenCS);
  genericIon->AddDataSet(tripCS);
  pManager->AddDiscreteProcess(genericIon);
}
