# include <iostream>
# include <fstream>
# include <cmath>
#include <cstdlib>
#include <random>
#include <stdlib.h>
#include <time.h>
#include "assignment1.hpp"
using namespace::std;

bool isValidDNA(string dna){//Checks if the string being analyzed is valid

  for(int i = 0; i < dna.length(); i++){
    if(toupper(dna[i]) != 'A' && toupper(dna[i]) != 'T' && toupper(dna[i]) != 'C' && toupper(dna[i]) != 'G' ){
      return false;
  }
}
  return true;
}

int countOccurances(string dna, string nucleo){//Counts the number of times a nucleotide or a bigram appears
  int occurances = 0;
  //for a single nucleotide
  if(nucleo.length() == 1){
    for(int i = 0; i < dna.length(); i++){
      if(toupper(dna[i]) == nucleo[0]){
        occurances++;
      }
    }
  //for a nucleotide bigram
  }else if(nucleo.length() == 2){
    for(int i = 0; i < dna.length()-1; i++){
      if(toupper(dna[i]) == nucleo[0] && toupper(dna[i+1]) == nucleo[1]){
        occurances++;
      }
    }
  }
  return occurances;
}

string populateSequence(string sequence, int aRemain, int tRemain, int cRemain, int gRemain){
  for(int i = 0; i < sequence.length(); i++ ){//Fills the string with nucleotides after creation
    int choice = rand()%4;
    if(choice == 0 && aRemain > 0){
      sequence[i] = 'A';
    }else if(choice == 1 && tRemain > 0){
      sequence[i] = 'T';
    }else if(choice == 2 && gRemain > 0){
      sequence[i] = 'G';
    }else if(choice = 3 && cRemain > 0){
      sequence[i] = 'C';
    }
  }
  return sequence;
}

void createString(double variance, double mean, string output, double aProb, double tProb, double cProb, double gProb, double sum){
  //Calculates the length of the string and then outputs it to the file
  double aCount = aProb * sum;
  double tCount = tProb * sum;
  double cCount = cProb * sum;
  double gCount = gProb * sum;
  double a;
  double b;
  ofstream outputFile;
  outputFile.open("output.txt", ios::app);
  string newSequence = "";
  srand(time(NULL));
  for(int i = 0; i < 1000; i++){
    a = rand() - RAND_MAX;
    b = rand() - RAND_MAX;
    double c = sqrt(2*exp(1/a)*(cos(2*3.14*b)));
    double d = sqrt(variance) * c * mean;
    while(isnan(d) != 0){
      a = rand() - RAND_MAX;
      b = rand() - RAND_MAX;
      c = sqrt(2*exp(1/a)*(cos(2*3.14*b)));
      d = sqrt(variance) * c * mean;
    }
    d = round(d);

    for(int j = 0; j < d; j++){
      newSequence.append("*");
    }
    newSequence = populateSequence(newSequence, aCount, tCount, cCount, gCount);
   outputFile << newSequence << "\r\n";
   newSequence = "";
  }
}



double calculateVariance(string filename, double mean, double lines){
  //A method to calculate the variance in a file of DNA strings
  ifstream dna;
  dna.open(filename);
  string currentLine;
  double variance;
  for(int i = 0; i < 5; i++){
    dna >> currentLine;
    if(isValidDNA(currentLine) == true){
      variance += (currentLine.length() - mean) * (currentLine.length()-mean);
    }
  }
  dna.close();
  return variance/(lines-1);
}

double nucleotideProbability(double dnaSum, double nucleotideCount){
  //a function to determine the probability of any nucleotide throughout the collection
  return nucleotideCount/dnaSum;
}

double bigramProbability(double dnaSum, double bigramCount){
  //a function to determine the probability of any bigram throughout the collection
  return bigramCount/(dnaSum/2);
}

