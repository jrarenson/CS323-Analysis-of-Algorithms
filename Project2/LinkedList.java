import java.util.*;
import java.io.*;
public class LinkedList{
    private ListNode listHead;

    LinkedList(){
        //create the dummy node
        ListNode dummy = new ListNode("dummy", 0);
        listHead = dummy;
    }

    LinkedList(ListNode Lh){
        ListNode dummy = new ListNode("dummy", 0);
        //assigns list head as the dummy node
        listHead = dummy;
        listHead.setNext(Lh);
    }

    public void linkedListOutput(Scanner inFile, PrintWriter outFile){
        String chStr;
        int prob;
        while(inFile.hasNext()){
            chStr = inFile.next();
            prob = inFile.nextInt();
            ListNode spot = findSpot(prob);
            ListNode nNode = new ListNode(chStr, prob);
            insertNode(spot, nNode);
            printList(outFile);
        }
    }

    private ListNode findSpot(int a){
        ListNode spot = listHead;
        while(spot.getNext()!=null && spot.getNext().getProb() < a)
            spot = spot.getNext();
        return spot;
    }

    private void insertNode(ListNode spot, ListNode nNode){
        nNode.setNext(spot.getNext());
        spot.setNext(nNode);
    }

    private void printList(PrintWriter outFile){
        ListNode current = listHead;
        outFile.print("Listhead --> " + current.toString());
        current = current.getNext();
        while(current != null){
            outFile.print(" --> " + current.toString());
            current = current.getNext();
        }
        outFile.println("--> NULL" + " \n ");
    }
}