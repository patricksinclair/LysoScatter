

#include "B4aEventAction.hh"
#include "B4Analysis.hh"
#include "B4PrimaryGeneratorAction.hh"
#include "B4aSteppingAction.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"


B4aEventAction::B4aEventAction()
        : G4UserEventAction(),
          initialEdepCA(0.),
          initialEdepCB(0.),

          cEnergyAbs_A(0.),
          NEnergyAbs_A(0.),
          EEnergyAbs_A(0.),
          SEnergyAbs_A(0.),
          WEnergyAbs_A(0.),

          cEnergyAbs_B(0.),
          NEnergyAbs_B(0.),
          EEnergyAbs_B(0.),
          SEnergyAbs_B(0.),
          WEnergyAbs_B(0.),
          //scatAng(0.),
          //scatPhi(0.),
          deltaPhi(0.)

{}


B4aEventAction::~B4aEventAction() {}


void B4aEventAction::BeginOfEventAction(const G4Event * /*event*/) {
    // initialisation per event
    initialEdepCA = 0.;
    initialEdepCB = 0.;

    cEnergyAbs_A = 0.;
    NEnergyAbs_A = 0.;
    EEnergyAbs_A = 0.;
    SEnergyAbs_A = 0.;
    WEnergyAbs_A = 0.;

    cEnergyAbs_B = 0.;
    NEnergyAbs_B = 0.;
    EEnergyAbs_B = 0.;
    SEnergyAbs_B = 0.;
    WEnergyAbs_B = 0.;
    //scatAng = 0.;
    //scatPhi = 0.;
    deltaPhi = 0.;

    scattered = false;
    recorded = false;

    enteredCA = false;
    enteredCB = false;

    alreadyScatA = false;
    alreadyScatB = false;

    simultaneous = false;

    scatNorthA = false, scatEastA = false, scatSouthA = false, scatWestA = false;
    scatNorthB = false, scatEastB = false, scatSouthB = false, scatWestB = false;
}


