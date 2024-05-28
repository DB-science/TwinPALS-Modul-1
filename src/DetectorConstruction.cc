
#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "TrackerSD.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal
G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = nullptr;

DetectorConstruction::DetectorConstruction()
  : G4VUserDetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
DetectorConstruction::~DetectorConstruction()
{
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4bool checkOverlaps = true;
  // ------------- Materials -------------
  G4double a, z, density;
 
  G4int nelements;

  G4NistManager *nistManager = G4NistManager::Instance();
    G4bool isotopes = false;

    G4Material *fAir = nistManager->FindOrBuildMaterial("G4_AIR");
    
    G4Material *fAl = nistManager->FindOrBuildMaterial("G4_Al");
    
    G4Element*  O = nistManager->FindOrBuildElement("O" , isotopes);
    G4Element* Si = nistManager->FindOrBuildElement("Si", isotopes);
    G4Element* Lu = nistManager->FindOrBuildElement("Lu", isotopes);
    G4Element* Y = nistManager->FindOrBuildElement("Y", isotopes);
    G4Element* N = nistManager->FindOrBuildElement("N", isotopes);
    G4Element* C = nistManager->FindOrBuildElement("C", isotopes);
    G4Element* H = nistManager->FindOrBuildElement("H", isotopes);
    G4Element* F = nistManager->FindOrBuildElement("F", isotopes);
    
    
  
    G4Material* DetectorMaterial = new G4Material("DetectorMaterial",51., 121.75*g/mole, 6.697*g/cm3);


    G4Material* LYSO = new G4Material("LYSO", 7.4*g/cm3, 4);
    LYSO->AddElement(Lu, 6);
    LYSO->AddElement(Si, 10);
    LYSO->AddElement(O , 50);
    LYSO->AddElement(Y, 14);
    
    G4Material* BC422Q = new G4Material("BC422Q", 1.032*g/cm3, 2);
    BC422Q->AddElement(C, 10);
    BC422Q->AddElement(H, 11);


    G4Material*SilicaGlass = new G4Material("SilicaGlass", 2.203*g/cm3, 2);
    SilicaGlass->AddElement(Si,1);
    SilicaGlass->AddElement(O,2);

    G4Material* opticalGrease = new G4Material("opticalGrease", 1.060*g/cm3, 4);
    opticalGrease->AddElement(C,2);
    opticalGrease->AddElement(H,6);
    opticalGrease->AddElement(Si,1);
    opticalGrease->AddElement(O,1);
    
  G4Material *fTeflon = new G4Material("Teflon", 2.2*g/cm3, 2);
  fTeflon->AddElement(C, 0.240183);
  fTeflon->AddElement(F, 0.759817);

  G4Material* Al = new G4Material("Aluminium", 13., 26.98*g/mole, 2.700*g/cm3);
  G4Material* Ni = new G4Material("Nickel", 28., 58.69*g/mole, 8.910*g/cm3);
  G4Material* Au = new G4Material("Gold", 79., 196.97*g/mole, 19.32*g/cm3);
  G4Material* Ag = new G4Material("Silber", 47., 107.87*g/mole, 10.49*g/cm3);
  G4Material* Pb = new G4Material("Blei", 82., 207.20*g/mole, 11.35*g/cm3);

  G4Material* Co = new G4Material("Cobalt", 27.,58.9332*g/mole , 8.9*g/cm3);

  std::vector<G4double> pdTeflonPhotonMomentum  = { 1.0*eV, 6.05*eV};
  std::vector<G4double> pdTeflonRefractiveIndex = {1.3, 1.3};
  std::vector<G4double> pdTeflonReflectivity = {1., 1.};
  //std::vector<G4double> pdTeflonBackscatter = {0.8, 0.8};
  std::vector<G4double> pdTeflonAbs = {0.001 *um, 0.001 *um};
  
  G4MaterialPropertiesTable *pTeflonPropertiesTable = new G4MaterialPropertiesTable();

  // Optical Properties
  pTeflonPropertiesTable->AddProperty("RINDEX", pdTeflonPhotonMomentum, pdTeflonRefractiveIndex);
  pTeflonPropertiesTable->AddProperty("REFLECTIVITY", pdTeflonPhotonMomentum, pdTeflonReflectivity);
  //pTeflonPropertiesTable->AddProperty("BACKSCATTERCONSTANT", pdTeflonPhotonMomentum, pdTeflonBackscatter);
  pTeflonPropertiesTable->AddProperty("ABSLENGTH", pdTeflonPhotonMomentum, pdTeflonAbs);
  fTeflon->SetMaterialPropertiesTable(pTeflonPropertiesTable);
  


	
  G4double energy[18] = {2.70 * eV, 2.76 * eV,  2.82 * eV,2.88 * eV, 2.95 * eV,3.02 * eV,3.10 * eV, 3.18 * eV,3.26 * eV,3.29 * eV, 3.35 * eV,3.44 * eV,3.54 * eV, 4.133 * eV,5.636 * eV, 6.525 * eV,7.749 * eV,8.266 * eV};
  G4double rAir [18]= {1.0,1.0,1.0,1.0,1.0,1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

  
	G4double fast [18] = {0.001,0.09,0.17,0.29,0.38,0.51,0.65,0.80,0.97,1.00,0.78,0.43,0.07,0.0001, 0.00,0.0,0.0,0.0};
                       

	G4double rBC422Q [18]= {1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58};

	
	G4double abs [18]= {8.0*cm,8.0*cm,8.0*cm,8.0*cm,8.0*cm,8.0*cm,8.0*cm,8.0*cm,8.0*cm,8.0*cm,8.0*cm,8.0*cm,8.0*cm,8.0*cm,8.0*cm,8.0*cm,8.0*cm,8.0*cm};


	G4double fraction [18]= {1.0,1.0,1.0,1.0,1.0,1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

    G4double reflectivity [18] = {1.0,1.0,1.0,1.0,1.0,1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    
    
    G4MaterialPropertiesTable *mptBC422Q = new G4MaterialPropertiesTable();
    
    mptBC422Q->AddProperty("SCINTILLATIONCOMPONENT1", energy, fast,18);
    //mptBC422Q->AddProperty("SCINTILLATIONCOMPONENT2", energy, fast);
    mptBC422Q->AddProperty("RINDEX",energy, rBC422Q,18);
    mptBC422Q->AddProperty("ABSLENGTH", energy, abs,18);
    mptBC422Q->AddConstProperty("SCINTILLATIONYIELD", 3306./MeV,true);
    mptBC422Q->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptBC422Q->AddConstProperty("SCINTILLATIONRISETIME1", 110.*ps,true);
    mptBC422Q->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 0.7*ns,true);
    //mptBC422Q->AddConstProperty("SCINTILLATIONYIELD1", 1.);
    BC422Q->SetMaterialPropertiesTable(mptBC422Q);
  

  // Silicon grease https://eljentechnology.com/products/accessories/ej-550-ej-552
  G4double rSiliconGrease []= {1.46,1.46,1.46,1.46,1.46,1.46,1.46,1.46,1.46,1.46,1.46,1.46,1.46,1.46,1.46,1.46,1.46,1.46};
  G4double TransmissionSiliconGrease []= {0.999,0.999,0.999,0.999,0.999,0.999,0.999,0.999,0.999,0.999,0.999, 0.99, 0.97, 0.9, 0.0, 0.0, 0.0, 0.0};
  G4double reflectionSiliconGrease []= {0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.001,0.01,0.03,0.1,1.0,1.0,1.0,1.0};

 
  //std::vector<G4double> efficiency = {1.0, 1.0,1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,1.0, 1.0,1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
  
  G4double transmittance []= {1.0, 1.0,1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,1.0, 1.0,1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
  G4double reflectivityDet []= {0, 0,0, 0, 0, 0, 0, 0, 0,0, 0,0, 0, 0, 0, 0, 0, 0};
  G4double absLengthDetector []= {0.0001*mm, 0.0001*mm,0.0001*mm, 0.0001*mm, 0.0001*mm, 0.0001*mm, 0.0001*mm, 0.0001*mm, 0.0001*mm,0.0001*mm, 0.0001*mm,0.0001*mm, 0.0001*mm, 0.0001*mm, 0.0001*mm, 0.0001*mm, 0.0001*mm, 0.0001*mm};

  
  // SiO2 Glass https://www.heraeus.com/en/hca/fused_silica_quartz_knowledge_base_1/t_calc_1/transmission_calc_opt/transmission_calculator_opt.html?chartIndex=0&selection=reflection_losses%2Csuprasil_311_312%2Csuprasil_3001_3002_300%2Csuprasil_1_2a%2Csuprasil_313%2Csuprasil_3301_3302%2Csuprasil_2b%2Csuprasil_cg%2Cinfrasil_301_302%2Cspectrosil_2000%2Choq_310%2Cnerasil&thickness=10&rangeX=120%2C4500

  G4double transmissionSiliconGlass []= {0.9324, 0.9324,0.9324,0.9324,0.9324, 0.9324, 0.9324, 0.9324, 0.9324, 0.9324,0.9316,0.9305,0.9287,0.9233,0.9137,0.9066,0.0006,0.00001};
  
  G4double reflectionSiliconGlass []= {0.0676, 0.0676, 0.0676, 0.0676, 0.0676, 0.0676, 0.0676, 0.0676, 0.0676, 0.0676, 0.0684, 0.0695, 0.0713, 0.0767, 0.0863, 0.0934, 0.9994,0.99999};
  
  
  // https://refractiveindex.info/?shelf=main&book=SiO2&page=Arosa
  G4double rSiliconGlass []= {1.4554,1.4554,1.4554,1.4554,1.4554,1.4554,1.4554,1.4554,1.4554,1.4554,1.4581,1.4624,1.4701,1.4877,1.53,1.53,1.5384,1.5384};
  
  /*G4MaterialPropertiesTable* mptDetectorMaterial = new G4MaterialPropertiesTable();
  mptDetectorMaterial->AddProperty("ABSLENGTH", energy, absLengthDetector);
  mptDetectorMaterial->AddProperty("EFFICIENCY", energy, efficiency);
  DetectorMaterial->SetMaterialPropertiesTable(mptDetectorMaterial);*/


  G4MaterialPropertiesTable* mptSilicionGrease = new G4MaterialPropertiesTable();
  mptSilicionGrease->AddProperty("RINDEX", energy, rSiliconGrease,18);
  mptSilicionGrease->AddProperty("REFLECTIVITY", energy, reflectionSiliconGrease,18);
  mptSilicionGrease->AddProperty("TRANSMITTANCE", energy, TransmissionSiliconGrease,18);
  opticalGrease->SetMaterialPropertiesTable(mptSilicionGrease);

  G4MaterialPropertiesTable* mptSiliconGlass = new G4MaterialPropertiesTable();
  mptSiliconGlass->AddProperty("RINDEX", energy, rSiliconGlass,18);
  mptSiliconGlass->AddProperty("REFLECTIVITY", energy, reflectionSiliconGlass,18);
  mptSiliconGlass->AddProperty("TRANSMITTANCE", energy, transmissionSiliconGlass,18);
  SilicaGlass->SetMaterialPropertiesTable(mptSiliconGlass);

  G4MaterialPropertiesTable* mptAl = new G4MaterialPropertiesTable();
  mptAl->AddProperty("RINDEX", energy, rSiliconGlass,18);
  mptAl->AddProperty("REFLECTIVITY", energy, reflectivityDet,18);
  mptAl->AddProperty("TRANSMITTANCE", energy, transmittance,18);
  fAl->SetMaterialPropertiesTable(mptAl);


  G4MaterialPropertiesTable *mptAir = new G4MaterialPropertiesTable();
  mptAir->AddProperty("RINDEX", energy, rAir, true);
  fAir->SetMaterialPropertiesTable(mptAir);
	
  G4MaterialPropertiesTable *OpSurfaceProperty = new G4MaterialPropertiesTable();


  G4OpticalSurface* opTeflonSurface = new G4OpticalSurface("TeflonSurface");
  opTeflonSurface->SetType(dielectric_LUT);
  opTeflonSurface->SetModel(LUT);
  opTeflonSurface->SetFinish(polishedteflonair);
  
  
  opTeflonSurface->SetMaterialPropertiesTable(OpSurfaceProperty);
	
    G4Material *SampleElement;

//////////////////////////////////////////////////////////////////////////////
///////////////// INPUT HERE /////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

    //World size
    G4double worldSizeXY = 20. * cm;
    G4double worldSizeZ = 20. * cm;

    //Crystal Parameters
    G4double cryst_dX = 40.* mm; //if Cylinder == diameter; if Cone == Scintillaror Surface to Detector
    G4double cryst_dY = 40.* mm;

    G4double cryst_dZ = 29.7* mm; //Tickness of the scintillator


    G4double Frontradius = 9.5*mm; //Cone == Frontradius scintillator to Sample

    //Scintillator_front_distance from origin 
    G4int Distance_from_origin = 3; // in mm

    //Chose your scintillator-geometry
    //0 == Cube; 1 == Cylinder; 2 == truncated Pyramid; 3 == truncated Cone
    G4int Scintillator_geometry_choice = 0; 


    //always two tube samples (Face-to-Face); Chose dimensions and element
    G4double SampleRadius = 8.0; //mm
    G4double SampleThicknes = 1.0; //
    SampleElement = Al; //Al, Ni, Ag, Au, Pb, Co



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

    // Get materials
    G4Material* defaultMaterial = G4Material::GetMaterial("G4_AIR");
    
    G4Material* cryst_mat = G4Material::GetMaterial("BC422Q");
    
      //G4Material* cryst_mat = G4Material::GetMaterial("LYSO");

    // World
    //
    G4VSolid *worldS
            = new G4Box("World",           // its name
                        worldSizeXY / 2, worldSizeXY / 2, worldSizeZ / 2); // its size

    G4LogicalVolume *worldLV
            = new G4LogicalVolume(
                    worldS,           // its solid
                    defaultMaterial,  // its material
                    "World");         // its name

    G4VPhysicalVolume *worldPV
            = new G4PVPlacement(
                    0,                // no rotation
                    G4ThreeVector(),  // at (0,0,0)
                    worldLV,          // its logical volume
                    "World",          // its name
                    0,                // its mother  volume
                    false,            // no boolean operation
                    0,                // copy number
                    fCheckOverlaps);  // checking overlaps
                    
	G4double cryst_xpos = cryst_dX , cryst_ypos = cryst_dY ;
	
	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rAir, 2);
	defaultMaterial->SetMaterialPropertiesTable(mptWorld);



    if(Scintillator_geometry_choice == 3){
      //Geometry for Cons>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    
      crystalS = new G4Cons("crystal", 0.,cryst_dX/2, 0., Frontradius, cryst_dZ/2, 0.,2*M_PI );
      
      crystalLV
            = new G4LogicalVolume(
                    crystalS,     // its solid
                    cryst_mat,  // its material0.75*mm
                    "Crystal");   // its name

      //Cylinder Geometrie Detektor>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      solidDetector = new G4Tubs("solidDetector", 0.,cryst_dX/2, 0.5*mm, 0.,2*M_PI );

      logicDetector = new G4LogicalVolume(solidDetector, fAl, "logicDetector");

      //Silicone grease
      solidOpticalGrease = new G4Tubs("solidOpticalGrease", 0.,cryst_dX/2, 0.05*mm, 0.,2*M_PI );

      logicOpticalGrease = new G4LogicalVolume(solidOpticalGrease, opticalGrease, "logicOpticalGrease");

      //Silica Glass
      solidOpticalWindow = new G4Tubs("solidOpticalWindow", 0.,cryst_dX/2, 1.*mm, 0.,2*M_PI );

      logicOpticalWindow = new G4LogicalVolume(solidOpticalWindow, SilicaGlass, "logicOpticalWindow ");

    
      //wrapping for cone geometry>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

      crystalShape = new G4Cons("crystalshape",  0.,cryst_dX/2, 0.,Frontradius , cryst_dZ/2, 0.,2*M_PI);//war 8mm

      BigTrd = new G4Cons("BigTrd",  0.,cryst_dX/2 + 0.5*mm, 0., Frontradius+0.5*mm, cryst_dZ/2, 0.,2*M_PI);
      
      substract = new G4SubtractionSolid("substract", BigTrd, crystalShape,0, G4ThreeVector(0.,0.,0.0*mm));

      logicSubstract = new G4LogicalVolume(substract , fTeflon, "logicSubstract");

      //Front Wrapping cylinder>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      solidFoilD = new G4Tubs("solidFoilD",  0., Frontradius +0.5*mm, 0.2*mm, 0.,2*M_PI );
    
      logicFoilD = new G4LogicalVolume(solidFoilD, fTeflon, "logicFoilD");
 
    }else if(Scintillator_geometry_choice == 2){
      //Pyrmiden geometry for crystal>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      crystalPyS = new G4Trd("crystal", cryst_dX/2, Frontradius/2, cryst_dY/2, Frontradius/2, cryst_dZ/2);
  
      crystalLV
            = new G4LogicalVolume(
                    crystalPyS,     // its solid
                    cryst_mat,  // its material0.75*mm
                    "Crystal");   // its name

      //Box Geometrie Detektor>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      solidDetectorPy = new G4Box("solidDetector", cryst_dX/2, cryst_dY/2, 0.5*mm);
      logicDetector = new G4LogicalVolume(solidDetectorPy, defaultMaterial, "logicDetector");

      //Silicone grease
      solidOpticalGreaseCube = new G4Box("solidOpticalGrease", cryst_dX/2, cryst_dY/2, 0.05*mm);

      logicOpticalGrease = new G4LogicalVolume(solidOpticalGreaseCube, opticalGrease, "logicOpticalGrease");

      //Silica Glass
      solidOpticalWindowCube = new G4Box("solidOpticalWindow", cryst_dX/2, cryst_dY/2, 1.*mm);

      logicOpticalWindow = new G4LogicalVolume(solidOpticalWindowCube, SilicaGlass, "logicOpticalWindow ");

    
      //wrapping for pyramid geometry>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

      crystalShapePy = new G4Trd("crystalshape", cryst_dX/2, Frontradius/2 , cryst_dY/2, Frontradius/2 , cryst_dZ/2);

      BigTrdPy = new G4Trd("BigTrd", cryst_dX/2 + 1*mm, Frontradius/2 +0.5*mm , cryst_dY/2 + 1*mm, Frontradius/2 +0.5*mm, cryst_dZ/2);
    
      substractPy = new G4SubtractionSolid("substract", BigTrdPy, crystalShapePy,0, G4ThreeVector(0.,0.,0.0*mm));

      logicSubstract = new G4LogicalVolume(substractPy , fTeflon, "logicSubstract");
    
      //Front wrapping Box>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

      solidFoilDPy = new G4Box("solidFoilD",  Frontradius/2 +0.5*mm,  Frontradius/2 +0.5*mm,   0.2 * mm);
    
      logicFoilD = new G4LogicalVolume(solidFoilDPy, fTeflon, "logicFoilD");


    }else if(Scintillator_geometry_choice == 1){
      //Geometry for Cylinder Crystals>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

      crystalSTube = new G4Tubs("crystal", 0.,cryst_dX/2, cryst_dZ/2, 0.,2*M_PI );

    
      crystalLV
            = new G4LogicalVolume(
                    crystalSTube,     // its solid
                    cryst_mat,  // its material0.75*mm
                    "Crystal");   // its name

      //Cylinder Geometrie Detektor>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      solidDetector = new G4Tubs("solidDetector", 0.,cryst_dX/2, 0.5*mm, 0.,2*M_PI );

      logicDetector = new G4LogicalVolume(solidDetector, fAl, "logicDetector");

      //Silicone grease
      solidOpticalGrease = new G4Tubs("solidOpticalGrease", 0.,cryst_dX/2, 0.05*mm, 0.,2*M_PI );

      logicOpticalGrease = new G4LogicalVolume(solidOpticalGrease, opticalGrease, "logicOpticalGrease");

      //Silica Glass
      solidOpticalWindow = new G4Tubs("solidOpticalWindow", 0.,cryst_dX/2, 1.*mm, 0.,2*M_PI );

      logicOpticalWindow = new G4LogicalVolume(solidOpticalWindow, SilicaGlass, "logicOpticalWindow ");

    
      //wrapping for cylinder geometry>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

      crystalShapeTube = new G4Tubs("crystalshape", 0.,cryst_dX/2, cryst_dZ/2, 0.,2*M_PI);

      BigTrdTube  = new G4Tubs("BigTrd", 0.,cryst_dX/2+0.5*mm, cryst_dZ/2, 0.,2*M_PI);
    
      substractTube  = new G4SubtractionSolid("substract", BigTrdTube, crystalShapeTube,0, G4ThreeVector(0.,0.,0.0*mm));

      logicSubstract = new G4LogicalVolume(substractTube , fTeflon, "logicSubstract");

      //Front Wrapping cylinder>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      solidFoilD = new G4Tubs("solidFoilD",  0., cryst_dX/2 +0.5*mm, 0.2*mm, 0.,2*M_PI );
    
      logicFoilD = new G4LogicalVolume(solidFoilD, fTeflon, "logicFoilD");
 
    }else if(Scintillator_geometry_choice == 0){
      //Box geometry for crystal>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

      crystalSBox = new G4Box("crystal", cryst_dX/2, cryst_dY/2, cryst_dZ/2);

      crystalLV
            = new G4LogicalVolume(
                    crystalSBox,     // its solid
                    cryst_mat,  // its material0.75*mm
                    "Crystal");   // its name

      //Box Geometrie Detektor>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      solidDetectorPy = new G4Box("solidDetector", cryst_dX/2, cryst_dY/2, 0.5*mm);
      logicDetector = new G4LogicalVolume(solidDetectorPy, defaultMaterial, "logicDetector");

      //Silicone grease
      solidOpticalGreaseCube = new G4Box("solidOpticalGrease", cryst_dX/2, cryst_dY/2, 0.05*mm);

      logicOpticalGrease = new G4LogicalVolume(solidOpticalGreaseCube, opticalGrease, "logicOpticalGrease");

      //Silica Glass
      solidOpticalWindowCube = new G4Box("solidOpticalWindow", cryst_dX/2, cryst_dY/2, 1.*mm);

      logicOpticalWindow = new G4LogicalVolume(solidOpticalWindowCube, SilicaGlass, "logicOpticalWindow ");

    
      //wrapping Box>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

      crystalShapeBox = new G4Box("crystalshape", cryst_dX/2, cryst_dY/2, cryst_dZ/2);

      BigBox = new G4Box("BigBox", cryst_dX/2 + 1*mm, cryst_dY/2 + 1*mm, cryst_dZ/2);
    
      substractBox = new G4SubtractionSolid("substract", BigBox, crystalShapeBox,0, G4ThreeVector(0.,0.,0.0*mm));

      logicSubstract = new G4LogicalVolume(substractBox , fTeflon, "logicSubstract");

      //Front wrapping Box>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

      solidFoilDPy = new G4Box("solidFoilD",  cryst_dX/2 +0.5*mm,  cryst_dY/2 +0.5*mm,   0.2 * mm);
    
      logicFoilD = new G4LogicalVolume(solidFoilDPy, fTeflon, "logicFoilD");
    }

    
    
    
    //Sample Cration and if you want shielding
    G4Tubs* Sample = new G4Tubs("sample", 0.,SampleRadius*mm, SampleThicknes/2*mm, 0.,2*M_PI );
    G4Tubs* SampleShield = new G4Tubs("sampleShield", 0.,cryst_dX/2, 0.75*mm, 0.,2*M_PI );

    G4VSolid * substractSampleshiled = new G4SubtractionSolid("substractSampleshiled", SampleShield, Sample,0, G4ThreeVector(0.,0.,0.0*mm));

    G4Tubs* GoldShield = new G4Tubs("goldShield",0., 20.*mm, 1.1*mm,0.,2*M_PI );

    G4LogicalVolume* sampleLVShiedl
            = new G4LogicalVolume(
                    SampleShield,     // its solid
                    Pb,  // its material
                    "sampleShield");


    G4LogicalVolume* sampleLV
            = new G4LogicalVolume(
                    Sample,     // its solid
                    SampleElement,  // its material
                    "sample");

    G4LogicalVolume* goldShieldLV
            = new G4LogicalVolume(
                    GoldShield,     // its solid
                    Pb,  // its material
                    "goldShield");

    

     G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin",worldLV, mirrorSurface); 
    


    
    //SHielding 90 grad Setup

    /*G4int Z = 14;
    G4Rotate3D rotZShield((45)*deg, G4ThreeVector(1,0,0));
    G4Rotate3D rotZShield2((90)*deg, G4ThreeVector(1,0,0));

    G4Translate3D transXSampleShield(G4ThreeVector(0,0,-(cryst_dZ/2+Z*mm) ));
		G4Transform3D transformSampleShield =(rotZShield)*(transXSampleShield)*(rotZShield2);

    G4VPhysicalVolume *physSampleShield = new G4PVPlacement(transformSampleShield, sampleLVShiedl, "physDSampleShield", worldLV, false,0, true);*/
		
    //Goldshield
    //G4VPhysicalVolume *physGoldShield = new G4PVPlacement(0, G4ThreeVector(0.*mm, 0.*mm, -3.3*mm), goldShieldLV, "physGoldshield", worldLV, false,0, true);
     
for(G4int i=0; i<2; i++)
	{

    /*G4OpticalSurface* OpSurfaceDetector = new G4OpticalSurface("DetectorSurface", glisur, polished, dielectric_metal,1);
    G4MaterialPropertiesTable * OpSurfaceDetectorProperty = new G4MaterialPropertiesTable();

    OpSurfaceDetectorProperty->AddProperty("REFLECTIVITY", energy, reflectivityDet);
    OpSurfaceDetectorProperty->AddProperty("TRANSMITTANCE", energy, transmittance);
    OpSurfaceDetectorProperty->AddProperty("EFFICIENCY", energy, efficiency);

    OpSurfaceDetector->SetMaterialPropertiesTable(OpSurfaceDetectorProperty);
    
    G4LogicalSkinSurface* DetSurface1 = new G4LogicalSkinSurface(
    "DetSurface1", logicDetector, OpSurfaceDetector);*/

		//90 Grad Arrangment>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		/*G4int Z = 14;

    G4Rotate3D rotZ((i*90)*deg, G4ThreeVector(1,0,0));

    
		G4Rotate3D rotZsample((315)*deg, G4ThreeVector(1,0,0));

    G4Translate3D transXScint(G4ThreeVector(0,0,-(cryst_dZ/2+Z*mm)));
		G4Transform3D transformScint =(rotZ)*(transXScint);
		
    G4Translate3D transXGrease(G4ThreeVector(0,0,-(cryst_dZ+Z*mm+0.05*mm)));
		G4Transform3D transformGrease =(rotZ)*(transXGrease);

    G4Translate3D transXWindow(G4ThreeVector(0,0,-(cryst_dZ+Z*mm+1.1*mm)));
		G4Transform3D transformWindow =(rotZ)*(transXWindow);


		G4Translate3D transXDet(G4ThreeVector(0,0, -(cryst_dZ+Z*mm+2.6*mm)));
		G4Transform3D transformDet =(rotZ)*(transXDet);
		
		G4Translate3D transXFolO(G4ThreeVector(0,0,-(cryst_dZ/2+Z*mm)));
		G4Transform3D transformFolO =(rotZ)*(transXFolO);
		
    G4Translate3D transXFolD(G4ThreeVector(0,0, -(Z*mm-0.2*mm)));
		G4Transform3D transformFolD =(rotZ)*(transXFolD);

    G4Translate3D transXSample(G4ThreeVector(0,0, i*(2.0*mm)-(1.00*mm)));
		G4Transform3D transformSample =(transXSample)*(rotZsample);
    */

    
    
    
    
    G4Rotate3D rotZ((i*180)*deg, G4ThreeVector(1,1,0));
    //Abstand der Scintilatoren
    G4int Z = Distance_from_origin;

		G4Translate3D transXScint(G4ThreeVector(0,0, i*(cryst_dZ+(2.0*Z*mm))-(cryst_dZ/2+Z*mm)));
		G4Transform3D transformScint =(transXScint)*(rotZ);
		

    G4Translate3D transXGrease(G4ThreeVector(0,0,i*(2*cryst_dZ+(2.0*Z*mm)+0.1*mm)-(cryst_dZ+Z*mm+0.05*mm)));
		G4Transform3D transformGrease =(transXGrease)*(rotZ);

    G4Translate3D transXWindow(G4ThreeVector(0,0,i*(2*cryst_dZ+(2.0*Z*mm)+2.2*mm)-(cryst_dZ+Z*mm+1.10*mm)));
		G4Transform3D transformWindow =(transXWindow)*(rotZ);

		G4Translate3D transXDet(G4ThreeVector(0,0,i*(2*cryst_dZ+(2.0*Z*mm)+5.2*mm)-(cryst_dZ+Z*mm+2.6*mm)));
		G4Transform3D transformDet =(transXDet)*(rotZ);
		
		G4Translate3D transXFolO(G4ThreeVector(0,0, i*(cryst_dZ+(2.0*Z*mm))-(cryst_dZ/2+Z*mm)));
		G4Transform3D transformFolO =(transXFolO)*(rotZ);
		
    G4Translate3D transXFolD(G4ThreeVector(0,0.,i*(2.0*Z*mm-0.4*mm)-(Z*mm-0.2*mm)));
		G4Transform3D transformFolD =(transXFolD)*(rotZ);


    G4Translate3D transXSample(G4ThreeVector(0,0.,i*(SampleThicknes*mm)-(SampleThicknes/2*mm)));
		G4Transform3D transformSample =(transXSample);
		
    G4VPhysicalVolume *physGrease = new G4PVPlacement(transformGrease, logicOpticalGrease, "physGrease", worldLV, false,i, true);
    G4VPhysicalVolume *physWindow = new G4PVPlacement(transformWindow, logicOpticalWindow, "physWindow", worldLV, false,i, true);
    G4VPhysicalVolume *physDetector = new G4PVPlacement(transformDet, logicDetector, "physDetector", worldLV, false,i, true);
    G4VPhysicalVolume *physSample = new G4PVPlacement(transformSample, sampleLV, "physDSample", worldLV, false,i, true);
    //G4VPhysicalVolume *physSampleShield = new G4PVPlacement(transformSample, sampleLVShiedl, "physDSampleShield", worldLV, false,i, true);
		
		cAbsorberPV
            = new G4PVPlacement(
            transformScint,  // at (0,0,0)
            crystalLV,          // its logical volume
            "crystalPV",    // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            i,                // copy number
            fCheckOverlaps);  // checking overlaps
            
            physFoilO = new G4PVPlacement(transformFolO, logicSubstract, "physFoilO", worldLV, false, i, true);
            
            physFoilD = new G4PVPlacement(transformFolD, logicFoilD, "physFoilD", worldLV, false, i, true);

		
  }



    G4LogicalSkinSurface* teflonSurface1 = new G4LogicalSkinSurface(
    "TeflonSurface1", logicSubstract, opTeflonSurface);
    G4LogicalSkinSurface* teflonSurface5 = new G4LogicalSkinSurface(
    "TeflonSurface5", logicFoilD, opTeflonSurface);
    
   

    fScoringVolume = crystalLV;
    
    
    
   
   

    

    G4VisAttributes *simpleBoxVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    simpleBoxVisAtt->SetVisibility(true);
    

    //
    // Always return the physical World
    //
    return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
  // Sensitive detectors

  G4String trackerSDname = "/TrackerChamberSD";
  TrackerSD* aTrackerSD = new TrackerSD(trackerSDname);
  G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
  
  
  
 
  SetSensitiveDetector("logicDetector", aTrackerSD, true);
  G4ThreeVector fieldValue = G4ThreeVector();
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);

  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}
void DetectorConstruction::SetMaxStep(G4double maxStep)
{
  if ((fStepLimit)&&(maxStep>0.)) fStepLimit->SetMaxAllowedStep(maxStep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


