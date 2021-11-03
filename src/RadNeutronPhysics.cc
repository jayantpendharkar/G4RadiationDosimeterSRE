//
////////////////////////////////////////////////////////////////////////////
//                                                                        //
//  Title:  Neutron physics for Space Sciences Physics List               //
//  Date:   20 March 2005                                                 //
//  Author: D.H. Wright (SLAC)                                            //
//                                                                        //  
//  080430 Modified by T. Koi (SLAC)                                      //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
//

#include "RadNeutronPhysics.hh"

#include "G4ParticleTable.hh"

// processes
#include "G4ProcessManager.hh"
#include "G4HadronElasticProcess.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4HadronFissionProcess.hh"
#include "G4HadronCaptureProcess.hh"

// cross sections
#include "G4BGGNucleonElasticXS.hh"
#include "G4BGGNucleonInelasticXS.hh"

#include "G4NeutronInelasticCrossSection.hh"
#include "G4NeutronHPElasticData.hh"
#include "G4NeutronHPInelasticData.hh"
#include "G4NeutronHPFissionData.hh"
#include "G4NeutronHPCaptureData.hh"

#include "G4NeutronHPJENDLHEElasticData.hh"
#include "G4NeutronHPJENDLHEInelasticData.hh"

// models
#include "G4LElastic.hh"
#include "G4CascadeInterface.hh"
#include "G4LENeutronInelastic.hh"
#include "G4LFission.hh"
#include "G4LCapture.hh"
#include "G4TheoFSGenerator.hh"
#include "G4GeneratorPrecompoundInterface.hh"
#include "G4ExcitationHandler.hh"
#include "G4PreCompoundModel.hh"
#include "G4QGSMFragmentation.hh"
#include "G4ExcitedStringDecay.hh"
#include "G4QGSParticipants.hh"
#include "G4QGSModel.hh"
#include "G4NeutronHPElastic.hh"
#include "G4NeutronHPInelastic.hh"
#include "G4NeutronHPFission.hh"
#include "G4NeutronHPCapture.hh"


RadNeutronPhysics::RadNeutronPhysics(const G4String& name)
                          :G4VPhysicsConstructor(name)
{;}

RadNeutronPhysics::~RadNeutronPhysics()
{;}


void RadNeutronPhysics::ConstructParticle()
{
  //  No need to construct anything here as long as 
  //  RadHadronPhysics is constructed
}


