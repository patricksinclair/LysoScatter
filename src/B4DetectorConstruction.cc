

#include <G4SubtractionSolid.hh>
#include "B4DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4PSEnergyDeposit.hh"


G4ThreadLocal
G4GlobalMagFieldMessenger *B4DetectorConstruction::fMagFieldMessenger = 0;


B4DetectorConstruction::B4DetectorConstruction()
        : G4VUserDetectorConstruction(),
          cAbsorberPV(0),
          NAbsorberPV(0),
          EAbsorberPV(0),
          SAbsorberPV(0),
          WAbsorberPV(0),

          cFoilPV(0),

          fGapPV(0),
          fCheckOverlaps(true) {
}


B4DetectorConstruction::~B4DetectorConstruction() {
}


G4VPhysicalVolume *B4DetectorConstruction::Construct() {
    // Define materials
    DefineMaterials();

    // Define volumes
    return DefineVolumes();
}



void B4DetectorConstruction::DefineMaterials() {

    G4NistManager *nistManager = G4NistManager::Instance();
    G4bool isotopes = false;

    nistManager->FindOrBuildMaterial("G4_AIR");
    G4double density = 2.700*g/cm3, a = 26.98*g/mole;

    G4Element*  Al = nistManager->FindOrBuildElement("Al" , isotopes);
    G4Material* Aluminium = new G4Material("Al", density, 1);
    Aluminium->AddElement(Al, 1);



    G4Element*  O = nistManager->FindOrBuildElement("O" , isotopes);
    G4Element* Si = nistManager->FindOrBuildElement("Si", isotopes);
    G4Element* Lu = nistManager->FindOrBuildElement("Lu", isotopes);
    G4Element* Y = nistManager->FindOrBuildElement("Y", isotopes);

    G4Material* LYSO = new G4Material("LYSO", 7.4*g/cm3, 4);
    LYSO->AddElement(Lu, 6);
    LYSO->AddElement(Si, 10);
    LYSO->AddElement(O , 50);
    LYSO->AddElement(Y, 14);
}


