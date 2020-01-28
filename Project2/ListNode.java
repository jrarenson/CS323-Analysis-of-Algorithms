import java.io.*;

public class ListNode{
    private String chStr;
    private int prob;
    ListNode next;

    ListNode(){
        chStr = null;
        prob = 0;
        next = null;
    }

    ListNode(String s, int i){
        chStr = s;
        prob = i;
        next = null;
    }

    public String getChStr(){
        return chStr;
    }

    public int getProb(){
        return prob;
    }


    public ListNode getNext(){
        return next;        
    }

    
    public void setNext(ListNode N){  
        next = N;      
    }

    public String toString(){
        String ans = "(\"" + chStr + "\", " + prob + ", ";
        if(next==null){
            ans += "NULL)";
        } else{
            ans += ("\"" + next.getChStr() + "\")");
        } 
        return ans;
    }

    public void printNode(PrintWriter outFile){
        if(this == null){
            outFile.println("NULL");
            return;
        }
    }
}