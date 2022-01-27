//Equivalent to Djikstra's algorithm from programming exercise 12

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <conio.h>
#include<windows.h>
#include <vector>
#include <algorithm>

#define offset 2
	
using namespace std;

#include "header.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
vector<string> citiesList;
string selectedIsland;

struct Vertex {
  	string Location, subLocation;
	int locationIndex, plotX, plotY;
};

void newVertex(struct Vertex Vertices[], string Location, string subLocation, int locationIndex, int plotX, int plotY) {
   struct Vertex* vertex = new Vertex; 
   	vertex->Location = Location;
  	vertex->subLocation = subLocation;
	vertex->locationIndex = locationIndex;	
	vertex->plotX = plotX;
	vertex->plotY = plotY;
   	Vertices[locationIndex] = *vertex;
}

void newConnection(int tempVal, int *connectedVertices, int index) {
   connectedVertices[index] = tempVal;
}

void gotoxy(int x, int y){ 
    HANDLE screen = GetStdHandle( STD_OUTPUT_HANDLE );
    COORD max_size = GetLargestConsoleWindowSize( screen );

    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition( screen, pos );
}

int lineCount(string AdjacencyFile){
	int count=0;
	string myText;
  	ifstream MyReadFile(AdjacencyFile.c_str());

 	while (getline (MyReadFile, myText)) {
    	++count;
  	}
  	MyReadFile.close();
  	return count;
}
int minimumDistanceIndex(int minimumDistance[], bool visitedVertex[], int maxVertexCount) {
	int min=INT_MAX,index;
	for(int i=0;i<maxVertexCount;i++) {
		if(visitedVertex[i]==false && minimumDistance[i]<=min){
			min=minimumDistance[i];
			index=i;
		}
	}
	return index;
}

void djikstrasAlgorithm(int connectedVertices[],int start, int end, int maxVertexCount, struct Vertex Vertices[]){
	int minimumDistance[maxVertexCount];     
	bool visitedVertex[maxVertexCount];
	int previousVertex[maxVertexCount];
	
	for(int i = 0; i<maxVertexCount; i++){
		minimumDistance[i] = INT_MAX;
		visitedVertex[i] = false;	
		previousVertex[i]=INT_MAX;
	}
	
	minimumDistance[start] = 0;      
	for(int count = 0; count<maxVertexCount; count++){
		int currentVertex=minimumDistanceIndex(minimumDistance,visitedVertex, maxVertexCount); 
		visitedVertex[currentVertex]=true;
		for(int cols = 0; cols<maxVertexCount; cols++){
			if(!visitedVertex[cols] && connectedVertices[(currentVertex*maxVertexCount)+cols]!=0 && minimumDistance[currentVertex]!=INT_MAX && minimumDistance[currentVertex]+connectedVertices[(currentVertex*maxVertexCount)+cols]<minimumDistance[cols]){
				minimumDistance[cols]=minimumDistance[currentVertex]+connectedVertices[(currentVertex*maxVertexCount)+cols];
				previousVertex[cols] = currentVertex;
			}
		}
	}
	printResult(start,end,previousVertex,minimumDistance,Vertices,connectedVertices, maxVertexCount);
}

string Capitalize(string str){ //IGNORE CASE
	int length = str.length();
  	str[0]=toupper(str[0]);
  	for(int i=1;i<length;i++){
  		str[i]=toupper(str[i]);
	}
  	for(int i=0;i<length;i++){
      	if(str[i]==' '){
          str[i+1]=toupper(str[i+1]);
      	}
  	}
 	return str;
}

string nameCase(string text) {
	for (int i=0;i<text.length(); i++){
		if (i==0){
			text[i]=toupper(text[i]);
		}
		else if (text[i-1]==' '){
			text[i]=toupper(text[i]);
		}
		else{
			text[i]=tolower(text[i]);
		}
	}
	int pos = text.find_first_not_of(' ');
	return text.substr(pos!=string::npos?pos:0);
}


