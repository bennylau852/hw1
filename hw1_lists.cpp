#include<iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Item {
    int val;
    Item* next;
    Item() {
        val = 0;
        next = NULL;
    }
    Item (int v, Item* n) {
        val = v;
        next = n;
    }
};

void readLists(Item*& head1, Item*& head2, char* textfile) {

    ifstream ifile (textfile); //use command line argument as input file

    if( ifile.fail() ) { // able to open file?

        cout << "Couldn't open file" << endl;

        return;
    }

    string myline;

    getline(ifile, myline); //able to get line?

    stringstream ss(myline);

    int number;

    while( ss >> number ) { //as long as stringstream can read an integer

        if (head1 == NULL) {

            head1 = new Item; //now points to a suitcase

            head1->val = number;

            head1->next = NULL;


        }

        else {

            Item* temp = head1; //temp pointer is now a copy of head

            while(temp->next != NULL) { //as long as temp is pointing at a suitcase

                temp = temp->next;

            }

            temp->next = new Item; //new pointer now points at a suitcase

            temp->next->val = number;

            temp->next->next = NULL;
        }

    }

    string myline2;

    getline(ifile, myline2);//able to get line?

    stringstream ss2(myline2);

    int number2;

    while( ss2 >> number2 ) { //as long as stringstream can read an integer

        if (head2 == NULL) {

            head2 = new Item; //now points to a suitcase

            head2->val = number2;

            head2->next = NULL;


        }

        else {

            Item* temp = head2; //temp pointer is now a copy of head

            while(temp->next != NULL) { //as long as temp is pointing at a suitcase

                temp = temp->next;

            }

            temp->next = new Item; //new pointer now points at a suitcase

            temp->next->val = number2;

            temp->next->next = NULL;
        }


    }

    ifile.close();

}

Item* copy(Item* head1, Item* head2) {

    if(head1->next == NULL) {

        head1->next = head2;

    }

    else {

        return new Item(head1->val, copy(head1->next, head2));
    }

}

Item* concatenate(Item* head1, Item* head2) {  // returns head pointer to new list

    Item* head3 = copy(head1, head2);

    return head3; 
}


void removeEvens(Item*& head) {

    if (head == NULL) {

        return;

    }

    if (head->val % 2 == 0) {

        Item* temp = head;

        head = head->next;

        delete temp;  

        removeEvens(head);

    }

    else {

        removeEvens(head->next);
    }

}

void sum_all(Item*head, double &sum, double &count) {

    if (head == NULL) {
        return;
    }

    sum = sum + head->val; 

    count++;

    sum_all(head->next, sum, count);
}


double findAverage(Item* head) {

    double sum = 0;
    double count = 0;

    sum_all(head, sum, count);

    double average = sum/count;

    return average;

}


void printList(std::ostream& ofile, Item* head)
{
  if(head == NULL)
    ofile << std::endl;
  else {
    ofile << head->val << " ";
    printList(ofile, head->next);
  }
}

void printList2(std::ostream& ofile, double number) {

    ofile << number;

}

int main (int argc, char** argv) {

    Item* head1 = NULL;

    Item* head2 = NULL;

    readLists(head1, head2, argv[1]);

    //Error message

    ofstream ofile (argv[2]);

    if ( argc < 3 ) {

        cout << "Inadequate command line arguments" << endl;

        return 1;

    }

    if( ofile.fail() ) { // able to open file?

        cout << "Couldn't open file" << endl;

        return 1;
    }

    printList(ofile, head1);

    printList(ofile, head2);

    Item* head3 = concatenate(head1, head2);  // returns head pointer to new list

    printList(ofile, head3);

    removeEvens(head3);

    printList(ofile, head3);

    double average = findAverage(head3);

    printList(ofile, head3);

    printList2(ofile, average);

    ofile.close();

}
