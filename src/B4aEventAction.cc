

#include "B4aEventAction.hh"
#include "B4Analysis.hh"
#include "B4PrimaryGeneratorAction.hh"
#include "B4aSteppingAction.hh"
#include "G4RunManager.hh"



B4aEventAction::B4aEventAction()
        : G4UserEventAction(),
          cEnergyAbs(0.),
          NEnergyAbs(0.),
          EEnergyAbs(0.),
          SEnergyAbs(0.),
          WEnergyAbs(0.),
          //scatAng(0.),
          //scatPhi(0.),
          deltaPhi(0.)

{}


B4aEventAction::~B4aEventAction() {}


void B4aEventAction::BeginOfEventAction(const G4Event * /*event*/) {
    // initialisation per event
    cEnergyAbs = 0.;
    NEnergyAbs = 0.;
    EEnergyAbs = 0.;
    SEnergyAbs = 0.;
    WEnergyAbs = 0.;
    //scatAng = 0.;
    //scatPhi = 0.;
    deltaPhi = 0.;

    scattered = false;
    recorded = false;
}


void B4aEventAction::EndOfEventAction(const G4Event *event) {
    // Accumulate statistics
    // get analysis manager
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    // fill histograms
    if(cEnergyAbs > 0) analysisManager->FillH1(1, cEnergyAbs);
    if(NEnergyAbs > 0) analysisManager->FillH1(2, NEnergyAbs);
    if(EEnergyAbs > 0) analysisManager->FillH1(3, EEnergyAbs);
    if(SEnergyAbs > 0) analysisManager->FillH1(4, SEnergyAbs);
    if(WEnergyAbs > 0) analysisManager->FillH1(5, WEnergyAbs);
    if(scattered && recorded) analysisManager->FillH1(6, scatAng);
    if(scattered) analysisManager->FillH1(7, scatPhi);
    if(scattered) analysisManager->FillH1(8, deltaPhi);

    // fill ntuple
    if(cEnergyAbs > 0) analysisManager->FillNtupleDColumn(0, cEnergyAbs);
    if(NEnergyAbs > 0) analysisManager->FillNtupleDColumn(1, NEnergyAbs);
    if(EEnergyAbs > 0) analysisManager->FillNtupleDColumn(2, EEnergyAbs);
    if(SEnergyAbs > 0) analysisManager->FillNtupleDColumn(3, SEnergyAbs);
    if(WEnergyAbs > 0) analysisManager->FillNtupleDColumn(4, WEnergyAbs);
    analysisManager->FillNtupleDColumn(5, scatAng);
    analysisManager->AddNtupleRow();

}




