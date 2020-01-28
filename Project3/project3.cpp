/*
*
*Jonathan Arenson
*CS323-21
*
*
*/

#include<fstream>
#include<iostream>
#include<string>

using namespace std;

struct listNode{
    string chStr;
    int prob;
    string code;
    listNode *next, *left, *right;
    
    listNode(){
        chStr = "";
        prob = 0;
        code = "";
        next = left = right = NULL;
    }

    listNode(string s, int i){
        chStr = s;
        prob = i;
        code = "";
        next = left = right = NULL;
    }

  string to_String(){
        listNode *T = this;
        string ans = "(\"" + (*T).chStr + "\", " + to_string((*T).prob) + ", ";
        if((*T).next == NULL) {
            ans = ans + "NULL)";
        }else{
            ans = ans + "\"" +  (*T).next->chStr + "\")";
        }

        return ans;
    }

    void printNode(listNode *T, ofstream& outFile){
        outFile << (*T).chStr << (*T).prob;

        if((*T).next == NULL){

            outFile;
        }else{
            outFile << " " + (*(*T).next).chStr;
        } 

        if((*T).left == NULL){

            outFile;
        }else{

            outFile<< (*(*T).left).chStr;
        }

        if((*T).right == NULL){

            outFile<< endl;
        }else{

            outFile<< (*(*T).right).chStr << endl;
        }

    }

    
};

class HuffmanListTree{
    private:
    listNode *listHead, *root;

    public:

    HuffmanListTree(){
        listNode *dummy = new listNode("dummy", 0);
        listHead = dummy;
        root = NULL;
    }

    HuffmanListTree(listNode *T){
        listNode *dummy = new listNode("dummy", 0);
        listHead = dummy;
        listHead->next = T;
        root = NULL;
    }

    listNode* getRoot(){
        return root;
    }

    listNode* getListhead(){
        return listHead;
    }

    void debuggerOutput(ifstream& input, ofstream& output){
        string chStr;
        int prob;
        while(input >> chStr >> prob){
            
            listNode* spot = findSpot(prob);
            listNode* NNode = new listNode(chStr, prob);
            insertNode(spot, NNode);
            printList(output);
        }
    }

    void constructHuffmanBinaryTree(ofstream& outFile){
        while(listHead->next->next!=NULL){
            listNode* first = listHead->next;
            listNode* second = first->next;

            int newProb = (*first).prob + second->prob;
            string newChar = (*first).chStr +second->chStr;

            listNode *NNode = new listNode(newChar, newProb);
            (*NNode).left = first;
            (*NNode).right = second;

            listNode* spot = findSpot(newProb);
            insertNode(spot, NNode);

            listHead->next = second->next;
            NNode->printNode(NNode, outFile);
            printList(outFile);
        }
        root = listHead->next;
    }

    void getCode(listNode* T, string code, ofstream& outFile){
       
        if(isLeaf(T)){
            (*T).code = code;
            outFile << T->chStr << ": " << T->code << endl;
            return;
        }
        getCode((*T).left, code + "0", outFile);
        getCode((*T).right, code + "1", outFile);
    }

    listNode* findSpot(int prob){
        listNode* spot = listHead;
        
        while(((*spot).next!= NULL) && ((*spot).next->prob < prob)){
          
            spot = spot->next;
        }
        return spot;
    }

    void insertNode(listNode* spot, listNode* NNode){
        (*NNode).next = spot->next;
        (*spot).next = NNode;
    }

    bool isLeaf(listNode* T){
        return (((*T).left == NULL) && ((*T).right== NULL));
    }

    void printList(ofstream& output){
        listNode* current = listHead;
        output << "Listhead --> " << current->to_String();
        current = current->next;
        while(current != NULL){
            output << " --> " << current->to_String();
            current = current->next;
        }
        output << "--> NULL\n";
    }

    //order traversals
    static void preOrderTraversal(listNode *T, ofstream& outFile){
        if(T == NULL) return;
        T->printNode(T, outFile);
        preOrderTraversal((*T).left, outFile);
        preOrderTraversal((*T).right, outFile);
    }
    
    static void inOrderTraversal(listNode *T, ofstream& outFile){
        if(T == NULL) return;
        preOrderTraversal((*T).left, outFile);
        (*T).printNode(T, outFile);
        preOrderTraversal((*T).right, outFile);
    }

    static void postOrderTraversal(listNode *T, ofstream& outFile){
        if(T == NULL) return;
        preOrderTraversal((*T).left, outFile);
        preOrderTraversal((*T).right, outFile);
        (*T).printNode(T, outFile);
    }
};

int main(int argc, char** argv){
    ifstream inFile;
    ofstream outFile1, outFile2, outFile3, outFile4, outFile5;

    inFile.open(argv[1]);    
    outFile1.open(argv[2]);   
    outFile2.open(argv[3]);   
    outFile3.open(argv[4]);   
    outFile4.open(argv[5]);   
    outFile5.open(argv[6]);   

   
   //if it's not in the file it outputs a message
    if(!inFile) {
        cout << "Cannot open file.\n";
        cout<< "Try again.\n";
        return 0;
    }

    // if it is in the file then it will continue

    if(inFile)
    {   
        //while it goes to the end of file it proceeds to outputs
        while(!inFile.eof())
        {
        
        HuffmanListTree* project3 = new HuffmanListTree();


        (*project3).debuggerOutput(inFile, outFile5);
        (*project3).constructHuffmanBinaryTree(outFile5);
        (*project3).getCode((*project3).getRoot(), "", outFile1);
        HuffmanListTree::preOrderTraversal((*project3).getRoot(), outFile2);
        HuffmanListTree::inOrderTraversal((*project3).getRoot(), outFile3);
        HuffmanListTree::postOrderTraversal((*project3).getRoot(), outFile4);

        }
    }   

    //close input and outputs
    inFile.close();
    outFile1.close();
    outFile2.close();
    outFile3.close();
    outFile4.close();
    outFile5.close();

    return 0;
}