

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



    void setInitEdepCA(G4double IECA);
    void setInitEdepCB(G4double IECB);
    G4double getInitEdepCA();
    G4double getInitEdepCB();

    void AddAbsC_A(G4double de);
    void AddAbsN_A(G4double de);
    void AddAbsE_A(G4double de);
    void AddAbsS_A(G4double de);
    void AddAbsW_A(G4double de);

    void AddAbsC_B(G4double de);
    void AddAbsN_B(G4double de);
    void AddAbsE_B(G4double de);
    void AddAbsS_B(G4double de);
    void AddAbsW_B(G4double de);

    void AddScatAngle(G4double ang);
    void AddScatPhi(G4double phi);
    void AddDeltaPhi(G4double delPhi);

    void ScatBool(G4bool scatYN);
    void RecordedBool(G4bool recordYN);

    bool getAlreadyScatA(), getAlreadyScatB();
    void setAlreadyScatA(G4bool hasScatteredA), setAlreadyScatB(G4bool hasScatteredB);

    bool getEnteredCABool(), getEnteredCBBool();
    void setEnteredCABool(G4bool hasEnteredCA), setEnteredCBBool(G4bool hasEnteredCB);

    bool getNAScatBool(), getEAScatBool(), getSAScatBool(), getWAScatBool();
    bool getNBScatBool(), getEBScatBool(), getSBScatBool(), getWBScatBool();

    void setNAScatBool(G4bool isScatNA), setEAScatBool(G4bool isScatEA),
            setSAScatBool(G4bool isScatSA), setWAScatBool(G4bool isScatWA);

    void setNBScatBool(G4bool isScatNB), setEBScatBool(G4bool isScatEB),
            setSBScatBool(G4bool isScatSB), setWBScatBool(G4bool isScatWB);



private:

    G4double initialEdepCA, initialEdepCB;

    G4double cEnergyAbs_A;
    G4double NEnergyAbs_A;
    G4double EEnergyAbs_A;
    G4double SEnergyAbs_A;
    G4double WEnergyAbs_A;

    G4double cEnergyAbs_B;
    G4double NEnergyAbs_B;
    G4double EEnergyAbs_B;
    G4double SEnergyAbs_B;
    G4double WEnergyAbs_B;

    G4double scatAng;
    G4double scatPhi;
    G4double deltaPhi;

    //these booleans are used to determine if there's a simultaneous scatter
    G4bool enteredCA;
    G4bool enteredCB;

    G4bool simultaneous;

    G4bool scattered;
    G4bool recorded;

    G4bool alreadyScatA;
    G4bool alreadyScatB;

    G4bool scatNorthA, scatEastA, scatSouthA, scatWestA;
    G4bool scatNorthB, scatEastB, scatSouthB, scatWestB;
};

// inline functions
//collect energy deposited in each crystal
inline G4double B4aEventAction::getInitEdepCA() {
    return initialEdepCA;
}
inline void B4aEventAction::setInitEdepCA(G4double IECA) {
    initialEdepCA = IECA;
}
inline G4double B4aEventAction::getInitEdepCB() {
    return initialEdepCB;
}
inline void B4aEventAction::setInitEdepCB(G4double IECB) {
    initialEdepCA = IECB;
}


inline void B4aEventAction::AddAbsC_A(G4double de){
    cEnergyAbs_A += de;
}
inline void B4aEventAction::AddAbsN_A(G4double de){
    NEnergyAbs_A += de;
}
inline void B4aEventAction::AddAbsE_A(G4double de){
    EEnergyAbs_A += de;
}
inline void B4aEventAction::AddAbsS_A(G4double de){
    SEnergyAbs_A += de;
}
inline void B4aEventAction::AddAbsW_A(G4double de){
    WEnergyAbs_A += de;
}

inline void B4aEventAction::AddAbsC_B(G4double de){
    cEnergyAbs_B += de;
}
inline void B4aEventAction::AddAbsN_B(G4double de){
    NEnergyAbs_B += de;
}
inline void B4aEventAction::AddAbsE_B(G4double de){
    EEnergyAbs_B += de;
}
inline void B4aEventAction::AddAbsS_B(G4double de){
    SEnergyAbs_B += de;
}
inline void B4aEventAction::AddAbsW_B(G4double de){
    WEnergyAbs_B += de;
}



//collect scattering angles of photons
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
////////////////////////////////////////////////////
//boolean methods for scattering

inline bool B4aEventAction::getAlreadyScatA(){
    return alreadyScatA;
}
inline void B4aEventAction::setAlreadyScatA(G4bool hasScatteredA){
    alreadyScatA = hasScatteredA;
}
inline bool B4aEventAction::getAlreadyScatB(){
    return alreadyScatB;
}
inline void B4aEventAction::setAlreadyScatB(G4bool hasScatteredB){
    alreadyScatB = hasScatteredB;
}

inline bool B4aEventAction::getEnteredCABool() {
    return enteredCA;
}
inline void B4aEventAction::setEnteredCABool(G4bool hasEnteredCA) {
    enteredCA = hasEnteredCA;
}
inline bool B4aEventAction::getEnteredCBBool() {
    return enteredCB;
}
inline void B4aEventAction::setEnteredCBBool(G4bool hasEnteredCB) {
    enteredCB = hasEnteredCB;
}
//array A
inline bool B4aEventAction::getNAScatBool(){
    return scatNorthA;
}
inline void B4aEventAction::setNAScatBool(G4bool isScatteredNA){
    scatNorthA = isScatteredNA;
}
inline bool B4aEventAction::getEAScatBool(){
    return scatEastA;
}
inline void B4aEventAction::setEAScatBool(G4bool isScatteredEA){
    scatEastA = isScatteredEA;
}
inline bool B4aEventAction::getSAScatBool(){
    return scatSouthA;
}
inline void B4aEventAction::setSAScatBool(G4bool isScatteredSA){
    scatSouthA = isScatteredSA;
}
inline bool B4aEventAction::getWAScatBool(){
    return scatWestA;
}
inline void B4aEventAction::setWAScatBool(G4bool isScatteredWA){
    scatWestA = isScatteredWA;
}
//array B
inline bool B4aEventAction::getNBScatBool(){
    return scatNorthB;
}
inline void B4aEventAction::setNBScatBool(G4bool isScatteredNB){
    scatNorthB = isScatteredNB;
}
inline bool B4aEventAction::getEBScatBool(){
    return scatEastB;
}
inline void B4aEventAction::setEBScatBool(G4bool isScatteredEB){
    scatEastB = isScatteredEB;
}
inline bool B4aEventAction::getSBScatBool(){
    return scatSouthB;
}
inline void B4aEventAction::setSBScatBool(G4bool isScatteredSB){
    scatSouthB = isScatteredSB;
}
inline bool B4aEventAction::getWBScatBool(){
    return scatWestB;
}
inline void B4aEventAction::setWBScatBool(G4bool isScatteredWB){
    scatWestB = isScatteredWB;
}
#endif

    
