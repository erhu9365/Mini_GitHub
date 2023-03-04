#include <iostream>
#include <fstream>
#include <filesystem>
#include "miniGit.hpp"

using namespace std;
namespace files = std::filesystem;

MiniGit::MiniGit()
{
    files::remove_all(".minigit");
    files::create_directory(".minigit");
    currentCommitN = 0;
    latestCommitN = 0;
}

MiniGit::~MiniGit()
{
    files::remove_all(".minigit");
}

void MiniGit::menu()
{
    cout << "Welcome to MiniGit!" << endl;
    cout << "Select a numerical option" << endl;
    cout << "+=====Main Menu=====+" << endl;
    cout << " 1. Initalize a new repository " << endl;
    cout << " 2. Add a file " << endl;
    cout << " 3. Remove a file  " << endl;
    cout << " 4. Commit changes  " << endl;
    cout << " 5. Checkout  " << endl;    
    cout << " 6. Quit  " << endl;
    cout << "+-------------------+" << endl;
}

void MiniGit::initalize()
{
    commitHead = new doublyNode;
    commitHead->commitNumber = 0;
    commitHead->head = NULL;
    commitHead->next = NULL;
    commitHead->previous = NULL;
}

void MiniGit::add(string fileName)
{
    if(commitHead == 0)
    {
        cerr << "Sorry, MiniGit has not been initalized" << endl;
    }
    else
    {
        singlyNode* current = commitHead->head;
        if(!files::exists(fileName))
        {
            cout << "Sorry, the file does not exist in the current directory." << endl;
            return;
        }
        while(current != 0)
        {
            if(current->fileName == fileName)
            {
                cout << "The given file name already exists in the commit list" << endl;
                return;
            }
            current = current->next;
        }
        singlyNode* newFile = new singlyNode;
        newFile->fileName = fileName;
        newFile->fileVersion = to_string(0) + "_" + newFile->fileName;
        newFile->next = NULL;
        newFile->increment = 0;
        cout << "The SLL of the file has been added." << endl;

        if(commitHead->head == NULL)
        {
            commitHead->head = newFile;
        }
        else
        {
            current = commitHead->head;
            while(current->next != NULL)
            {
                current = current->next;
            }
            current->next = newFile;
        }  
        show_records();
        return;
    }
}

void MiniGit::remove(string fileName)
{
    if(commitHead == 0)
    {
        cerr << "Sorry, MiniGit has not been initalized" << endl;
    }
    else
    {
        singlyNode* current = commitHead->head;
        singlyNode* previous = 0;
        while(current != 0)
        {
            if(current->fileName == fileName)
            {
                if(previous != 0)
                {
                    previous->next = current->next;
                    delete current;
                    show_records();
                    cout << "The SLL of the file has been deleted." << endl;
                    return;
                }
                else
                {
                    commitHead->head = current->next;
                    delete current;
                    show_records();
                    cout << "The SLL of the file has been deleted." << endl;
                    return; 
                }
            }
            previous = current;
            current = current->next;
        }
        cout << "The given file name does not exist in the commit list" << endl;
        show_records();
        return;
    }
}

void MiniGit::commit()
{
    singlyNode* current = commitHead->head;
    while(1)
    {
        if(!files::exists(".minigit/" + current->fileVersion))
        {
            string newfileVersion = ".minigit/" + current->fileVersion;
            copyfile(current->fileName, newfileVersion);
            if(!files::exists(newfileVersion))
            {
                cout << "Sorry, the copy did not go through." << endl;
            }
            else
            {
                cout << "The file has been copied into the minigit directory." << endl;
            } 
        }
        else
        {
            bool check = checkequal(current->fileName, ".minigit/" + current->fileVersion);
            if(check == false)
            {
                current->increment++;
                string newfileVersion = ".minigit/" + to_string(0 + current->increment) + "_" + current->fileName;
                copyfile(current->fileName, newfileVersion);
                current->fileVersion = to_string(0 + current->increment) + "_" + current->fileName;
                if(!files::exists(newfileVersion))
                {
                    cout << "Sorry, the copy did not go through." << endl;
                }
                else
                {
                    cout << "The file has been copied into the minigit directory." << endl;
                }
            }
        }
        if(current->next == NULL)
        {
            break;
        } 
        current = current->next;
    }    
    doublyNode* newcommitHead= new doublyNode;
    newcommitHead->commitNumber = commitHead->commitNumber + 1;
    newcommitHead->head = NULL;
    newcommitHead->next = NULL;
    newcommitHead->previous = commitHead;
    commitHead->next = newcommitHead;
    singlyNode* previous= 0;

    current = commitHead->head;

    while(1)
    {
        newNode = new singlyNode;
        newNode->fileName = current->fileName;
        newNode->fileVersion = current->fileVersion;
        newNode->next = NULL;
        newNode->increment = current->increment;
        if(previous == 0)
        {
            newcommitHead->head = newNode;
            cout << "new DLL: " << newcommitHead << " to head node " << newNode << endl;
        }
        else
        {
            previous->next = newNode;
        }
        if(current->next == NULL) 
        {
            break;
        }
        previous = newNode;
        current = current->next;
    }
    commitHead = newcommitHead;
    latestCommitN = commitHead->commitNumber;
    currentCommitN = commitHead->commitNumber;
    show_records();
}

