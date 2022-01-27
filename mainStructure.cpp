#include "header.h"

vector<recipientsList> Recipient;
vector<SuppliesList> Supply;
string RecipientsFile, SuppliesFile, AdjacencyFile, VerticesFile;

//QUEUE FOR SUPPLY DISTRIBUTION
void readRecipient(){ //Enqueue all names in the file
	
	ifstream recipientsFile(RecipientsFile.c_str());
	string line;
	
	int i=0; //Index of Recipient Vector
	
	if(!recipientsFile.is_open()) {
     	cout<<"File " << RecipientsFile << " not found.  Make sure the .dat files are downloaded." << endl;
     	throw exception();
	}
	
	while(getline(recipientsFile,line)){
		Recipient.push_back(recipientsList());
		string tempString;
		istringstream tempLine(line);
		getline(tempLine,Recipient[i].firstName,'\t');
		getline(tempLine,Recipient[i].lastName,'\t');
		getline(tempLine,tempString,'\t');
		Recipient[i].age = atoi(tempString.c_str());
		getline(tempLine,tempString,'\t');
		Recipient[i].queueNumber = atoi(tempString.c_str());
		i++;
	}
}

void addRecipient(int *currentQueue, int *lastQueue){ //Manual enqueue
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	string firstName;
	string lastName;
	int age;
	
	string fNMessage="Enter the recipient's first name:";
	string lNMessage="Enter the recipient's last name:" ;
	string aMessage="Enter the age of the recipient:";
	string dMessage="The user is already on the queue";
	string dMessage1="or has already received donations.";
	string sMessage="Succesfully added the following name:";
	string eMessage="Input cannot be empty.";
	string e1Message="Invalid input.  Please try again.";
	
	do{
		SetConsoleTextAttribute(hOut, 15);
		gotoxy((MAXDIMX-MINDIMX)/6-(fNMessage.size()/2),(MAXDIMY)/4+0);
		cout << fNMessage;
		gotoxy((MAXDIMX-MINDIMX)/6-5,(MAXDIMY)/4+1);
		getline(cin,firstName);
		if(firstName.find_first_not_of(' ')==string::npos){
			SetConsoleTextAttribute(hOut, 12);
			gotoxy((MAXDIMX-MINDIMX)/6-(eMessage.size()/2),(MAXDIMY)/4+2);
			cout << eMessage;
		}
	}while(firstName.find_first_not_of(' ')==string::npos);
	firstName=nameCase(firstName);
	SetConsoleTextAttribute(hOut, 10);
	clearLine(MINDIMX,(MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/4+1,(MAXDIMY)/4+1);
	gotoxy((MAXDIMX-MINDIMX)/6-(firstName.size()/2),(MAXDIMY)/4+1);
	cout << firstName;
	
	
	do{
		SetConsoleTextAttribute(hOut, 15);
		gotoxy((MAXDIMX-MINDIMX)/6-(lNMessage.size()/2),(MAXDIMY)/4+2);
		cout << lNMessage;
		gotoxy((MAXDIMX-MINDIMX)/6-5,(MAXDIMY)/4+3);
		getline(cin,lastName);
		if(lastName.find_first_not_of(' ')==string::npos){
			SetConsoleTextAttribute(hOut, 12);
			gotoxy((MAXDIMX-MINDIMX)/6-(eMessage.size()/2),(MAXDIMY)/4+4);
			cout << eMessage;
		}
	}while(lastName.find_first_not_of(' ')==string::npos);
	lastName=nameCase(lastName);
	SetConsoleTextAttribute(hOut, 10);
	clearLine(MINDIMX,(MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/4+3,(MAXDIMY)/4+3);
	gotoxy((MAXDIMX-MINDIMX)/6-(lastName.size()/2),(MAXDIMY)/4+3);
	cout << lastName;
	
	for (int i=0; i<Recipient.size();i++){
 		if(Capitalize(Recipient[i].firstName)==Capitalize(firstName)&&Capitalize(Recipient[i].lastName)==Capitalize(lastName)){
			SetConsoleTextAttribute(hOut, 12);
			gotoxy((MAXDIMX-MINDIMX)/6-(dMessage.size()/2),(MAXDIMY)/4+5);
			cout << dMessage;
			gotoxy((MAXDIMX-MINDIMX)/6-(dMessage1.size()/2),(MAXDIMY)/4+6);
			cout << dMessage1;
			SetConsoleTextAttribute(hOut, 15);
			return;
		}
	}

	do{
		SetConsoleTextAttribute(hOut, 15);
		gotoxy((MAXDIMX-MINDIMX)/6-(dMessage.size()/2),(MAXDIMY)/4+4);
		cout << aMessage;
		gotoxy((MAXDIMX-MINDIMX)/6-5,(MAXDIMY)/4+5);
		cin >> age;	
		if(cin.fail()|| age<1 || age>100){
			SetConsoleTextAttribute(hOut, 12);
			gotoxy((MAXDIMX-MINDIMX)/6-(e1Message.size()/2),(MAXDIMY)/4+6);
			cout << e1Message;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			clearLine(MINDIMX,(MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/4+5,(MAXDIMY)/4+5);
		}
	}while(age<1||age>100);
	SetConsoleTextAttribute(hOut, 10);
	clearLine(MINDIMX,(MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/4+5,(MAXDIMY)/4+6);
	gotoxy((MAXDIMX-MINDIMX)/6-(charCount(to_str(age))/2),(MAXDIMY)/4+5);
	cout << age;
	
	*lastQueue+=1;
	int lastQueue1 = *lastQueue;
	Recipient.push_back({firstName, lastName, age, lastQueue1});
	
	SetConsoleTextAttribute(hOut, 10);
	gotoxy((MAXDIMX-MINDIMX)/6-(sMessage.size()/2),(MAXDIMY)/4+7);
	cout << sMessage;
	gotoxy((MAXDIMX-MINDIMX)/6-((firstName.size()+lastName.size()+5)/2),(MAXDIMY)/4+8);
	cout << firstName << " " << lastName << "(" << age << ")";
	SetConsoleTextAttribute(hOut, 15);
	
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	saveRecipientFile();
}

void nextRecipient(int *currentQueue, int *lastQueue){ //Enqueue
	if(checkSupply()){
		return;
	}
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(*currentQueue!=*lastQueue&&*lastQueue!=0&&!Recipient.empty()){
		string pRecipient = "Previous Recipient:";
		string cRecipient = "CURRENT RECIPIENT:";
		string nRecipient = "Next Recipient:";
		
		refreshRecipientsList();
		
		//Previous Recipient
		SetConsoleTextAttribute(hOut, 8);
		gotoxy((MAXDIMX-MINDIMX)/6-(pRecipient.size()/2),(MAXDIMY)/4+0);
		cout << pRecipient;
		gotoxy((MAXDIMX-MINDIMX)/6-1,(MAXDIMY)/4+1);
		cout << "#" << Recipient[0].queueNumber;
		gotoxy((MAXDIMX-MINDIMX)/6-((charCount(Recipient[0].firstName)+charCount(Recipient[0].lastName))/2+1),(MAXDIMY)/4+2);
		cout << Recipient[0].firstName << " " << Recipient[0].lastName << endl;
	
		Recipient.erase(Recipient.begin());
		
		if(!Recipient.empty()){
			//Current Recipient
			SetConsoleTextAttribute(hOut, 160);
			gotoxy((MAXDIMX-MINDIMX)/6-(cRecipient.size()/2),(MAXDIMY)/4+4);
			cout << cRecipient;
			gotoxy((MAXDIMX-MINDIMX)/6-1,(MAXDIMY)/4+5);
			cout << "#" << Recipient[0].queueNumber;
			gotoxy((MAXDIMX-MINDIMX)/6-((charCount(Recipient[0].firstName)+charCount(Recipient[0].lastName))/2+1),(MAXDIMY)/4+6);
			cout << Recipient[0].firstName << " " << Recipient[0].lastName << endl;
			
			//Next Recipient
			SetConsoleTextAttribute(hOut, 8);
			gotoxy((MAXDIMX-MINDIMX)/6-(nRecipient.size()/2),(MAXDIMY)/4+8);
			cout << nRecipient;
			gotoxy((MAXDIMX-MINDIMX)/6-1,(MAXDIMY)/4+9);
			cout << "#" << Recipient[1].queueNumber;
			gotoxy((MAXDIMX-MINDIMX)/6-((charCount(Recipient[1].firstName)+charCount(Recipient[1].lastName))/2+1),(MAXDIMY)/4+10);
			cout << Recipient[1].firstName << " " << Recipient[1].lastName << endl;
			SetConsoleTextAttribute(hOut, 15);
		}
		//Update supply amount values
		for(int i=0;i<Supply.size();i++){
			Supply[i].amount-=Supply[i].amountPerPerson;
		}
		
		saveSuppliesFile();
		saveRecipientFile();
	}
	else{
		SetConsoleTextAttribute(hOut, 12);
		string qEmpty = "Queue is empty.";
		gotoxy((MAXDIMX-MINDIMX)/6-(qEmpty.size()/2),(MAXDIMY)/4+0);
		cout <<qEmpty;
		SetConsoleTextAttribute(hOut, 15);
	}
}

//SUPPLY LOGISTICS
void readSuppliesList(){
	ifstream suppliesFile(SuppliesFile.c_str());
	string line;
	int i=0;
	if(!suppliesFile.is_open()) {
     	cout<<"File " << SuppliesFile << " not found.  Make sure the .dat files are downloaded." << endl;
     	throw exception();
	}
	while(getline(suppliesFile,line)){
		Supply.push_back(SuppliesList());
		
		string tempString;
		istringstream tempLine(line);
		getline(tempLine,Supply[i].name,'\t');
		
		getline(tempLine,tempString,'\t');
		Supply[i].amount = strtod(tempString.c_str(),0);
		
		getline(tempLine,tempString,'\t');
		Supply[i].amountPerPerson = strtod(tempString.c_str(),0);
		
		i++;
	}
	suppliesFile.close();
}

void addSupply(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	string name;
	double amount, amountPerPerson;
	
	string snMessage="Enter the name of the supply";
	string a2Message="Enter the amount of supplies (new item):";
	string aMessage="Enter the amount you would like to add:";
	string sMessage="The following item was added to the list:";
	string nMessage="Name: ";
	string a1Message="Added amount: ";
	string n1Message="New amount: ";
	string ppMessage="Enter the per person to be distributed";
	string pp1Message="Amount per person: ";
	string eMessage="Input cannot be empty.";
	string e1Message="Invalid input.  Please try again.";

	do{
		SetConsoleTextAttribute(hOut, 15);
		gotoxy((MAXDIMX-MINDIMX)/6-(snMessage.size()/2),(MAXDIMY)/4+0);
		cout << snMessage;
		gotoxy((MAXDIMX-MINDIMX)/6-5,(MAXDIMY)/4+1);
		getline(cin,name);
		if(name.find_first_not_of(' ')==string::npos){
			SetConsoleTextAttribute(hOut, 12);
			gotoxy((MAXDIMX-MINDIMX)/6-(eMessage.size()/2),(MAXDIMY)/4+2);
			cout << eMessage;
		}
	}while(name.find_first_not_of(' ')==string::npos);
	name=nameCase(name);
	SetConsoleTextAttribute(hOut, 10);
	clearLine(MINDIMX,(MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/4+1,(MAXDIMY)/4+1);
	gotoxy((MAXDIMX-MINDIMX)/6-(name.size()/2),(MAXDIMY)/4+1);
	cout << name;
	
	for(int i=0; i<Supply.size(); i++){
		if(Capitalize(Supply[i].name)==Capitalize(name)){
			SetConsoleTextAttribute(hOut, 15);
			gotoxy((MAXDIMX-MINDIMX)/6-(aMessage.size()/2),(MAXDIMY)/4+2);
			cout << aMessage;
			gotoxy((MAXDIMX-MINDIMX)/6-5,(MAXDIMY)/4+3);
			cin >> amount;
			
			refreshSuppliesList();
			SetConsoleTextAttribute(hOut, 10);
			Supply[i].amount+=amount;
			gotoxy((MAXDIMX-MINDIMX)/6-(sMessage.size()/2),(MAXDIMY)/4+5);
			cout << sMessage;
			gotoxy((MAXDIMX-MINDIMX)/6-((nMessage.size()+name.size())/2),(MAXDIMY)/4+6);
			cout << nMessage << name;
			gotoxy((MAXDIMX-MINDIMX)/6-((a1Message.size()+charCount(to_str(amount)))/2),(MAXDIMY)/4+7);
			cout << a1Message << amount;
			gotoxy((MAXDIMX-MINDIMX)/6-((n1Message.size()+charCount(to_str(Supply[i].amount)))/2),(MAXDIMY)/4+8);
			cout << n1Message << Supply[i].amount;
			SetConsoleTextAttribute(hOut, 15);
			
			saveSuppliesFile();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return;
		}
	}

	do{
		SetConsoleTextAttribute(hOut, 15);
		gotoxy((MAXDIMX-MINDIMX)/6-(a2Message.size()/2),(MAXDIMY)/4+2);
		cout << a2Message;
		gotoxy((MAXDIMX-MINDIMX)/6-5,(MAXDIMY)/4+3);
		cin >> amount;
		if(cin.fail()||amount<0){
			SetConsoleTextAttribute(hOut, 12);
			gotoxy((MAXDIMX-MINDIMX)/6-(e1Message.size()/2),(MAXDIMY)/4+4);
			cout << e1Message;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			clearLine(MINDIMX,(MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/4+3,(MAXDIMY)/4+3);
		}
	}while(amount<=0);
	SetConsoleTextAttribute(hOut, 10);
	clearLine(MINDIMX,(MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/4+3,(MAXDIMY)/4+3);
	gotoxy((MAXDIMX-MINDIMX)/6-(charCount(to_str(amount))/2),(MAXDIMY)/4+3);
	cout << amount;
	
	do{
		SetConsoleTextAttribute(hOut, 15);
		gotoxy((MAXDIMX-MINDIMX)/6-(ppMessage.size()/2),(MAXDIMY)/4+4);
		cout << ppMessage;
		gotoxy((MAXDIMX-MINDIMX)/6-5,(MAXDIMY)/4+5);
		cin >> amountPerPerson;
		if(cin.fail()||amountPerPerson<0){
			SetConsoleTextAttribute(hOut, 12);
			gotoxy((MAXDIMX-MINDIMX)/6-(e1Message.size()/2),(MAXDIMY)/4+6);
			cout << e1Message;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			clearLine(MINDIMX,(MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/4+5,(MAXDIMY)/4+5);
		}
	}while(amountPerPerson<=0);
	SetConsoleTextAttribute(hOut, 10);
	clearLine(MINDIMX,(MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/4+5,(MAXDIMY)/4+6);
	gotoxy((MAXDIMX-MINDIMX)/6-(charCount(to_str(amountPerPerson))/2),(MAXDIMY)/4+5);
	cout << amountPerPerson;
	
	
	Supply.push_back({name, amount, amountPerPerson});
	
	SetConsoleTextAttribute(hOut, 15);
	gotoxy((MAXDIMX-MINDIMX)/6-(sMessage.size()/2),(MAXDIMY)/4+7);
	cout << sMessage;
	SetConsoleTextAttribute(hOut, 10);
	gotoxy((MAXDIMX-MINDIMX)/6-((nMessage.size()+name.size())/2),(MAXDIMY)/4+8);
	cout << nMessage << name;
	gotoxy((MAXDIMX-MINDIMX)/6-((a1Message.size()+charCount(to_str(amount)))/2),(MAXDIMY)/4+9);
	cout << a1Message << amount;
	gotoxy((MAXDIMX-MINDIMX)/6-((pp1Message.size()+charCount(to_str(amount)))/2),(MAXDIMY)/4+10);
	cout << pp1Message << amountPerPerson;
	
	SetConsoleTextAttribute(hOut, 15);
	
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	saveSuppliesFile();
}

void deleteSupply(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	string nMessage="Enter the name of the item:";
	string sMessage="Succesfully deleted the item from the list.";
	string fMessage="Item not found on the list!";
	
	string name;
	
	gotoxy((MAXDIMX-MINDIMX)/6-(nMessage.size()/2),(MAXDIMY)/4+0);
	cout << nMessage;
	gotoxy((MAXDIMX-MINDIMX)/6-10,(MAXDIMY)/4+1);
	getline(cin,name);
	
	for(int i=0; i<Supply.size(); i++){
		if(Capitalize(name)==Capitalize(Supply[i].name)){
			SetConsoleTextAttribute(hOut, 10);
			Supply.erase(Supply.begin()+i);
			gotoxy((MAXDIMX-MINDIMX)/6-(sMessage.size()/2),(MAXDIMY)/4+3);
			cout << sMessage;
			saveSuppliesFile();
			SetConsoleTextAttribute(hOut, 15);
			return;
		}
	}
	SetConsoleTextAttribute(hOut, 12);
	gotoxy((MAXDIMX-MINDIMX)/6-(fMessage.size()/2),(MAXDIMY)/4+3);
	cout << fMessage;
	SetConsoleTextAttribute(hOut, 15);
	
}

int charCount(string string){
	return string.length();
}

string to_str(double i){ //to_str not supported by the compiler
	stringstream ss;
	ss<< i;
	return ss.str();
}
bool checkSupply(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, 12);
	bool outOfStock=0;
	int j=0;
	string ofsMessage="no longer has available supplies to deliver.";
	string ofsMessage1="Please restock!";
	string ofsMessage2="There's nothing to be delivered to the recipients!";
	
	if(Supply.empty()){
		gotoxy((MAXDIMX-MINDIMX)/6-(ofsMessage2.size()/2),(MAXDIMY)/4);
		cout <<  ofsMessage2;
		return 1;
	}
	for(int i=0; i<Supply.size();i++){
		if(Supply[i].amount<Supply[i].amountPerPerson||Supply.empty()){
			gotoxy((MAXDIMX-MINDIMX)/6-(charCount(Supply[i].name)/2),(MAXDIMY)/4+j);
			cout <<  Supply[i].name;
			j++;
			gotoxy((MAXDIMX-MINDIMX)/6-(ofsMessage.size()/2),(MAXDIMY)/4+j);
			cout <<  ofsMessage;
			j++;
			gotoxy((MAXDIMX-MINDIMX)/6-(ofsMessage1.size()/2),(MAXDIMY)/4+j);
			cout <<  ofsMessage1;
			j+=2;
			outOfStock=1;
		}
	}
	SetConsoleTextAttribute(hOut, 15);
	return outOfStock;
}

void getQueue(int *currentQueue, int *lastQueue){
	if(!Recipient.empty()){
		*currentQueue = Recipient[0].queueNumber; //Front end
		*lastQueue = Recipient[Recipient.size()-1].queueNumber; //Rear end
	}
}

void printRecipientsList(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	for (int i=0;i<MAXDIMX/3-2;i++){ //Clears recipients list
		for (int j=0; j<MAXDIMY-1;j++){
			gotoxy(MAXDIMX/3+i+1,MINDIMY+6+j);
			cout << " ";
			if(j==MAXDIMY-10){
			break;
			}
		}
	}
	if(Recipient.size()==0){
		gotoxy(6*MAXDIMX/18+2,MINDIMY+7);
		cout << "(Queue is empty)";
		return;
	}
	for(int i=0; i<Recipient.size();i++){
		if(i==0){
			SetConsoleTextAttribute(hOut, 32);	
		}
		if(i==MAXDIMY-10){
			gotoxy(7*MAXDIMX/18,MINDIMY+7+i);
			cout << "And many more...";
			break;
		}
		gotoxy(6*MAXDIMX/18+2,MINDIMY+7+i);
		cout << Recipient[i].queueNumber;
		
		gotoxy(7*MAXDIMX/18,MINDIMY+7+i);
		cout << nameCase(Recipient[i].firstName.substr(0,2*MAXDIMX/18-5));
		if(Recipient[i].firstName.size()>=2*MAXDIMX/18-5){
			cout << "...";
		}
		
		gotoxy(9*MAXDIMX/18,MINDIMY+7+i);
		cout << nameCase(Recipient[i].lastName.substr(0,2*MAXDIMX/18-5));
		if(Recipient[i].lastName.size()>=2*MAXDIMX/18-5){
			cout << "...";
		}
		
		gotoxy(11*MAXDIMX/18,MINDIMY+7+i);
		cout << Recipient[i].age;
		SetConsoleTextAttribute(hOut, 15);
}
}
void printSuppliesList(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	for (int i=0;i<MAXDIMX/3-2;i++){ //Clears recipients list
		for (int j=0; j<MAXDIMY-1;j++){
			gotoxy(2*MAXDIMX/3+i+1,MINDIMY+6+j);
			cout << " ";
			if(j==MAXDIMY-10){
			break;
			}
		}
	}
	if(Supply.size()==0){
		gotoxy(13*MAXDIMX/18,MINDIMY+7);
		cout << "(Supplies is empty)";
		return;
	}
	for(int i=0; i<Supply.size();i++){
		if(Supply[i].amount<Supply[i].amountPerPerson||Supply.empty()){
			SetConsoleTextAttribute(hOut, 12);	
		}
		else if(Supply[i].amount<10*Supply[i].amountPerPerson){
			SetConsoleTextAttribute(hOut, 14);	
		}
		else if(i==MAXDIMY-10){
			gotoxy(13*MAXDIMX/18,MINDIMY+7+i);
			cout << "And many more...";
			break;
		}
	
		gotoxy(12*MAXDIMX/18+2,MINDIMY+7+i);
		cout << nameCase(Supply[i].name.substr(0,2*MAXDIMX/18-2));
		if(Supply[i].name.size()>=2*MAXDIMX/18-2){
			cout << "...";
		}
		gotoxy(15*MAXDIMX/18-(charCount(to_str(Supply[i].amount))/2),MINDIMY+7+i);
		cout << Supply[i].amount;
		gotoxy(17*MAXDIMX/18-(charCount(to_str(Supply[i].amountPerPerson))/2),MINDIMY+7+i);
		cout << Supply[i].amountPerPerson;
		SetConsoleTextAttribute(hOut, 15);	
	}
}

void refreshRecipientsList(){
	Recipient.clear();
	readRecipient();
}
void refreshSuppliesList(){
	Supply.clear();
	readSuppliesList();
}
void saveSuppliesFile(){
	ofstream PrintFile;
	PrintFile.open(SuppliesFile.c_str(), ios::out);
	for(int i=0; i<Supply.size();i++){
		PrintFile  << Supply[i].name << "\t" << Supply[i].amount << "\t" << Supply[i].amountPerPerson << endl;
	}
	PrintFile.close();
}
void saveRecipientFile(){
	ofstream PrintFile;
	PrintFile.open(RecipientsFile.c_str(), ios::out);
	
	for(int i=0; i<Recipient.size();i++){
		PrintFile << Recipient[i].firstName << "\t" << Recipient[i].lastName << "\t" << Recipient[i].age << "\t" << Recipient[i].queueNumber << endl;
	}
	PrintFile.close();
}

