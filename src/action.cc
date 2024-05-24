#include "action.hh"

MyActionInitialization::MyActionInitialization(G4int theMCID)
{
    fMCID = theMCID;
}



void MyActionInitialization::BuildForMaster() const
{
    // Here must be initialized only Run Action
    MyRunAction *runAction = new MyRunAction(fMCID);
    SetUserAction(runAction);
}



void MyActionInitialization::Build() const
{
    // Initialize all the user actions. Only PrimaryGenerator is mandatory in G4
    MyPrimaryGenerator *generator = new MyPrimaryGenerator();
    SetUserAction(generator);

    MyEventAction *eventAction = new MyEventAction();
    SetUserAction(eventAction);

    MyRunAction *runAction = new MyRunAction(fMCID);
    SetUserAction(runAction);
}
