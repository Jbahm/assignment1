#include <iostream>
using namespace::std;

class assignment1
{
public:
  bool isValidDna(string dna);

  string populateSequence(string sequence, int aRemain, int tRemain, int cRemain, int gRemain);

  void createString(double variance, double mean, string output, double aProb, double tProb, double cProb, double gProb, double sum);

  int countOccurances(string dna, string nucleo);

  double calculateVariance(string filename, double mean, double lines);

  double nucleotideProbability(double dnaSum, double nucleotideCount);

  double bigramProbability(double dnaSum, double bigramCount);


  string currentLine;
  string answer;
  bool repeat;
  string file;
  double A, AA, AT, AC, AG;
  double T, TT, TA, TC, TG;
  double C, CC, CA, CT, CG;
  double G, GG, GA, GT, GC;
  double dnaSum;
  double stringsCounted;
  double averageLength;
  double variance;
  double standardDeviation;



};
