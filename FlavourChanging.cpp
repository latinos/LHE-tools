// g++ -Wall -o FlavourChanging.exe   FlavourChanging.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include "LHEF.h"

#include <cstdlib>


int main(int argc, char** argv) {

 std::cout << " FlavourChanging " << std::endl;
 std::string line;
 std::string line2;
 if(argc < 3) {
  std::cout << ">>> FlavourChanging.cpp::Usage:   " << argv[0] << "  newfile.lhe   oldfile.lhe  idInput[11 (ele)]  idOutput" << std::endl;
  return -1;
 }

 std::cout << " argv[1] = " << argv[1] << std::endl;
 std::cout << " argv[2] = " << argv[2] << std::endl;
 
 char* fileToAddNames;
 fileToAddNames = argv[2];
 
 int idInput = 11; 
 if(argc >= 4) {
  idInput = atoi(argv[3]);
 }
 
 std::cout << "FlavourChanging " << argc-2 << " LHE files" << std::endl;
 std::cout << "FlavourChanging :: idInput = " << idInput << std::endl;
  
 // open lhe file
 std::ofstream outFile(argv[1], std::ios::out);

 LHEF::Writer writer (outFile) ;

 int eventIt = 0;

 LHEF::Reader reader(fileToAddNames);
 
 writer.headerBlock() << reader.headerBlock;
 writer.initComments() << reader.initComments;
 writer.heprup = reader.heprup;
 writer.init();
 
 while ( reader.readEvent() ) {
//   if ( reader.outsideBlock.length() ) std::cout << reader.outsideBlock;
  writer.hepeup = reader.hepeup;
  //    writer.writeEvent();

  int whattochange;
  whattochange = rand() % 9;
//   std::cout << " whattochange = " << whattochange << std::endl;
  
  int id1 = 0;
  int id2 = 0;
  
  //---- electron 11
  //---- muon     13
  //---- tau      15
  
  if (whattochange == 0 || whattochange == 1 || whattochange == 2 ) {
   id1 = 11; //---- electron
  }
  
  if (whattochange == 3 || whattochange == 4 || whattochange == 5 ) {
   id1 = 13; //---- muon
  }
  
  if (whattochange == 6 || whattochange == 7 || whattochange == 8 ) {
   id1 = 15; //---- tau
  }
  
  
  
  if (whattochange == 0 || whattochange == 3 || whattochange == 6 ) {
   id2 = 11; //---- electron
  }
  
  if (whattochange == 1 || whattochange == 4 || whattochange == 7 ) {
   id2 = 13; //---- muon
  }
  
  if (whattochange == 2 || whattochange == 5 || whattochange == 8 ) {
   id2 = 15; //---- tau
  }
  
  
  // loop over particles in the event
  for (int iPart = 0 ; iPart < reader.hepeup.IDUP.size (); ++iPart) {
   // outgoing particles         
   if (reader.hepeup.ISTUP.at (iPart) == 1) {
    
    
    //---- charged leptons
    if (abs (reader.hepeup.IDUP.at (iPart)) == idInput) {               
     if (reader.hepeup.IDUP.at (iPart) ==  idInput) reader.hepeup.IDUP.at (iPart) = id1 ;
     if (reader.hepeup.IDUP.at (iPart) == -idInput) reader.hepeup.IDUP.at (iPart) = -id2 ;               
    }
    //---- neutrinos
    if (abs (reader.hepeup.IDUP.at (iPart)) == (idInput+1)) {               
     if (reader.hepeup.IDUP.at (iPart) ==  (idInput+1)) reader.hepeup.IDUP.at (iPart) = id2 ;
     if (reader.hepeup.IDUP.at (iPart) == -(idInput+1)) reader.hepeup.IDUP.at (iPart) = -id1 ;               
    }
    
    
   } // outgoing particles
  } // loop over particles in the event
  
  writer.eventComments() << reader.eventComments;
  writer.hepeup = reader.hepeup;
  writer.writeEvent();
 
  eventIt++;
  
 }
 

 std::cout << "Added " << eventIt << " events from " << argc-2 << " file to file " << argv[1] << std::endl;
 return 0;

 
}


