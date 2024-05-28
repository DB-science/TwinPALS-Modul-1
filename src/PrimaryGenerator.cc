#include "PrimaryGenerator.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryParticle.hh"
#include "G4PrimaryVertex.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "DG4LTSettingsManager.hh"
#include "DG4LTLifetimeSimulatorEngine.hh"
#include "G4AnalysisManager.hh"
#include <chrono>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGenerator::PrimaryGenerator()
: G4VPrimaryGenerator(), primaryGenType(DG4LTPGenParticleType::UNKNOWN)
    , fLifetime(0.)
{DG4LTLifetimeSimulatorEngine::sharedInstance()->init(DG4LTSimulationParameterManager::sharedInstance()->m_isotopeName);

timeA = 0.;
fLifetime = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGenerator::~PrimaryGenerator()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double PrimaryGenerator::getTheoLifetime() const {
	return fLifetime;
}
    double PrimaryGenerator::getStartTime() const {
		return timeA;
	}

void PrimaryGenerator::GeneratePrimaryVertex(G4Event* event)
{

  G4int Wich_gamma_energy = 1; //0 for 1275keV; 1 for colinear 511keV

  const double PI = 3.141592654;
   unsigned int seed1 = static_cast<unsigned int>(time(nullptr));
   seed1 ^= static_cast<unsigned int>(rand());
   srand(seed1);



  double theta = 0, phi = 0;
   
    theta = 2*PI*irand(0,1);

    unsigned int seed2 = static_cast<unsigned int>(time(nullptr))+11;
    seed2 ^= static_cast<unsigned int>(rand());
    srand(seed2);
    // corrrect
    phi = acos(2*irand(0,1)-1.0);

    const float r_x_start = sin(phi) * cos(theta);
    const float r_y_start = sin(phi) * sin(theta);
    const float r_z_start = cos(phi);


    double theta1 = 0, phi1 = 0;

    theta1 = 2*PI*irand1(0,1);
    // corrrect
    phi1 = acos(2*irand1(0,1)-1.0);

    const float r_x_stop = sin(phi1) * cos(theta1);
    const float r_y_stop = sin(phi1) * sin(theta1);
    const float r_z_stop = cos(phi1);
   
   
   
   
   /*unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::mt19937 generatorStart (seed);
    std::uniform_real_distribution<double> uniform01(0.0, 1.0);

        const float theta = 2 * M_PI * uniform01(generator);
        const float phi = acos(1 - 2 * uniform01(generator));
        const float r_x_start = sin(phi) * cos(theta);
        const float r_y_start = sin(phi) * sin(theta);
        const float r_z_start = cos(phi);
	
    std::mt19937 generatorStopp (seed);
    std::uniform_real_distribution<double> uniform012(0.0, 1.0);

        const float theta1 = 2 * M_PI * uniform012(generator);
        const float phi1 = acos(1 - 2 * uniform012(generator));
        const float r_x_stop = sin(phi1) * cos(theta1);
        const float r_y_stop = sin(phi1) * sin(theta1);
        const float r_z_stop = cos(phi1);*/


  const float absr_start = sqrt(r_x_start * r_x_start + r_y_start * r_y_start + r_z_start * r_z_start);
  const float absr_stop  = sqrt(r_x_stop * r_x_stop + r_y_stop * r_y_stop + r_z_stop * r_z_stop);

  const G4ThreeVector vec_start(r_x_start / absr_start, r_y_start / absr_start, r_z_start / absr_start);
  const G4ThreeVector vec_stop(r_x_stop / absr_stop, r_y_stop / absr_stop, r_z_stop / absr_stop);

  /* set source position */

  const G4double x0 = 0.0;
  const G4double y0 = 0.0*mm;
  const G4double z0 = 0.0;
  //
  
  StartWinkelX = r_x_start / absr_start;
  StartWinkelY = r_y_start / absr_start; 
  StartWinkelZ = r_z_start / absr_start;
  StoppWinkel1X = r_x_stop / absr_stop;
  StoppWinkel1Y = r_y_stop / absr_stop;
  StoppWinkel1Z = r_z_stop / absr_stop;
  StoppWinkel2X = -StoppWinkel1X;
  StoppWinkel2Y = -StoppWinkel1Y;
  StoppWinkel2Z = -StoppWinkel1Z;

  
  G4ThreeVector positionA(x0, y0, z0);
  
  G4PrimaryVertex* vertexA = new G4PrimaryVertex(positionA, 0);

  G4ThreeVector positionB(x0, y0, z0);

  G4PrimaryVertex* vertexB = new G4PrimaryVertex(positionB, 0);

  //particle 1 at vertex A
  
  G4ParticleDefinition* particleDefinition
           = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
  G4PrimaryParticle* particle1;
  G4PrimaryParticle* particle2;
  G4PrimaryParticle* particle3;

  if(Wich_gamma_energy==0){
    particle1 = new G4PrimaryParticle(particleDefinition);
    particle1->SetMomentumDirection(vec_start);    
    particle1->SetKineticEnergy(1.275*MeV);//   Na22 = 1.274*MeV
  
    vertexA->SetPrimary(particle1);
    event->AddPrimaryVertex(vertexA);
  }
  
  
  if(Wich_gamma_energy==1){
    //vertex (B) symetric to vertex A
    //particles 2 and 3 at vertex B       
    particle2 = new G4PrimaryParticle(particleDefinition);
    particle2->SetMomentumDirection(vec_stop);    
    particle2->SetKineticEnergy(511.*keV);
    
    particle3 = new G4PrimaryParticle(particleDefinition);
    particle3->SetMomentumDirection(G4ThreeVector(-vec_stop));    
    particle3->SetKineticEnergy(511*keV);
    vertexB->SetPrimary(particle2);
    vertexB->SetPrimary(particle3);  
    event->AddPrimaryVertex(vertexB);
  }  
  
  G4AnalysisManager* AnalysisManager = G4AnalysisManager::Instance();


}

float PrimaryGenerator::getStartAngleX() const {
	return StartWinkelX;
}
float PrimaryGenerator::getStoppAngle1X() const {
	return StoppWinkel1X;
}
float PrimaryGenerator::getStoppAngle2X() const {
	return StoppWinkel2X;
}
float PrimaryGenerator::getStartAngleY() const {
	return StartWinkelY;
}
float PrimaryGenerator::getStoppAngle1Y() const {
	return StoppWinkel1Y;
}
float PrimaryGenerator::getStoppAngle2Y() const {
	return StoppWinkel2Y;
}
float PrimaryGenerator::getStartAngleZ() const {
	return StartWinkelZ;
}
float PrimaryGenerator::getStoppAngle1Z() const {
	return StoppWinkel1Z;
}
float PrimaryGenerator::getStoppAngle2Z() const {
	return StoppWinkel2Z;
}
