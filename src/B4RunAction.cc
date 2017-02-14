

#include "B4RunAction.hh"
#include "B4Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"



B4RunAction::B4RunAction()
        : G4UserRunAction()
{
    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(1);

    // Create analysis manager
    // The choice of analysis technology is done via selection of a namespace
    // in B4Analysis.hh
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    G4cout << "Using " << analysisManager->GetType() << G4endl;

    analysisManager->SetVerboseLevel(1);
    analysisManager->SetFirstHistoId(1);

    // Book histograms, ntuple

    // Creating histograms
    analysisManager->CreateH1("1", "Edep in central absorber (A)", 800, 0., 0.6*MeV);
    analysisManager->CreateH1("2", "Edep in North absorber (A)", 800, 0., 0.6*MeV);
    analysisManager->CreateH1("3", "Edep in East absorber (A)", 800, 0., 0.6*MeV);
    analysisManager->CreateH1("4", "Edep in South absorber (A)", 800, 0., 0.6*MeV);
    analysisManager->CreateH1("5", "Edep in West absorber (A)", 800, 0., 0.6*MeV);

    analysisManager->CreateH1("6", "Edep in central absorber (B)", 800, 0., 0.6*MeV);
    analysisManager->CreateH1("7", "Edep in North absorber (B)", 800, 0., 0.6*MeV);
    analysisManager->CreateH1("8", "Edep in East absorber (B)", 800, 0., 0.6*MeV);
    analysisManager->CreateH1("9", "Edep in South absorber (B)", 800, 0., 0.6*MeV);
    analysisManager->CreateH1("10", "Edep in West absorber (B)", 800, 0., 0.6*MeV);

    analysisManager->CreateH1("11", "Scattering angle", 4, 0., 360*degree);
    analysisManager->CreateH1("12", "Scattering angle (phi)", 360, 0., 360*degree);
    analysisManager->CreateH1("13", "Delta phi", 4, 0., 360*degree);

    // Creating ntuple
    analysisManager->CreateNtuple("LysoScatter", "Edep");
    analysisManager->CreateNtupleDColumn("EabsC_A");
    analysisManager->CreateNtupleDColumn("EabsN_A");
    analysisManager->CreateNtupleDColumn("EabsE_A");
    analysisManager->CreateNtupleDColumn("EabsS_A");
    analysisManager->CreateNtupleDColumn("EabsW_A");

    analysisManager->CreateNtupleDColumn("EabsC_B");
    analysisManager->CreateNtupleDColumn("EabsN_B");
    analysisManager->CreateNtupleDColumn("EabsE_B");
    analysisManager->CreateNtupleDColumn("EabsS_B");
    analysisManager->CreateNtupleDColumn("EabsW_B");

    analysisManager->CreateNtupleDColumn("ScatAngle");
    analysisManager->CreateNtupleDColumn("ScatPhi");
    analysisManager->CreateNtupleDColumn("DeltaPhi");
    analysisManager->FinishNtuple();
}




B4RunAction::~B4RunAction()
{
    delete G4AnalysisManager::Instance();
}


void B4RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
    //inform the runManager to save random number seed
    //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

    // Get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // Open an output file
    G4String fileName = "LysoScatter_main_randomPol";
    analysisManager->OpenFile(fileName);
}



void B4RunAction::EndOfRunAction(const G4Run* /*run*/)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // save histograms & ntuple
    analysisManager->Write();
    analysisManager->CloseFile();
}


