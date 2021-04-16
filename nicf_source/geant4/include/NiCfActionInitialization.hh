/// \file NiCfActionInitialization.hh
/// \brief Definition of the NiCfActionInitialization class; adapted from
///        Geant4 example B5 B5ActionInitialization.hh

#ifndef NiCfActionInitialization_h
#define NiCfActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class
class NiCfActionInitialization : public G4VUserActionInitialization
{
  public:
    NiCfActionInitialization();
    virtual ~NiCfActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
