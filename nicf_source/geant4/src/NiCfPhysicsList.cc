/// \file NiCfPhysicsList.cc
/// \brief Implementation of the NiCfPhysicsList class; adapted from
///        Geant4 example B5 B5PhysicsList.cc

#include "NiCfPhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NiCfPhysicsList::NiCfPhysicsList()
: G4VModularPhysicsList(){
  G4int verb = 1;
  SetVerboseLevel(verb);

  // EM Physics
  RegisterPhysics( new G4EmStandardPhysics(verb) );

  // Synchroton Radiation & Gamma Nuclear Physics
  RegisterPhysics( new G4EmExtraPhysics(verb) );

  // Decays
  RegisterPhysics( new G4DecayPhysics(verb) );

  // Hadron Elastic scattering
  RegisterPhysics( new G4HadronElasticPhysicsHP(verb) );

  // Hadron Physics
  RegisterPhysics( new G4HadronPhysicsQGSP_BIC_HP(verb));

  // Stopping Physics
  RegisterPhysics( new G4StoppingPhysics(verb) );

  // Ion Physics
  RegisterPhysics( new G4IonPhysics(verb));

  // Radioactive decay
  RegisterPhysics( new G4RadioactiveDecayPhysics(verb) );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NiCfPhysicsList::~NiCfPhysicsList()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NiCfPhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}
