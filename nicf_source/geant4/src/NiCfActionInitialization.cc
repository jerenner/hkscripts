/// \file NiCfActionInitialization.cc
/// \brief Implementation of the NiCfActionInitialization class; adapted from
///        Geant4 example B5 B5ActionInitialization.cc

#include "NiCfActionInitialization.hh"
#include "NiCfPrimaryGeneratorAction.hh"
#include "NiCfRunAction.hh"
#include "NiCfEventAction.hh"
#include "NiCfTrackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NiCfActionInitialization::NiCfActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NiCfActionInitialization::~NiCfActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NiCfActionInitialization::BuildForMaster() const
{
  NiCfEventAction* eventAction = new NiCfEventAction;
  SetUserAction(new NiCfRunAction(eventAction));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NiCfActionInitialization::Build() const
{
  SetUserAction(new NiCfPrimaryGeneratorAction);

  auto eventAction = new NiCfEventAction;
  SetUserAction(eventAction);

  SetUserAction(new NiCfRunAction(eventAction));
  SetUserAction(new NiCfTrackingAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
