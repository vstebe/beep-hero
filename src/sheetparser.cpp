#include "sheetparser.h"
#include "fstream"
#include "utils.h"


SheetParser::SheetParser()
{
}
SheetParser::SheetParser(std::string fileName)
{
    _fileName = fileName;
}

Sheet SheetParser::getSheet()
{
    int tempo;
    std::vector <Note> vec;

    std::ifstream _file(_fileName, std::ios::in);
    if(_file)
    {
            std::string line;  // déclaration d'une chaîne qui contiendra la ligne lue
            std::getline(_file, line);  // on met dans "contenu" la ligne
            tempo = std::stoi(line);
            numLigne = 1;


            while(std::getline(_file, line))            //other lines
            {
                numLigne++;
                if (line != "" && line[0] != '#')      //empty line or comment
                {
                    Note n = getNote(line);
                    vec.push_back(n);
                }
            }

            _file.close();
    }
    else
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;

   return Sheet(vec, tempo);
}


Note SheetParser::getNote(std::string ligne)
{
    if (ligne[0] == '/') //special command
    {
        if (ligne == "/r")
             return Note(WHOLE, SILENCE);
        if (ligne == "/r.")
             return Note(WHOLE_POINT, SILENCE);
        if(ligne == "/b")
             return Note(HALF, SILENCE);
        if (ligne == "/b.")
             return Note(HALF_POINT, SILENCE);
        if (ligne == "/n")
             return Note(QUARTER, SILENCE);
        if (ligne == "/n.")
             return Note(QUARTER_POINT, SILENCE);
        if (ligne ==  "/c")
             return Note(EIGHTH, SILENCE);
        if  (ligne == "/c.")
            return Note(EIGHTH_POINT, SILENCE);
        if (ligne == "/dc")
             return Note(SIXTEENTH, SILENCE);
        if (ligne == "/dc.")
            return Note(SIXTEENTH_POINT, SILENCE);
        if (ligne == "/tc")
            return Note(THIRTYSECOND, SILENCE);
        if (ligne == "/tc.")
            return Note (THIRTYSECOND_POINT, SILENCE);
        std::cerr << "ERROR : " << numLigne << " : " << ligne;

    }
    else
    {
       std::vector<std::string> liste = Utils::split(ligne, ':');
       TYPE_NOTE type;
       LENGTH length;
       int octave;

        std::cout << liste.size() << std::endl;

       if (liste.size() == 3)
       {
           octave = std::stoi(liste[2]);

           if (liste[0] ==  "do" || liste[0] == "C")
                type=DO;
           else if (liste[0] == "do#" || liste[0] == "C#" || liste[0] == "reb" || liste [0] == "Db")
                type=DO_D;
           else if (liste[0] ==  "re" || liste[0] == "D")
                type=RE;
           else if (liste[0] ==  "re#" || liste[0] == "D#" || liste[0] == "mib" || liste [0] == "Eb")
                type=RE_D;
           else if (liste[0] ==   "mi" || liste[0] == "E"  || liste[0] == "fab" || liste [0] == "Fb")
                type=MI;
           else if (liste[0] ==   "fa" || liste[0] == "F")
                type=FA;
           else if (liste[0] ==   "fa#" || liste[0] == "F#" || liste[0] == "solb" || liste [0] == "Gb")
                type=FA_D;
           else if (liste[0] ==   "sol" || liste[0] == "G")
                type=SOL;
           else if (liste[0] ==   "sol#" || liste[0] == "G#" || liste[0] == "lab" || liste [0] == "Ab")
                type=SOL_D;
           else if (liste[0] ==   "la" || liste[0] == "A")
                type=LA;
           else if (liste[0] ==  "la#" || liste[0] == "A#" || liste[0] == "sib" || liste [0] == "Bb")
                type=LA_D;
           else if (liste[0] ==   "si" || liste[0] == "B" || liste[0] == "dob" || liste [0] == "Cb")
                type=SI;
           else
               std::cerr << "ERRORA : " << numLigne << " : " << ligne;


           if (liste[1] == "r")
               length=WHOLE;
           else if (liste[1] == "r.")
               length=WHOLE_POINT;
           else if (liste[1] == "b")
               length=HALF;
           else if (liste[1] == "b.")
               length=HALF_POINT;
           else if (liste[1] == "n")
               length=QUARTER;
           else if (liste[1] == "n.")
               length=QUARTER_POINT;
           else if (liste[1] == "c")
               length=EIGHTH;
           else if (liste[1] == "c.")
               length=EIGHTH_POINT;
           else if (liste[1] == "dc")
               length=SIXTEENTH;
           else if (liste[1] == "dc.")
               length=SIXTEENTH_POINT;
           else if (liste[1] == "tc")
               length=THIRTYSECOND;
           else if (liste[1] == "tc.")
               length=THIRTYSECOND_POINT;
           else
               std::cerr << "ERRORB : " << numLigne << " : " << ligne;
       }
       else
           std::cerr << "ERRORC : " << numLigne << " : " << ligne;

       return Note(length, type, octave);
    }
return Note();
}
