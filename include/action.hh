#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "generator.hh"
#include "run.hh"
#include "event.hh"


class MyActionInitialization : public G4VUserActionInitialization
{
public:
    MyActionInitialization(G4int theMCID);
    ~MyActionInitialization() override = default;
    
    void Build() const override;
    void BuildForMaster() const override;

private:
    G4int fMCID;
};

#endif  // ACTION_HH
