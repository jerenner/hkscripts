/// \file NiCfTrackingAction.hh
/// \brief Definition of the NiCfTrackingAction class

#ifndef NiCfTrackingAction_h
#define NiCfTrackingAction_h 1

#include "G4UserTrackingAction.hh"

class G4VTrajectory;

class NiCfTrackingAction: public G4UserTrackingAction
{

public:

  // Default constructor
  NiCfTrackingAction();
  // Destructor
  virtual ~NiCfTrackingAction();

  static void ClearTrajectoryMap();

  virtual void PreUserTrackingAction(const G4Track*);
  virtual void PostUserTrackingAction(const G4Track*);

private:

  static std::map<int, G4VTrajectory*> fTrajectoryMap;
};

#endif
