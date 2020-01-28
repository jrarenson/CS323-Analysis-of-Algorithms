/*
*
*Jonathan Arenson
*CS323
*Project 5
*/

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

struct listNode{
    string chStr;
    int prob;
    string code;
    listNode* next, *left, *right;

    listNode(){
        prob = 0;
        next = right = left = NULL;
    }

    listNode(string s, int i){
        chStr = s;
        prob = i;
        next = right = left = NULL;
    }

    string printNode(listNode* t){
        string s = (*t).chStr + " " + to_string((*t).prob)+ " ";
        if((*t).next != NULL){

            s += (*t).next->chStr+ " ";
        }

        if(t->right != NULL){
            s += (*t).right->chStr + " ";
        }
        if(t->left != NULL){
            s += (*t).left->chStr;
        }

        return s + "\n";
    }
};

struct linkedList{
    listNode* listHead;

    linkedList(){
        listHead = new listNode("dummy", 0);
    }
    linkedList(listNode* lh){
        listHead = lh;
    }

    listNode* findSpot(listNode* listHead, listNode* NNode){
        listNode* spot = listHead;
        while(spot->next != NULL && spot->next->prob < NNode->prob){
            spot = spot->next;
        }
        return spot;
    }


    void insertNode(listNode* spot, listNode* NNode){

        NNode->next = spot->next;
        spot->next = NNode;
    }

    string printList(listNode* listHead){
        string list = "listHead-->";
        listNode* spot;
        for (spot = listHead; spot->next != NULL; spot = spot->next){
            list += string("(\"") + string(spot->chStr) + string("\",") + to_string(spot->prob) + string(", \"") + string(spot->next->chStr) + string("\")-->");       
        }
        list += string("(\"") + string(spot->chStr) + string("\", ") + to_string(spot->prob) + string(", NULL)-->NULL");
        return list;
    }   
};

int atoi(string s){
    int j;
    for (int i = 0; i < s.length(); i++){
        j = (int)s[i];
    }
    return j;
}

struct HuffmanBinaryTree{
    listNode* root;
    listNode* listHead;
    int charCounts[256];
    string charCode[256];

    HuffmanBinaryTree(){
        root = NULL;
    }


    void printAry(ofstream& outFile, int charCounts[]){
        int index = 0;
        char symbol;
        while(index < 256){
            if(charCounts[index] > 0){
                symbol = (char)index;
                outFile << symbol << " " << charCounts[index] << "\n";
            }
            index++;
        }
    }

    void computeCount(ifstream& inFile1, ofstream& outFile4){
        char charIn;
        int index;

        while(inFile1.get(charIn))
        {
            index = (int)charIn;
            if(index != 10){
                charCounts[index]++;
            }
        }
        printAry(outFile4, charCounts);
    }

    void constructHuffmanLList(int charCounts[], ofstream& outFile4)
    {
        string chStr;
        int prob;
        linkedList* list = new linkedList();
        listHead = list->listHead;
        int index = 0;

        while(index < 256){   
            if (charCounts[index]>0){
                
                chStr = char(index);
                prob = charCounts[index];
                listNode* NNode = new listNode(chStr, prob);
                listNode* spot = list->findSpot(listHead, NNode);
                list->insertNode(spot, NNode);

            }

            index++;
        }
        outFile4 << list->printList(listHead) << endl;
    }

    void constructHuffmanBinTree(listNode* listHead, ofstream& outFile4){
        linkedList* list = new linkedList(listHead);
        listNode* NNode;

        while(listHead->next->next != NULL){

            int prob = listHead->next->prob + listHead->next->next->prob;
            string chStr = listHead->next->chStr + listHead->next->next->chStr;
            NNode = new listNode(chStr, prob); 
            (*NNode).left = listHead->next; 
            (*NNode).right = listHead->next->next; 
            listNode* spot = list->findSpot(listHead, NNode);
            list->insertNode(spot, NNode);
            listHead->next = listHead->next->next->next;
            outFile4 << list->printList(listHead) << endl;

        }   
        root = NNode; 
    }

    void getCode(listNode* t, string code, ofstream& outFile1){   
        if (isLeaf(t)){
            t->code = code;
            int index = atoi(t->chStr);
            charCode[index] = code; 
            outFile1 << t->chStr << " " << t->code << endl;
        }else{
            getCode(t->left, code + "0", outFile1);
            getCode(t->right,code + "1", outFile1);
        }
    }
    bool isLeaf(listNode* t){
        return(t->left == NULL && t->right == NULL);
    }

    void Encode(ifstream& inFile2, ofstream& outFile2){
        char charIn;
        int index;
        string code;


        while(inFile2.get(charIn)){
            index = (int)charIn;
            if((index < 256) && (index !=10) && (index >= 0)){   
                code = charCode[index];             

                outFile2 << code;
            }
        }
    }
    void Decode(ifstream& inFile3, ofstream& outFile3, listNode* node){
        char charIn;
        if(isLeaf(node)){
            outFile3 << node->chStr;
            Decode(inFile3, outFile3, root);
        }else{
            if(inFile3.eof() && !isLeaf(node)){
                cout<<"The encoded file is a corrupted file";
            }else{
                inFile3.get(charIn); 

                if(charIn == '0'){
                    Decode(inFile3, outFile3, node->left);
                }
                if(charIn == '1'){
                    Decode(inFile3, outFile3, node->right);
                }
            }
        }
    }
};  

int main(int argc, char** argv){
    ifstream inFile1, inFile2, inFile3;
    ofstream outFile1, outFile2, outFile3, outFile4;
    //opens all files
    inFile1.open(argv[1]);
    inFile2.open(argv[2]);
    inFile3.open(argv[3]);
    outFile1.open(argv[4]);
    outFile2.open(argv[5]);
    outFile3.open(argv[6]);
    outFile4.open(argv[7]);


    HuffmanBinaryTree* project5 = new HuffmanBinaryTree();

    (*project5).computeCount(inFile1, outFile4);
    (*project5).constructHuffmanLList((*project5).charCounts, outFile4);
    (*project5).constructHuffmanBinTree((*project5).listHead, outFile4);
    (*project5).getCode(project5->root, "", outFile1);
    (*project5).Encode(inFile2, outFile2);
    //asks the user for the name of the file
    string fileName;
    cout<<"Enter the name of the file";
    cin >> fileName;
    inFile3.open(fileName);
    project5->Decode(inFile3, outFile3, (*project5).root);
  
    //closes all files 
    inFile1.close();
    inFile2.close();
    inFile3.close();
    outFile1.close();
    outFile2.close();
    outFile3.close();
    outFile4.close();
    return 0;
}