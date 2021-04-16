/// \file NiCfAnalysis.hh
/// \brief Selection of the analysis technology; adapted from
///        Geant4 example B5 B5Analysis.cc

#ifndef NiCfAnalysis_h
#define NiCfAnalysis_h 1

#include "g4hdf5.hh"
//#include "g4root.hh"
//#include "g4csv.hh"
//#include "g4xml.hh"

//#include "G4GenericAnalysisManager.hh"
//using G4AnalysisManager = G4GenericAnalysisManager;
using G4AnalysisManager = G4Hdf5AnalysisManager;

#endif
