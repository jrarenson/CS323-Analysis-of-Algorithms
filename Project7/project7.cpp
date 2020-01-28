/*
*
*Jonathan Arenson
*Project 7 - CS323
*/

#include <iostream>
#include <fstream>
#include <math.h> 
using namespace std;


class Kmean{
    public:

        class xyCoord{
    public:
        xyCoord(){};
        double xCoord;
        double yCoord;
        int Label;
        xyCoord(double x, double y){
            xCoord = x;
            yCoord = y;
        }
};
class Point{
    public:
        Point(){};
        int xCoord;
        int yCoord;
        int Label;
        double Distance;
        Point(int x, int y){
            xyCoord xy(x,y);
            xCoord = xy.xCoord;
            yCoord = xy.yCoord;
            Distance = 9999.0;
        }
};

    int K; 
    int numPts;
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int **imageArray;
    int changeLabel;
    int iterations;
    Point* pointSet;
    xyCoord* Kcentroids;



Kmean(int rows, int cols, int min, int max, int k){
    numRows = rows;
    numCols = cols;
    minVal = min;
    maxVal = max;   
    K = k;
    imageArray = new int*[numRows];

    for (int i = 0; i < numRows; i++){
        imageArray[i] = new int[numCols];
    }

    for (int x = 0; x < numRows; x++){
        for (int y = 0; y < numCols; y++){
            imageArray[x][y] = 0;
        }
    }

    Kcentroids = new xyCoord[K+1];
    numPts = 0;
    changeLabel = 0;
}

int extractPts(ifstream& input, ofstream& output){
    numPts = 0;
    int point;
    for(int rows = 0; rows < numRows; rows++){
        for(int cols = 0; cols < numCols; cols++){
            input >> point;
        if(point > 0){
            output<< rows <<" "<< cols <<endl;
            numPts++;
        }
        }
    }
    return numPts;
}

void loadPointSet(ifstream& input2, Point pointSet[]){
    int i = 0, x, y;
    while(input2 >> x >> y && i < numPts){
        pointSet[i] = Point(x,y);
        i++;
    }
}

void assignLabel(Point pointSet[] , int K){
    int front = 0;
    int back = numPts-1;
    int label = 1;
    while(front <= back){
        if(label > K){
            label = 1;
        }else if(label == K){
            pointSet[front].Label = label;
            front++;
            label++;
            
            pointSet[back].Label = 1;
            back--;
        }else{
            pointSet[front].Label = label;
            front++;
            label++;
            
            pointSet[back].Label = label;
            back--;
            label++;
        }   
    }
}

void Point2Image (Point pointSet[], int** imageArray){

    for (int i = 0; i < numPts; i++){   
        imageArray[pointSet[i].xCoord][pointSet[i].yCoord] = pointSet[i].Label;
    }   
}

void printImage(int** imageArray, ofstream& output2, int iterations){

    output2<<"** Result of iteration "<< ++iterations<< " **\n";
    for (int x = 0; x < numRows; x++){
        for (int y = 0; y < numCols; y++){   
            if(imageArray[x][y] > 0){
                output2<<imageArray[x][y];
            }else{
                output2<<" ";
            }
        }
        output2<<endl;
    }
}

void computeCentroids(Point pointSet[], xyCoord Kcentroids[]){

    int *sumX = new int[K+1];
    int *sumY = new int[K+1];
    int *totalPt = new int[K+1];

    for(int i = 1 ; i<K+1; i++){
        sumX[i]=0;
        sumY[i]=0;
        totalPt[i]=0;
    }

    int index = 0, label;
    while(index < numPts){

        label = pointSet[index].Label;
        sumX[label] += pointSet[index].xCoord;
        sumY[label] += pointSet[index].yCoord;
        totalPt[label]++;
        index++;
    }
    label = 1;
    while(label <= K){
        if(totalPt[label] == 0){
            Kcentroids[label].xCoord = sumX[label];
            Kcentroids[label].yCoord = sumY[label];
            break;
        }
        Kcentroids[label].xCoord = sumX[label]/totalPt[label];
        Kcentroids[label].yCoord = sumY[label]/totalPt[label];
        label++;
    }
}

double computeDist(Point p1, xyCoord p2){
    double resultX,resultY;
    resultX = (p2.xCoord - p1.xCoord)*(p2.xCoord - p1.xCoord);
    resultY = (p2.yCoord - p1.yCoord)*(p2.yCoord - p1.yCoord);
    return sqrt(resultX + resultY);
}

void distanceMinLabel(Point &p, xyCoord Kcentroids[]){

    double minDist = 99999.0;
    int minLabel = 0;
    int label = 1;
    while(label <= K){
        double distance = computeDist(p, Kcentroids[label]);
        if(distance < minDist){
            minLabel = label;
            minDist = distance;
        }
        label++;
    }

    if(minDist < p.Distance){
        p.Distance = minDist;
        p.Label = minLabel;
        changeLabel++;
    }
}

void writePtSet(Point pointSet[], ofstream& o3){
    o3<<numPts<<endl;
    o3<<numRows<<" "<<numCols<<endl;
    for (int i = 0; i < numPts; ++i){
        o3<<pointSet[i].xCoord<<" "<<pointSet[i].yCoord<<" "<<pointSet[i].Label<<endl;
    }
}

void kMeansClustering(Point pointSet[] , int K, ofstream& output2){
    iterations = 0;
    assignLabel(pointSet, K);
    while(true){
        Point2Image(pointSet, imageArray); 
        printImage(imageArray, output2, iterations);

        changeLabel = 0;
        computeCentroids(pointSet, Kcentroids);
        int index = 0;

        while(index < numPts){
            distanceMinLabel(pointSet[index],Kcentroids);
            index++;    
        }
        if(changeLabel ==0){
            break;
        }
        iterations++;
    }   
}
};


int main(int argc, char const *argv[]){
    ifstream input;
    ofstream output,output2,output3;
    input.open(argv[1]);

    int numRows,numCols,minVal,maxVal,K;
    input >> numRows;
        input >> numCols;
        input >> minVal;
        input >> maxVal;

        output.open(argv[2]);
        output2.open(argv[3]);
        output3.open(argv[4]);
        string newOutput = argv[2];
        cout<<"Enter K: ";
        cin >> K;

        Kmean project7(numRows,numCols,minVal,maxVal,K);
        int numPts = project7.extractPts(input,output);
        project7.numPts = numPts;
        project7.pointSet = new Kmean::Point[numPts];

        output.close();

        ifstream input2;
        input2.open(newOutput);

        project7.loadPointSet(input2, project7.pointSet);
        project7.kMeansClustering(project7.pointSet, K,output2);
        project7.writePtSet(project7.pointSet,output3);

        input.close();
        input2.close();
        output2.close();
        output3.close();
        return 0;
}