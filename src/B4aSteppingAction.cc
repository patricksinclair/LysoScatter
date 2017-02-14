
#include <G4SIunits.hh>
#include "B4aSteppingAction.hh"
#include "B4aEventAction.hh"
#include "B4DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"



B4aSteppingAction::B4aSteppingAction(
        const B4DetectorConstruction* detectorConstruction, B4aEventAction* eventAction)
        : G4UserSteppingAction(),
          fDetConstruction(detectorConstruction),
          fEventAction(eventAction)
{
}


B4aSteppingAction::~B4aSteppingAction()
{
}



void B4aSteppingAction::UserSteppingAction(const G4Step* step)
{
// Collect energy and track length step by step

    // get volume of the current step
    G4VPhysicalVolume* volume
            = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

    G4double gammaE = step->GetPreStepPoint()->GetTotalEnergy();


    // energy deposit
    G4double edep = step->GetTotalEnergyDeposit();
    G4double phi = step->GetPostStepPoint()->GetPolarization().getPhi();
    G4double delPhi = step->GetPostStepPoint()->GetPolarization().deltaPhi(step->GetPreStepPoint()->GetPolarization());


    fEventAction->AddDeltaPhi(delPhi);

    isScattered = false;
    alreadyRecorded = false;






    if ( volume == fDetConstruction->GetCAbsorberPV_A()){
        fEventAction->setEnteredCABool(true);
        if(fEventAction->getInitEdepCA() > 0.0000001) fEventAction->setInitEdepCA(edep);

    }else if(volume == fDetConstruction->GetCAbsorberPV_B()){
        fEventAction->setEnteredCBBool(true);
        if(fEventAction->getInitEdepCB() > 0.0000001) fEventAction->setInitEdepCB(edep);
    }

    if(fEventAction->getEnteredCABool() == true && fEventAction->getEnteredCBBool() == true){
        //G4cout << "simultaneous! \n";
        //fEventAction->AddAbsC_A(fEventAction->getInitEdepCA());
        //fEventAction->AddAbsC_B(fEventAction->getInitEdepCB());
        //G4cout << fEventAction->getInitEdepCA() << G4endl;

        if ( volume == fDetConstruction->GetCAbsorberPV_A()) {
            fEventAction->AddAbsC_A(edep);

        }else if(volume == fDetConstruction->GetNAbsorberPV_A()){
            fEventAction->AddAbsN_A(edep);

            if(fEventAction->getAlreadyScatA() == false){
                fEventAction->setNAScatBool(true);
                fEventAction->setAlreadyScatA(true);
            }


        }else if(volume == fDetConstruction->GetEAbsorberPV_A()){
            fEventAction->AddAbsE_A(edep);

            if(fEventAction->getAlreadyScatA() == false){
                fEventAction->setEAScatBool(true);
                fEventAction->setAlreadyScatA(true);
            }

        }else if(volume == fDetConstruction->GetSAbsorberPV_A()){
            fEventAction->AddAbsS_A(edep);

            if(fEventAction->getAlreadyScatA() == false){
                fEventAction->setSAScatBool(true);
                fEventAction->setAlreadyScatA(true);
            }

        }else if(volume == fDetConstruction->GetWAbsorberPV_A()){
            fEventAction->AddAbsW_A(edep);

            if(fEventAction->getAlreadyScatA() == false){
                fEventAction->setWAScatBool(true);
                fEventAction->setAlreadyScatA(true);
            }

        }



        if (volume == fDetConstruction->GetCAbsorberPV_B()){
            fEventAction->AddAbsC_B(edep);

        }else if(volume == fDetConstruction->GetNAbsorberPV_B()){
            fEventAction->AddAbsN_B(edep);

            if(fEventAction->getAlreadyScatB() == false){
                fEventAction->setNBScatBool(true);
                fEventAction->setAlreadyScatB(true);
            }

        }else if(volume == fDetConstruction->GetEAbsorberPV_B()){
            fEventAction->AddAbsE_B(edep);

            if(fEventAction->getAlreadyScatB() == false){
                fEventAction->setEBScatBool(true);
                fEventAction->setAlreadyScatB(true);
            }

        }else if(volume == fDetConstruction->GetSAbsorberPV_B()){
            fEventAction->AddAbsS_B(edep);

            if(fEventAction->getAlreadyScatB() == false){
                fEventAction->setSBScatBool(true);
                fEventAction->setAlreadyScatB(true);
            }

        }else if(volume == fDetConstruction->GetWAbsorberPV_B()){
            fEventAction->AddAbsW_B(edep);

            if(fEventAction->getAlreadyScatB() == false){
                fEventAction->setWBScatBool(true);
                fEventAction->setAlreadyScatB(true);
            }

        }

    }


    /*else if ( volume == fDetConstruction->GetNAbsorberPV_A() ) {

        if(edep > 0.) fEventAction->AddAbsN(edep);
        if(!alreadyRecorded) {

            fEventAction->AddScatAngle(0.*degree);
            fEventAction->AddScatPhi(phi);

            fEventAction->ScatBool(true);
            alreadyRecorded = true;
            fEventAction->RecordedBool(true);
        }

    } else if ( volume == fDetConstruction->GetEAbsorberPV_A() ) {

        fEventAction->AddAbsE(edep);
        if(!alreadyRecorded) {

            fEventAction->AddScatAngle(90.*degree);
            fEventAction->AddScatPhi(phi);

            fEventAction->ScatBool(true);
            alreadyRecorded = true;
            fEventAction->RecordedBool(true);
        }

    } else if ( volume == fDetConstruction->GetSAbsorberPV_A() ) {

        fEventAction->AddAbsS(edep);
        if(!alreadyRecorded) {

            fEventAction->AddScatAngle(180.*degree);
            fEventAction->AddScatPhi(phi);

            fEventAction->ScatBool(true);
            alreadyRecorded = true;
            fEventAction->RecordedBool(true);
        }

    } else if ( volume == fDetConstruction->GetWAbsorberPV_A() ) {

        fEventAction->AddAbsW(edep);
        if (!alreadyRecorded) {

            fEventAction->AddScatAngle(270. * degree);
            fEventAction->AddScatPhi(phi);

            fEventAction->ScatBool(true);
            alreadyRecorded = true;
            fEventAction->RecordedBool(true);
        }
    }*/

    /* } else if ( volume == fDetConstruction->GetNEAbsorberPV() ) {

         if(!alreadyRecorded){
             fEventAction->AddScatAngle(45.*degree);
             fEventAction->ScatBool(true);
             alreadyRecorded = true;
             fEventAction->RecordedBool(true);
         }

     }
     else if ( volume == fDetConstruction->GetSEAbsorberPV() ) {

         fEventAction->AddAbsW(edep);
         if(!alreadyRecorded){
             fEventAction->AddScatAngle(135.*degree);
             fEventAction->ScatBool(true);
             alreadyRecorded = true;
             fEventAction->RecordedBool(true);
         }

     } else if ( volume == fDetConstruction->GetSWAbsorberPV() ) {

         fEventAction->AddAbsW(edep);
         if(!alreadyRecorded){
             fEventAction->AddScatAngle(225.*degree);
             fEventAction->ScatBool(true);
             alreadyRecorded = true;
             fEventAction->RecordedBool(true);
         }

     } else if ( volume == fDetConstruction->GetNWAbsorberPV() ) {

         fEventAction->AddAbsW(edep);
         if(!alreadyRecorded){
             fEventAction->AddScatAngle(315.*degree);
             fEventAction->ScatBool(true);
             alreadyRecorded = true;
             fEventAction->RecordedBool(true);
         }

     }*/

}