void B4aEventAction::EndOfEventAction(const G4Event *event) {
    // Accumulate statistics
    // get analysis manager
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

   /* G4cout << "1. " << initialEdepCA << G4endl;
    G4cout << "2. " << cEnergyAbs_A+initialEdepCA << G4endl;*/

    G4double totECA = cEnergyAbs_A+initialEdepCA;
    G4double totECB = cEnergyAbs_B+initialEdepCB;

    if(enteredCA == true && enteredCB == true) simultaneous = true;

    // fill histograms
    if(totECA > 0 && simultaneous == true) analysisManager->FillH1(1, totECA);
    if(NEnergyAbs_A > 0 && simultaneous == true) analysisManager->FillH1(2, NEnergyAbs_A);
    if(EEnergyAbs_A > 0 && simultaneous == true) analysisManager->FillH1(3, EEnergyAbs_A);
    if(SEnergyAbs_A > 0 && simultaneous == true) analysisManager->FillH1(4, SEnergyAbs_A);
    if(WEnergyAbs_A > 0 && simultaneous == true) analysisManager->FillH1(5, WEnergyAbs_A);

    if(totECB > 0 && simultaneous == true) analysisManager->FillH1(6, totECB);
    if(NEnergyAbs_B > 0 && simultaneous == true) analysisManager->FillH1(7, NEnergyAbs_B);
    if(EEnergyAbs_B > 0 && simultaneous == true) analysisManager->FillH1(8, EEnergyAbs_B);
    if(SEnergyAbs_B > 0 && simultaneous == true) analysisManager->FillH1(9, SEnergyAbs_B);
    if(WEnergyAbs_B > 0 && simultaneous == true) analysisManager->FillH1(10, WEnergyAbs_B);


    /*if(scattered && recorded) analysisManager->FillH1(11, scatAng);
    if(scattered) analysisManager->FillH1(12, scatPhi);
    if(scattered) analysisManager->FillH1(13, deltaPhi);*/

    if(simultaneous) {
        if (scatNorthA == true) {
            //analysisManager->FillH1(13, 0.*degree);
            //G4cout << "NorthA" << G4endl;
            if (scatNorthB == true) analysisManager->FillH1(13, 0.*degree);
            else if (scatEastB == true) analysisManager->FillH1(13, 90.*degree);
            else if (scatSouthB == true) analysisManager->FillH1(13, 180.*degree);
            else if (scatWestB == true) analysisManager->FillH1(13, 270.*degree);

        } else if (scatEastA == true) {
            //analysisManager->FillH1(13, 90.*degree);
            //G4cout << "EastA" << G4endl;
            if (scatEastB == true) analysisManager->FillH1(13, 0.*degree);
            else if (scatSouthB == true) analysisManager->FillH1(13, 90.*degree);
            else if (scatWestB == true) analysisManager->FillH1(13, 180.*degree);
            else if (scatNorthB == true) analysisManager->FillH1(13, 270.*degree);

        } else if (scatSouthA == true) {
            //analysisManager->FillH1(13, 180.*degree);
            //G4cout << "SouthA" << G4endl;
            if (scatSouthB == true) analysisManager->FillH1(13, 0.*degree);
            else if (scatWestB == true) analysisManager->FillH1(13, 90.*degree);
            else if (scatNorthB == true) analysisManager->FillH1(13, 180.*degree);
            else if (scatEastB == true) analysisManager->FillH1(13, 270.*degree);

        } else if (scatWestA == true) {
            //analysisManager->FillH1(13, 270.*degree);
            //G4cout << "WestA" << G4endl;
            if (scatWestB == true) analysisManager->FillH1(13, 0.*degree);
            else if (scatNorthB == true) analysisManager->FillH1(13, 90.*degree);
            else if (scatEastB == true) analysisManager->FillH1(13, 180.*degree);
            else if (scatSouthB == true) analysisManager->FillH1(13, 270*degree);
        }
    }

    // fill ntuple
    if(totECA > 0 && simultaneous == true) analysisManager->FillNtupleDColumn(0, totECA);
    if(NEnergyAbs_A > 0) analysisManager->FillNtupleDColumn(1, NEnergyAbs_A);
    if(EEnergyAbs_A > 0) analysisManager->FillNtupleDColumn(2, EEnergyAbs_A);
    if(SEnergyAbs_A > 0) analysisManager->FillNtupleDColumn(3, SEnergyAbs_A);
    if(WEnergyAbs_A > 0) analysisManager->FillNtupleDColumn(4, WEnergyAbs_A);

    if(totECB > 0 && simultaneous == true) analysisManager->FillNtupleDColumn(5, totECB);
    if(NEnergyAbs_B > 0) analysisManager->FillNtupleDColumn(6, NEnergyAbs_B);
    if(EEnergyAbs_B > 0) analysisManager->FillNtupleDColumn(7, EEnergyAbs_B);
    if(SEnergyAbs_B > 0) analysisManager->FillNtupleDColumn(8, SEnergyAbs_B);
    if(WEnergyAbs_B > 0) analysisManager->FillNtupleDColumn(9, WEnergyAbs_B);

    analysisManager->FillNtupleDColumn(10, scatAng);
    analysisManager->FillNtupleDColumn(11, scatPhi);

    if(simultaneous) {
        if (scatNorthA == true) {
            //G4cout << "NorthA" << G4endl;
            if (scatNorthB == true) analysisManager->FillNtupleDColumn(12, 0.);
            else if (scatEastB == true) analysisManager->FillNtupleDColumn(12, 90.);
            else if (scatSouthB == true) analysisManager->FillNtupleDColumn(12, 180.);
            else if (scatWestB == true) analysisManager->FillNtupleDColumn(12, 270.);

        } else if (scatEastA == true) {
            //G4cout << "EastA" << G4endl;
            if (scatEastB == true) analysisManager->FillNtupleDColumn(12, 0.);
            else if (scatSouthB == true) analysisManager->FillNtupleDColumn(12, 90.);
            else if (scatWestB == true) analysisManager->FillNtupleDColumn(12, 180.);
            else if (scatNorthB == true) analysisManager->FillNtupleDColumn(12, 270.);

        } else if (scatSouthA == true) {
            //G4cout << "SouthA" << G4endl;
            if (scatSouthB == true) analysisManager->FillNtupleDColumn(12, 0.);
            else if (scatWestB == true) analysisManager->FillNtupleDColumn(12, 90.);
            else if (scatNorthB == true) analysisManager->FillNtupleDColumn(12, 180.);
            else if (scatEastB == true) analysisManager->FillNtupleDColumn(12, 270.);

        } else if (scatWestA == true) {
            //G4cout << "WestA" << G4endl;
            if (scatWestB == true) analysisManager->FillNtupleDColumn(12, 0.);
            else if (scatNorthB == true) analysisManager->FillNtupleDColumn(12, 90.);
            else if (scatEastB == true) analysisManager->FillNtupleDColumn(12, 180.);
            else if (scatSouthB == true) analysisManager->FillNtupleDColumn(12, 270.);
        }
    }
    analysisManager->AddNtupleRow();

}




