#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "G4GenericMessenger.hh"

#include "globalsettings.hh"


class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
    MyPrimaryGenerator();
    ~MyPrimaryGenerator() override;

    void GeneratePrimaries(G4Event *anEvent) override;

private:
    void PrimariesForSpreadBeam();
    void PrimariesForCircleBeam();    
    void DefineCommands();

    // Particle gun
    G4ParticleGun *fParticleGun;

    // Generic Messengers
    G4GenericMessenger *fMessenger_Mode;
    G4GenericMessenger *fMessenger_Gun;

    // Define variables that want to set as UI
    G4int fBeamType;
    G4double fMeanEnergy,
             fSigmaEnergy,
             fRadiusSpread,
             fRadiusCircle;
};

#endif  // GENERATOR_HH
