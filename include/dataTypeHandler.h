#ifndef DATATYPEHANDLER_H
#define DATATYPEHANDLER_H
#include<vector>
#include<string>
#include<cstring>
#include<unordered_map>
#define vs vector<string>
#define vps vector<pair<string,string> >

using namespace std;

class dataTypeHandler
{
    public:
        dataTypeHandler();
        string validate_Types(vps &cols);
        virtual ~dataTypeHandler();

    protected:

    private:
};

#endif // DATATYPEHANDLER_H
