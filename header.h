#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <algorithm>

using namespace std;

//main.cpp
void getQueue(int *currentQueue, int *lastQueue);
int selectMode(bool homeScreen);
void QSBorder(bool direction);
void printMiniHeader();

//mainStructure.cpp
void readRecipient();
void addRecipient(int *currentQueue, int *lastQueue);
void nextRecipient(int *currentQueue, int *lastQueue);
void readSuppliesList();
void addSupply();
bool checkSupply();
void printSuppliesList();
void printRecipientsList();
void refreshSuppliesList();
void refreshRecipientsList();
void refreshSuppliesList();
void saveSuppliesFile();
void saveRecipientFile();
int charCount(string string);
string to_str(double i);
void deleteSupply();

//locationFinder.cpp
string Capitalize(string str);
string nameCase(string text);
void locationFinder();
void getIsland(bool homeScreen);
void gotoxy(int x, int y);
void printResult(int start, int end, int previousVertex[],int minimumDistance[], struct Vertex Vertices[], int connectedVertices[], int maxVertexCount);
void clearLine(int columnstart, int columnend, int rowstart, int rowend);


#define MINDIMX 0
#define MINDIMY 0
#define MAXDIMX 155
#define MAXDIMY 43

#define MINBORDERDIMX MAXDIMX/3
#define MINRORDERDIMY MINDIMY+1
#define MAXBORDERDIMX MAXDIMX-MAXDIM
#define MAXBORDERDIMY MINBORDERDIMX+150
#define offset 2

struct recipientsList{
	string firstName;
	string lastName;
	int age;
	int queueNumber;
};

struct SuppliesList{
	string name;
	double amount;
	double amountPerPerson;
};

extern vector<recipientsList> Recipient;
extern vector<SuppliesList> Supply;
extern string RecipientsFile, SuppliesFile, AdjacencyFile, VerticesFile;

