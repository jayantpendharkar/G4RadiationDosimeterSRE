//
///////////////////////////////////////////////////////////////////////////
//                                                                       //
//  Title:  Boson Physics for Space Sciences Physics List                //
//  Date:   22 March 2005                                                //
//  Author: D.H. Wright (SLAC)                                           //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
//

#include "RadBosonPhysics.hh"

#include "G4ProcessManager.hh"

// processes
#include "G4GammaConversion.hh"
#include "G4ComptonScattering.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4PhotoNuclearProcess.hh"

// models
#include "G4GammaNuclearReaction.hh"
#include "G4TheoFSGenerator.hh"
#include "G4GeneratorPrecompoundInterface.hh"
#include "G4QGSMFragmentation.hh"
#include "G4ExcitedStringDecay.hh"
#include "G4GammaParticipants.hh"
#include "G4QGSModel.hh"

#include "G4ChargedGeantino.hh"
#include "G4Geantino.hh"
#include "G4Gamma.hh"


RadBosonPhysics::RadBosonPhysics(const G4String& name)
                     :  G4VPhysicsConstructor(name)
{;}


RadBosonPhysics::~RadBosonPhysics()
{;}


void RadBosonPhysics::ConstructParticle()
{
  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();
  // gamma
  G4Gamma::GammaDefinition();  
}


void RadBosonPhysics::ConstructProcess()
{
  //
  // First define the gamma-nuclear models
  //

  // low energy part
  G4GammaNuclearReaction* lowEGammaModel = new G4GammaNuclearReaction();
  lowEGammaModel->SetMaxEnergy(3.5*GeV);
 
  // high energy part
  G4TheoFSGenerator* highEGammaModel = new G4TheoFSGenerator();
  G4GeneratorPrecompoundInterface* preComModel =
                         new G4GeneratorPrecompoundInterface();
  highEGammaModel->SetTransport(preComModel);
 
  G4QGSModel<G4GammaParticipants>* theStringModel =
                         new G4QGSModel<G4GammaParticipants>;
  G4QGSMFragmentation* fragModel = new G4QGSMFragmentation();
  G4ExcitedStringDecay* stringDecay =
                            new G4ExcitedStringDecay(fragModel);
  theStringModel->SetFragmentationModel(stringDecay);
 
  highEGammaModel->SetHighEnergyGenerator(theStringModel);
  highEGammaModel->SetMinEnergy(3.*GeV);
  highEGammaModel->SetMaxEnergy(100.*TeV); 
 
  // Now add the processes to the gamma, including e+e- pair creation, 
  // Compton scattering and photo-electric effect

  G4ProcessManager* pManager = G4Gamma::Gamma()->GetProcessManager();
  pManager->AddDiscreteProcess(new G4GammaConversion());
  pManager->AddDiscreteProcess(new G4ComptonScattering());
  pManager->AddDiscreteProcess(new G4PhotoElectricEffect());

  G4PhotoNuclearProcess* thePhotoNuclearProcess = new G4PhotoNuclearProcess();
  thePhotoNuclearProcess->RegisterMe(lowEGammaModel);
  thePhotoNuclearProcess->RegisterMe(highEGammaModel);
  pManager->AddDiscreteProcess(thePhotoNuclearProcess);
}

