/*
Nathan Groves and Jayden Fleisher
The purpose of this program is to create 3 different
linked lists of words.  One will be created by adding nodes
to the front.  Another will be created by adding nodes at the end. Another will be created by inserting nodes in alphabetical order.

The class will be a doubly-linked list of nodes whose only
value is a string (word)
*/



#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node
{
  string data;
  Node * next;
  Node * previous;

Node (string d)
{
    data = d;
    next = NULL;
    previous = NULL;
  }
};




class WordList
{
  private:
    Node * head;
    Node * tail;
  public:
    WordList()
    {
      head = NULL;
      tail = NULL;
    }

    //Destructor
    ~WordList()
    {
      Node * traverse = head;
      while (traverse != NULL)
      {
        head = traverse->next;
        delete traverse;
        traverse = head;
      }
      head = NULL;
    }//End of destructor function

    //Insert new nodes at the front of the list
    void insertAtFront(string d)
    {
      //Create new node
      Node * temp = new Node(d);
      
      //Check if empty list
      if(head == NULL)
      {
        //If the list is empty, the new node is the head
        head = temp;
        tail = temp;
      }
      else
      {
        //Otherwise, link the new node in and make it new head
        temp-> next = head;
        head -> previous = temp;
        head = temp;
      }
    }

    //Insert new nodes at the back of the list 
    void insertAtEnd(string d)
    {
       //Create new node
      Node * temp = new Node(d);
      
      //Check if empty list
      if(head == NULL)
      {
        //If the list is empty, the new node is the head
        head = temp;
        tail = temp;
      }
      else
      {
        tail->next = temp;
        temp -> previous = tail;
        tail = temp;
      }
    }

void displayList(ofstream& outfile)
    {
      //Make a temporary pointer to traverse the list
      Node * traverse = head;

      //Run through every item
      while(traverse)
        {
          outfile << traverse->data << " ";
          traverse = traverse-> next;
        }
    }

//Function to search for a given value and remove it from the list
void remove (string d)
{

  if(d == head->data && head == tail)
      {
        //Set head and tail to NULL (will now be an empty list)
        head = NULL;
        tail = NULL;
      }//End of deleting single Node conditional (need to reset head & tail both)
  else if (d == head -> data)
  {
    Node * temp = head;
    Node * temp2 = NULL;//testing
    
    temp2 = head -> next; //testing
    temp2 -> previous = head ->previous; //testing
    
    head = temp2; //testing
    temp = NULL;
    delete temp;
  }

 

  else if (d == tail -> data)
  {
    Node * temp = tail;
    tail = tail -> previous;
    tail -> next = NULL;
    temp = NULL;
    delete temp;
  }


  
  
    Node * traverse = head;
    Node * trailing = NULL;
    Node * temp1 = NULL;

    while (traverse && traverse->data != d)
      {
        trailing = traverse;
        traverse = traverse -> next;
      }


  if (traverse != NULL)
  {
   trailing -> next = traverse -> next;
   temp1 = traverse -> next;
    temp1 -> previous = traverse -> previous;
    if (temp1 == tail)
    {
      tail -> previous = trailing;
    }
    traverse = NULL;
    delete traverse;
  }




}
  
  

int size ()
{
   //Make a temporary pointer to traverse the list
      Node * traverse = head;
      int count = 0;
  
      //Run through every item
      while(traverse)
        {
          count++;
          traverse = traverse-> next;
        }

    return count;
}

void insertInOrder(string d)
    {
      //Create new node
      Node * temp = new Node(d);
      
      //Check if empty list
      if(head == NULL)
      {
        //If the list is empty, the new node is the head
        head = temp;
        tail = temp;
      }
      else
      {
        //If the item to be inserted is less than our current smallest value,
        //insert at the front of the list
        if(temp->data < head->data)
        {
          insertAtFront(d);
          }
        else
        {
          //Create a pointer to traverse the list
          //NEVER traverse through head! (You will lose the list)
          Node * traverse = head;
          Node * trailing = NULL;

          //Traverse the list until we find a larger value or hit the end of the list
          while(temp->data > traverse->data && traverse -> next != NULL)
          {
            //Trailing pointer keeps track of the current node (old node)
            trailing = traverse;
            //Traverse moves on to the next node
            traverse = traverse->next;
          }

          //If you reached the end of the list, item to be inserted is the largest value
          if(traverse->next == NULL && temp -> data > traverse -> data)
            insertAtEnd(d);
          //Otherwise, insert the node in order at the trailing pointer location
          else
          {
            temp ->next = traverse;
            temp -> previous = trailing;
            trailing->next = temp;
            traverse -> previous = temp;
          }
        }
      }
      
    }//End of insertInOrder


void displayListReversed (ofstream& outfile)
{
  Node * move = tail;

  while(move)        
    {
  outfile << move -> data << " ";
      move = move -> previous;
  
    }

  }

};


int main()
  {
  ifstream infile;
  ofstream outfile;
  string word;
  infile.open("words.dat");
  
  // Use your last name here
  outfile.open("Groves-Fleisher.txt");
  WordList listA, listB, listC;
  
  if (infile && outfile)
  {
    outfile << "<Nathan Groves and Jayden Fleisher>\n";
    outfile << "Linked Lists Program\n\n";
    
    // Read until sentinel of STOP_READING is found
    // Use insert at Front
    while (infile >> word && word != "STOP_READING"){
      listA.insertAtFront(word);
    }
    
    outfile << "List built with insertAtFront:\n";
    listA.displayList(outfile);
    outfile << endl;

    
    // Remove words from list until
    // STOP_REMOVING is found
    while (infile >> word && word != "STOP_REMOVING"){
      listA.remove(word);
    }
    
    outfile << "After removing:\n";
    listA.displayList(outfile);
    outfile << endl;

    
    
    outfile << "Size: " << listA.size() << endl;

    
    
    outfile << "Reversed:\n";
    listA.displayListReversed(outfile);
    outfile << endl << endl;

    
    // Test insert at End
    // Read until sentinel of STOP_READING is found
    while (infile >> word && word != "STOP_READING"){
      listB.insertAtEnd(word);
    }
    
    outfile << "List build with insertAtEnd:\n";
    listB.displayList(outfile);
    outfile << endl;
    
    // Remove words from list until
    // STOP_REMOVING is found
    while (infile >> word && word != "STOP_REMOVING"){
      listB.remove(word);
    }
    
    outfile << "After removing:\n";
    listB.displayList(outfile);
    outfile << endl;
    
    outfile << "Size: " << listB.size() << endl;

  
    outfile << "Reversed: \n";
    listB.displayListReversed(outfile);
    outfile << endl << endl;

    // Test Insert in Order
    // Read until sentinel of "STOP_READING" is found
    // Use insertInOrder
    while (infile >> word && word != "STOP_READING")
    {
      listC.insertInOrder(word);
    }
    
    outfile << "List built with insertInOrder:\n";
    listC.displayList(outfile);
    outfile << endl;

  
    
    // Remove words from list until
    // STOP_REMOVING is found
    while (infile >> word && word != "STOP_REMOVING"){
      listC.remove(word);
    }
    
    outfile << "After removing:\n";
    listC.displayList(outfile);
    outfile << endl;
    
    outfile << "Size: " << listC.size() << endl;

    
    outfile << "Reversed:\n";
    listC.displayListReversed(outfile);
    outfile << endl << endl;


    // Close files
    outfile.close();
    infile.close();
  }
  
  else
  cout << "Couldn't open one or more files.\n";

  return 0;
}