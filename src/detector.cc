#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
    ResetEventData();
}



G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    // Store time and position of arrival of primary gamma (or daughters)
    if(aStep->GetPreStepPoint()->GetStepStatus() == fGeomBoundary)
    {
        G4double newtimein = aStep->GetPreStepPoint()->GetGlobalTime();
        G4ThreeVector newposin = aStep->GetPreStepPoint()->GetPosition();
        
        SetArrival(newtimein, newposin);
    }

    // Sum the energy deposited in the step
    G4double edep = aStep->GetTotalEnergyDeposit();
    AddEdep(edep);
    
    // Check if it is the maximum deposition of energy per unit length.
    // If yes it will be stored with its position.
    G4double dx = aStep->GetStepLength();
    if(dx == 0) return false;

    G4ThreeVector maxedeppos = (aStep->GetPreStepPoint()->GetPosition() + aStep->GetPostStepPoint()->GetPosition())/2;
    SetMaxEdep(edep/dx, maxedeppos);

    return true;
}



void MySensitiveDetector::ResetEventData()
{
    // Default values
    fTimeIn = 999999;
    fPosXIn = 0.;
    fPosYIn = 0.;
    fEdep = 0.;
    fMaxEdep = 0.;
    fMaxEdepPos = G4ThreeVector(0., 0., 0.);
}