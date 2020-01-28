/*
 *
 *Jonathan Arenson
 *CS323-21
 *
 */

import java.util.*;
import java.io.*;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;



public class Project4 {
    public static void main(String args[]) {

    
        int numRows, numCols, minVal, maxVal, currVal, nextVal;

        Scanner inFile = null;
        PrintWriter outFile = null;

        try {

            inFile = new Scanner(new FileReader(args[0]));
            outFile = new PrintWriter(args[1]);

            numRows = inFile.nextInt();
            numCols = inFile.nextInt();
            minVal = inFile.nextInt();
            maxVal = inFile.nextInt();
            RunLength rl = new RunLength(numRows, numCols, minVal, maxVal);
            
            //This is the header information
            outFile.print("\n" + rl.numRows + " " + rl.numCols + " " + rl.minVal + " " + rl.maxVal);
            int r = 0;

            while (r < rl.numRows) {
                
                int c = 0;
                int count = 0;
                currVal = inFile.nextInt();

                outFile.print("\n" + r + " " + c + " " + currVal + " ");

                count++;


                while (c < rl.numCols-1) {

                    c++;

                    nextVal = inFile.nextInt();

                    if (nextVal == currVal) {

                        count++;

                    } else {

                        outFile.print(" " + count);
                        currVal = nextVal;
                        count = 1;
                        outFile.print("\n" + r + " " + c + " " + currVal);

                    }
                }

                outFile.print(" " + count);
                r++;


            }
        inFile.close();
        outFile.close();

        } catch (IOException io) {

            System.out.println(io);

        }

    }
}