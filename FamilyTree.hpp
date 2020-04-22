#include <iostream>
#include <string>

using namespace std;
namespace family
{
class Tree
    {
    private:
        string name;
        Tree * father;
        Tree * mother;
        int level;
        string findName;
        
    public:
        Tree(string name);
        Tree &addFather(string child, string father);
        Tree &addMother(string child, string mother);
        string relation(string name);
        string find(string name);
        void display();
        void remove(string name);
        int relationHelp(Tree * T, string name, int level);
        int findHelp(Tree * T,string name, int level);
        bool existsFather(Tree * t);
        bool existsMother(Tree * t);
        void del(Tree * t, int relation);
        void removeFind(Tree * t, string name);
    };
};