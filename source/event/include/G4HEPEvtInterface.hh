// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4HEPEvtInterface.hh,v 2.1 1998/07/12 02:53:50 urbi Exp $
// GEANT4 tag $Name: geant4-00 $
//

#ifndef G4HEPEvtInterface_h
#define G4HEPEvtInterface_h 1

#include <fstream.h>
#include <rw/tpordvec.h>
#include "globals.hh"
#include "G4VPrimaryGenerator.hh"
#include "G4HEPEvtParticle.hh"

class G4PrimaryVertex;
class G4Event;

class G4HEPEvtInterface:public G4VPrimaryGenerator
{
  public:
    G4HEPEvtInterface(char* evfile);
    G4HEPEvtInterface(G4String evfile);
    ~G4HEPEvtInterface();

    void GeneratePrimaryVertex(G4Event* evt);

  private:
    G4String fileName;
    ifstream inputFile;
    RWTPtrOrderedVector<G4HEPEvtParticle> HPlist;
};

#endif
