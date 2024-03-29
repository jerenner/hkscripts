/// \file nicf_source.cc
/// \brief Main function for simulation of the NiCf source; adapted from
///        Geant4 example B5 exampleB5.cc

#include "NiCfPhysicsList.hh"
#include "NiCfDetectorConstruction.hh"
#include "NiCfActionInitialization.hh"

#include "G4RunManagerFactory.hh"

#include "G4UImanager.hh"
#include "G4StepLimiterPhysics.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Construct the default run manager
  auto* runManager =
    G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  // Detector construction initialization
  runManager->SetUserInitialization(new NiCfDetectorConstruction);

  // Physics list initialization
  auto physicsList = new NiCfPhysicsList();
  physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  runManager->SetUserInitialization(physicsList);

  // User action initialization
  runManager->SetUserInitialization(new NiCfActionInitialization());

  // Visualization manager construction
  auto visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  auto UImanager = G4UImanager::GetUIpointer();

  if ( !ui ) {
    // execute an argument macro file if exist
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    if (ui->IsGUI()) {
         UImanager->ApplyCommand("/control/execute gui.mac");
    }
    // start interactive session
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

  delete visManager;
  //delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
