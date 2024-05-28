
#include "TrackerSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include <G4ITStepProcessor.hh>
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4SystemOfUnits.hh"
#include "G4VTouchable.hh"
#include "G4OpticalPhoton.hh"
#include "G4Gamma.hh"
#include "DetectorConstruction.hh"
#include "G4ParticleDefinition.hh"
#include <iterator>
#include "TrackerHit.hh"
#include <fstream>
#include <array>

using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerSD::TrackerSD(G4String name)
 : G4VSensitiveDetector(name), 
  fhitCollection(0)
{
  quEff = new G4PhysicsOrderedFreeVector();
  G4String hitsCollectionName;
  collectionName.insert(hitsCollectionName="HitCollect");

  fstream datafile;
  datafile.open("eff.dat");

  while(1)
  {
    G4double energy, queff;

    datafile >> energy >> queff;

    if(datafile.eof())
      break;

    quEff->InsertValues(energy, queff);
  }

  datafile.close();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerSD::~TrackerSD()
{}


void TrackerSD::BeginOfEvent(G4HCofThisEvent*hitCollection )
{

}


void TrackerSD::Initialize(G4HCofThisEvent* hitCollection)
{

  
  // Create hits collection

   fhitCollection 
    = new TrackerHitCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce

  G4int hcID
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hitCollection->AddHitsCollection( hcID, fhitCollection );
}

void TrackerSD::ResetVars()
{
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool TrackerSD::ProcessHits(G4Step* aStep,
                                     G4TouchableHistory *ROhist)
{


	static G4ParticleDefinition* gamma =
       G4Gamma::GammaDefinition();
	static G4ParticleDefinition* opticalPhoton =
       G4OpticalPhoton::OpticalPhotonDefinition();
  G4AnalysisManager *AnalysisManager = G4AnalysisManager::Instance();
  
  G4Track *track = aStep->GetTrack();
  track->SetTrackStatus(fStopAndKill);
  G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
  G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

  G4ThreeVector momPhoton = preStepPoint->GetMomentum();
  G4double PhotonEnergy = 0.0;
  if(opticalPhoton){
  PhotonEnergy = momPhoton.mag()/eV;
  //cout<< PhotonEnergy<<endl;


  
  }

  // Get Detector number 
  const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
  G4int copyNo = touchable->GetVolume()->GetCopyNo();
  



 if(G4UniformRand() < quEff->Value(PhotonEnergy)){
  //____Detector 0
  if((copyNo==0)){//
  G4double TrackDistance = track->GetTrackLength()/mm;
  G4double ArrTime1 =
   aStep->GetPreStepPoint()-> GetGlobalTime()/ns;

    MeanArrivalTime1.push_back(ArrTime1);
    MeanTrackLength1.push_back(TrackDistance);
 
    }

//_____Detector 1
   if((copyNo==1)){//
   G4double timeOfArrival = aStep->GetPreStepPoint()-> GetGlobalTime()/ns;
    G4double TrackDistance = track->GetTrackLength()/mm;
    MeanArrivalTime2.push_back(timeOfArrival);

    MeanTrackLength2.push_back(TrackDistance);
   }
}

  
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerSD::EndOfEvent(G4HCofThisEvent*hitCollection)
{



//Mean Value of Arrivaltime at detector0
if(MeanArrivalTime1.size()>=2){
avg1 = getAverage1(MeanArrivalTime1);
numberOfCounts1 =MeanArrivalTime1.size();
/*for(int i; i< MeanArrivalTime1.size(); i++){
  Det1_arrivaltimes[i] = MeanArrivalTime1[i];
}*/
}
else{
  avg1=0;
  numberOfCounts1 =0;
}
//Mean Value of Arrivaltime at detector1
if(MeanArrivalTime2.size()>=2){
avg2 = getAverage2(MeanArrivalTime2);
numberOfCounts2=MeanArrivalTime2.size();
/*for(int i; i< MeanArrivalTime2.size(); i++){
  Det2_arrivaltimes[i] = MeanArrivalTime2[i];
}*/
}
else{
  avg2=0;
  numberOfCounts2=0;
}
//cout<<numberOfCounts2<<" "<<numberOfCounts1<<endl;

//Mean Value of TrackLength at detector0
if(MeanTrackLength1.size()>=2){
TrackLength1 = getAverage1(MeanTrackLength1);

}
else{
  TrackLength1=0;
}

//Mean Value of TrackLength at detector0
if(MeanTrackLength2.size()>=2){
TrackLength2 = getAverage2(MeanTrackLength2);

}
else{
  TrackLength2=0;
}

  fhitCollection->SetMean1(avg1);
  fhitCollection->SetMean2(avg2);
  fhitCollection->SetnumberOfCounts1(numberOfCounts1);
  fhitCollection->SetnumberOfCounts2(numberOfCounts2);

  fhitCollection->SetTrackMean1(TrackLength1);
  fhitCollection->SetTrackMean2(TrackLength2);

  //median 
if(MeanArrivalTime1.size()>=2){
  std::sort(MeanArrivalTime1.begin(),MeanArrivalTime1.end());
  int index1 =MeanArrivalTime1.size()/2;
  Median1 = MeanArrivalTime1[index1];
  
  //if size is pair
  if(!MeanArrivalTime1.size()%2)
  {
    Median1=(Median1+MeanArrivalTime1[index1-1])/2;
  }
}
else{
  Median1 = 0.0;
}
  
  
if(MeanArrivalTime2.size()>=2){
  std::sort(MeanArrivalTime2.begin(),MeanArrivalTime2.end());
  int index2 =MeanArrivalTime2.size()/2;
  Median2 = MeanArrivalTime2[index2];
  
  //if size is pair
  if(!MeanArrivalTime2.size()%2)
  {
    Median2=(Median1+MeanArrivalTime2[index2-1])/2;
  }
}
else{
  Median2 = 0.0;
}


//fhitCollection->SetTimes1(Det1_arrivaltimes);
//fhitCollection->SetTimes2(Det2_arrivaltimes);

//fhitCollection->SetMedian1(Median1);
//fhitCollection->SetMedian2(Median2);
/*fstream myfile("/home/simulation/Schreibtisch/StreamReader/Data/ReconvolutionStudyWithLQE/1Puls_1275.txt",ios::out);
fstream myfile1("/home/simulation/Schreibtisch/StreamReader/Data/ReconvolutionStudyWithLQE/2Puls_1275.txt",ios::out);

for(int n = 0; n< MeanArrivalTime1.size(); n++){
  double Value = MeanArrivalTime1[n];
  myfile<<Value<<endl;
}

for(int n = 0; n< MeanArrivalTime2.size(); n++){
  double Value = MeanArrivalTime2[n];
  myfile1<<Value<<endl;
}*/


    fhitCollection->insert(new TrackerHit);
    
//Det1_arrivaltimes ={0.0};
//Det2_arrivaltimes = {0.0};    
MeanArrivalTime1.clear();
MeanArrivalTime2.clear();
MeanTrackLength1.clear();
MeanTrackLength2.clear();

//myfile.close();
//myfile1.close();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



