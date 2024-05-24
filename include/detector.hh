#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4SystemOfUnits.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"

#include "globalsettings.hh"


class MySensitiveDetector : public G4VSensitiveDetector
{
public:
    MySensitiveDetector(G4String name);
    ~MySensitiveDetector() override = default;
    
    G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override;
    void ResetEventData();

    // Get methods
    inline G4double GetTimeIn() const { return fTimeIn; }
    inline G4double GetPosXIn() const { return fPosXIn; }
    inline G4double GetPosYIn() const { return fPosYIn; }
    inline G4double GetEdep() const { return fEdep; }
    inline G4double GetMaxEdep() const { return fMaxEdep; }
    inline G4ThreeVector GetMaxEdepPos() const { return fMaxEdepPos; }


private:
    inline void SetArrival(G4double newtimein, G4ThreeVector newposin)
    {
        if(newtimein < fTimeIn)
        {
            fTimeIn = newtimein;
            fPosXIn = newposin.x();
            fPosYIn = newposin.y();
        }
    }
    inline void AddEdep(G4double edep) { fEdep += edep; }
    inline void SetMaxEdep(G4double edepondx, G4ThreeVector maxedeppos)
    {
        if(edepondx > fMaxEdep)
        {
            fMaxEdep = edepondx;
            fMaxEdepPos = maxedeppos;
        }
    };

    // Primary's data
    G4double fTimeIn;
    G4double fPosXIn;
    G4double fPosYIn;
    
    // Crystal's data
    G4double      fEdep;
    G4double      fMaxEdep;
    G4ThreeVector fMaxEdepPos;
};

#endif  // DETECTOR_HH
