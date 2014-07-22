// g++ -Wall -o SplitLHEfiles.exe   SplitLHEfiles.cpp
#include "LHEF.h"
#include <iomanip>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

std::string exec(const char* cmd) {
 FILE* pipe = popen(cmd, "r");
 if (!pipe) return "ERROR";
 char buffer[128];
 std::string result = "";
 while(!feof(pipe)) {
  if(fgets(buffer, 128, pipe) != NULL)
   result += buffer;
 }
 pclose(pipe);
 return result;
}


int main(int argc, char ** argv) {
 if(argc < 4) {
  std::cout << "Usage: " << argv[0] << " fileToSplit.lhe number_of_files tag_for_splitting" << std::endl ;
  return -1;
 }

 std::ifstream ifs (argv[1]) ;
 LHEF::Reader reader (ifs) ;

 int number_of_files = atoi (argv[2]) ;

 std::string command = std::string("cat  ") + argv[1] + std::string(" | grep \\<\\/event\\> | wc ");

 std::string str_total_events = exec(command.c_str());

 int total_events = (int) atof(str_total_events.c_str());
 int eventsPerFile = total_events / number_of_files;

 std::cout << " real total events = " << str_total_events << std::endl;
 std::cout << " usable total events [int conversion] = " << total_events << std::endl;
 std::cout << " number of files = " << number_of_files << std::endl;
 std::cout << " events per file = " << eventsPerFile << std::endl;
 std::cout << " total used events = " << eventsPerFile*number_of_files << std::endl;

 LHEF::Writer * writer ;
 std::ofstream outputStream ;

 int ieve = 0 ;
 int index = 0 ;
 // loop over input events
 while (reader.readEvent ()) {
  if (ieve == 0) {
   std::stringstream filename ;
   filename << argv[3] << "_" << index << ".lhe" ;
   outputStream.open (filename.str ().c_str ()) ;
   std::cout << "opening in output : " << filename.str () << std::endl ;
   writer = new LHEF::Writer (outputStream) ;
   writer->headerBlock() << reader.headerBlock ;
   writer->initComments() << reader.initComments ;
   writer->heprup = reader.heprup ;
   writer->init () ;
  }

  if ( reader.outsideBlock.length() ) std::cout << reader.outsideBlock;
  writer->eventComments() << reader.eventComments;
  writer->hepeup = reader.hepeup;
  writer->writeEvent();
  ieve++ ;

  if (ieve % eventsPerFile == 0) {
   ieve = 0 ;
   index++ ;
   delete writer ;
   outputStream.close () ;
  }
 } // loop over input events

 if (ieve % eventsPerFile != 0) delete writer ;
 return 0 ;
}



