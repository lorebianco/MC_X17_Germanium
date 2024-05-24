#include "run.hh"

MyRunAction::MyRunAction(G4int theMCID) : fMCID(theMCID)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    // Create the TTree
    man->CreateNtuple("ger", "Primary Gamma, energy deposition inside the crystal");
    // Data of primary gamma
    man->CreateNtupleIColumn("Event"); // entry 0
    man->CreateNtupleDColumn("E_gun");
    man->CreateNtupleDColumn("X_gun");
    man->CreateNtupleDColumn("Y_gun");
    man->CreateNtupleDColumn("Z_gun");
    man->CreateNtupleDColumn("MomX_gun"); // entry 5
    man->CreateNtupleDColumn("MomY_gun");
    man->CreateNtupleDColumn("MomZ_gun");
    man->CreateNtupleDColumn("ToA");
    man->CreateNtupleDColumn("XoA");
    man->CreateNtupleDColumn("YoA"); // entry 10
    // Data of energy deposition inside the crystal
    man->CreateNtupleDColumn("Edep");
    man->CreateNtupleDColumn("MaxEdep");
    man->CreateNtupleDColumn("MaxEdepPosX");
    man->CreateNtupleDColumn("MaxEdepPosY"); 
    man->CreateNtupleDColumn("MaxEdepPosZ"); // entry 15

    man->FinishNtuple(0);
}



void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    // Create and open the file root
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    std::stringstream strMCID;
    strMCID << fMCID;

    man->OpenFile("MCID_" + strMCID.str() + ".root");
}



void MyRunAction::EndOfRunAction(const G4Run* run)
{
    // Write TTree and close root file
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}