#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Jonathan Arenson

void printAry(ofstream& outFile, int charCounter[]){
    int index = 0;
    char symbol;

    
   while(index < 256){

        if(charCounter[index]>0){
            symbol = (char)index;

                outFile<< symbol<< " " << ":" << charCounter[index] <<endl;
        }
    index++;

    }

}


int main(int argc, char* argv[]){
        ifstream inFile;
        ofstream outFile;
        //ofstream outFile;
        string str;
        int index;
        int charCounter[256] = {0};
        inFile.open (argv[1]);
        outFile.open (argv[2]);
        char charIn;
        if(inFile) {
          while(!inFile.eof()){
                inFile.get(charIn);
                
                index = (int)charIn;   
                charCounter[index]++;

    }
}


printAry(outFile, charCounter);


        inFile.close();
        outFile.close();
        return 0;

}


