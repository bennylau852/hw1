/**
 * Code to generate all permutations of a string of characters
 */

#include <iostream>
#include <cstring>

using namespace std;


// A nice interface to the user who doesn't care about a current location
void all_perms(char *src_chars, char* buf);

// This is where we'll do the work
void perm_helper(char *src_chars, char* buf, int curr);

// Calls the helper
void all_perms(char *src_chars, char* buf)
{
  perm_helper(src_chars, buf, 0);
}

// Iterates through all possible characters for the 'curr' location which are characters not previously used earlier in buf
void perm_helper(char *src_chars, char* buf, int curr)
{
  if(buf[curr] == '\0') { //When end of c string is reached, display c string
    cout << buf << endl;
  }

  else {

    int len = strlen(src_chars); //Gets the length of the string passed by reference 

    for(int i=0; i < len; i++){ 

      buf[curr] = src_chars[i]; 

      if (curr > 0) {

        char* gotya = strchr(buf, buf[curr]); 

        for (int j = 0; j < curr; j++) {

          if (gotya[0] == buf[j]) {

            buf[curr] = ' ';

            break;

          }

        }

      }

      if (buf[curr] != ' ') {

        perm_helper(src_chars, buf, curr+1); //Increments position of character by 1

      }

    }

  }

}

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide a string of characters to generate all permutations" << endl;
    return 1;
  }

  char* buf = new char[strlen(argv[1])+1]; // Allocate a temporary buffer of equal size to the src string

  for(int i=0; i < strlen(argv[1]); i++) {

    buf[i] = ' '; //Initiailize the string with empty spaces 

  }

  buf[strlen(argv[1])] = '\0'; //Null character for the end 

  all_perms(argv[1], buf); //Calls perm function 

  // Cleanup and return
  delete [] buf;

  return 0;
}
