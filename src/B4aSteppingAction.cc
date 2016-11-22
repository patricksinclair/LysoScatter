
#include <G4SIunits.hh>
#include "B4aSteppingAction.hh"
#include "B4aEventAction.hh"
#include "B4DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"



B4aSteppingAction::B4aSteppingAction(
        const B4DetectorConstruction* detectorConstruction,
        B4aEventAction* eventAction)
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
    //i deleted the touchable handle bit. add back in if issues arise
    G4VPhysicalVolume* volume
            = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();



    // energy deposit
    G4double edep = step->GetTotalEnergyDeposit();
    G4double phi = step->GetPostStepPoint()->GetPolarization().getPhi();
    G4double delPhi = step->GetPostStepPoint()->GetPolarization().deltaPhi(step->GetPreStepPoint()->GetPolarization());


    fEventAction->AddDeltaPhi(delPhi);

    isScattered = false;
    alreadyRecorded = false;

    if ( volume == fDetConstruction->GetCAbsorberPV() ) {
        fEventAction->AddAbsC(edep);

    } else if ( volume == fDetConstruction->GetNAbsorberPV() ) {

        if(edep > 0.) fEventAction->AddAbsN(edep);
        if(!alreadyRecorded) {

            fEventAction->AddScatAngle(0.*degree);
            fEventAction->AddScatPhi(phi);

            fEventAction->ScatBool(true);
            alreadyRecorded = true;
            fEventAction->RecordedBool(true);
        }

    } else if ( volume == fDetConstruction->GetEAbsorberPV() ) {

        fEventAction->AddAbsE(edep);
        if(!alreadyRecorded) {

            fEventAction->AddScatAngle(90.*degree);
            fEventAction->AddScatPhi(phi);

            fEventAction->ScatBool(true);
            alreadyRecorded = true;
            fEventAction->RecordedBool(true);
        }

    } else if ( volume == fDetConstruction->GetSAbsorberPV() ) {

        fEventAction->AddAbsS(edep);
        if(!alreadyRecorded) {

            fEventAction->AddScatAngle(180.*degree);
            fEventAction->AddScatPhi(phi);

            fEventAction->ScatBool(true);
            alreadyRecorded = true;
            fEventAction->RecordedBool(true);
        }

    } else if ( volume == fDetConstruction->GetWAbsorberPV() ) {

        fEventAction->AddAbsW(edep);
        if (!alreadyRecorded) {

            fEventAction->AddScatAngle(270. * degree);
            fEventAction->AddScatPhi(phi);

            fEventAction->ScatBool(true);
            alreadyRecorded = true;
            fEventAction->RecordedBool(true);
        }
    }

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







