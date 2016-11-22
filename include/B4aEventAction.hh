

#ifndef B4aEventAction_h
#define B4aEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///
/// It defines data members to hold the energy deposit and track lengths
/// of charged particles in Absober and Gap layers:
/// - fEnergyAbs, fEnergyGap, fTrackLAbs, fTrackLGap
/// which are collected step by step via the functions
/// - AddAbs(), AddGap()

class B4aEventAction : public G4UserEventAction {
public:
    B4aEventAction();

    virtual ~B4aEventAction();

    virtual void BeginOfEventAction(const G4Event *event);

    virtual void EndOfEventAction(const G4Event *event);

    void AddAbsC(G4double de);
    void AddAbsN(G4double de);
    void AddAbsE(G4double de);
    void AddAbsS(G4double de);
    void AddAbsW(G4double de);

    void AddScatAngle(G4double ang);
    void AddScatPhi(G4double phi);
    void AddDeltaPhi(G4double delPhi);

    void ScatBool(G4bool scatYN);
    void RecordedBool(G4bool recordYN);


private:
    G4double cEnergyAbs;
    G4double NEnergyAbs;
    G4double EEnergyAbs;
    G4double SEnergyAbs;
    G4double WEnergyAbs;
    G4double scatAng;
    G4double scatPhi;
    G4double deltaPhi;
    G4bool scattered;
    G4bool recorded;
};

// inline functions
inline void B4aEventAction::AddAbsC(G4double de){
    cEnergyAbs += de;
}
inline void B4aEventAction::AddAbsN(G4double de){
    NEnergyAbs += de;
}
inline void B4aEventAction::AddAbsE(G4double de){
    EEnergyAbs += de;
}
inline void B4aEventAction::AddAbsS(G4double de){
    SEnergyAbs += de;
}
inline void B4aEventAction::AddAbsW(G4double de){
    WEnergyAbs += de;
}

inline void B4aEventAction::AddScatAngle(G4double ang){
    scatAng = ang;
}

inline void B4aEventAction::AddScatPhi(G4double phi){
    scatPhi = phi;
}

inline void B4aEventAction::AddDeltaPhi(G4double dPhi) {
    deltaPhi += dPhi;
}

inline void B4aEventAction::ScatBool(G4bool isScattered){
    scattered = isScattered;
}
inline void B4aEventAction::RecordedBool(G4bool isRecorded) {
    recorded = isRecorded;
}
#endif

    
