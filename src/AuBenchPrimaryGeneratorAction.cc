#include "AuBenchPrimaryGeneratorAction.hh"
#include "AuBenchSteppingAction.hh"
#include "AuBenchRunAction.hh"
#include "AuBenchRun.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

#include "Randomize.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MSG4PrimaryGeneratorAction::MSG4PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  // In this Function, you must set
  // - number of the bombarded particle
  // - the definition of the particle
  // - the energy of the particle
  // - the momentumDirection
  //
  // in addtion, you can set
  // - the charge
  // - polarization
  //
  // see details in G4ParticleGun.hh
  //
  // To set the particle, we use variable "fParticleGun".
  // fParticleGun is an instance of G4ParticleGun.
  //


  // number of neutron
  G4int number_of_particle = 1;
  fParticleGun  = new G4ParticleGun(number_of_particle);

  // Get the Definitions of particles from ParticleTable
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName = "neutron");
  fParticleGun->SetParticleDefinition(particle);

  // Z positive direction
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MSG4PrimaryGeneratorAction::~MSG4PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MSG4PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
  // This function is called at the beginning of each event.
  //
  G4double radiusOfNeutronBeam = 0.5*cm;

  // 装填

  fParticleGun->SetParticleEnergy(4.9*eV);

  G4double x_pos = (0.5 - G4UniformRand()) * 2 * radiusOfNeutronBeam;
  G4double y_pos = (0.5 - G4UniformRand()) * 2 * radiusOfNeutronBeam;

  fParticleGun->SetParticlePosition(G4ThreeVector(x_pos, y_pos, -15*cm));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
