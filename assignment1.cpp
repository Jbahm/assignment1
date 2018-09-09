# include <iostream>
# include <fstream>
using namespace::std;

bool isValidDNA(string dna){

  for(int i = 0; i < dna.length(); i++){
    if(toupper(dna[i]) != 'A' && toupper(dna[i]) != 'T' && toupper(dna[i]) != 'C' && toupper(dna[i]) != 'G' ){
      return false;
  }
}
  return true;
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

double nucleotideProbability(int dnaSum, int nucleotideCount){
  return nucleotideCount/dnaSum;
}

double bigramProbability(int dnaSum, int bigramCount){
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


  averageLength = dnaSum/stringsCounted;
  variance = calculateVariance("test.txt", averageLength, stringsCounted);
//  standardDeviation = pow(variance, 0.5);
  cout << "sum: " << dnaSum << endl;
  cout << "mean: " << averageLength << endl;
  cout << "variance: " << variance << endl;
//  cout << "standard deviation: " << standardDeviation;

}
