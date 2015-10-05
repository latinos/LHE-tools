LHE-tools
=========

LHE tools

merge LHE events
====

From https://twiki.cern.ch/twiki/pub/CMSPublic/SWGuideSubgroupMC/mergeLheFiles.cpp

Compile:

    g++ -Wall -o MergeLHEfiles.exe   MergeLHEfiles.cpp

run:

    ./MergeLHEfiles.exe   new.lhe    old1.lhe   old2.lhe   old3.lhe





split LHE events
====

Source https://github.com/govoni/LHEActions/blob/master/splitLHEfile.cpp

Compile:

    g++ -Wall -o SplitLHEfiles.exe   SplitLHEfiles.cpp

run:

    ./SplitLHEfiles.exe   old.lhe    N    new

options:

    it uses "old.new" to create N new files called "new"_1, "new"_2, ...


    


transform lepton flavours
====

Source https://github.com/govoni/LHEActions/blob/master/muToEleInLHE.cpp

Compile:

    g++ -Wall -o FlavourChanging.exe   FlavourChanging.cpp
    
run:

    ./FlavourChanging.exe    newfile.lhe   oldfile.lhe  idInput[11 (ele)]  idOutput

options:

    it uses "oldfile.lhe" new file and mix flavour decays
    
    


    
    
    
    
Backup
====

where:

    /home/amassiro/Latinos/LHE-tools
    /afs/cern.ch/user/a/amassiro/work/Latinos/LHE/LHE-tools


