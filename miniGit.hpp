#ifndef MINIGIT_HPP
#define MINIGIT_HPP
#include <string>

using namespace std;

struct singlyNode
{
    string fileName; // Name of local file
    string fileVersion; // Name of file in .minigit folder singlyNode * next;
    singlyNode* next;
    int increment;
};

struct doublyNode
{
    int commitNumber;
    singlyNode* head;
    doublyNode* previous;
    doublyNode* next;
};

class MiniGit
{
    public:
    MiniGit();
    ~MiniGit();
    void menu();
    void initalize();
    void add(string fileName);
    void remove(string fileName);
    void commit();
    void checkout(int commitNumber);
    void copyfile(string firstfile, string secondfile);
    bool checkequal(string firstfile, string secondfile);
    void show_records();
    int currentCommitN;
    int latestCommitN;

    private:
    doublyNode* commitHead;
    singlyNode* newNode;
};

#endif