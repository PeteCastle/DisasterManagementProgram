/*
Class Group Case Project Study
Due January 11, 2022 1:00 PM

Instructions:
This is a group work case project study.
Your group will chose the topic for your case project.
The topic should be related with our subject in data structures.
Your group will create a Project Application using the different topics you have learned in data structures
Your project should be the combination of the different topics and subject matters in our class in data structures.

CPE 0211.1 Data Structures and Algorithms (lab)
	Group 5
		CAYCO, Francis Mark M. 
		MERCULIO, Miraiza Elisa V. 
		SOLIVEN, Reynel N. 
		PEREZ, Kelvin Eldeson D. 
		VILLAR, Helen Claire J.

Dr. Ronaldo A. Tan, LPT
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include "header.h"

int homeScreen(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	string logo[7];
	

	logo[0]="DDDDD   iii                     tt                     MM    MM                                                                   tt    "; //FIX
	logo[1]="DD  DD       sss    aa aa  sss  tt      eee  rr rr     MMM  MMM   aa aa nn nnn    aa aa  gggggg   eee  mm mm mmmm    eee  nn nnn  tt    ";
	logo[2]="DD   DD iii s      aa aaa s     tttt  ee   e rrr  r    MM MM MM  aa aaa nnn  nn  aa aaa gg   gg ee   e mmm  mm  mm ee   e nnn  nn tttt  ";
	logo[3]="DD   DD iii  sss  aa  aaa  sss  tt    eeeee  rr        MM    MM aa  aaa nn   nn aa  aaa ggggggg eeeee  mmm  mm  mm eeeee  nn   nn tt    ";
	logo[4]="DDDDDD  iii     s  aaa aa     s  tttt  eeeee rr        MM    MM  aaa aa nn   nn  aaa aa      gg  eeeee mmm  mm  mm  eeeee nn   nn  tttt ";
	logo[5]="             sss           sss                                                           ggggg                                          ";
	
	logo[6]="Tayo, Kabayan"; //TAGLINE PART
	
	
	SetConsoleTextAttribute(hOut, 14);
	for(int i=0;i<sizeof(logo)/sizeof(logo[0]);i++){
		gotoxy((MAXDIMX-MINDIMX)/2-(logo[i].size()/2),(MAXDIMY-MINDIMY)/2-((sizeof(logo)/sizeof(logo[0]))/2)-5+i);
		cout << logo[i];
	}
	SetConsoleTextAttribute(hOut, 15);
	
	string waitKey="Press any key to continue...";
	string choiceError="Press the key of your choice.  Please try again.";
	string successMessage="Success!";
	
	gotoxy((MAXDIMX-MINDIMX)/2-(waitKey.length()/2),3*((MAXDIMY-MINDIMY)/4)-7);
	cout << waitKey;
	int temp = getch();
	SetConsoleTextAttribute(hOut, 0);
	gotoxy((MAXDIMX-MINDIMX)/2-(waitKey.length()/2),3*((MAXDIMY-MINDIMY)/4)-7);
	cout << waitKey;
	
	int mode = selectMode(1);
	SetConsoleTextAttribute(hOut, 0);
	gotoxy((MAXDIMX-MINDIMX)/4-(choiceError.length()/2),3*((MAXDIMY-MINDIMY)/4)-2+8);
	cout << choiceError;
	SetConsoleTextAttribute(hOut, 10);
	gotoxy((MAXDIMX-MINDIMX)/4-(successMessage.length()/2),3*((MAXDIMY-MINDIMY)/4)-2+8);
	cout << successMessage;
	SetConsoleTextAttribute(hOut, 15);

	getIsland(1);
	
	return mode;
}

void printMiniHeader(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	string miniHeader[5];
	miniHeader[0]="     dBBBBb  dBBBBBBb dBBBBBb";
    miniHeader[1]="    dB'   '   dB'     dB'    ";
	miniHeader[2]="   dBP dB' dB'dB'dB'  dBBBP' ";
	miniHeader[3]="  dBP dB' dB'dB'dB'  dBP     ";
	miniHeader[4]=" dBBBBB' dB'dB'dB'  dBP      ";
	miniHeader[4]=" DISASTER MANAGEMENT PROGRAM ";
	SetConsoleTextAttribute(hOut, 96);
	for(int i=0;i<sizeof(miniHeader)/sizeof(miniHeader[0]);i++){
		gotoxy((MAXDIMX-MINDIMX)/6-(miniHeader[i].size()/2),(MINDIMY)+2+i);
		cout << miniHeader[i];
	}
	SetConsoleTextAttribute(hOut, 15);
}

int selectMode(bool homeScreen){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	string waitQuestion="What would you like to do?";
	string waitQuestion1="What would you like to do next?";
	
	string choices[9]={"[F1] Add Recipient", 
						"[F2] Next Recipient", 
						"[F3] View Recipients", 
						"[F4] Add Supply",
						"[F5] Remove Supply",
						"[F6] View Supplies",
						"[F7] Location Finder",
						"[F8] Change Location",
						"[F9] Exit the Program"};
	
	SetConsoleTextAttribute(hOut, 15);
	if(homeScreen){
		gotoxy((MAXDIMX-MINDIMX)/4-(waitQuestion.length()/2),3*((MAXDIMY-MINDIMY)/4)-5);
		cout << waitQuestion;
	}
	else{
		gotoxy((MAXDIMX-MINDIMX)/6-(waitQuestion1.length()/2),3*(MAXDIMY-MINDIMY)/4);
		cout << waitQuestion1;
	}
	
	for(int i=0; i<sizeof(choices)/sizeof(choices[0]);i++){ ///sizeof(choices[0])
		if(homeScreen){
			gotoxy((MAXDIMX-MINDIMX)/4-(choices[i].length()/2),3*((MAXDIMY-MINDIMY)/4)-2+i);
			if(i>6){
				continue;
			}
		}
		else{
			gotoxy((MAXDIMX-MINDIMX)/6-(choices[i].length()/2),3*(MAXDIMY-MINDIMY)/4+1+i);
		}
		cout << choices[i];
	}
	
	int mode;
	bool repeat;
	string choiceError="Press the key of your choice.  Please try again.";
	string tyMessage="  Thank you for using our program!  ";
	do{
		repeat=0;
		int choice = getch()-59;
		
		switch(choice){
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				SetConsoleTextAttribute(hOut, 240);	
				if(homeScreen==1){
					gotoxy((MAXDIMX-MINDIMX)/4-(choices[choice].length()/2),3*((MAXDIMY-MINDIMY)/4)-2+choice);
				}
				else{
					
				}
				cout << choices[choice];
				mode=choice;
				SetConsoleTextAttribute(hOut, 15);
				break;
			case 7:
				if(!homeScreen){
					mode = choice;
					break;
				}
			case 8:
				SetConsoleTextAttribute(hOut, 10);	
				if(!homeScreen){
					clearLine(MINDIMX,(MAXDIMX-MINDIMX)/3-1,MAXDIMY-2,MAXDIMY);
					gotoxy((MAXDIMX-MINDIMX)/6-(tyMessage.length()/2),(MAXDIMY-MINDIMY)-2);
					cout << tyMessage;
					mode=-1;
					SetConsoleTextAttribute(hOut, 15);
					break;
				}
			default:
				SetConsoleTextAttribute(hOut, 12);	
				if(homeScreen==1){
					gotoxy((MAXDIMX-MINDIMX)/4-(choiceError.length()/2),3*((MAXDIMY-MINDIMY)/4)-2+8);
				}
				else{
					gotoxy((MAXDIMX-MINDIMX)/6-(choiceError.length()/2),(MAXDIMY-MINDIMY)-2);
				}
				cout << choiceError;
				repeat=1;
				SetConsoleTextAttribute(hOut, 15);
				break;
		}
	}while(repeat);
	return mode;
}

void QSBorder(bool direction){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	string queue = "               QUEUE               ", supplies="               SUPPLIES               ";
	string name="NAME",amount="AMOUNT",amountpp="PER PERSON";
	string queuenum="#",fname="FIRST NAME",lname="LAST NAME", age="AGE";
	
	if(!direction){
		SetConsoleTextAttribute(hOut, 112);		
		gotoxy((MAXDIMX/2)-(queue.length()/2),MINDIMY+2);
		cout << queue;
		gotoxy(15*MAXDIMX/18-(supplies.length()/2),MINDIMY+2); //(supplies.length()/2)
		cout << supplies;
		SetConsoleTextAttribute(hOut, 15);	
		gotoxy(6*MAXDIMX/18+2, MINDIMY+5);
		cout << queuenum;
		gotoxy(7*MAXDIMX/18, MINDIMY+5);
		cout << fname;
		gotoxy(9*MAXDIMX/18, MINDIMY+5);
		cout << lname;
		gotoxy(11*MAXDIMX/18, MINDIMY+5);
		cout << age;
		gotoxy(13*MAXDIMX/18-(name.length()/2),MINDIMY+5);
		cout << name;
		gotoxy(15*MAXDIMX/18-(amount.length()/2),MINDIMY+5);
		cout << amount;
		gotoxy(17*MAXDIMX/18-(amountpp.length()/2),MINDIMY+5);
		cout << amountpp;
	}
	for(int i=MINDIMY+1;i<MAXDIMY-1;i++){
		gotoxy(MAXDIMX/3,i);
		cout << "|";
		if(!direction){
			gotoxy(MAXDIMX/3+MAXDIMX/3,i);
			cout << "|";
		}
		gotoxy(MAXDIMX-1,i);
		cout << "|";
	}
	for (int i=MAXDIMX/3;i<MAXDIMX;i++){
		gotoxy(i,MINDIMY+1);
		cout << "=";
		if(!direction){
			gotoxy(i,MINDIMY+3);
			cout << "=";	
		}
		gotoxy(i,MAXDIMY-1);
		cout << "=";
	}
}



int main(){
	//Window Restraints
	HWND console = GetConsoleWindow();
 	RECT r;
  	GetWindowRect(console, &r); 
	MoveWindow(console, r.left, r.top, 1280	, 740, TRUE);
	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	
	//Prevents Window Scrolling
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD maxDimSize;
    maxDimSize.X = MAXDIMX;
    maxDimSize.Y = MAXDIMY;
    SetConsoleScreenBufferSize(hOut, maxDimSize);
    
	int mode = homeScreen(), currentQueue, lastQueue;
	system("cls");
	refreshRecipientsList();
	refreshSuppliesList();
	
	while(mode!=-1){
		if(mode!=6||mode!=7){
			refreshRecipientsList();
			refreshSuppliesList();
		}
		system("cls");
		
		QSBorder(0);
		printMiniHeader();
		switch(mode){
			case 0:
				printRecipientsList();
				getQueue(&currentQueue, &lastQueue);
				addRecipient(&currentQueue, &lastQueue);
				printRecipientsList();
				break;
			case 1:
				nextRecipient(&currentQueue, &lastQueue);
				printSuppliesList();
				printRecipientsList();
				break;
			case 2:
				printRecipientsList();
				break;
			case 3:
				printSuppliesList();
				addSupply();
				printSuppliesList();
				break;
			case 4:
				printSuppliesList();
				deleteSupply();
				printSuppliesList();
				break;
			case 5:
				printSuppliesList();
				break;
			case 6:
				locationFinder();
				break;
			case 7:
				printRecipientsList();
				printSuppliesList();
				getIsland(0);
				refreshRecipientsList();
				refreshSuppliesList();
				printRecipientsList();
				printSuppliesList();
				break;
			case 8:
				break;
				//Coded by: Francis Mark Cayco
				//Program will be available soon at https://github.com/PeteCastle/
			default:
				break;
		}	
		mode = selectMode(0);
	}
    return 0;                                                                                                                                             
}



