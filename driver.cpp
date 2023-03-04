#include <iostream>
#include <filesystem>
#include "miniGit.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    MiniGit* MiniG;
    bool quit = false;
    bool initalized = false;

	while (!quit)
	{
        MiniG->menu();

		int option;
		string inputLine;

		getline(cin, inputLine);

		if (inputLine.length() != 1 || inputLine[0] < '0'
			|| inputLine[1] > '4') 
        {
			cerr << "Invalid option : " << inputLine << endl;
			continue;
		}

		option = stoi(inputLine);

		switch (option)
		{
			case 1:
			{
                if(!initalized)
                {
                    initalized = true;
                    MiniG = new MiniGit();
                    MiniG->initalize();
                    cout << "A new sub-directory called .minigit has been created." << endl;
                }
                break;
			}
			case 2:
			{
                if(initalized == false)
                {
                    cout << "Please initalize a respitory before you add a file." << endl;
                    break;
                }
                if(MiniG->currentCommitN != MiniG->latestCommitN)
                {
                    cout << "You can't use this operation since the current version differs from the recent commit." << endl;
                    break;
                }

		        string inputLine;

                cout << "Enter the filename you wish to add to your respitory." << endl;
		        getline(cin, inputLine);

                MiniG->add(inputLine);
                break;
			}
	        case 3:
			{
                if(initalized == false)
                {
                    cout << "Please initalize a respitory before you add a file." << endl;
                    break;
                }
                if(MiniG->currentCommitN != MiniG->latestCommitN)
                {
                    cout << "You can't use this operation since the current version differs from the recent commit." << endl;
                    break;
                }
                string inputLine;

                cout << "Enter the filename you wish to delete from your respitory." << endl;
		        getline(cin, inputLine);
                
                MiniG->remove(inputLine);
                break;
			}
            case 4:
            {
                if(initalized == false)
                {
                    cout << "Please initalize a respitory before you add a file." << endl;
                    break;
                }
                if(MiniG->currentCommitN != MiniG->latestCommitN)
                {
                    cout << "You can't use this operation since the current version differs from the recent commit." << endl;
                    break;
                }

                MiniG->commit();
                break;
            }
            case 5:
            {
                if(initalized == false)
                {
                    cout << "Please initalize a respitory before you add a file." << endl;
                    break;
                }
                int commitN;
                string inputLine;

                cout << "Enter the commit number you wish to revert back to from your respitory." << endl;
		        getline(cin, inputLine);
                commitN = stoi(inputLine);

                MiniG->checkout(commitN);
                break;
            }
			case 6:
			{
				quit = true;
			}
        }
    }
	cout << "Goodbye!" << endl;

	return 0;
}