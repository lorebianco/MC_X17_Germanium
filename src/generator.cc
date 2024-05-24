#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    DefineCommands();

    // Default values     
    fBeamType = 0;

    fMeanEnergy = 1.*MeV;
    fSigmaEnergy = 10.*keV;

    // Spread and Circle beam
    fRadiusSpread = 10*mm;
    fRadiusCircle = 10*mm;

    // Construct the Particle Gun
    fParticleGun = new G4ParticleGun(1);
    
    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
    
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0.));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleDefinition(particle);
}



MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fMessenger_Gun;
    delete fParticleGun;
}



void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    // Sample the kinetic energy from Gaus
    G4double energy = G4RandGauss::shoot(fMeanEnergy, fSigmaEnergy);
    fParticleGun->SetParticleEnergy(energy);
            
    switch(fBeamType)
    {
        case 0:  // Pointlike beam
        default:
            if(fBeamType != 0) G4cerr << "Not valid beam type! Pointlike beam is selected!" << G4endl;
            break;

        case 1:  // Spread beam
            PrimariesForSpreadBeam();
            break;
            
        case 2:  // Circle beam
            PrimariesForCircleBeam();
            break;
    }

    // Finally generate the primary vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);
}



void MyPrimaryGenerator::PrimariesForSpreadBeam()
{
    // Set position at the center
    G4ThreeVector pos(0., 0., 0.);

    // Sample the momentum direction uniformly within the given range
    G4double fThetaMax = std::atan(fRadiusSpread/GS::zFrontFaceCrystal);
    G4double fCosThetaMax = std::cos(fThetaMax);

    G4double cosTheta = 1-G4UniformRand()*(1-fCosThetaMax);
    G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
    G4double phi = CLHEP::twopi*G4UniformRand();

    G4double ux = sinTheta*std::cos(phi);
    G4double uy = sinTheta*std::sin(phi);
    G4double uz = cosTheta;

    G4ThreeVector mom(ux, uy, uz);

    // Set fParticleGun
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
}



void MyPrimaryGenerator::PrimariesForCircleBeam()
{
    G4double posR = fRadiusCircle*std::sqrt(G4UniformRand());
    G4double posPhi = CLHEP::twopi*G4UniformRand();

    G4ThreeVector pos(posR*std::cos(posPhi), posR*std::sin(posPhi), 0);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
}



void MyPrimaryGenerator::DefineCommands()
{
    // Define my UD-messenger for primary gamma
    fMessenger_Gun = new G4GenericMessenger(this, "/MC_Germanium/myGun/", "Cinematical settings for initial gamma");
    fMessenger_Gun->DeclareProperty("BeamType", fBeamType, "Available types are: 0 = Pointlike, 1 = Spread, 2 = Circle");
    fMessenger_Gun->DeclarePropertyWithUnit("meanEnergy", "MeV", fMeanEnergy, "Mean of the gaussian distribution of initial gamma energy");
    fMessenger_Gun->DeclarePropertyWithUnit("sigmaEnergy", "MeV", fSigmaEnergy, "Sigma of the gaussian distribution of initial gamma energy");
    fMessenger_Gun->DeclarePropertyWithUnit("radiusSpread", "mm", fRadiusSpread, "Set radius of the spread on the front face of scintillator");
    fMessenger_Gun->DeclarePropertyWithUnit("radiusCircle", "mm", fRadiusCircle, "Set radius of the beam (in 'Circle' case)");
}
