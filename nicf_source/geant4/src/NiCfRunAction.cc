/// \file NiCfRunAction.cc
/// \brief Implementation of the NiCfRunAction class; adapted from
///        Geant4 example B5 B5RunAction.cc

#include "NiCfAnalysis.hh"
#include "NiCfRunAction.hh"
#include "NiCfEventAction.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericAnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NiCfRunAction::NiCfRunAction(NiCfEventAction* eventAction)
 : G4UserRunAction(),
   fEventAction(eventAction)
{
  // Create the generic analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("nisource");

  // Creating ntuple
  if ( fEventAction ) {
    analysisManager->CreateNtuple("nisource", "Particles");
    analysisManager->CreateNtupleIColumn("event");         // column Id = 0
    analysisManager->CreateNtupleSColumn("particleName");  // column Id = 1
    analysisManager->CreateNtupleIColumn("trackID");       // column Id = 2
    analysisManager->CreateNtupleIColumn("parentID");      // column Id = 3
    analysisManager->CreateNtupleDColumn("mass");          // column Id = 4
    analysisManager->CreateNtupleDColumn("xi");            // column Id = 5
    analysisManager->CreateNtupleDColumn("yi");            // column Id = 6
    analysisManager->CreateNtupleDColumn("zi");            // column Id = 7
    analysisManager->CreateNtupleDColumn("ti");            // column Id = 8
    analysisManager->CreateNtupleDColumn("xf");            // column Id = 9
    analysisManager->CreateNtupleDColumn("yf");            // column Id = 10
    analysisManager->CreateNtupleDColumn("zf");            // column Id = 11
    analysisManager->CreateNtupleDColumn("tf");            // column Id = 12
    analysisManager->CreateNtupleDColumn("pxi");           // column Id = 13
    analysisManager->CreateNtupleDColumn("pyi");           // column Id = 14
    analysisManager->CreateNtupleDColumn("pzi");           // column Id = 15
    analysisManager->CreateNtupleDColumn("pxf");           // column Id = 16
    analysisManager->CreateNtupleDColumn("pyf");           // column Id = 17
    analysisManager->CreateNtupleDColumn("pzf");           // column Id = 18
    analysisManager->CreateNtupleSColumn("volInit");       // column Id = 19
    analysisManager->CreateNtupleSColumn("volFinal");      // column Id = 20
    analysisManager->FinishNtuple();
  }

  // Set ntuple output file
  analysisManager->SetNtupleFileName(0, "nisource_ntuple");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NiCfRunAction::~NiCfRunAction()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NiCfRunAction::BeginOfRunAction(const G4Run* /*run*/)
{
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  // The default file name is set in NiCfRunAction::NiCfRunAction(),
  // it can be overwritten in a macro
  analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NiCfRunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // save histograms & ntuple
  //
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
