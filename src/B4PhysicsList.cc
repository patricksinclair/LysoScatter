#include "B4PhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"


B4PhysicsList::B4PhysicsList()
        : G4VModularPhysicsList(){
    SetVerboseLevel(1);

    // Default physics
    RegisterPhysics(new G4DecayPhysics());

    // Radioactive decay
    RegisterPhysics(new G4RadioactiveDecayPhysics());

    //Polarised EM physics
    RegisterPhysics(new G4EmLivermorePolarizedPhysics());
}



B4PhysicsList::~B4PhysicsList()
{
}