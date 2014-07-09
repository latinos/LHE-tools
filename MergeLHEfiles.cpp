// g++ -Wall -o MergeLHEfiles.exe   MergeLHEfiles.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdio.h>

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

 bool writeEvent = false;
 int eventIt = 0;

 outFile << "<LesHouchesEvents>" << std::endl;

 for(int fileIt = 0; fileIt < argc-2; fileIt++) {
  std::ifstream fileToAdd(fileToAddNames.at(fileIt), std::ios::in);

  while(!fileToAdd.eof()) {
   getline(fileToAdd, line2); 

     // decide whether to skip event or not 
   if( line2 == "<event>" )  {
    ++eventIt;
    writeEvent = true;
   }
     // write line to outFile
   if(writeEvent == true) {
    outFile << line2 << std::endl;
   }
     // end of event
   if( line2 == "</event>" ) {
    writeEvent = false;
   }
  }
 }
 outFile << "</LesHouchesEvents>" << std::endl;
 std::cout << "Added " << eventIt << " events from " << argc-2 << " files to file " << argv[1] << std::endl;
 return 0;
}


