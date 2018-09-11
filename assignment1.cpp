# include <iostream>
# include <fstream>
# include <cmath>
#include <cstdlib>
#include <random>
using namespace::std;

bool isValidDNA(string dna){

  for(int i = 0; i < dna.length(); i++){
    if(toupper(dna[i]) != 'A' && toupper(dna[i]) != 'T' && toupper(dna[i]) != 'C' && toupper(dna[i]) != 'G' ){
      return false;
  }
}
  return true;
}

string populateSequence(string sequence, int aRemain, int tRemain, int cRemain, int gRemain){
  int rand();
  for(int i = 0; i < sequence.length(); i++ ){
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

void createString(double variance, double mean, string output, double aProb, double tProb, double cProb, double gProb){
  int rand();
  double aCount = aProb * 1000;
  double tCount = tProb * 1000;
  double cCount = cProb * 1000;
  double gCount = gProb * 1000;
  ofstream outputFile;
  outputFile.open("output.txt", ios::app);
  for(int i = 0; i < 1000; i++){
    string newSequence = "";
    int a = rand();
    int b = rand();
    double c = sqrt(-2*log(a)*(cos(2*3.14*b)));
    int d = sqrt(variance) * c * mean;
    int value = rand()%d;
    for(int j = 0; j < value; j++){
      newSequence.append("*");
    }
    newSequence = populateSequence(newSequence, aCount, tCount, cCount, gCount);

   outputFile << newSequence << "\r\n";
  }
}

int countOccurances(string dna, string nucleo){
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

double calculateVariance(string filename, double mean, double lines){
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
  return nucleotideCount/dnaSum;
}

double bigramProbability(double dnaSum, double bigramCount){
  return bigramCount/(dnaSum/2);
}

int main(int argc, char** argv){
  ifstream dna;
  dna.open("test.txt");
  //Change with getting file from commandline

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

  ofstream outputFile;
  outputFile.open("output.txt");
  averageLength = dnaSum/stringsCounted;
  variance = calculateVariance("test.txt", averageLength, stringsCounted);
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
  createString(variance, averageLength, "output.txt", A, T, C, G);

}
