/// \file NiCfEventAction.hh
/// \brief Definition of the NiCfEventAction class; adapted from
///        Geant4 example B5 B5EventAction.hh

#ifndef NiCfEventAction_h
#define NiCfEventAction_h 1


#include "G4UserEventAction.hh"
#include "globals.hh"

#include <vector>
#include <array>

/// Event action
class NiCfEventAction : public G4UserEventAction
{
public:
    NiCfEventAction();
    virtual ~NiCfEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
