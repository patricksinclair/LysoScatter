//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B4DetectorConstruction.hh 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file B4DetectorConstruction.hh
/// \brief Definition of the B4DetectorConstruction class

#ifndef B4DetectorConstruction_h
#define B4DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In addition a transverse uniform magnetic field is defined 
/// via G4GlobalMagFieldMessenger class.

class B4DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    B4DetectorConstruction();
    virtual ~B4DetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    // get methods
    //
    const G4VPhysicalVolume* GetCAbsorberPV() const;
    const G4VPhysicalVolume* GetNAbsorberPV() const;
    const G4VPhysicalVolume* GetNEAbsorberPV() const;
    const G4VPhysicalVolume* GetEAbsorberPV() const;
    const G4VPhysicalVolume* GetSEAbsorberPV() const;
    const G4VPhysicalVolume* GetSAbsorberPV() const;
    const G4VPhysicalVolume* GetSWAbsorberPV() const;
    const G4VPhysicalVolume* GetWAbsorberPV() const;
    const G4VPhysicalVolume* GetNWAbsorberPV() const;

    const G4VPhysicalVolume* GetGapPV() const;

  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    // data members
    //
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger;
                                      // magnetic field messenger

    G4VPhysicalVolume*   cAbsorberPV; // the absorber physical volume
    G4VPhysicalVolume*   NAbsorberPV; // the absorber physical volume
    G4VPhysicalVolume*   EAbsorberPV; // the absorber physical volume
    G4VPhysicalVolume*   SAbsorberPV; // the absorber physical volume
    G4VPhysicalVolume*   WAbsorberPV; // the absorber physical volume
    G4VPhysicalVolume*   NEAbsorberPV; // the absorber physical volume
    G4VPhysicalVolume*   SEAbsorberPV; // the absorber physical volume
    G4VPhysicalVolume*   SWAbsorberPV; // the absorber physical volume
    G4VPhysicalVolume*   NWAbsorberPV; // the absorber physical volume


    G4VPhysicalVolume*   cFoilPV;
    G4VPhysicalVolume*   nFoilPV;
    G4VPhysicalVolume*   eFoilPV;
    G4VPhysicalVolume*   sFoilPV;
    G4VPhysicalVolume*   wFoilPV;
    G4VPhysicalVolume*   neFoilPV;
    G4VPhysicalVolume*   seFoilPV;
    G4VPhysicalVolume*   swFoilPV;
    G4VPhysicalVolume*   nwFoilPV;


    G4VPhysicalVolume*   fGapPV;      // the gap physical volume

    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

// inline functions

inline const G4VPhysicalVolume* B4DetectorConstruction::GetCAbsorberPV() const {
  return cAbsorberPV;
}
inline const G4VPhysicalVolume* B4DetectorConstruction::GetNAbsorberPV() const {
    return NAbsorberPV;
}
inline const G4VPhysicalVolume* B4DetectorConstruction::GetNEAbsorberPV() const {
    return NEAbsorberPV;
}
inline const G4VPhysicalVolume* B4DetectorConstruction::GetEAbsorberPV() const {
    return EAbsorberPV;
}
inline const G4VPhysicalVolume* B4DetectorConstruction::GetSEAbsorberPV() const {
    return SEAbsorberPV;
}
inline const G4VPhysicalVolume* B4DetectorConstruction::GetSAbsorberPV() const {
    return SAbsorberPV;
}
inline const G4VPhysicalVolume* B4DetectorConstruction::GetSWAbsorberPV() const {
    return SWAbsorberPV;
}
inline const G4VPhysicalVolume* B4DetectorConstruction::GetWAbsorberPV() const {
    return WAbsorberPV;
}
inline const G4VPhysicalVolume* B4DetectorConstruction::GetNWAbsorberPV() const {
    return NWAbsorberPV;
}


inline const G4VPhysicalVolume* B4DetectorConstruction::GetGapPV() const  {
  return fGapPV;
}



#endif

