// g++ -Wall -o MergeLHEfiles.exe   MergeLHEfiles.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include "LHEF.h"

int main(int argc, char** argv) {

 std::string line;
 std::string line2;
 if(argc < 3) {
  std::cout << ">>>MergeLHEfiles.cpp::Usage:   " << argv[0] << "  newfile.lhe   fileToAdd1.lhe   fileToAdd2.lhe ..." << std::endl;
  return -1;
 }

 std::vector<char*> fileToAddNames;

 for(int fileIt = 0; fileIt < argc-2; fileIt++) {
  fileToAddNames.push_back( argv[2+fileIt] );
  std::cout << "fileToAddName = " << fileToAddNames.at(fileIt) << std::endl ;
 }

 std::cout << "Merging " << argc-2 << " LHE files" << std::endl;

 // open lhe file
 std::ofstream outFile(argv[1], std::ios::out);

 LHEF::Writer writer (outFile) ;

 int eventIt = 0;

 for(int fileIt = 0; fileIt < argc-2; fileIt++) {
  std::cout << " Opening " << fileToAddNames.at(fileIt) << std::endl;
  std::ifstream fileToAdd(fileToAddNames.at(fileIt), std::ios::in);
  LHEF::Reader reader(fileToAdd);

  if (fileIt == 0) {
   writer.headerBlock() << reader.headerBlock;
   writer.initComments() << reader.initComments;
   writer.heprup = reader.heprup;
   writer.init();
  }

  while ( reader.readEvent() ) {
   if ( reader.outsideBlock.length() ) std::cout << reader.outsideBlock;
   writer.eventComments() << reader.eventComments;
   writer.hepeup = reader.hepeup;
   writer.writeEvent();
   eventIt++;
  }
 }

 std::cout << "Added " << eventIt << " events from " << argc-2 << " files to file " << argv[1] << std::endl;
 return 0;
}


