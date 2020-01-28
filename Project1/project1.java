/**
 * 
 * 
 * @Jonathan Arenson
 * CS323-21
 * Project1
 * 
 */

import java.io.FileReader;
import java.io.IOException;
import java.io.*;
import java.io.PrintWriter;
import java.io.BufferedWriter;
import java.util.Scanner;

public class project1 {
	public static void main(String[] args){
		//this sets the input file as null
		Scanner input = null;
		//this sets the output file as null
		PrintWriter output = null;
		//initializes and declare all necessary variables

		//256 is the max number of ascii chars
		int[] charCounter = new int[256];
		String symbol;
		int index;
		char charIn;


		try{
			//allows user to enter the input text name
			input = new Scanner(new FileReader(args[0]));
			//allows users to enter to output text name
			output = new PrintWriter(args[1]);

		}

		/*catch(FileNotFoundException fnf){
			System.out.println(fnf);
		}*/

		catch(IOException io){
			System.out.println(io);
		}

		//This checks for all symbols
		input.useDelimiter("");

		while(input.hasNext()){
			//This continuously searches for more characters
			charIn = input.next().charAt(0);
			index = (int)charIn;

			if(index>32 && index<256){
				charCounter[index]++;
			}		
		}

		
		for(int i = 0; i<256; i++){

			if (charCounter[i]>0) {
				output.println((char)i+": "+charCounter[i]+" ");
			}
		}
		//closes input file
		input.close();
		//closes output file
		output.close();
	}	
}