void MiniGit::checkout(int commitNumber)
{
    doublyNode* checkCommitN = commitHead;
    while(1)
    {
        if(checkCommitN->previous != NULL)
        {
            checkCommitN = checkCommitN->previous;
        }
        else
        {
            break;
        }
    }
    while(1)
    {
        if(checkCommitN->commitNumber != commitNumber)
        {
            checkCommitN = checkCommitN->next;
        }
        else
        {
            singlyNode* current = checkCommitN->head;
            string inputLine;
            cout << "WARNING: Are you sure you want to checkout? You lose some local changes if you haven't commited yet (Y/N)" << endl;
            getline(cin, inputLine);
            if(inputLine == "Y")
            {
                while(1)
                {
                    copyfile(".minigit/" + current->fileVersion, current->fileName);
                    if(current->next != NULL)
                    {
                        current = current->next;
                    }
                    else
                    {
                        break;
                    }
                }
                cout << "Checkout has been completed." << endl;
                currentCommitN = checkCommitN->commitNumber;
                break;
            }
            else if(inputLine == "N")
            {
                break;
            }
            else
            {
                cout << "Please enter Y or N for valid comfirmation." << endl;
                getline(cin, inputLine);
            }
        }
        if(checkCommitN->next == NULL && checkCommitN->commitNumber != commitNumber)
        {
            cerr << "Sorry, we weren't able to find the commit number you were searching for." << endl;
            break;
        }
    }
    return;
}

void MiniGit::copyfile(string firstfile, string secondfile)
{
    ifstream first(firstfile);
    ofstream second(secondfile);
    char firstchar, secondchar;
    bool check = true;

    if(!first.is_open())
    {
        cout << "Sorry, the input file can not be opened" << endl;
        return;
    }

    if(!second.is_open())
    {
        cout << "Sorry, the output file can not be opened" << endl;
        return;
    }

    while(1)
    {
        firstchar = first.get();
        if(firstchar == EOF)
        {
            break;
        }
        second << firstchar;
    }

    first.close();
    second.close();
    cout << "The file has been added." << endl;
}

bool MiniGit::checkequal(string firstfile, string secondfile)
{
    ifstream first, second;

    first.open(firstfile.c_str());
    second.open(secondfile.c_str());

    bool is_equal = true;
    
    if(!first.is_open() || !second.is_open())
    {
        cerr << "The files can't be check equality since one/both files are not able to open." << endl;
        return false;
    }

    while(!first.eof() || !second.eof())
    {
        string str1, str2;
        getline(first, str1);
        getline(second, str2);
        if(str1.compare(str2) != 0)
        {
            is_equal = false;
            cout << "The files aren't equal to each other." << endl;
            return is_equal;
        }
    }
    if(is_equal)
    {
        cout << "The files are equal to each other." << endl;
        return is_equal;
    }

    first.close();
    second.close();
}

void MiniGit::show_records()
{
    doublyNode* checkCommit=commitHead;

    while(checkCommit->previous != NULL){
        checkCommit = checkCommit->previous;
    }
    while(1)
    {
        cout << "Commit Number: " << checkCommit->commitNumber << "." << endl;
        cout<< "==========================" << endl;
        if (checkCommit->head == NULL) 
        {
            cout << "NO FILES" << endl;
        }
        else 
        {
            singlyNode* current = checkCommit->head;
            while (current->next != NULL ) 
            {
                cout<<"File: " <<current->fileName;
                cout<<" File Version: "<<current->fileVersion<<endl;
                current = current->next;
            }
            cout << "File: " << current->fileName;
            cout << " File Version: " << current->fileVersion << endl;
            cout << "==========================" << endl;
        }
        if(checkCommit->next == NULL)
        {
            break;
        }
        else
        {
            checkCommit=checkCommit->next;
        }
    }
}