//
// Created by psinclair on 26/10/16.
//

#ifndef B4PhysicsList_h
#define B4PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include "G4EmLivermorePolarizedPhysics.hh"

class G4VPhysicsConstructor;

class B4PhysicsList: public G4VModularPhysicsList
{
public:
    B4PhysicsList();
    virtual ~B4PhysicsList();

};


#endif