void RadNeutronPhysics::ConstructProcess()
{
  G4bool HPN;
  if (getenv("G4NEUTRONHPDATA")) {
    G4cout << "physics list: Constructing high precision neutron models" << G4endl;
    G4cout << "              using cross sections in "
           << getenv("G4NEUTRONHPDATA") << G4endl;
    HPN = true;
  } else {
    G4cout << "physics list: Constructing non-high-precision neutron models" << G4endl;
    HPN = false;
  }

  G4ProcessManager* pManager = G4Neutron::Neutron()->GetProcessManager();

  G4double HPNLimit = 19.9*MeV;

  // Neutron elastic process, models and cross sections

  G4HadronElasticProcess* elasticProcess = new G4HadronElasticProcess();


  G4LElastic* theLElasticModel = new G4LElastic();

  G4BGGNucleonElasticXS* elastic_XC_0 = new G4BGGNucleonElasticXS( G4Neutron::Neutron() );
  elasticProcess->AddDataSet( elastic_XC_0 );

  if (HPN) {

    // Use JENDL HE model 20 MeV ~ 3GeV
    G4NeutronHPJENDLHEInelasticData* elastic_XC_1 = new G4NeutronHPJENDLHEInelasticData();
    elasticProcess->AddDataSet( elastic_XC_1 );

    theLElasticModel->SetMinEnergy(HPNLimit);
    G4NeutronHPElastic* theHPElasticModel = new G4NeutronHPElastic();
    G4NeutronHPElasticData* theHPElasticData = new G4NeutronHPElasticData();
    elasticProcess->RegisterMe(theHPElasticModel);
    elasticProcess->AddDataSet(theHPElasticData);
  }

  elasticProcess->RegisterMe(theLElasticModel);
  pManager->AddDiscreteProcess(elasticProcess);

  // Neutron inelastic process, models and cross sections
  // Use Quark-Gluon String Model between 15 GeV and 100 TeV

  G4NeutronInelasticProcess* ninelProc = new G4NeutronInelasticProcess();

  G4TheoFSGenerator* QGSPModel = new G4TheoFSGenerator();
  G4GeneratorPrecompoundInterface* theCascade = 
                                    new G4GeneratorPrecompoundInterface();
  G4ExcitationHandler* exHandler = new G4ExcitationHandler();
  G4PreCompoundModel* preCompound = new G4PreCompoundModel(exHandler);
  theCascade->SetDeExcitation(preCompound);
  QGSPModel->SetTransport(theCascade);
  G4QGSMFragmentation* frag = new G4QGSMFragmentation();
  G4ExcitedStringDecay* stringDecay = new G4ExcitedStringDecay(frag);
  G4QGSModel<G4QGSParticipants>* stringModel = 
                                   new G4QGSModel<G4QGSParticipants>();
  stringModel->SetFragmentationModel(stringDecay);
  QGSPModel->SetHighEnergyGenerator(stringModel);
  QGSPModel->SetMinEnergy(15*GeV);
  QGSPModel->SetMaxEnergy(100*TeV);

  // Use LEP model between 9.5 and 25 GeV
  G4LENeutronInelastic* LEPnModel = new G4LENeutronInelastic();
  LEPnModel->SetMinEnergy(9.5*GeV);
  LEPnModel->SetMaxEnergy(25.0*GeV);

  // Use Bertini cascade model between 0 and 9.9 GeV
  G4CascadeInterface* theBertiniModel = new G4CascadeInterface();
  theBertiniModel->SetMaxEnergy(9.9*GeV);

  G4BGGNucleonInelasticXS* inelastic_XC_0 = new G4BGGNucleonInelasticXS( G4Neutron::Neutron() );
  ninelProc->AddDataSet( inelastic_XC_0 );

  if (HPN) {

    // Use JENDL HE model 20 MeV ~ 3GeV
    G4NeutronHPJENDLHEInelasticData* inelastic_XC_1 = new G4NeutronHPJENDLHEInelasticData();
    ninelProc->AddDataSet( inelastic_XC_1 );

    // Use high precision neutron model below 20 MeV 
    theBertiniModel->SetMinEnergy(HPNLimit);
    G4NeutronHPInelastic* theHPInelasticModel = new G4NeutronHPInelastic();
    G4NeutronHPInelasticData* theHPInelasticData = new G4NeutronHPInelasticData();
    ninelProc->RegisterMe(theHPInelasticModel);
    ninelProc->AddDataSet(theHPInelasticData);
  } 

  ninelProc->RegisterMe(QGSPModel);
  ninelProc->RegisterMe(LEPnModel);
  ninelProc->RegisterMe(theBertiniModel);
  pManager->AddDiscreteProcess(ninelProc);

  // Neutron-induced fission process, models and cross sections

  G4HadronFissionProcess* neutronFission = new G4HadronFissionProcess();
  G4LFission* theLFissionModel = new G4LFission();
  theLFissionModel->SetMaxEnergy(20.*TeV);
  if (HPN) {
    theLFissionModel->SetMinEnergy(HPNLimit);
    G4NeutronHPFission* theHPFissionModel = new G4NeutronHPFission();
    G4NeutronHPFissionData* theHPFissionData=new G4NeutronHPFissionData();
    neutronFission->RegisterMe(theHPFissionModel);
    neutronFission->AddDataSet(theHPFissionData);
  }
  neutronFission->RegisterMe(theLFissionModel);
  pManager->AddDiscreteProcess(neutronFission);

  // Neutron capture process, models and cross sections

  G4HadronCaptureProcess* neutronCapture = new G4HadronCaptureProcess();
  G4LCapture* theLCaptureModel = new G4LCapture();
  theLCaptureModel->SetMaxEnergy(20.*TeV);
  if (HPN) {
    theLCaptureModel->SetMinEnergy(HPNLimit);
    G4NeutronHPCapture* theHPCaptureModel = new G4NeutronHPCapture();
    G4NeutronHPCaptureData* theHPCaptureData = new G4NeutronHPCaptureData();
    neutronCapture->RegisterMe(theHPCaptureModel);
    neutronCapture->AddDataSet(theHPCaptureData);
  }
  neutronCapture->RegisterMe(theLCaptureModel);
  pManager->AddDiscreteProcess(neutronCapture);

}
