/// \file NiCfPrimaryGeneratorAction.hh
/// \brief Implementation of the NiCfPrimaryGeneratorAction class; adapted from
///        Geant4 example B5 B5PrimaryGeneratorAction.hh

#ifndef NiCfPrimaryGeneratorAction_h
#define NiCfPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ParticleGun.hh"

class G4Event;

/// Primary generator
///
/// A single particle is generated.
/// User can select
/// - the initial momentum and angle
/// - the momentum and angle spreads
/// - random selection of a particle type from proton, kaon+, pi+, muon+, e+


class NiCfPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    NiCfPrimaryGeneratorAction();
   ~NiCfPrimaryGeneratorAction();

   virtual void GeneratePrimaries(G4Event*);
   G4ParticleGun* GetParticleGun() { return fParticleGun;} ;

  private:
    G4ParticleGun*  fParticleGun;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
