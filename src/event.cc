#include "event.hh"

void MyEventAction::BeginOfEventAction(const G4Event *event)
{
    // Set at 0 ns the time of primary vertex (need this for 176Lu Decay Mode)
    event->GetPrimaryVertex()->SetT0(0);

    MySensitiveDetector *sensDet = static_cast<MySensitiveDetector*>(G4SDManager::GetSDMpointer()->FindSensitiveDetector("SensitiveDetector"));
    
    sensDet->ResetEventData(); 
}



void MyEventAction::EndOfEventAction(const G4Event *event)
{
    // Access sensitive detector
    MySensitiveDetector *sensDet = static_cast<MySensitiveDetector*>(G4SDManager::GetSDMpointer()->FindSensitiveDetector("SensitiveDetector"));

    // Access info about primary particle
    G4PrimaryVertex* primaryVertex = event->GetPrimaryVertex();
    G4PrimaryParticle *primaryParticle = primaryVertex->GetPrimary(); 

    // Store data
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    G4int evt = event->GetEventID();
    
    // Fill the primary gamma branches
    man->FillNtupleIColumn(0, evt);
    man->FillNtupleDColumn(1, primaryParticle->GetTotalEnergy());
    man->FillNtupleDColumn(2, primaryVertex->GetX0());
    man->FillNtupleDColumn(3, primaryVertex->GetY0());
    man->FillNtupleDColumn(4, primaryVertex->GetZ0());
    man->FillNtupleDColumn(5, primaryParticle->GetMomentumDirection().x());
    man->FillNtupleDColumn(6, primaryParticle->GetMomentumDirection().y());
    man->FillNtupleDColumn(7, primaryParticle->GetMomentumDirection().z());
    man->FillNtupleDColumn(8, sensDet->GetTimeIn());
    man->FillNtupleDColumn(9, sensDet->GetPosXIn());
    man->FillNtupleDColumn(10, sensDet->GetPosYIn());
    // Fill the energy deposition branches
    man->FillNtupleDColumn(11, sensDet->GetEdep());
    man->FillNtupleDColumn(12, sensDet->GetMaxEdep());
    man->FillNtupleDColumn(13, sensDet->GetMaxEdepPos().x());
    man->FillNtupleDColumn(14, sensDet->GetMaxEdepPos().y());
    man->FillNtupleDColumn(15, sensDet->GetMaxEdepPos().z());
     // Close the row
    man->AddNtupleRow(0);
}