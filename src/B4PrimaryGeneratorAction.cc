
#define _USE_MATH_DEFINES

#include "B4PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Box.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"

#include <stdlib.h>
#include <math.h>
#include <cmath>

B4PrimaryGeneratorAction::B4PrimaryGeneratorAction()
        : G4VUserPrimaryGeneratorAction(),
          fParticleGun(0),
          gParticleGun(0)
{
    G4int nofParticles = 1;
    fParticleGun = new G4ParticleGun(nofParticles);
    gParticleGun = new G4ParticleGun(nofParticles);
    // default particle kinematic
    //
    G4ParticleDefinition* particleDefinition
            = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
    fParticleGun->SetParticleDefinition(particleDefinition);
    fParticleGun->SetParticleEnergy(0.511*MeV);


   /* gParticleGun->SetParticleDefinition(particleDefinition);
    gParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,-1.));
    gParticleGun->SetParticleEnergy(0.511*MeV);
    gParticleGun->SetParticlePolarization(G4ThreeVector(0., 1., 0.));*/
    //fParticleGun->SetParticlePolarization(G4ThreeVector(0., 1., 0.));
}



B4PrimaryGeneratorAction::~B4PrimaryGeneratorAction()
{
    delete fParticleGun;
    delete gParticleGun;
}



void B4PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    // This function is called at the begining of event

    // In order to avoid dependence of PrimaryGeneratorAction
    // on DetectorConstruction class we get world volume
    // from G4LogicalVolumeStore
    //
    G4double worldZHalfLength = 0;
    G4LogicalVolume* worldLV
            = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
    G4Box* worldBox = 0;
    if ( worldLV) worldBox = dynamic_cast< G4Box*>(worldLV->GetSolid());
    if ( worldBox ) {
        worldZHalfLength = worldBox->GetZHalfLength();
    }
    else  {
        G4ExceptionDescription msg;
        msg << "World volume of box not found." << G4endl;
        msg << "Perhaps you have changed geometry." << G4endl;
        msg << "The gun will be place in the center.";
        G4Exception("B4PrimaryGeneratorAction::GeneratePrimaries()",
                    "MyCode0002", JustWarning, msg);
    }

    // Set gun position
    fParticleGun
            ->SetParticlePosition(G4ThreeVector(0., 0., 0));

   // gParticleGun
        //    ->SetParticlePosition(G4ThreeVector(0., 0., 0));

    G4double x = 2.;
    G4double y = 100.;
    G4double p_xA = (-1.+2.*((G4double)rand())/RAND_MAX)*tan(x/y);
    G4double p_yA = (-1.+2.*((G4double)rand())/RAND_MAX)*tan(x/y);
    G4double p_xB = -p_xA;
    G4double p_yB = -p_yA;


    G4double phi = (-1.+2.*((G4double)rand())/RAND_MAX)*2.*M_PI;
    G4double sinp = sin(phi);
    G4double cosp = cos(phi);

    G4ThreeVector polA = G4ThreeVector(cosp, sinp, 0.);
    G4ThreeVector polB = polA.cross(G4ThreeVector(0., 0., 1.));
    G4ThreeVector polX = G4ThreeVector(1., 0., 0.);
    G4ThreeVector polY = G4ThreeVector(0., 1., 0.);

    G4ThreeVector momA = G4ThreeVector(p_xA, p_yA, 1.);
    G4ThreeVector momB = G4ThreeVector(p_xB, p_yB, -1.);
    G4ThreeVector mom1 = G4ThreeVector(0., 0., 1.);
    G4ThreeVector mom2 = G4ThreeVector(0., 0., -1.);

    //G4cout << "polA: " << polA << G4endl;
    //G4cout << "polB: " << polB << G4endl;

    fParticleGun->SetParticlePolarization(polA);
    fParticleGun->SetParticleMomentumDirection(mom1);
    fParticleGun->GeneratePrimaryVertex(anEvent);

    fParticleGun->SetParticlePolarization(polB);
    fParticleGun->SetParticleMomentumDirection(mom2);
    fParticleGun->GeneratePrimaryVertex(anEvent);

    //gParticleGun->GeneratePrimaryVertex(anEvent);
}



