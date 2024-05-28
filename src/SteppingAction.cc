#include "SteppingAction.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpticalPhoton.hh"
#include "G4Gamma.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "DetectorConstruction.hh"
#include "TrackerSD.hh"
#include "G4SteppingVerbose.hh"
#include "G4UImanager.hh"
SteppingAction::SteppingAction(MyEventAction *eventAction)
{
	fEventAction = eventAction;
       InterActionX = 0.;
       InterActionY = 0.;
       InterActionZ = 0.;
       ReflectionCounter =0;
       GammaReflectionCounter = 0;
       trackCounter = 0;


}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step *step)
{      
       
       G4Track* aTrack = step->GetTrack();
       G4ParticleDefinition* particleDef = aTrack->GetDefinition();
       G4LogicalVolume* currentVolume = aTrack->GetVolume()->GetLogicalVolume();
	static G4ParticleDefinition* gamma =
       G4Gamma::GammaDefinition();
	static G4ParticleDefinition* opticalPhoton =
       G4OpticalPhoton::OpticalPhotonDefinition();

        G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

        const DetectorConstruction *detectorConstruction = static_cast<const DetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

        G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();

        if(volume != fScoringVolume)
        	return;
        	
        	G4LogicalVolume* lVolume = step->GetPreStepPoint()->GetTouchableHandle()
                             ->GetVolume()->GetLogicalVolume();
  
  const G4VTouchable *touchable = step->GetPreStepPoint()->GetTouchable();
  G4int copyNo = touchable->GetCopyNumber();
  G4int iVol = 0;
  if  (copyNo ==0)  iVol = 1;
  if  (copyNo ==1) iVol = 2;

  if((opticalPhoton)){
       if(step->GetPostStepPoint()->GetStepStatus() == fGeomBoundary){
              ReflectionCounter=1;   
       }
  }



  G4double edepStep = step->GetTotalEnergyDeposit();
  if (edepStep <= 0.) return;
  G4double time   = step->GetPreStepPoint()->GetGlobalTime();



  

  if((opticalPhoton)&&(aTrack->GetCurrentStepNumber() == 1)){
      G4ThreeVector  posPhoton = step->GetPreStepPoint()->GetPosition();
      InterActionX = posPhoton[0];
      InterActionY = posPhoton[1];
      InterActionZ = posPhoton[2];

  }


   if (aTrack->GetDefinition()->GetPDGEncoding() == 22) // Überprüfen, ob es sich um ein Gamma handelt.
        {
            // Verwenden Sie die eindeutige ID des Gammas (normalerweise die Track-ID).
            G4int gammaID = aTrack->GetTrackID();

            if (step->GetPostStepPoint()->GetStepStatus() == fGeomBoundary)
            {
                // Das Gamma ist an einer geometrischen Grenze und verlässt das Volumen.

                // Überprüfen, ob es zuvor in diesem Volumen war und es jetzt wieder betritt.
                if (gammaVisitedVolumes[gammaID].find(currentVolume) != gammaVisitedVolumes[gammaID].end())
                {
                    // Das Gamma hat das Volumen verlassen und betritt es erneut.

                    GammaReflectionCounter = 2;

                    // Aktualisieren Sie die Informationen für dieses Gamma.
                    gammaVisitedVolumes[gammaID].clear();
                }

                // Das Gamma hat das Volumen verlassen, aktualisieren Sie die Informationen.
                gammaVisitedVolumes[gammaID].insert(currentVolume);
            }
        }


	fEventAction->AddEdep(iVol, edepStep, time, InterActionX, InterActionY, InterActionZ, ReflectionCounter, GammaReflectionCounter);

	

	
	
	
	
  
	
	G4LogicalVolume* PreStepPoint = step->GetPreStepPoint()->GetTouchableHandle()
	->GetVolume()->GetLogicalVolume();

	//G4StepStatus PreStepStatus = step->GetPreStepPoint()->GetStepStatus();
	// get the volume of the post step point
	G4LogicalVolume* PostStepPoint = step->GetPostStepPoint()->GetTouchableHandle()
	->GetVolume()->GetLogicalVolume();
	




}
