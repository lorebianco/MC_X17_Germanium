#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
    DefineMaterials();
}



void MyDetectorConstruction::DefineMaterials()
{
    G4NistManager *nist = G4NistManager::Instance();

    // Germanium
    fGermanium = nist->FindOrBuildMaterial("G4_Ge");

    // Air
    fAir = nist->FindOrBuildMaterial("G4_AIR");
}



G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    // Construct the World
    G4Box *solidWorld = new G4Box("solidWorld", GS::halfSideWorld, GS::halfSideWorld, GS::halfSideWorld);
    logicWorld = new G4LogicalVolume(solidWorld, fAir, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);


    // Construct the crystal
    G4Tubs *solidCrystal = new G4Tubs("solidCrystal", 0.*cm, GS::radiusCrystal, GS::halfheightCrystal, 0.*deg, 360.*deg);
    logicCrystal = new G4LogicalVolume(solidCrystal, fGermanium, "logicCrystal");
    G4VPhysicalVolume *physCrystal = new G4PVPlacement(0, G4ThreeVector(GS::xCrystal, GS::yCrystal, GS::zCrystal), logicCrystal, "physCrystal", logicWorld, false, 0, true);

    
    // Add visualization attributes
    DefineVisAttributes();

    // Always return physWorld
    return physWorld;
}



void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = static_cast<MySensitiveDetector*>(G4SDManager::GetSDMpointer()->FindSensitiveDetector("SensitiveDetector"));

    if(!sensDet)
    {
        sensDet = new MySensitiveDetector("SensitiveDetector");
        G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
    }

    SetSensitiveDetector(logicCrystal, sensDet);
}



void MyDetectorConstruction::DefineVisAttributes()
{
    // World
    G4VisAttributes *visWorld = new G4VisAttributes();
    visWorld->SetVisibility(false);
    logicWorld->SetVisAttributes(visWorld);

    // Crystal
    G4VisAttributes *visCrystal = new G4VisAttributes();
    visCrystal->SetColour(0.8, 0.8, 0, 0.4);
    logicCrystal->SetVisAttributes(visCrystal);
}