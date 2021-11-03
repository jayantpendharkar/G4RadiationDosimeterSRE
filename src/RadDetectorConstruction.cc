#include "RadDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"

RadDetectorConstruction::RadDetectorConstruction()
{;}

RadDetectorConstruction::~RadDetectorConstruction()
{
}

G4int RadDetectorConstruction::CheckInteractionVol(G4String& volName){

G4int rtnval;

	if (volName == "Shield"){
	   rtnval = AL_SHIELD;
	} else if (volName == "Active_top"){
	   rtnval = SI_ACTIVE_TOP;
        } else if (volName == "Active_bot"){
           rtnval = SI_ACTIVE_BOT;
        } else if (volName == "Absorber"){
           rtnval = PB_ABS;
        } else {
           rtnval = NO_MATERIAL;
	}

   return rtnval;

}

G4VPhysicalVolume* RadDetectorConstruction::Construct()
{
  //------------------------------------------------------ materials

  G4String symbol;
  G4int ncomponents;
  G4double fractionmass;
  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double density, temperature, pressure;

  G4Material* Al = 
  new G4Material("Aluminum", z= 13., a= 26.98*g/mole, density= 2.7*g/cm3);

  G4Material* Pb =
  new G4Material("Lead"     , z=82., a= 207.19*g/mole, density= 11.35*g/cm3);

  G4Material* Si =
  new G4Material("Silicon", z= 14., a= 28.09*g/mole, density= 2.33*g/cm3);

  G4Material* Vacuum =
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                           kStateGas, 2.73*kelvin, 3.e-18*pascal);

//  ---------------------------------------------------- volumes

//  ------------------------------------------ world volume

  G4double Dosimeter_x = 30.0;
  G4double Dosimeter_y = 30.0;
  G4double Dosimeter_z = 30.0;
  G4double AlOutBox_w = 20.0;
  G4double AlOutBox_h = 20.0;
  G4double AlOutBox_t = 20.0;
  G4double AlInBox_w = 16.0;
  G4double AlInBox_h = 18.0;
  G4double AlInBox_t = 36.0;
  G4double Active_w = 10.0;
  G4double Active_h = 0.3;
  G4double Active_t = 10.0;
  G4double Active_top_Xpos = 0.0;
  G4double Active_top_Ypos = 5.0;
  G4double Active_top_Zpos = 0.0;
  G4double Active_bot_Xpos = 0.0;
  G4double Active_bot_Ypos = -5.0;
  G4double Active_bot_Zpos = 0.0;
  G4double Absorber_x = 10.0;
  G4double Absorber_y = 2.5;
  G4double Absorber_z = 10.0;
  G4double Absorber_Xpos = 0.0;
  G4double Absorber_Ypos = 0.0;
  G4double Absorber_Zpos = 0.0;

  G4Box* Dosimeter_box
    = new G4Box("Dosimeter_box",Dosimeter_x*cm,Dosimeter_y*cm,Dosimeter_z*cm);
  G4LogicalVolume* Dosimeter_log = new G4LogicalVolume(Dosimeter_box,
                                             Vacuum,"Dosimeter_log",0,0,0);
  G4VPhysicalVolume* Dosimeter_phys = new G4PVPlacement(0,G4ThreeVector(),
                                      Dosimeter_log,"Dosimeter",0,false,0);

// ---------------------------- Aluminum Shield ---------------------------

  G4Box* AlOutBox = new G4Box("OutBox",AlOutBox_w*cm,AlOutBox_h*cm,AlOutBox_t*cm);
  G4Box* AlInBox = new G4Box("InBox",AlInBox_w*cm,AlInBox_h*cm,AlInBox_t*cm);

  G4RotationMatrix* rotAlBox = new G4RotationMatrix;
  rotAlBox->rotateX(0*deg);
  G4ThreeVector zTrans1(0.*cm,-2.*cm,0.*cm);

  G4SubtractionSolid* Shield_Box = new G4SubtractionSolid("Shield_Box",AlOutBox,AlInBox,rotAlBox,zTrans1);

  G4LogicalVolume* Shield_log = new G4LogicalVolume(Shield_Box,Al,"Shield_log",0,0,0);

  G4ThreeVector Shield_place(0.0*cm, 0.0*cm, 0.0*cm);

  G4VPhysicalVolume* Shield_phys = new G4PVPlacement(0,Shield_place,Shield_log,"Shield",Dosimeter_log,false,0);

  G4VisAttributes* Shield_log_VisAtt = new G4VisAttributes(
					G4Colour(G4Colour::Grey()));
  Shield_log_VisAtt->SetForceSolid(true);
  Shield_log->SetVisAttributes(Shield_log_VisAtt);

// ---------------------------- Active volumes --------------------------
  G4Box* Active = new G4Box("Active",Active_w*cm,Active_h*mm,Active_t*cm);

  G4LogicalVolume* Active_top_log = new G4LogicalVolume(Active,Si,"Active_top_log",0,0,0);

  G4VisAttributes* Active_top_log_VisAtt = new G4VisAttributes(
					G4Colour(G4Colour::Green()));
  Active_top_log_VisAtt->SetForceSolid(true);
  Active_top_log->SetVisAttributes(Active_top_log_VisAtt);

  G4ThreeVector Active_top_place(Active_top_Xpos*cm, Active_top_Ypos*cm, Active_top_Zpos*cm);

  G4VPhysicalVolume* Active_top_phys = new G4PVPlacement(0,Active_top_place, Active_top_log,"Active_top",Dosimeter_log,false,0);

  G4LogicalVolume* Active_bot_log = new G4LogicalVolume(Active,Si,"Active_bot_log",0,0,0);

  G4VisAttributes* Active_bot_log_VisAtt = new G4VisAttributes(
					G4Colour(G4Colour::Green()));
  Active_bot_log_VisAtt->SetForceSolid(true);
  Active_bot_log->SetVisAttributes(Active_bot_log_VisAtt);

  G4ThreeVector Active_bot_place(Active_bot_Xpos*cm, Active_bot_Ypos*cm, Active_bot_Zpos*cm);

  G4VPhysicalVolume* Active_bot_phys = new G4PVPlacement(0,Active_bot_place, Active_bot_log,"Active_bot",Dosimeter_log,false,0);

// ------------------------ Absorber volume ---------------------------------

  G4Box* Absorber_box
    = new G4Box("Absorber_box",Absorber_x*cm,Absorber_y*mm,Absorber_z*cm);

  G4LogicalVolume* Absorber_log = new G4LogicalVolume(Absorber_box,
                                             Pb,"Absorber_log",0,0,0);

  G4ThreeVector Absorber_place(Absorber_Xpos*cm, Absorber_Ypos*cm, Absorber_Zpos*mm);

  G4VPhysicalVolume* Absorber_phys = new G4PVPlacement(0,Absorber_place, Absorber_log,"Absorber",Dosimeter_log,false,0);

  G4VisAttributes* Absorber_log_VisAtt = new G4VisAttributes(
					G4Colour(G4Colour::Magenta()));
  Absorber_log_VisAtt->SetForceSolid(true);
  Absorber_log->SetVisAttributes(Absorber_log_VisAtt);


  return Dosimeter_phys;

}