G4VPhysicalVolume *B4DetectorConstruction::DefineVolumes() {
    // Geometry parameters

    //World size
    G4double worldSizeXY = 4. * cm;
    G4double worldSizeZ = 4. * cm;

    //Crystal Parameters
    G4double cryst_dX = 3 * mm, cryst_dY = 3 * mm, cryst_dZ = 22 * mm;
    G4double foilThickness = 1 * mm;
    G4double outBox_dX = cryst_dX+foilThickness, outBox_dY = cryst_dY+foilThickness, outBox_dZ = cryst_dZ;


    // Get materials
    G4Material* defaultMaterial = G4Material::GetMaterial("G4_AIR");
    G4Material* cryst_mat = G4Material::GetMaterial("LYSO");
    G4Material* foil_mat = G4Material::GetMaterial("Al");



    //
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



    //
    //Crystals wrapped in foil
    //
    G4double gap = 0. * mm;        //a gap for wrapping
    //Foil wrapping
    G4Box* outerBox = new G4Box("Outerbox", outBox_dX/2, outBox_dY/2, outBox_dZ/2);
    G4Box* innerBox = new G4Box("Innerbox", cryst_dX/2, cryst_dY/2, cryst_dZ/2+5*mm);

    G4SubtractionSolid* foilS = new G4SubtractionSolid("Foilwrapping", outerBox, innerBox);
    G4double foil_xpos = cryst_dX+2*foilThickness+gap, foil_ypos = cryst_dY+2*foilThickness+gap;

    G4double cryst_xpos = cryst_dX + gap, cryst_ypos = cryst_dY + gap;
    G4Box* crystalS = new G4Box("crystal", cryst_dX/2, cryst_dY/2, cryst_dZ/2);

    G4LogicalVolume* crystalLV
            = new G4LogicalVolume(
                    crystalS,     // its solid
                    cryst_mat,  // its material
                    "lysoCrystal");   // its name

    G4LogicalVolume* foilLV
            = new G4LogicalVolume(
                    foilS,     // its solid
                    foil_mat,  // its material
                    "foilwrap");   // its name

    cAbsorberPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(),  // at (0,0,0)
            crystalLV,          // its logical volume
            "crystalPV",    // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            0,                // copy number
            fCheckOverlaps);  // checking overlaps
    cFoilPV
            = new G4PVPlacement(
            0,
            G4ThreeVector(),
            foilLV,
            "foilPV",
            worldLV,
            false,
            0,
            fCheckOverlaps);

    NAbsorberPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(0, cryst_ypos+foilThickness, 0), // at (0,0,0)
            crystalLV,          // its logical volume
            "crystalPV",    // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            1,                // copy number
            fCheckOverlaps);  // checking overlaps
    nFoilPV
            = new G4PVPlacement(
            0,
            G4ThreeVector(0, cryst_ypos+foilThickness, 0),
            foilLV,
            "foilPV",
            worldLV,
            false,
            1,
            fCheckOverlaps);

    NEAbsorberPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(cryst_xpos+foilThickness, cryst_ypos+foilThickness, 0), // at (0,0,0)
            crystalLV,          // its logical volume
            "crystalPV",    // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            2,                // copy number
            fCheckOverlaps);  // checking overlaps
    neFoilPV
            = new G4PVPlacement(
            0,
            G4ThreeVector(cryst_xpos+foilThickness, cryst_ypos+foilThickness, 0),
            foilLV,
            "foilPV",
            worldLV,
            false,
            2,
            fCheckOverlaps);


    EAbsorberPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(cryst_xpos+foilThickness, 0, 0),  // at (0,0,0)
            crystalLV,          // its logical volume
            "crystalPV",    // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            3,                // copy number
            fCheckOverlaps);  // checking overlaps
    eFoilPV
            = new G4PVPlacement(
            0,
            G4ThreeVector(cryst_xpos+foilThickness, 0, 0),
            foilLV,
            "foilPV",
            worldLV,
            false,
            3,
            fCheckOverlaps);

    SEAbsorberPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(cryst_xpos+foilThickness, -cryst_ypos-foilThickness, 0), // at (0,0,0)
            crystalLV,          // its logical volume
            "crystalPV",    // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            4,                // copy number
            fCheckOverlaps);  // checking overlaps
    seFoilPV
            = new G4PVPlacement(
            0,
            G4ThreeVector(cryst_xpos+foilThickness, -cryst_ypos-foilThickness, 0),
            foilLV,
            "foilPV",
            worldLV,
            false,
            4,
            fCheckOverlaps);

    SAbsorberPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(0, -cryst_ypos-foilThickness, 0),  // at (0,0,0)
            crystalLV,          // its logical volume
            "crystalPV",    // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            5,                // copy number
            fCheckOverlaps);  // checking overlaps
    sFoilPV
            = new G4PVPlacement(
            0,
            G4ThreeVector(0, -cryst_ypos-foilThickness, 0),
            foilLV,
            "foilPV",
            worldLV,
            false,
            5,
            fCheckOverlaps);

    SWAbsorberPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(-cryst_xpos-foilThickness, -cryst_ypos-foilThickness, 0), // at (0,0,0)
            crystalLV,          // its logical volume
            "crystalPV",    // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            6,                // copy number
            fCheckOverlaps);  // checking overlaps
    swFoilPV
            = new G4PVPlacement(
            0,
            G4ThreeVector(-cryst_xpos-foilThickness, -cryst_ypos-foilThickness, 0),
            foilLV,
            "foilPV",
            worldLV,
            false,
            6,
            fCheckOverlaps);

    WAbsorberPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(-cryst_xpos-foilThickness, 0, 0),  // at (0,0,0)
            crystalLV,          // its logical volume
            "crystalPV",    // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            7,                // copy number
            fCheckOverlaps);  // checking overlaps
    wFoilPV
            = new G4PVPlacement(
            0,
            G4ThreeVector(-cryst_xpos-foilThickness, 0, 0),
            foilLV,
            "foilPV",
            worldLV,
            false,
            7,
            fCheckOverlaps);

    NWAbsorberPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(-cryst_xpos-foilThickness, cryst_ypos+foilThickness, 0), // at (0,0,0)
            crystalLV,          // its logical volume
            "crystalPV",    // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            8,                // copy number
            fCheckOverlaps);  // checking overlaps
    nwFoilPV
            = new G4PVPlacement(
            0,
            G4ThreeVector(-cryst_xpos-foilThickness, cryst_ypos+foilThickness, 0),
            foilLV,
            "foilPV",
            worldLV,
            false,
            8,
            fCheckOverlaps);

    worldLV->SetVisAttributes(G4VisAttributes::Invisible);

    G4VisAttributes *simpleBoxVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    simpleBoxVisAtt->SetVisibility(true);
    crystalLV->SetVisAttributes(simpleBoxVisAtt);

    //
    // Always return the physical World
    //
    return worldPV;
}



void B4DetectorConstruction::ConstructSDandField() {

}

