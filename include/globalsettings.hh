#ifndef GLOBALSETTINGS_HH
#define GLOBALSETTINGS_HH

#include "G4SystemOfUnits.hh"

namespace GS
{
    // Ge Crystal
    constexpr G4double radiusCrystal = 36.25*mm;
    constexpr G4double halfheightCrystal = 36.1*mm;

    constexpr G4double xCrystal = 0*cm;
    constexpr G4double yCrystal = 0*cm;
    constexpr G4double zCrystal = 20*cm;

    constexpr G4double zFrontFaceCrystal = zCrystal - halfheightCrystal;
    constexpr G4double zBackFaceCrystal = zCrystal + halfheightCrystal;


    // World Dimensions 
    constexpr G4double halfSideWorld = 0.5*m;
}

#endif  // GLOBALSETTINGS_HH
