/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 1: Nucleotides

Assignment does expected task when provided with expected characters (A,C,T, or G either uppercase or 
lowercase), but does not crash due to unexpected characters.  It treats unexpected characters as an
unknown nucleotide, thus decreasing the probability of all nucleotides.  Additionally, it treats lack
thereof (for example, no bigrams) as a probability of 0 instead of the default nan for readability.
*/

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

char getCharFromUser();

int main(int argc, char** argv) {
    if(argc < 2) {
        cout << "Please provide an input file as a command argument" << endl;
        exit(1); //http://www.cplusplus.com/reference/cstdlib/exit/
    }
    string filename = argv[1];
    char response = '?'; //Initializing do while condition
    do {
        if(response == 'y') { //This means that it is not the first iteration of the loop, since in the first iteration response is ?, but for all future iterations it's y
            cout << "What is the name of the file you'd like to open? " << endl;
            getline(cin, filename);
        }
        ifstream is(filename); //http://www.cplusplus.com/reference/fstream/ifstream/
        if(is.fail()) {
            cout << "File '" + filename + "' could not be opened." << endl;
            cout << "Would you like to process another file?  (y/n) ";
            response = getCharFromUser();
            continue;
        }
        //Initializing all counts
        int ACount = 0;
        int CCount = 0;
        int TCount = 0;
        int GCount = 0;
        int AACount = 0;
        int ACCount = 0;
        int ATCount = 0;
        int AGCount = 0;
        int CACount = 0;
        int CCCount = 0;
        int CTCount = 0;
        int CGCount = 0;
        int TACount = 0;
        int TCCount = 0;
        int TTCount = 0;
        int TGCount = 0;
        int GACount = 0;
        int GCCount = 0;
        int GTCount = 0;
        int GGCount = 0;
        int sumLengths = 0;
        int numLines = 0;
        int numBigrams = 0;
        double varSum = 0; //Using the more efficient definition of variance from sciencebuddies, varSum is the sum of x^2 for all x: //https://www.sciencebuddies.org/science-fair-projects/science-fair/variance-and-standard-deviation
        string line; //Declaring line ahead of time to avoid recreating it with every loop, since getline already clears it
        while(!is.eof()) {
            getline(is, line);
            int length = 0;
            for(int i = 0; i < line.length(); ++i) {
                ++length;
                char c = tolower(line[i]); //Optimizing nucleotide recognition by ensuring all characters are lowercase http://www.cplusplus.com/reference/cctype/tolower/
                if(c == 'a') {
                    ++ACount;
                    if(i == 0) {
                        continue; //If it is the first character in the line, it cannot possibly be a bigram (since I'm checking bigrams with the previous character)
                    }
                    //Bigram Recognition
                    ++numBigrams;
                    char cprev = tolower(line[i-1]);
                    if (cprev == 'a') {
                        ++AACount;
                    } else if (cprev == 'c') {
                        ++ACCount;
                    } else if (cprev == 't') {
                        ++ATCount;
                    } else if (cprev == 'g') {
                        ++AGCount;
                    }
                } else if (c == 'c') {
                    ++CCount;
                    if(i == 0) {
                        continue;
                    }
                    //Bigram Recognition
                    ++numBigrams;
                    char cprev = tolower(line[i-1]);
                    if (cprev == 'a') {
                        ++CACount;
                    } else if (cprev == 'c') {
                        ++CCCount;
                    } else if (cprev == 't') {
                        ++CTCount;
                    } else if (cprev == 'g') {
                        ++CGCount;
                    }
                } else if (c == 't') {
                    ++TCount;
                    if(i == 0) {
                        continue;
                    }
                    //Bigram Recognition
                    ++numBigrams;
                    char cprev = tolower(line[i-1]);
                    if (cprev == 'a') {
                        ++TACount;
                    } else if (cprev == 'c') {
                        ++TCCount;
                    } else if (cprev == 't') {
                        ++TTCount;
                    } else if (cprev == 'g') {
                        ++TGCount;
                    }
                } else if (c == 'g') {
                    ++GCount;
                    if(i == 0) {
                        continue;
                    }
                    //Bigram Recognition
                    ++numBigrams;
                    char cprev = tolower(line[i-1]);
                    if (cprev == 'a') {
                        ++GACount;
                    } else if (cprev == 'c') {
                        ++GCCount;
                    } else if (cprev == 't') {
                        ++GTCount;
                    } else if (cprev == 'g') {
                        ++GGCount;
                    }
                }
            }
            sumLengths += length;
            varSum += pow(length, 2);
            ++numLines;
        }
        is.close(); //Closing stream when done with it
        double meanLength = sumLengths / (double)numLines;
        double variance = (varSum/numLines) - pow(meanLength,2); //https://www.sciencebuddies.org/science-fair-projects/science-fair/variance-and-standard-deviation
        double stdev = sqrt(variance); //http://www.cplusplus.com/reference/cmath/sqrt/
        //Initializing all probabilities using ternary operators to rule out division by 0
        double AProbability = sumLengths > 0 ? ACount / (double)sumLengths : 0; //sumLengths is same as numNucleotides would have been
        double CProbability = sumLengths > 0 ? CCount / (double)sumLengths : 0;
        double TProbability = sumLengths > 0 ? TCount / (double)sumLengths : 0;
        double GProbability = sumLengths > 0 ? GCount / (double)sumLengths : 0;
        double AAProbability = numBigrams > 0 ? AACount / (double)numBigrams : 0;
        double ACProbability = numBigrams > 0 ? ACCount / (double)numBigrams : 0;
        double ATProbability = numBigrams > 0 ? ATCount / (double)numBigrams : 0;
        double AGProbability = numBigrams > 0 ? AGCount / (double)numBigrams : 0;
        double CAProbability = numBigrams > 0 ? CACount / (double)numBigrams : 0;
        double CCProbability = numBigrams > 0 ? CCCount / (double)numBigrams : 0;
        double CTProbability = numBigrams > 0 ? CTCount / (double)numBigrams : 0;
        double CGProbability = numBigrams > 0 ? CGCount / (double)numBigrams : 0;
        double TAProbability = numBigrams > 0 ? TACount / (double)numBigrams : 0;
        double TCProbability = numBigrams > 0 ? TCCount / (double)numBigrams : 0;
        double TTProbability = numBigrams > 0 ? TTCount / (double)numBigrams : 0;
        double TGProbability = numBigrams > 0 ? TGCount / (double)numBigrams : 0;
        double GAProbability = numBigrams > 0 ? GACount / (double)numBigrams : 0;
        double GCProbability = numBigrams > 0 ? GCCount / (double)numBigrams : 0;
        double GTProbability = numBigrams > 0 ? GTCount / (double)numBigrams : 0;
        double GGProbability = numBigrams > 0 ? GGCount / (double)numBigrams : 0;
        ofstream os; //http://www.cplusplus.com/reference/fstream/ofstream/
        if(response == 'y') { //Append to the output file if this is not the first loop running the program, override otherwise.
            os.open("nicholasmirchandani.out", ofstream::out | ofstream::app);
        } else {
            os.open("nicholasmirchandani.out", ofstream::out | ofstream::trunc);
        }
        os << "Name: Nicholas Mirchandani" << endl;
        os << "Student ID: 2317024" << endl;
        os << "Email: nmirchandani@chapman.edu" << endl;
        os << "Class: CPSC 350-02" << endl;
        os << "File Name: " << filename << endl;
        os << "Sum of Line Lengths: " << sumLengths << endl;
        os << "Mean of Line Lengths: " << meanLength << endl;
        os << "Variance of Line Lengths: " << variance << endl;
        os << "Standard Deviation of Line Lengths: " << stdev << endl;
        os << "A Probability: " << AProbability << endl;
        os << "C Probability: " << CProbability << endl;
        os << "T Probability: " << TProbability << endl;
        os << "G Probability: " << GProbability << endl;
        os << "AA Probability: " << AAProbability << endl;
        os << "AC Probability: " << ACProbability << endl;
        os << "AT Probability: " << ATProbability << endl;
        os << "AG Probability: " << AGProbability << endl;
        os << "CA Probability: " << CAProbability << endl;
        os << "CC Probability: " << CCProbability << endl;
        os << "CT Probability: " << CTProbability << endl;
        os << "CG Probability: " << CGProbability << endl;
        os << "TA Probability: " << TAProbability << endl;
        os << "TC Probability: " << TCProbability << endl;
        os << "TT Probability: " << TTProbability << endl;
        os << "TG Probability: " << TGProbability << endl;
        os << "GA Probability: " << GAProbability << endl;
        os << "GC Probability: " << GCProbability << endl;
        os << "GT Probability: " << GTProbability << endl;
        os << "GG Probability: " << GGProbability << endl;
        //Using the hint, we can ascertain variables c and d used for calculating each line's length
        srand(time(0)); //Seeding based on time

        for(int i = 0; i < 1000; ++i) { //Generate 1000 lines and append them to yourname.out
            double a = rand() / (double)RAND_MAX; //double forcing division using RAND_MAX to clamp the value between 0 and 1
            double b = rand() / (double)RAND_MAX;
            double c = sqrt(-2 * log(a)) * cos(2 * 3.14159 * b); //using 3.14159 as pi
            double d = stdev * c + meanLength;
            os << endl; //Line formatting
            for (int j = 0; j < d; ++j) { //d is this line's length
            /*To generate random nucleotides, here I'm using a generator variable that can be anywhere from 0 to 1 along
            with the probabilities for each nucleotide, which should add up to 1.  One at a time, I subtract each probability,
            and when the generator variable drops to or below 0, the nucleotide probability that dropped it there is the nucleotide
            that will be printed.*/
                double generator = rand() / (double)RAND_MAX; 
                generator -= AProbability;
                if (generator <= 0) {
                    os << 'A';
                    continue;
                }
                generator -= CProbability;
                if (generator <= 0) {
                    os << 'C';
                    continue;
                }
                generator -= TProbability;
                if (generator <= 0) {
                    os << 'T';
                    continue;
                }
                os << 'G'; //No need to run any calculations here, since it HAS to be G at this point.
            }
        }
        os.close();
        cout << "Would you like to process another file?  (y/n) ";
        response = tolower(getCharFromUser());
    } while (response == 'y');
    return 0;
}

char getCharFromUser() { //Accounting for bad input and clearing the buffer, Function taken from interterm c++ assignments
    char input;
    cin >> input;
    cin.ignore(32767, '\n');
    return input;
}