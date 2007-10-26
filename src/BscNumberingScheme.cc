///////////////////////////////////////////////////////////////////////////////
// File: BscNumberingScheme.cc
// Date: 02.2006
// Description: Numbering scheme for Bsc
// Modifications:
///////////////////////////////////////////////////////////////////////////////
#include "SimG4CMS/Forward/interface/BscNumberingScheme.h"
//
#include "CLHEP/Units/SystemOfUnits.h"
#include "globals.hh"
#include "FWCore/MessageLogger/interface/MessageLogger.h"


using namespace std;
using namespace edm;

BscNumberingScheme::BscNumberingScheme() {
  LogDebug("BscSim") << " Creating BscNumberingScheme" ;
}

BscNumberingScheme::~BscNumberingScheme() {
 LogDebug("BscSim") << " Deleting BscNumberingScheme" ;
}

                                                                                
int BscNumberingScheme::detectorLevel(const G4Step* aStep) const {
                                                                                
  //Find number of levels
  const G4VTouchable* touch = aStep->GetPreStepPoint()->GetTouchable();
  int level = 0;
  if (touch) level = ((touch->GetHistoryDepth())+1);
  return level;
}
                                                                                
void BscNumberingScheme::detectorLevel(const G4Step* aStep, int& level,
                                        int* copyno, G4String* name) const {
                                                                                
  //Get name and copy numbers
  if (level > 0) {
    const G4VTouchable* touch = aStep->GetPreStepPoint()->GetTouchable();
    for (int ii = 0; ii < level; ii++) {
      int i      = level - ii - 1;
      name[ii]   = touch->GetVolume(i)->GetName();
      copyno[ii] = touch->GetReplicaNumber(i);
    }
  }
}
                                                                                



unsigned int BscNumberingScheme::getUnitID(const G4Step* aStep) const {

  unsigned intindex=0;
  int level = detectorLevel(aStep);

  LogDebug("BscSim") << "BscNumberingScheme number of levels= " << level << endl;

 //  unsigned int intIndex = 0;
  if (level > 0) {
    int*      copyno = new int[level];
    G4String* name   = new G4String[level];
    detectorLevel(aStep, level, copyno, name);

    int det   = 0;
    int zside   = 0;
    int station  = 0;
    for (int ich=0; ich  <  level; ich++) {
      // new and old set up configurations are possible:
      if(name[ich] == "BSC") {
	zside   = copyno[ich]-1;
      } else if(name[ich] == "BSCTrap") {
	det   = 0;
        station =  2*(copyno[ich]-1);
      } else if(name[ich] == "BSCTubs") {
	det   = 1;
        station =  copyno[ich]-1;
      } else if(name[ich] == "BSCTTop") {
	++station;
      }

      LogDebug("BscSim") << "BscNumberingScheme  " << "ich=" << ich  << "copyno" 
		   << copyno[ich] << "name="  << name[ich] << endl;

    }
    intindex = packBscIndex (zside,det,  station);
    LogDebug("BscSim") << "BscNumberingScheme : det " << det << " zside " 
		  << zside << " station " << station 
		  << " UnitID 0x" << hex << intindex << dec << endl;

    for (int ich = 0; ich < level; ich++)
      LogDebug("BscSim") <<" name = " << name[ich] <<" copy = " << copyno[ich] 
		    << endl;
    LogDebug("BscSim")<< " packed index = 0x" << hex << intindex << dec << endl;

    delete[] copyno;
    delete[] name;
  }

  return intindex;
  
}

unsigned BscNumberingScheme::packBscIndex(int zside,int det,  int station){
  unsigned int idx = 6 << 28; // autre numero que les detecteurs existants 
  idx += (zside<<4)&16;    // vaut 0 ou 1 bit 4    
  idx += (det<<3)&8;                  //bit 3    det:0-1    1 bit:0-1
  idx += (station&7);                //bits 0-2   station:0-7=8-->2**3 =8     3 bits:0-2         
  LogInfo("BscSim") << "Bsc packing: det " << det 
 << " zside  " << zside << " station " << station  << "-> 0x" << hex << idx << dec <<  endl;

  //  unpackBscIndex(idx);  
return idx;
}

void BscNumberingScheme::unpackBscIndex(const unsigned int& idx) {
  int zside, det, station;
  zside  = (idx&16)>>4;
  det    = (idx&8)>>3;
  station = idx&7;                                           
  LogDebug("BscSim") << " Bsc unpacking: 0x " << hex << idx << dec << " -> det " <<   det  << " zside  " << zside << " station " << station  ;
}
                                                                                
