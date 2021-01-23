#include "ReadTextFile.hpp"

#include <string>

ReadTextFile::ReadTextFile(char cDelim)
    : _cDelim(cDelim), _uNbCol(0), _uNbLine(0) {}

ReadTextFile::~ReadTextFile() { closeTextFile(); }

inline bool ReadTextFile::emptyLine(const std::string &str) {
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
        if (*it >= ' ') return false;

    return true;
}

inline void ReadTextFile::splitline(const std::string &str, char cDelim,
                                    std::vector<std::string> &vstring) const {
    vstring.clear();
    // StringTokenizer...
    for (size_t posBegin = 0, posEnd = 0; posEnd != std::string::npos;
         posBegin = posEnd + 1) {
        posEnd = str.find_first_of(cDelim, posBegin);
        while (str[posBegin] == ' ') {
            ++posBegin;
        }

        size_t posEnd2 =
            posEnd == std::string::npos ? str.length() - 1 : posEnd - 1;

        while (posEnd2 > posBegin && str[posEnd2] == ' ') {
            --posEnd2;
        }
        vstring.push_back(str.substr(posBegin, posEnd2 - posBegin + 1));
    }
}

inline void ReadTextFile::computeNbLine(const char *szFileName) {
    _uNbLine = 0;

    std::string str;
    std::ifstream ifs;
    ifs.open(szFileName);
    if (!_ifs.good()) {
        return;
    }
    while (!std::getline(ifs, str)) {
        if (!emptyLine(str)) {
            ++_uNbLine;
        }
    }

    if (_uNbLine > 0) {
        --_uNbLine;  // on ne compte pas la ligne des noms de colonnes
    }
}

inline bool ReadTextFile::readline(std::string &str) {
    str.clear();

    while (true) {
        if (!std::getline(_ifs, str)) {
            return false;
        }

        size_t lenInit = str.length();
        size_t lenCur = lenInit;
        while (lenCur > 0 &&
               (str[lenCur - 1] == '\n' || str[lenCur - 1] == '\r' ||
                str[lenCur - 1] == ' ')) {
            --lenCur;
        }
        if (lenInit > lenCur) str = str.substr(0, lenCur);

        if (!emptyLine(str)) {
            return true;
        }
    }

    return false;
}

bool ReadTextFile::openTextFile(const char *szFileName,
                                std::vector<std::string> &vstring) {
    // Au cas ou le fichier serait ouvert
    closeTextFile();

    _ifs.open(szFileName);
    if (!_ifs.good()) {
        return false;
    }

    // Le delim est connu
    if ('\0' != getDelim()) {
        // lecture pas strick la premiere fois, on ne sait pas encore combien de
        // colonnes on a...
        getline(vstring, false);
    } else {
        // On recherche le delimiteur
        std::string line;
        if (readline(line)) {
            char cDelimTest[] = {',', ';', '\t'};
            unsigned int delimTested = 0;
            unsigned int bestScore = 0;
            unsigned int bestScoreDelimTested = 0;

            for (delimTested = 0; delimTested < sizeof cDelimTest;
                 ++delimTested) {
                splitline(line, cDelimTest[delimTested], vstring);
                if (vstring.size() > bestScore) {
                    bestScore = (unsigned int)vstring.size();
                    bestScoreDelimTested = delimTested;
                }
            }
            if (0 == bestScore) {
                return false;
            }

            setDelim(cDelimTest[bestScoreDelimTested]);
            splitline(line, cDelimTest[bestScoreDelimTested], vstring);
        }
    }

    computeNbLine(szFileName);
    setNbCol(vstring.size());
    colNames = vstring;
    return true;
}

void ReadTextFile::closeTextFile() {
    _uNbLine = 0;

    if (_ifs.is_open()) _ifs.close();
}

bool ReadTextFile::getline(std::vector<std::string> &vstring,
                           bool strick /*= true*/) {
    std::string str;

    if (!readline(str)) {
        return false;
    }
    splitline(str, getDelim(), vstring);

    return !strick || (vstring.size() == getNbCol());
}