int main(int argc, char** argv){
  bool repeat = true;
  string answer;
  while(repeat == true){
  ifstream dna;
  string file;
  cout << "Enter the name of the file!" << endl;
  cin >> file;
  dna.open(file);

  string currentLine;
  double A, AA, AT, AC, AG;
  double T, TT, TA, TC, TG;
  double C, CC, CA, CT, CG;
  double G, GG, GA, GT, GC;
  double dnaSum;
  double stringsCounted;
  double averageLength;
  double variance;
  double standardDeviation;

  for(int i = 0; i < 5; i++){
    dna >> currentLine;
    if(isValidDNA(currentLine) == true){
      //Below are the calculations needed to determine the probability of the nucleotides
      A += countOccurances(currentLine, "A");
      AA += countOccurances(currentLine, "AA");
      AT += countOccurances(currentLine, "AT");
      AC += countOccurances(currentLine, "AC");
      AG += countOccurances(currentLine, "AG");

      T += countOccurances(currentLine, "T");
      TT += countOccurances(currentLine, "TT");
      TA += countOccurances(currentLine, "TA");
      TC += countOccurances(currentLine, "TC");
      TG += countOccurances(currentLine, "TG");

      C += countOccurances(currentLine, "C");
      CC += countOccurances(currentLine, "CC");
      CA += countOccurances(currentLine, "CA");
      CT += countOccurances(currentLine, "CT");
      CG += countOccurances(currentLine, "CG");

      G += countOccurances(currentLine, "G");
      GG += countOccurances(currentLine, "GG");
      GA += countOccurances(currentLine, "GA");
      GT += countOccurances(currentLine, "GT");
      GC += countOccurances(currentLine, "GC");

      dnaSum += currentLine.length();
      stringsCounted++;
    }
  }
  dna.close();
  //actually calculates the probability of each
  A = nucleotideProbability(dnaSum, A);
  AA = bigramProbability(dnaSum, AA);
  AT = bigramProbability(dnaSum, AT);
  AC = bigramProbability(dnaSum, AC);
  AG = bigramProbability(dnaSum, AG);

  T = nucleotideProbability(dnaSum, T);
  TA = bigramProbability(dnaSum, TA);
  TT = bigramProbability(dnaSum, TT);
  TC = bigramProbability(dnaSum, TC);
  TG = bigramProbability(dnaSum, TG);

  C = nucleotideProbability(dnaSum, C);
  CA = bigramProbability(dnaSum, CA);
  CT = bigramProbability(dnaSum, CT);
  CC = bigramProbability(dnaSum, CC);
  CG = bigramProbability(dnaSum, CG);

  G = nucleotideProbability(dnaSum, G);
  GA = bigramProbability(dnaSum, GA);
  GT = bigramProbability(dnaSum, GT);
  GC = bigramProbability(dnaSum, GC);
  GG = bigramProbability(dnaSum, GG);

  //Begining of outputting all statistics and new strings
  ofstream outputFile;
  outputFile.open("output.txt");
  averageLength = dnaSum/stringsCounted;
  variance = calculateVariance(file, averageLength, stringsCounted);
  standardDeviation = pow(variance, 0.5);
  outputFile << "Letter Probability:\r\n";
  outputFile << "A: " << A << "\r\n";
  outputFile << "AA: " << AA << " AT: " << AT << " AC: " << AC << " AG: " << AG << "\r\n";
  outputFile << "" << "\r\n";
  outputFile << "C: " << C << "\r\n";
  outputFile << "CA: " << CA << " CT: " << CT << " CC: " << CC << " CG: " << CG << "\r\n";
  outputFile << "" << "\r\n";
  outputFile << "T: " << T << "\r\n";
  outputFile << "TA: " << TA << " TT: " << TT << " TC: " << TC << " TG: " << TG << "\r\n";
  outputFile << "" << "\r\n";
  outputFile << "G: " << G << "\r\n";
  outputFile << "GA: " << GA << " GT: " << GT << " GC: " << GC << " GG: " << GG << "\r\n";
  outputFile << "" << "\r\n";
  outputFile << "Statistics:\r\n";
  outputFile << "Mean: " << averageLength << "\r\n";
  outputFile << "Variance: " << variance << "\r\n";
  outputFile << "Standard Deviation " << standardDeviation << "\r\n";
  createString(variance, averageLength, "output.txt", A, T, C, G, dnaSum);

  //asks the user if they want to repeat the process with a new set of DNA
  cout << "Do you want to analyze a new set? Y/N?" << endl;
  cin >> answer;
  if(answer == "N" or answer == "n"){
    repeat = false;
  }
}
}
