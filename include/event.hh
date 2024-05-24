#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"

#include "globalsettings.hh"
#include "detector.hh"

class MyEventAction : public G4UserEventAction
{
public:
    MyEventAction() = default;
    ~MyEventAction() override = default;

    void BeginOfEventAction(const G4Event *event) override;
    void EndOfEventAction(const G4Event *event) override;
};

#endif  // EVENT_HH
