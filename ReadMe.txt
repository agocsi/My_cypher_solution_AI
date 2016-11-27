========================================================================
    CONSOLE APPLICATION : My_cypher_solution_AI Project Overview
========================================================================

1. Kérjen be a felhasználótól egy maximum 255 karakternyi, nem üres szöveget! A továbbiakban ez a nyílt szöveg.
2. Alakítsa át a nyílt szöveget, hogy a késõbbi kódolás feltételeinek megfeleljen! A kódolás feltételei: A magyar ékezetes karakterek helyett ékezetmenteseket kell használni. (Például á helyett a; õ helyett o stb.) A nyílt szövegben az átalakítás után csak az angol ábécé betûi szerepelhetnek. A nyílt szöveg az átalakítás után legyen csupa nagybetûs.
3. Írja ki a képernyõre az átalakított nyílt szöveget!
4. Kérjen be a felhasználótól egy maximum 5 karakteres, nem üres kulcsszót! A kulcsszó a kódolás feltételeinek megfelelõ legyen! (Sem átalakítás, sem ellenõrzés nem kell!) Alakítsa át a kulcsszót csupa nagybetûssé!
5. A kódolás elsõ lépéseként fûzze össze a kulcsszót egymás után annyiszor, hogy az így kapott karaktersorozat (továbbiakban kulcsszöveg) hossza legyen egyenlõ a kódolandó szöveg hosszával! Írja ki a képernyõre az így kapott kulcsszöveget!
6. A kódolás második lépéseként a következõket hajtsa végre! Vegye az átalakított nyílt szöveg elsõ karakterét, és keresse meg avtabla.dat fájlból beolvasott táblázat elsõ oszlopában! Ezután vegye a kulcsszöveg elsõ karakterét, és keresse meg a táblázat elsõ sorában! Az így kiválasztott sor és oszlop metszéspontjában lévõ karakter lesz a kódolt szöveg elsõ karaktere. Ezt ismételje a kódolandó szöveg többi karakterével is!
7. Írja ki a képernyõre és a kodolt.dat fájlba a kapott kódolt szöveget!

My_cypher_solution_AI.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

My_cypher_solution_AI.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

My_cypher_solution_AI.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named My_cypher_solution_AI.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