int search(struct Vertex Vertices[], string locationChoice, string subLocationChoice, int maxVertexCount, int switchCase, int row){
	string ilMessage="Invalid location.";
	//Linear Search Algorithm
	for(int i=0;i<maxVertexCount;i++){
		switch(switchCase){
			case 1:
				if(Capitalize(Vertices[i].Location)==(locationChoice=Capitalize(locationChoice))){
					return Vertices[i].locationIndex;
				}
				break;
			case 2:
				if(Capitalize(Vertices[i].Location)==(locationChoice=Capitalize(locationChoice))&&(Capitalize(Vertices[i].subLocation)==(subLocationChoice=Capitalize(subLocationChoice))||(atoi(subLocationChoice.c_str())==Vertices[i].locationIndex&&i!=0))){
					return Vertices[i].locationIndex;
				}
				break;
		}
	}
	
	SetConsoleTextAttribute(hConsole, 12);
	gotoxy((MAXDIMX-MINDIMX)/6-(ilMessage.size()/2),row);
	cout << ilMessage;
	SetConsoleTextAttribute(hConsole, 15);
	return -1;	

}
	
void printArrow(struct Vertex Vertices[], int connectedVertices[], int maxVertexCount, int i, int j){
	//PRINTS PATHS
	if(j==-1||i==-1){
		return;
	}
	int minPathX=0, maxPathX=0, minPathY=0, maxPathY=0;
	if(connectedVertices[i*maxVertexCount+j]!=0){
		//ARROWS THAT ARE DIRECTED AT 2ND AND 4TH QUADRANT
		if((Vertices[i].plotX<Vertices[j].plotX&&Vertices[i].plotY<Vertices[j].plotY)||(Vertices[i].plotX>Vertices[j].plotX&&Vertices[i].plotY>Vertices[j].plotY)){
			if(Vertices[i].plotX>Vertices[j].plotX){
				minPathX=Vertices[j].plotX;
				maxPathX=Vertices[i].plotX;
			}
			else{
				minPathX=Vertices[i].plotX;
				maxPathX=Vertices[j].plotX;
			}
			if(Vertices[i].plotY>Vertices[j].plotY){
				minPathY=Vertices[j].plotY;
				maxPathY=Vertices[i].plotY;
			}
			else{
				minPathY=Vertices[i].plotY;
				maxPathY=Vertices[j].plotY;
			}
			while(minPathX<maxPathX||minPathY<maxPathY){
				gotoxy(minPathX+offset,minPathY);
				
				if(minPathX==maxPathX){
					cout << "|";
					minPathY+=1;
					continue;
				}
				if(minPathY==maxPathY){
					cout << "--";
					minPathX+=1;
					continue;
				}
					minPathX+=1;
					minPathY+=1;
					cout << "\\";
			}
		}
		
		//ARROWS THAT ARE DIRECTED AT 1ST AND 3RD QUADRANT
		else if((Vertices[i].plotX>Vertices[j].plotX&&Vertices[i].plotY<Vertices[j].plotY)||(Vertices[i].plotX<Vertices[j].plotX&&Vertices[i].plotY>Vertices[j].plotY)){
			if(Vertices[i].plotX<Vertices[j].plotX){
				minPathX=Vertices[i].plotX;
				maxPathX=Vertices[j].plotX;
			}
			else{
				minPathX=Vertices[j].plotX;
				maxPathX=Vertices[i].plotX;
			}
			if(Vertices[i].plotY>Vertices[j].plotY){
				minPathY=Vertices[j].plotY;
				maxPathY=Vertices[i].plotY;
			}
			else{
				minPathY=Vertices[i].plotY;
				maxPathY=Vertices[j].plotY;
			}
			
			int distanceY=(abs(minPathY-maxPathY))/15;
			int distanceX=(abs(maxPathX-minPathX))/15;
			if(distanceX==0){
				distanceX=1;
			}
			if(distanceY==0){
				distanceY=1;
			}
			while(minPathX<maxPathX||minPathY<maxPathY){
				gotoxy(minPathX+offset,maxPathY);
				
				if(minPathX==maxPathX){
					cout << "|";
					maxPathY--;
					continue;
				}
				if(minPathY==maxPathY){
					cout << "--";
					minPathX++;
					continue;
				}
				cout << "/";
				minPathX+=1;
				maxPathY-=1;
			}
		}
		//ARROWS THAT ARE DIRECTED VERTICALLY
		else if(Vertices[i].plotX==Vertices[j].plotX){
			if(Vertices[i].plotY>Vertices[j].plotY){
				minPathY=Vertices[j].plotY;
				maxPathY=Vertices[i].plotY;
			}
			else{
				minPathY=Vertices[i].plotY;
				maxPathY=Vertices[j].plotY;
			}
			while(minPathY<maxPathY){
				gotoxy(Vertices[i].plotX+offset,minPathY);
				cout << "|";
				minPathY+=1;
			}
		}
		//ARROWS THAT ARE DIRECTED HORIZONTALLY
		else if(Vertices[i].plotY==Vertices[j].plotY){
			if(Vertices[i].plotX>Vertices[j].plotX){
				minPathX=Vertices[j].plotX;
				maxPathX=Vertices[i].plotX;
			}
			else{
				minPathX=Vertices[i].plotX;
				maxPathX=Vertices[j].plotX;
			}
			while(minPathX<maxPathX){
				gotoxy(minPathX+offset,Vertices[i].plotY);
				cout << "--";
				minPathX+=1;
			}
		}
		else{
			system("cls");
			gotoxy(0,0);
			cout <<"WALANG GUMANA";
			return;
		}
	}
}
void printMap(struct Vertex Vertices[], int connectedVertices[], int maxVertexCount){
	for(int i=0; i<maxVertexCount; i++){
		for(int j=0; j<maxVertexCount;j++){
			printArrow(Vertices, connectedVertices, maxVertexCount, i, j);
		}
	}
	for(int i=0;i<citiesList.size();i++){
		SetConsoleTextAttribute(hConsole, i+1);	
		for(int j=0; j<maxVertexCount;j++){
			if(citiesList[i]==Vertices[j].Location){
				gotoxy(Vertices[j].plotX,Vertices[j].plotY);
				cout << Vertices[j].subLocation << "(" << Vertices[j].locationIndex <<")";
			}
		}
	}
	SetConsoleTextAttribute(hConsole, 15);	
}

