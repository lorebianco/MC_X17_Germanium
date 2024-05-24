//****************************************************************************//
//                        Lorenzo Bianco 21/05/2024                           //
//                                                                            //
//        My Montecarlo Simulation for the Germanium detector for X17         //
//                                                                            //
//****************************************************************************//

#include <iostream>
#include <chrono>

#include "G4RunManagerFactory.hh"
#include "G4VisManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"
//#include "summary.hh"

int main(int argc, char** argv)
{
    // Set randomly the seed of the simulation and store it
    G4Random::setTheSeed(time(NULL) + getpid());
    G4int fSeed = G4Random::getTheSeed();

    // Construct the run manager
    auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);
    
    // Set mandatory initialization classes
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization(fSeed));
    
    // Detect interactive mode (if no arguments) and define UI session
    G4UIExecutive *ui = 0;
    if(argc == 1)
    {
        ui = new G4UIExecutive(argc, argv);
    }

    // Initialize visualization
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    // Start UI session or process macro
    if(ui)
    {
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }
    else
    {
        // Batch mode
        auto start = std::chrono::high_resolution_clock::now();
        
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        
        // Save a summary of the simulation
        //MC_summary(fileName, fSeed, duration.count(), "MC_summaries.txt");
        //G4cout << G4endl;
        //G4cout << "If you have any custom settings to annotate in the summary, please edit the MC_summaries file at the corresponding MC-SerialNumber." << G4endl;
    }
    
    G4cout << "The rootfile of this Monte Carlo has serial number (MCID): " << fSeed << G4endl;

    // Job termination
    delete visManager;
    delete runManager;
    return 0;
}