# include <iostream>
# include <fstream>
using namespace::std;

int main(int argc, char** argv){
  ifstream dna;
  dna.open("test.txt");
  string currentLine;
  for(int i = 0; i < 5; i++){
    dna >> currentLine;
    //add a to uppercase method
    cout << currentLine << endl;
  }
}
