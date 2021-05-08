#ifndef DBFUNTIONS_H
#define DBFUNTIONS_H
#include<vector>
#include<string>

class dbFunctions{
   public:
    std::vector<std::string> parse(std::string command);
    int hash(std::string name);
};
#endif // DBFUNTIONS_H
