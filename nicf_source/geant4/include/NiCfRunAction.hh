/// \file NiCfRunAction.hh
/// \brief Definition of the NiCfRunAction class; adapted from
///        Geant4 example B5 B5RunAction.hh

#ifndef NiCfRunAction_h
#define NiCfRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class NiCfEventAction;
class G4Run;

/// Run action class
class NiCfRunAction : public G4UserRunAction
{
  public:
    NiCfRunAction(NiCfEventAction* eventAction);
    virtual ~NiCfRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

  private:
    NiCfEventAction* fEventAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
