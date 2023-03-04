MiniGit Project (Our implemetation of a mini version of a version control system)
By: Eric Huynh and Matthew Etter

User Interface:
- When the user interacts with the program, a menu with a list of choices will pop up, ranging from 1 through 6. 
Welcoming the user to the MiniGit, the user will get multiple options: initalize a new repository, add a file, remove a file,
commit any changes they've made, checkout, and/or quit the program.

1. Initalize a new repository:
- When the user chooses to initalize a new repository, the program will check if a repository has been initalized or not. If one hasn't
been initalized yet, the program will create a new repository and a doubly linked list with a single head node. If the user tries
to initialize again, it will tell the user that a repository has already been initalized and return them back to the menu. 

2. Add a file:
- When the user chooses to add a file, the program will first check if the user initalize a repository. If not, it sents the user
back to the menu. Otherwise, it checks if the given filename exists within the current directory. If it doesn't exist, then it returns the user
back to the menu. Otherwise, it will go through the SLL and check through each one if the given filename already exists. If it does,
then it tells us that the filename already exits. Otherwise, it will create a new singly list node and initalize its variables.
Then it traverses through the singly linked list to check if there are already singly list nodes placed. If not, it will place the 
new file node as the first singly linked list node. Otherwise, it goes traverse through any following singly list node and places it after the
file node in the list.

3. Remove a file:
- When the user chooses to remove a file, the program will first check if the user initalize a repository. If not, it sents the
user back to the menu. Otherwise, we traverse through the singly linked list to find the file that the user wants to remove using
a while loop (until the end of the singly linked list). If the program finds the node that matches with the given input, then it
checks whether the node is at the beginning or not. If it is not, we use previous as a variable to hold the node after the node to be 
deleted then we delete the node. If it is at the beginning, the head of the singly linked list becomes the next node. If the program
checks the node and does not find the file to be remove, previous holds onto the current node and current becomes the next node. 
Once it reaches the end of the loop, that means the file to be remove does not exist.

4. Commit changes:
- When the user chooses to commit changes, the program will first check if the user initalize a repository. If not, it sents the
user back to the menu. Otherwise, the program traverses through each node in the singly linked list using a while loop. First, the program checks 
if the file in the node exists in the minigit directory. If it doesn't, the program takes the file name in the current directory
and copies it to the minigit. If it does, the program takes the file from the minigit and current directory and check if they are 
equal or not using the checkequal function. If they are, the program will not do anything and return to the menu. Otherwise, the program will copy the file from 
the current directory to the minigit and updates the file version name of the node with an incremented version (by 1 using the increment variable 
implemented into the singlyNode struct). The program will also check if the copy went through successfuly or not. 
Then, the program will create a new DLL with the commit number incremented by 1. Also, the previous SLL will also be deep copied to the new DLL using a while loop.
It also keeps of the current commit number and latest commit number for a special case in the checkout function.

5. Checkout:
- When the user chooses to checkout, the program will first check if the user initalize a repository. If not, it sents the
user back to the menu. Otherwise, the program takes the user's input (desired commit number they want to revert back to) and 
searches through the DLL to find the matching commit number. Going through a while loop, it first takes the current doublyNode
and make sure we are starting at the first DLL. Then within another while loop, it checks to see if the current DLL has the matching commiting
number. If it does not, it will send a message that the commit number wasn't found and return the user back to the menu. Otherwise,
the user will be asked if they want to proceed with their checkout, losing any local changes they may of made w/o commiting. It breaks
if the user says "N" and reask the user if they don't put in a valid input. Otherwise, it will traverse through the singly linked list
that is linked to the DLL to copy the files within the minigit to replace the files in the current directory. It also replaces 
the current commit number with the latest checkout and is later used to check when the current version is different 
from the most recent commit (the last DLL node). If they are different, the user cannot use the add, remove or check operations.

6. Quit:
- When the user chooses to quit, it exits them out of the program.

Extra Functions: 
show_records();
- The function is used to go into each node in the doubly linked list and print out each node in the singly list node, meaning
it will print out the file name(s) and file version(s) that have been implemented.
is_equal(f1, f2);
- The function is used for the commit function to check the two files if they are equal or not, specifically for the case 
when the fileVersion already exists in the minigit -> to check the current directory file to the one in the minigit.
copyfile(f1, f2);
- The function is used to copy files from the current directory to the minigit directory and vice versa.
