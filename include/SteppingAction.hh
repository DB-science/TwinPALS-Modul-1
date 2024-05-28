#pragma once
#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "DetectorConstruction.hh"
#include "MyEventAction.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Track.hh"
#include "G4LogicalVolume.hh"
#include <set>
#include <unordered_map>




class SteppingAction : public G4UserSteppingAction
{
public:
	SteppingAction(MyEventAction* eventAction);
	~SteppingAction();

	void UserSteppingAction(const G4Step*);


private:
	MyEventAction *fEventAction;
	G4double InterActionX;
	G4double InterActionY;
	G4double InterActionZ;
	G4int ReflectionCounter;
	G4int GammaReflectionCounter;

	int trackCounter;

	std::map<G4int, std::set<G4LogicalVolume*>> gammaVisitedVolumes; // Liste der besuchten Volumina für jedes Gamma.


};

#endif
