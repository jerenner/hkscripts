/// \file NiCfDetectorConstruction.cc
/// \brief Implementation of the NiCfDetectorConstruction class; adapted from
///        Geant4 example B5 B5DetectorConstruction.cc

#include "NiCfDetectorConstruction.hh"
#include "NiCfConstants.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"

#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UserLimits.hh"
#include "G4RunManager.hh"
#include "G4GenericMessenger.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NiCfDetectorConstruction::NiCfDetectorConstruction()
: G4VUserDetectorConstruction(),
  fMessenger(nullptr), fWorldRadius(10.), fSourceRadius(7.),
  fMassFractionNiO(0.65), fMassFractionPoly(0.35),
  fVisAttributes()

{

  // define commands for this class
  DefineCommands();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NiCfDetectorConstruction::~NiCfDetectorConstruction()
{
  delete fLogicSource;
  delete fMessenger;

  for (auto visAttributes: fVisAttributes) {
    delete visAttributes;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* NiCfDetectorConstruction::Construct()
{

  fWorldRadius = 10.*cm;

  G4bool checkOverlaps = true;

  // Construct materials
  ConstructMaterials();
  G4Material* air = G4Material::GetMaterial("G4_AIR");
  G4Material* mat_source = G4Material::GetMaterial("NIO_POLY");

  // World
  G4Sphere*
  solidWorld = new G4Sphere("World", 0., fWorldRadius, 0., 360.*deg, 0., 180.*deg);

  G4LogicalVolume*
  logicWorld = new G4LogicalVolume(solidWorld,             // its solid
                                   air,                    // its material
                                   "World");               // its name
  G4VPhysicalVolume*
  physiWorld = new G4PVPlacement(0,                      // no rotation
                                 G4ThreeVector(),        // at (0,0,0)
                                 logicWorld,             // its logical volume
                                 "World",                // its name
                                 0,                      // its mother  volume
                                 false,                  // no boolean operation
                                 0,                      // copy number
                                 checkOverlaps);

  // The Ni sphere.
  G4Sphere*
  solidSource = new G4Sphere("Source", 0., fSourceRadius, 0., 360.*deg, 0., 180.*deg);

  fLogicSource = new G4LogicalVolume(solidSource, mat_source, "Source");
  new G4PVPlacement(0,
                    G4ThreeVector(),        // at (0,0,0)
                    fLogicSource,            // its logical volume
                    "Source",               // its name
                    logicWorld,           // its mother  volume
                    false,                  // no boolean operation
                    0,                      // copy number
                    checkOverlaps);

  // visualization attributes ------------------------------------------------

  auto visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  visAttributes->SetVisibility(false);
  logicWorld->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);

  visAttributes = new G4VisAttributes(G4Colour(0.9,0.9,0.9));   // LightGray
  fLogicSource->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);

  // return the world physical volume ----------------------------------------
  return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NiCfDetectorConstruction::ConstructMaterials()
{
  auto nistManager = G4NistManager::Instance();

  // Air
  nistManager->FindOrBuildMaterial("G4_AIR");

  // NiO
  G4double density_NiO = kDensityNiO*g/cm3;
  G4Element* elNi = nistManager->FindOrBuildElement("Ni", true);
  G4Element* elO = nistManager->FindOrBuildElement("O", true);
  G4Material* NiO = new G4Material("NICKEL_OXIDE", density_NiO, 2);
  NiO->AddElement(elNi,1);
  NiO->AddElement(elO,1);

  // Polyethylene
  G4Material* polyethylene = nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");

  // Create the mixture.
  G4double density_poly = polyethylene->GetDensity();
  G4Material * NiO_poly = new G4Material("NIO_POLY", fMassFractionNiO*density_NiO + fMassFractionPoly*density_poly, 2);
  NiO_poly->AddMaterial(NiO, fMassFractionNiO);
  NiO_poly->AddMaterial(polyethylene, fMassFractionPoly);

  // Vacuum "Galactic"
  // nistManager->FindOrBuildMaterial("G4_Galactic");

  G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NiCfDetectorConstruction::DefineCommands()
{
  // Define /NiCf/detector command directory using generic messenger class
  fMessenger = new G4GenericMessenger(this,
                                       "/NiCf/detector/",
                                       "Detector control");

  // World radius command
  auto& worldRadiusCmd
   = fMessenger->DeclareMethodWithUnit("worldRadius","cm",
                               &NiCfDetectorConstruction::SetWorldRadius,
                               "Set radius of world");
  worldRadiusCmd.SetParameterName("radius", true);
  worldRadiusCmd.SetRange("radius>=0.");
  worldRadiusCmd.SetDefaultValue("8.");

  // Source radius command
  auto& sourceRadiusCmd
   = fMessenger->DeclareMethodWithUnit("sourceRadius","cm",
                               &NiCfDetectorConstruction::SetSourceRadius,
                               "Set radius of NiCf source");
  sourceRadiusCmd.SetParameterName("radius", true);
  sourceRadiusCmd.SetRange("radius>=0.");
  sourceRadiusCmd.SetDefaultValue("7.");

  // Mass fraction of NiO command
  auto& massFractionNiOCmd
   = fMessenger->DeclareMethodWithUnit("massFractionNiO","mm",
                               &NiCfDetectorConstruction::SetMassFractionNiO,
                               "Set mass fraction of NiO");
  massFractionNiOCmd.SetParameterName("frac", true);
  massFractionNiOCmd.SetRange("frac>=0. && frac<=1.");
  massFractionNiOCmd.SetDefaultValue("0.65");

  // Mass fraction of polyethylene command
  auto& massFractionPolyCmd
   = fMessenger->DeclareMethodWithUnit("massFractionPoly","mm",
                               &NiCfDetectorConstruction::SetMassFractionPoly,
                               "Set mass fraction of polyethylene");
  massFractionPolyCmd.SetParameterName("frac", true);
  massFractionPolyCmd.SetRange("frac>=0. && frac<=1.");
  massFractionPolyCmd.SetDefaultValue("0.35");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
