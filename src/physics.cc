#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
    // EM physics
    RegisterPhysics(new G4EmStandardPhysics());
}