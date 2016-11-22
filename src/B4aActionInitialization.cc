

#include "B4aActionInitialization.hh"
#include "B4PrimaryGeneratorAction.hh"
#include "B4RunAction.hh"
#include "B4aEventAction.hh"
#include "B4aSteppingAction.hh"
#include "B4DetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4aActionInitialization::B4aActionInitialization
                            (B4DetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
   fDetConstruction(detConstruction)
{}



B4aActionInitialization::~B4aActionInitialization()
{}



void B4aActionInitialization::BuildForMaster() const
{
  SetUserAction(new B4RunAction);
}



void B4aActionInitialization::Build() const
{
  SetUserAction(new B4PrimaryGeneratorAction);
  SetUserAction(new B4RunAction);
  B4aEventAction* eventAction = new B4aEventAction;
  SetUserAction(eventAction);
  SetUserAction(new B4aSteppingAction(fDetConstruction,eventAction));
}  


