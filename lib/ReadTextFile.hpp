#pragma once

#include <fstream>
#include <string>
#include <vector>

class ReadTextFile {
  private:
    char _cDelim;
    size_t _uNbCol;
    size_t _uNbLine;
    std::ifstream _ifs;
    std::vector<std::string> colNames;

    void setDelim(const char cDelim) {
        _cDelim = cDelim;
    }
    char getDelim() {
        return _cDelim;
    }
    void setNbCol(const size_t nNbCol) {
        _uNbCol = nNbCol;
    }

    void computeNbLine(const char *szFileName);
    bool emptyLine(const std::string &str);

    void splitline(const std::string &str, char cDelim,
                   std::vector<std::string> &vstring) const;
    bool readline(std::string &str);

  public:
    ReadTextFile(char cDelim = '\0');
    ~ReadTextFile();

    size_t getNbLine() {
        return _uNbLine;
    }
    size_t getNbCol() {
        return _uNbCol;
    }

    bool openTextFile(const char *szFileName, std::vector<std::string> &vstring);
    void closeTextFile();

    bool getline(std::vector<std::string> &vstring, bool strict = true);
};
