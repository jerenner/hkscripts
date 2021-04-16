/// \file NiCfPhysicsList.hh
/// \brief Definition of the NiCfPhysicsList class; adapted from
///        Geant4 example B5 B5PhysicsList.cc

#ifndef NiCfPhysicsList_h
#define NiCfPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

/// Modular physics list
class NiCfPhysicsList: public G4VModularPhysicsList
{
public:
  NiCfPhysicsList();
  virtual ~NiCfPhysicsList();

  //virtual void ConstructParticle();
  //virtual void ConstructProcess();
  virtual void SetCuts();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
