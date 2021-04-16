/// \file NiCfDetectorConstruction.hh
/// \brief Definition of the NiCfDetectorConstruction class; adapted from
///        Geant4 example B5 B5DetectorConstruction.hh

#ifndef NiCfDetectorConstruction_h
#define NiCfDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

#include <vector>

class G4VPhysicalVolume;
class G4Material;
class G4VisAttributes;
class G4GenericMessenger;

/// Detector construction

class NiCfDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    NiCfDetectorConstruction();
    virtual ~NiCfDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    void ConstructMaterials();

    inline G4double GetWorldRadius()               { return fWorldRadius;      }
    inline void SetWorldRadius(G4double radius)    { fWorldRadius = radius;    }
    inline G4double GetSourceRadius()              { return fSourceRadius;     }
    inline void SetSourceRadius(G4double radius)   { fSourceRadius = radius;   }
    inline G4double GetMassFractionNiO()           { return fMassFractionNiO;  }
    inline void SetMassFractionNiO(G4double frac)  { fMassFractionNiO = frac;  }
    inline G4double GetMassFractionPoly()          { return fMassFractionPoly; }
    inline void SetMassFractionPoly(G4double frac) { fMassFractionPoly = frac; }

  private:
    void DefineCommands();

    G4LogicalVolume* fLogicSource;
    G4GenericMessenger* fMessenger;

    G4double fWorldRadius;      // radius of the world
    G4double fSourceRadius;     // radius of the source
    G4double fMassFractionNiO;  // mass fraction of NiO in the source
    G4double fMassFractionPoly; // mass fraction of polyethylene in the source

    std::vector<G4VisAttributes*> fVisAttributes;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
