// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4ParticleChangeForLoss.cc,v 2.1 1998/12/02 17:20:26 urban Exp $
// GEANT4 tag $Name: geant4-00 $
//
// 
// --------------------------------------------------------------
//	GEANT 4 class implementation file 
//
//	For information related to this code contact:
//	CERN, CN Division, ASD Group
//	
//	
// ------------------------------------------------------------
//   Implemented for the new scheme                 23 Mar. 1998  H.Kurahige
// --------------------------------------------------------------

#include "G4ParticleChangeForLoss.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4TrackFastVector.hh"
#include "G4DynamicParticle.hh"

G4ParticleChangeForLoss::G4ParticleChangeForLoss():G4VParticleChange()
{
  debugFlag = false;
#ifdef G4VERBOSE
  if (verboseLevel>2) {
    G4cerr << "G4ParticleChangeForLoss::G4ParticleChangeForLoss() " << endl;
  }
#endif
}

G4ParticleChangeForLoss::~G4ParticleChangeForLoss() 
{
#ifdef G4VERBOSE
  if (verboseLevel>2) {
    G4cerr << "G4ParticleChangeForLoss::~G4ParticleChangeForLoss() " << endl;
  }
#endif
}

// copy constructor
G4ParticleChangeForLoss::G4ParticleChangeForLoss(const G4ParticleChangeForLoss &right): G4VParticleChange(right)
{
   if (verboseLevel>1) {
    G4cerr << "G4ParticleChangeForLoss::  copy constructor is called " << endl;
   }
   theEnergyChange = right.theEnergyChange;
}

// assignemnt operator
G4ParticleChangeForLoss & G4ParticleChangeForLoss::operator=(const G4ParticleChangeForLoss &right)
{
   if (verboseLevel>1) {
    G4cerr << "G4ParticleChangeForLoss:: assignment operator is called " << endl;
   }
   if (this != &right)
   {
      theEnergyChange = right.theEnergyChange;
      theLocalEnergyDeposit = right.theLocalEnergyDeposit ;
   }
   return *this;
}


//----------------------------------------------------------------
// functions for Initialization
//

void G4ParticleChangeForLoss::Initialize(const G4Track& track)
{
  // use base class's method at first
  G4VParticleChange::Initialize(track);

  // set Energy equal to those of the parent particle
  const G4DynamicParticle*  pParticle = track.GetDynamicParticle();
  theEnergyChange          = pParticle->GetKineticEnergy();
}

//----------------------------------------------------------------
// methods for updating G4Step 
//

G4Step* G4ParticleChangeForLoss::UpdateStepForAlongStep(G4Step* pStep)
{
  // A physics process always calculates the final state of the
  // particle relative to the initial state at the beginning
  // of the Step, i.e., based on information of G4Track (or
  // equivalently the PreStepPoint). 
  // So, the differences (delta) between these two states have to be
  // calculated and be accumulated in PostStepPoint. 
  

  G4StepPoint* pPreStepPoint  = pStep->GetPreStepPoint(); 
  G4StepPoint* pPostStepPoint = pStep->GetPostStepPoint(); 
  G4Track*     aTrack  = pStep->GetTrack();
 
  // calculate new kinetic energy
  G4double energy = pPostStepPoint->GetKineticEnergy() 
                    + (theEnergyChange - pPreStepPoint->GetKineticEnergy()); 

  // update kinetic energy and momentum direction
  if (energy > 0.0) {
    pPostStepPoint->SetKineticEnergy( energy );
  } else {
    // stop case
    pPostStepPoint->SetKineticEnergy(0.0);
  }

  if (debugFlag) CheckIt(*aTrack);

  //  Update the G4Step specific attributes 
  return UpdateStepInfo(pStep);
}

//----------------------------------------------------------------
// methods for printing messages  
//

void G4ParticleChangeForLoss::DumpInfo() const
{
// use base-class DumpInfo
  G4VParticleChange::DumpInfo();

  G4cout.precision(3);
  G4cout << "        Kinetic Energy (MeV): " 
       << setw(20) << theEnergyChange/MeV
       << endl;
}

G4bool G4ParticleChangeForLoss::CheckIt(const G4Track& aTrack)
{
  G4bool    itsOK = true;
  if (theEnergyChange > aTrack.GetKineticEnergy()) {
    G4cout << " !!! the energy becomes larger than the initial energy !!!"
         << " :  " << (theEnergyChange -aTrack.GetKineticEnergy())/MeV
         << "MeV " <<endl;
    itsOK = false;
  }
  if (!itsOK) { 
    G4cout << " G4ParticleChange::CheckIt " <<endl;
    G4cout << " pointer : " << this <<endl ;
    DumpInfo();
  }
  return itsOK;
}