string minutesToHours(int minutes){
	string temp;
	if(minutes<60){
		temp = to_str(minutes) + " minutes";
	}
	else if(minutes%60==0){
		if(minutes==60){
			temp = to_str(minutes/60) + " hour";
		}
		else{
			temp = to_str(minutes/60) + " hours";
		}
	}
	else if(minutes>60){
		if(minutes/60==1){
			temp = to_str(minutes/60) + " hour";
		}
		else{
			temp = to_str(minutes/60) + " hours";
		}
		temp = temp + " and " + to_str(minutes%60) + " minutes";
	}
	return temp;
}

void printResult(int start, int end, int previousVertex[],int minimumDistance[], struct Vertex Vertices[], int connectedVertices[], int maxVertexCount){
	vector<string> resultsList;
	
	string eMessage="The two locations points to itself ";
	string e1Message="or does not have any available path.";
	string cpMessage="CALCULATED ROUTE:";
	string tnMessage="TOTAL TIME NEEDED:";
	string wMessage="Press a key to continue...";
	
	if(previousVertex[end]==INT_MAX){
		gotoxy((MAXDIMX-MINDIMX)/6-(eMessage.size()/2),(MAXDIMY)/5+7);
		cout << eMessage;
		gotoxy((MAXDIMX-MINDIMX)/6-(e1Message.size()/2),(MAXDIMY)/5+8);
		cout << e1Message;
		gotoxy((MAXDIMX-MINDIMX)/6-(wMessage.size()/2),(MAXDIMY)/5+10);
		cout << wMessage;
		getch();
		clearLine(MINDIMX,(MAXDIMX-MINDIMX)/6,3*(MAXDIMY-MINDIMY)/4,MAXDIMY-1);
		return;
	}
	
	clearLine(MINDIMX, (MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/5+6,(MAXDIMY-MINDIMY));
	
	gotoxy((MAXDIMX-MINDIMX)/6-(cpMessage.size()/2),(MAXDIMY)/5+6);
	cout << cpMessage;
	
	int current=end, previous=-1; 
	SetConsoleTextAttribute(hConsole, 240);	
	while(current!=start){ 
		printArrow(Vertices, connectedVertices, maxVertexCount, current, previous);
		gotoxy(Vertices[previous].plotX, Vertices[previous].plotY);
		if(previous!=-1){
			cout << Vertices[previous].subLocation;
		}
		gotoxy(Vertices[current].plotX, Vertices[current].plotY);
		cout << Vertices[current].subLocation;
		resultsList.push_back(Vertices[current].subLocation + " (" + Vertices[current].Location + ") ");
		previous = current;
		current = previousVertex[current];
	}
	printArrow(Vertices, connectedVertices, maxVertexCount, start, previous);
	gotoxy(Vertices[previous].plotX, Vertices[previous].plotY);
	cout << Vertices[previous].subLocation;
	gotoxy(Vertices[start].plotX, Vertices[start].plotY);
	cout << Vertices[start].subLocation;
	resultsList.push_back(Vertices[start].subLocation + " (" + Vertices[start].Location + ") ");
	reverse(resultsList.begin(), resultsList.end());
	
	SetConsoleTextAttribute(hConsole, 10);
	int i=0;
	for(i;i<resultsList.size();i++){
		gotoxy((MAXDIMX-MINDIMX)/6-(charCount(resultsList[i])/2),(MAXDIMY)/5+i+8);
		cout<< resultsList[i];
	}
	i++;
	SetConsoleTextAttribute(hConsole, 15);

	gotoxy((MAXDIMX-MINDIMX)/6-(tnMessage.size()/2),(MAXDIMY)/5+i+8);
	cout << tnMessage;
	i++;
	
	SetConsoleTextAttribute(hConsole, 10);
	string timeRequired=minutesToHours(minimumDistance[end]);
	gotoxy((MAXDIMX-MINDIMX)/6-(timeRequired.size()/2),(MAXDIMY)/5+i+8);
	cout << timeRequired;
	i+=2;
	SetConsoleTextAttribute(hConsole, 15);
	
	gotoxy((MAXDIMX-MINDIMX)/6-(wMessage.size()/2),(MAXDIMY)/5+i+8);
	cout << wMessage;
	getch();
	clearLine(MINDIMX,(MAXDIMX-MINDIMX)/6,3*(MAXDIMY-MINDIMY)/4,MAXDIMY-1);
	return;
}


int getCityIndex(string Location){
	for(int i=0;citiesList.size(); i++){
		if(Location==citiesList[i]){
			return i;
		}
	}
}

void printLocationGuide(){
	string lmMessage="LIST OF MUNICIPALITIES IN";
	gotoxy((MAXDIMX-MINDIMX)/6-(lmMessage.size()/2),2*(MAXDIMY-MINDIMY)/4+0);
	cout << lmMessage;
	gotoxy((MAXDIMX-MINDIMX)/6-(selectedIsland.size()/2),2*(MAXDIMY-MINDIMY)/4+1);
	cout << selectedIsland;
	
	int row=2*(MAXDIMY-MINDIMY)/4+2, column=(MAXDIMX/12);
	int row2=2*(MAXDIMY-MINDIMY)/4+2;
	
	if(citiesList.size()<(MAXDIMY-MINDIMY)/4-2){
		for(int i=0; i<citiesList.size();i++){
			SetConsoleTextAttribute(hConsole, i+1);
			gotoxy(MAXDIMX/6-(charCount(citiesList[i])/2), row++);
			cout << citiesList[i];
		}
	}
	else{
		for(int i=0; i<citiesList.size();i++){
			SetConsoleTextAttribute(hConsole, i+1);
			if(i<(MAXDIMY-MINDIMY)/4-2){
				gotoxy(MAXDIMX/12-(charCount(citiesList[i])/2), row++);
			}
			else if (i>=(MAXDIMY-MINDIMY)/4-2){
				column=3*(MAXDIMX/12);
				gotoxy(column-(charCount(citiesList[i])/2), row2++);
			}
			cout << citiesList[i];
		}
	}
	
	SetConsoleTextAttribute(hConsole, 15);
}


void printSubLocationGuide(struct Vertex Vertices[], int maxVertexCount, string Location){
	int index=0, color;
	color=getCityIndex(Location)+1;
	SetConsoleTextAttribute(hConsole, 15);
	
	string lbMessage="LIST OF BARANGAYS IN";
	gotoxy((MAXDIMX-MINDIMX)/6-(lbMessage.size()/2),3*(MAXDIMY)/4+0);
	cout << lbMessage;
	
	gotoxy((MAXDIMX-MINDIMX)/6-(Location.size()/2),3*(MAXDIMY)/4+1);
	cout << Location;

	SetConsoleTextAttribute(hConsole, color);
	
	int row=3*(MAXDIMY-MINDIMY)/4+2, column=(MAXDIMX/12);
	int row2=3*(MAXDIMY-MINDIMY)/4+2;
	
	for(int i=0; i<maxVertexCount;i++){
		if(Location==Vertices[i].Location){
			if(i<(MAXDIMY-MINDIMY)/4-2){
				gotoxy(MAXDIMX/12-(charCount(Vertices[i].subLocation)/2), row++);
			}
			else if (i>=(MAXDIMY-MINDIMY)/4-2){
				column=3*(MAXDIMX/12);
				gotoxy(column-(charCount(Vertices[i].subLocation)/2), row2++);
			}
			cout << Vertices[i].subLocation << "(" << Vertices[i].locationIndex <<")";
			gotoxy(Vertices[i].plotX, Vertices[i].plotY);
			cout << Vertices[i].subLocation << "(" << Vertices[i].locationIndex <<")";
		}
	}
	SetConsoleTextAttribute(hConsole, 15);
}

void getIsland(bool homeScreen){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	string islands[3]={"Masbate","Mindoro","Samar"}; //Subject to change
	string askIsland="Press the key of the chosen province.";
	string choiceError="Invalid choice.  Please try again.";
	string successMessage="Success!";
	string waitKey="Press any key to continue...";
	string csMessage="Currently Selected:";
	
	if(homeScreen){
		gotoxy(3*(MAXDIMX-MINDIMX)/4-(askIsland.length()/2),3*((MAXDIMY-MINDIMY)/4)-5);
		cout << askIsland;
		
		for(int i=0; i<sizeof(islands)/sizeof(islands[0]);i++){
			gotoxy(3*(MAXDIMX-MINDIMX)/4-(islands[i].length()/2),3*((MAXDIMY-MINDIMY)/4)-2+i);
			cout << "[" << i+1 << "]" << islands[i];
		}
	}
	else{
		gotoxy((MAXDIMX-MINDIMX)/6-(askIsland.length()/2),((MAXDIMY-MINDIMY)/4));
		cout << askIsland;
		
		gotoxy((MAXDIMX-MINDIMX)/6-(csMessage.length()/2),((MAXDIMY-MINDIMY)/4)+1);
		cout << csMessage;
		
		SetConsoleTextAttribute(hOut, 10);
		gotoxy((MAXDIMX-MINDIMX)/6-(selectedIsland.length()/2),((MAXDIMY-MINDIMY)/4)+2);
		cout << selectedIsland;
		SetConsoleTextAttribute(hOut, 15);
		
		for(int i=0; i<sizeof(islands)/sizeof(islands[0]);i++){
			gotoxy((MAXDIMX-MINDIMX)/6-(charCount(islands[i])/2)-2,((MAXDIMY-MINDIMY)/4)+5+i);
			cout << "[" << i+1 << "]" << islands[i];
		}
	}
	
	
	bool repeat=0;
	do{
		repeat=0;
		int choice = getch()-49;
		switch(choice){
			case 0:
			case 1:
			case 2:
				selectedIsland=islands[choice];
				SetConsoleTextAttribute(hOut, 240);	
				
				if(homeScreen){
					gotoxy(3*(MAXDIMX-MINDIMX)/4-(islands[choice].length()/2),3*((MAXDIMY-MINDIMY)/4)-2+choice);
				}
				else{
					gotoxy((MAXDIMX-MINDIMX)/6-(islands[choice].length()/2)-2,((MAXDIMY-MINDIMY)/4)+5+choice);
				}
				cout << "[" << choice+1 << "]" << islands[choice];
				AdjacencyFile= Capitalize(islands[choice])+"_Matrix.dat";
				VerticesFile = Capitalize(islands[choice])+"_Vertices.dat";
				RecipientsFile = Capitalize(islands[choice])+"_Recipients.dat";
				SuppliesFile = Capitalize(islands[choice])+"_Supplies.dat";
				
				break;
			default:
				SetConsoleTextAttribute(hOut, 12);	
				if(homeScreen){
					gotoxy(3*(MAXDIMX-MINDIMX)/4-(choiceError.length()/2),3*((MAXDIMY-MINDIMY)/4)-2+8);
				}
				else{
					gotoxy((MAXDIMX-MINDIMX)/6-(choiceError.length()/2),((MAXDIMY-MINDIMY)/4)+9);
				}
				cout << choiceError;
				repeat=1;
				SetConsoleTextAttribute(hOut, 15);
				break;
		}
	}while(repeat);
	SetConsoleTextAttribute(hOut, 0);
	if(homeScreen){
		gotoxy(3*(MAXDIMX-MINDIMX)/4-(choiceError.length()/2),3*((MAXDIMY-MINDIMY)/4)-2+8);
		cout << choiceError;
		SetConsoleTextAttribute(hOut, 10);
		gotoxy(3*(MAXDIMX-MINDIMX)/4-(successMessage.length()/2),3*((MAXDIMY-MINDIMY)/4)-2+8);
		cout << successMessage;
		SetConsoleTextAttribute(hOut, 15);
		gotoxy((MAXDIMX-MINDIMX)/2-(waitKey.length()/2),3*((MAXDIMY-MINDIMY)/4)-7);
		cout << waitKey;
		getch();	
	}
	else{
		clearLine(MINDIMX,(MAXDIMX-MINDIMX)/6-1,(MAXDIMY-MINDIMY)/4+8,(MAXDIMY-MINDIMY)/4+11);
		SetConsoleTextAttribute(hOut, 10);
		gotoxy((MAXDIMX-MINDIMX)/6-(successMessage.length()/2),((MAXDIMY-MINDIMY)/4)+9);
		cout << successMessage;
		SetConsoleTextAttribute(hOut, 15);
		gotoxy((MAXDIMX-MINDIMX)/6-(waitKey.length()/2),((MAXDIMY-MINDIMY)/4)+10);

		cout << waitKey;
		getch();
	}
} 

void clearLine(int columnstart, int columnend, int rowstart, int rowend){
	//Note that start and end values are inclusive
	for(int i=columnstart; i<=columnend; i++){
		for (int j=rowstart; j<=rowend; j++){
			gotoxy(i,j);
			cout <<" ";
		}
	}
	return;
}
 
void locationFinder() { //Equivalent to main cpp file
	citiesList.clear();
	
	//Determine max vertex count
	int maxVertexCount;
	if(lineCount(AdjacencyFile)==lineCount(VerticesFile)){
		maxVertexCount = lineCount(AdjacencyFile);
	}
	else{
		cout << lineCount(AdjacencyFile);
		cout << lineCount(VerticesFile);
		cout << "Two files are not equal in size!  Make sure that there's no extra lines.";
		throw exception();
	}
	
	//ADJACENCY MATRIX
	//Note that 1d array is represented as a 2d array due to c++ can't support variable array sizes when passing 2d arrays
	int connectedVertices[maxVertexCount*maxVertexCount];
	int rows=0, cols=0;
	string line;
	ifstream ReadMatrix(AdjacencyFile.c_str());
	
	if(!ReadMatrix.is_open()) {
     	std::cout<<"File " << AdjacencyFile << " not found.  Make sure the .dat files are downloaded." << endl;
     	throw exception();
	}
	while(getline(ReadMatrix,line)){
	cols=0;
		istringstream is(line);
		int tempVal;
		while(is >>tempVal){
			int index=((rows*maxVertexCount)+cols);
			newConnection(tempVal, connectedVertices, index);	
			cols++;
		}
	rows++;
	}
	ReadMatrix.close();
	
	//VERTICES
	struct Vertex Vertices[maxVertexCount];
	ifstream ReadVertex(VerticesFile.c_str());
	if(!ReadVertex.is_open()) {
     std::cout<<"File " << VerticesFile << " not found.  Make sure the .dat files are downloaded." << endl;
     throw exception();
	}
	int locationIndex=0;
	while(getline(ReadVertex,line)){
		string vertexLocation, vertexsubLocation, tempString;
		int plotX, plotY;
		istringstream tempLine(line);
		getline(tempLine,vertexLocation,'\t');
		
		if(find(citiesList.begin(),citiesList.end(),vertexLocation)==citiesList.end()){
		citiesList.push_back(vertexLocation);
		}

		getline(tempLine,vertexsubLocation,'\t');
		getline(tempLine,tempString,'\t');
		plotX = atoi(tempString.c_str())+MAXDIMX/6;
		getline(tempLine,tempString,'\t');
		plotY = atoi(tempString.c_str())+MINDIMY;
		
		newVertex(Vertices,vertexLocation,vertexsubLocation,locationIndex,plotX,plotY);
		locationIndex++;
	}
	ReadVertex.close();

	//MAIN
	string choice;
	string locationChoice;
	string subLocationChoice;
	int initialIndex=-1, finalIndex=-1;
	


	system("cls");
	QSBorder(1);
	printMiniHeader();
	printLocationGuide();
	printMap(Vertices,connectedVertices,maxVertexCount);
	
	
	string idMessage="INITIAL DESTINATION";
	string fDMessage="FINAL DESTINATION";
	string ciMessage="Choose if:";
	string eaMessage="(A) Evacuation Area";
	string caMEssage="(B) Custom Destination";
	string cmMessage="Please select the municipality:";
	string cbMessage="Select the barangay in ";
	string iMessage="Invalid Key.";
	
	gotoxy((MAXDIMX-MINDIMX)/6-(idMessage.size()/2),(MAXDIMY)/5+0);
	cout << idMessage;
		
	gotoxy((MAXDIMX-MINDIMX)/6-(ciMessage.size()/2),(MAXDIMY)/5+1);
	cout << ciMessage;
		
	gotoxy((MAXDIMX-MINDIMX)/6-(eaMessage.size()/2),(MAXDIMY)/5+2);
	cout << eaMessage;
		
	gotoxy((MAXDIMX-MINDIMX)/6-(caMEssage.size()/2),(MAXDIMY)/5+3);
	cout << caMEssage;
	
	int mode;	
	do{
		mode = getch();
		switch(mode){
			case 65:
			case 97:
				clearLine(MINDIMX, (MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/5+1,(MAXDIMY)/5+4);
				initialIndex=0; 
				//Note that in vertices and connections file, the evacuation center is the first item
				gotoxy((MAXDIMX-MINDIMX)/6-(((charCount(Vertices[initialIndex].subLocation)+charCount(Vertices[initialIndex].Location))/2+2)),(MAXDIMY)/5+1);
				SetConsoleTextAttribute(hConsole, 10);
				cout << " " << Vertices[initialIndex].subLocation << "(" << Vertices[initialIndex].Location <<")";
				SetConsoleTextAttribute(hConsole, 15);
				break;
			case 66:
			case 98:
				//Initial Location
				clearLine(MINDIMX, (MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/5+1,(MAXDIMY)/5+4);
				gotoxy((MAXDIMX-MINDIMX)/6-(cmMessage.size()/2),(MAXDIMY)/5+1);
				cout << cmMessage;
				do{
					clearLine(MINDIMX, (MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/5+2,(MAXDIMY)/5+2);
					gotoxy((MAXDIMX-MINDIMX)/6-5,(MAXDIMY)/5+2);
					getline(cin,locationChoice);
					initialIndex=search(Vertices, locationChoice, subLocationChoice, maxVertexCount, 1,(MAXDIMY)/5+3);
				}while(initialIndex==-1);
				printSubLocationGuide(Vertices, maxVertexCount, Vertices[initialIndex].Location);
				
				//Initial Sublocation
				clearLine(MINDIMX, (MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/5+1,(MAXDIMY)/5+3);
				gotoxy((MAXDIMX-MINDIMX)/6-((cbMessage.size()+locationChoice.size())/2),(MAXDIMY)/5+1);
				cout << cbMessage << locationChoice;
				do{
					clearLine(MINDIMX, (MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/5+2,(MAXDIMY)/5+2);
					gotoxy((MAXDIMX-MINDIMX)/6-5,(MAXDIMY)/5+2);
					 getline(cin,subLocationChoice);
					initialIndex=search(Vertices, locationChoice, subLocationChoice, maxVertexCount, 2, (MAXDIMY)/5+3);
				}while(initialIndex==-1);
				
				clearLine(MINDIMX, (MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/5+1,(MAXDIMY)/5+3);
				SetConsoleTextAttribute(hConsole, 10);
				gotoxy((MAXDIMX-MINDIMX)/6-(charCount(Vertices[initialIndex].subLocation)+charCount(Vertices[initialIndex].Location)+2)/2,(MAXDIMY)/5+1);
				cout << Vertices[initialIndex].subLocation << "(" << Vertices[initialIndex].Location << ")";
				SetConsoleTextAttribute(hConsole, 15);
				break;
			default:
				gotoxy((MAXDIMX-MINDIMX)/6-iMessage.size()/2,(MAXDIMY)/5+4);
				SetConsoleTextAttribute(hConsole, 12);
				cout << iMessage;
				mode =-1;
				SetConsoleTextAttribute(hConsole, 15);
				break;
		}
	}while(mode==-1);
	
	
	gotoxy((MAXDIMX-MINDIMX)/6-(fDMessage.size()/2),(MAXDIMY)/5+3);
	cout << fDMessage;
	
	int mode1=-1;
	do{ //65 97 EVAC 66 98 CUSTOM
		if(mode==66||mode==98){
			gotoxy((MAXDIMX-MINDIMX)/6-(ciMessage.size()/2),(MAXDIMY)/5+4);
			cout << ciMessage;
		
			gotoxy((MAXDIMX-MINDIMX)/6-(eaMessage.size()/2),(MAXDIMY)/5+5);
			cout << eaMessage;
		
			gotoxy((MAXDIMX-MINDIMX)/6-(caMEssage.size()/2),(MAXDIMY)/5+6);
			cout << caMEssage;
		
			mode1 = getch();
		}
		if(mode==65||mode==97){
			mode1=66;
		}
		switch(mode1){
			case 65:
			case 97:
				clearLine(MINDIMX, (MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/5+4,(MAXDIMY)/5+6);
				finalIndex=0; 
				//Note that in vertices and connections file, the evacuation center is the first item
				gotoxy((MAXDIMX-MINDIMX)/6-(((charCount(Vertices[finalIndex].subLocation)+charCount(Vertices[finalIndex].Location))/2+2)),(MAXDIMY)/5+4);
				SetConsoleTextAttribute(hConsole, 10);
				cout << " " << Vertices[finalIndex].subLocation << "(" << Vertices[finalIndex].Location <<")";
				SetConsoleTextAttribute(hConsole, 15);
				mode=0;
				break;
			case 66:
			case 98:
				//Final Location
				clearLine(MINDIMX, (MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/5+4,(MAXDIMY)/5+7);
				gotoxy((MAXDIMX-MINDIMX)/6-cmMessage.size()/2,(MAXDIMY)/5+4);
				cout << cmMessage;
				do{
					clearLine(MINDIMX, (MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/5+5,(MAXDIMY)/5+5);
					gotoxy((MAXDIMX-MINDIMX)/6-5,(MAXDIMY)/5+5);
					getline(cin,locationChoice);
					finalIndex=search(Vertices, locationChoice, subLocationChoice, maxVertexCount, 1,(MAXDIMY)/5+6);
				}while(finalIndex==-1);
				clearLine(MINDIMX, (MAXDIMX-MINDIMX)/3-1,3*(MAXDIMY)/4,(MAXDIMY));
				printSubLocationGuide(Vertices, maxVertexCount, Vertices[finalIndex].Location);
			
				//Final Sublocation
				clearLine(MINDIMX, (MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/5+4,(MAXDIMY)/5+7);
				gotoxy((MAXDIMX-MINDIMX)/6-((cbMessage.size()+locationChoice.size())/2),(MAXDIMY)/5+4);
				cout << cbMessage << locationChoice;
				do{
					clearLine(MINDIMX, (MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/5+5,(MAXDIMY)/5+5);
					gotoxy((MAXDIMX-MINDIMX)/6-5,(MAXDIMY)/5+5);
					getline(cin,subLocationChoice);
					finalIndex=search(Vertices, locationChoice, subLocationChoice, maxVertexCount, 2, (MAXDIMY)/5+6);
				}while(finalIndex==-1);
				
				clearLine(MINDIMX, (MAXDIMX-MINDIMX)/3-1,(MAXDIMY)/5+4,(MAXDIMY)/5+6);
				SetConsoleTextAttribute(hConsole, 10);
				gotoxy((MAXDIMX-MINDIMX)/6-(charCount(Vertices[finalIndex].subLocation)+charCount(Vertices[finalIndex].Location)+2)/2,(MAXDIMY)/5+4);
				cout << Vertices[finalIndex].subLocation << "(" << Vertices[finalIndex].Location << ")";
				SetConsoleTextAttribute(hConsole, 15);
				break;
			default:
				gotoxy((MAXDIMX-MINDIMX)/6-iMessage.size()/2,(MAXDIMY)/5+7);
				SetConsoleTextAttribute(hConsole, 12);
				cout << iMessage;
				mode1 =-1;
				SetConsoleTextAttribute(hConsole, 15);
				break;
		}
	}while(mode1==-1);

	djikstrasAlgorithm(connectedVertices,initialIndex,finalIndex,maxVertexCount,Vertices);
		
	return;
}



