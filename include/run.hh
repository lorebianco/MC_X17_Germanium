#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"

#include "event.hh"


class MyRunAction : public G4UserRunAction
{
public:
    MyRunAction(G4int theMCID);
    ~MyRunAction() override = default;
    
    void BeginOfRunAction(const G4Run* run) override;
    void EndOfRunAction(const G4Run* run) override;

private:
    G4int fMCID;
};

#endif  // RUN_HH
