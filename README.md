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


Backup
====

where:

    /home/amassiro/Latinos/LHE-tools

