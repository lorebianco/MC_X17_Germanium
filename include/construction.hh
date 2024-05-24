#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

#include "globalsettings.hh"
#include "detector.hh"


class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction() override = default;

    G4VPhysicalVolume *Construct() override;

private:
    void ConstructSDandField() override;
    void DefineMaterials();
    void DefineVisAttributes();

    // Logical volumes
    G4LogicalVolume *logicWorld,
                    *logicCrystal;
                    
    // Materials
    G4Material *fGermanium,
               *fAir;
    };

#endif  // CONSTRUCTION_HH
