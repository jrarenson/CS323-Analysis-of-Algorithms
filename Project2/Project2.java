/*
*
*Jonathan Arenson
*CS323-21
*/
import java.util.*;
import java.io.*;


public class Project2{
    
    public static void main(String args[]){

        try{
            //reads input file
            Scanner inFile= new Scanner(new FileReader(args[0]));
           //prints output file 
            PrintWriter outFile = new PrintWriter(args[1]);
            
            LinkedList project = new LinkedList();
            project.linkedListOutput(inFile, outFile);
            
            //closes input file
            inFile.close();
            //closes output file
            outFile.close();
           
        }catch(IOException io){
            
            System.out.println(io);
        
        }
    }
}