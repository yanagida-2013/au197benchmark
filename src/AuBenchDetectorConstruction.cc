#include "AuBenchDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MSG4DetectorConstruction::MSG4DetectorConstruction()
: G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MSG4DetectorConstruction::~MSG4DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* MSG4DetectorConstruction::Construct()
{

  flight_path = 120*mm;
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  //
  // World
  //
  G4double world_sizeXY = 100*mm;
  G4double world_sizeZ  = 300*mm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld = new G4Box("World",
                                0.5*world_sizeXY,
                                0.5*world_sizeXY,
                                0.5*world_sizeZ);
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld,
                                                    world_mat,
                                                    "World");
  G4VPhysicalVolume* physWorld
      = new G4PVPlacement(0,                     //no rotation
                          G4ThreeVector(),       //at (0,0,0)
                          logicWorld,            //its logical volume
                          "World",               //its name
                          0,                     //its mother  volume
                          false,                 //no boolean operation
                          0);                    //copy number


  G4double sample_center_pos = flight_path-world_sizeZ/2;
  //
  // Sample (Au-197, Metal)
  //
  G4String name, symbol;
  G4int natoms, ncomponents, z;
  G4double a = 196.9665687*g/mole;
  G4Element* elnatAu = new G4Element(name="natAu", symbol="Au", z=79, a);
  G4double density = 17.00*g/cm3;
  G4Material* au_mat = new G4Material(name="NatAu", density, ncomponents=1);
  au_mat->AddElement(elnatAu, natoms=1);
  G4double au_thisckness = 0.8*mm;
  G4double au_radius = 27.5*mm;
  G4Tubs* solidAuSample
      = new G4Tubs("AuSample",
                   0.0*mm,
                   au_radius,
                   au_thisckness/2,
                   0*degree, 360*degree
                   );
  G4LogicalVolume* logicAuSample = new G4LogicalVolume(
                                                       solidAuSample,
                                                       au_mat,
                                                       "AuSample");
  G4ThreeVector pos = G4ThreeVector(0*cm, 0*cm, sample_center_pos);
  new G4PVPlacement(0,
                    pos,
                    logicAuSample,
                    "AuSample",
                    logicWorld,
                    false,
                    0);
  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
