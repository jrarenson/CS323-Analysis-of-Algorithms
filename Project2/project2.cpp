/*
*
*Jonathan Arenson
*CS323-21
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
	listNode *next;

	listNode(){
		chStr = "";
		prob = 0;
		next = NULL;

	}

	listNode(string s, int p){
		chStr = s;
		prob = p;
		next = NULL;

	}

	string to_String(){
		listNode *T = this;
		string ans = "(\"" + T->chStr + "\", " + to_string(T->prob) + ", ";
		if(T->next == NULL) {
			ans = ans + "NULL)";
		}else{
			ans = ans + "\"" +  T->next->chStr + "\")";
		}

		return ans;
	}

	void printNode(listNode *T, ofstream& outFile){
		if(T==NULL) {
			outFile << "NULL" << endl;
			return;
		}        
	}
};

class LinkedList{
	
private:
		listNode *listHead; 

public:

	LinkedList(){
	listNode *dummy = new listNode("dummy", 0);
	listHead = dummy;
}

LinkedList(listNode *T){
	listNode *dummy = new listNode("dummy", 0);
	listHead = dummy;
	listHead->next = T;
}


void LinkedListOutput(ifstream& input, ofstream& outFile){
	string chStr;
	int prob;
	
	while(input.good()){
		input >> chStr >> prob;
			
			listNode* spot = findSpot(prob);
			listNode* newNode = new listNode(chStr, prob);
			insertNode(spot, newNode);
			printList(outFile);
	}
}

listNode* findSpot(int prob){
	listNode* spot = listHead;
	
	while(spot->next!=NULL && spot->next->prob < prob){
		spot = spot->next;
	}
	return spot;
}

void insertNode(listNode* spot, listNode* newNode){
	newNode->next = spot->next;
	spot->next = newNode;
}


void printList(ofstream& outFile){
	listNode* x = listHead;
	outFile << "Listhead --> " << x->to_String();
	x = x->next;
	
	while(x!= NULL){
		outFile << " --> " << x->to_String();
		x = x->next;
	}
	outFile << "--> NULL\n";
	}
};

int main(int argc, char** argv){
	ifstream inFile;
	ofstream outFile;  
	inFile.open(argv[1]);    
	outFile.open(argv[2]);   

	if(!inFile){
		cout<<"Wrong file."<<endl;
		return 0;
	}	

	if(inFile){
		//makes sure that while it isn't at the end of the file
		while(!inFile.eof()){

	LinkedList* project = new LinkedList();

	project->LinkedListOutput(inFile, outFile);
	//flushes out the buffer 
	outFile.flush();

		}

	}

	//close input file
	inFile.close();
	//close output file
	outFile.close();


	return 0;
}