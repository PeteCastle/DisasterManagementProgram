# DisasterManagmentProgram
BACKGROUND OF THE PROJECT TOPIC

The modern world is ruled over by technology and inventions that take humanity to its peak capacity, but little do we notice that there is another player in this eternal development, the yin to the yang, and those are what we call natural phenomena or as we in the Philippines call it by the name we frighteningly live upon, Natural Disasters.

The Philippines, one of the number-one patrons of Natural Disasters in South-East Asia, considering its position in the Pacific Ring of Fire and in addition to this being adjoined by a massive mass of water (Pacific Ocean) makes the natural phenomena grow tenfold: disasters. It has also seen its fair share of calamities like Super Typhoons; Ondoy, Yolanda, the recent Odette, Destructive earthquakes in Bohol(1990), and Laoag (1983), Volcanic Eruptions like the famous Mayon Eruption, and special mention: will we ever forget this COVID-19 Pandemic which continues to haunt us until this day?

The main impetus of our Case Project Study is to serve our fellow countrymen. Not only to protect but also to cater to those who’ve fought their way through disasters with a steel heart, a trait which we Pinoys survive with. Our Project can be used in its current form when disasters hit and also serve as a footprint for those who’d want to improve it for the betterment of the Filipino people.


TOPICS AND SUBJECT MATTERS IN USED IN THE PROJECT

Searching Algorithms
Arrays
Structures
Pointers
Queues
File Manipulation








TOPICS AND SUBJECT: APPLICATIONS
	
Searching Algorithms
The program uses Linear Searching Algorithm to determine whether the user input is found in the array.   This is used in Location Finder - one of the highlighting features of the program - (1) when searching for the shortest path using Dijkstra's Algorithm; (2) asking for user’s input of a specific location and checking the array whether the location exists or not.  It is also used when searching for the available list of supplies.  If it exists, the user is meant to add a certain quantity of supplies.  If not, the program assumes it is a new item.  The algorithm is also present in other parts of the program.
int search(struct Vertex Vertices[], string locationChoice, string subLocationChoice, int maxVertexCount, int switchCase, int row){
	//Linear Search Algorithm
	for(int i=0;i<maxVertexCount;i++){
		switch(switchCase){
			case 1:	
                          if(//long if statement){
					return Vertices[i].locationIndex;
				}
				break;
			case 2:
                          if (//long if statement){
					return Vertices[i].locationIndex;
				}
				break;
		}
	}
}

Linear Search algorithm in determining whether the user input of location is present on the list.
Arrays and Vectors
The program uses arrays and vectors in order to store, add, and retrieve data (recipients, list of supplies, and list of locations).  
extern vector<recipientsList> Recipient;
extern vector<SuppliesList> Supply;
struct Vertex Vertices[maxVertexCount];
int connectedVertices[maxVertexCount*maxVertexCount];








Structures
Each recipient, supply, and location indices contain different types of information (such as name, quantity, age, province, barangay, and island) which is defined in the program through the use of structures.
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
struct Vertex {
  	string Location, subLocation;
	int locationIndex, plotX, plotY;
};


Queues
The program is used to serve the recipients using the First in, First Out algorithm.  The figure below shows the queue of a location in the Philippine island of Masbate.  The program also shows who the previous recipient is, the current recipient, and the next recipient.  Note that as more recipients are added to the list, their queue number is unique to them.







Pointers
Pointers are used in the program in conjunction with queues to serve the recipients while modifying the variable currentQueue and lastQueue across different methods as well as other features in graph-related functions.
void nextRecipient(int *currentQueue, int *lastQueue){ //Enqueue
	if(checkSupply()){
		return;
	}
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
      if(*currentQueue!=*lastQueue&&*lastQueue!=0&&!Recipient.empty()){
...


File Manipulation
Another key defining feature of this program is the use of Files Manipulation to save information for later use.  The program is designed to be used simultaneously across devices (assuming that everyone uses the same directory whether in local network or web) regardless of their location without any form of duplication and inaccurate amount of supplies.  Every time the list is modified, the file is automatically saved, and the program itself updates the list from the current file.
void saveRecipientFile(){
	ofstream PrintFile;
	PrintFile.open(RecipientsFile.c_str(), ios::out);
	
	for(int i=0; i<Recipient.size();i++){
		PrintFile << Recipient[i].firstName << "\t" << Recipient[i].lastName << "\t" << Recipient[i].age << "\t" << Recipient[i].queueNumber << endl;
	}
	PrintFile.close();
}
void readSuppliesList(){
	ifstream suppliesFile(SuppliesFile.c_str());
	string line;
	int i=0;
	if(!suppliesFile.is_open()) {
     	cout<<"File " << SuppliesFile << " not found.  Make sure the .dat files are downloaded." << endl;
     	throw exception();
	}
…

	








Graphs
	Since the program uses maps to search for the shortest path from either the evacuation center or user-defined location to a certain destination, the group uses graphs where each barangay (sublocation) is a vertex that is under a cluster called (location) or the municipality it belongs to.  The graph also contains a graphical view within the program itself (see coordinate system below).  

Map of SamarIsland

Other Data Structures
Coordinate System
The program uses a coordinate system that shows all available pathways from one location to another.  Each location has its own assigned X and Y coordinates.  Whereas, the lines that were shown are algorithmically designed to connect from one location to another depending on what was written in the adjacency matrix.  A sample map of Masbate is shown in the figure below.

Map of Samar Island within the Program

PROJECT BENEFITS
This project is an all-in-one solution that can be used inside bases wherein it will be operated by disaster volunteer groups in the Philippines for them to neatly arrange and queue recipients, monitor supply logistics, and locate evacuation centers in cities that were affected by the calamity. Overall, the true beneficiaries of this project are the struggling Filipinos especially in their time of need, serving the Filipino people.

In addition to this, the easily accessible and editable data files for supply logistics and map maker (vertices.dat, matrix.dat) can be easily modified to fit any place in the Philippines (like our previous NCR Map data files in our last project)

STEP BY STEP OPERATION
Upon opening the program, you are greeted and instructed to press a keyboard key of your choice:
[Function 1] Add Recipient - If you would like to add recipients to the queue
[Function 2] Next Recipient - Discards the current recipient in the queue and proceeds the next as to be received by the donations.
[Function 3] View Recipients - Simply lists the list of recipients (Including their First Name, Last Name, Age, and their number inline).  Note that the first in line (highlighted in green) is the current recipient.
[Function 4] Add Supply - This allows the user to add a supply of their choice, the total amount available, and the amount that will be given to each person.
[Function 5]  Remove Supply - Discards a supply that is present on the list.  Useful for duplicate inputs, typographical errors in name, or amount.
[Function 6] View Supplies - Lists the number of supplies available.  Colors in yellow represent that the amount of supply is low and needs to be replenished soon.  Meanwhile, the red color represents that the supply is empty.
[Function 7]  Location Finder - this part locates for the nearest place of a user’s choice (whether the evacuation area or other) from a specified location.
[Function 8] Change Location (Only available after choosing a location) - This allows the user to change the location of the program.  Note that changing affects the list of recipients, supplies, and the direction in the location finder.  
[Function 9] Exit Program - Exits the program.

After selecting a function, the user is then instructed to press the key to their chosen province.  The program currently supports three different provinces: 
Masbate Island;
Mindoro Island;
and Samar Island.
The program can theoretically support various provinces in the Philippines without any error.  As a demonstration, we’ve chosen the three islands above as these islands were devastated by the latest typhoon that caused the lives of hundreds of people.  Hence, they were prioritized to be served by the program.
After selecting a key of their chosen province, the next step to do depends on what the user has pressed on Step 1.  

Sample Title Screen Screenshot
If the user pressed [F1] Add Recipient,
The user will be asked to enter the recipient’s first name.  The program features an input verifier and detects if there’s no input, and the names will format automatically.

Then, the last name of the recipient. 

The program will tell the user if the name already exists, like this one.

If the name is still not in the database, it will ask for the recipient’s age.  It also verifies if the input is an integer or not and if the age is realistic or not.

After all information is entered, the program will tell the user that the name has been added to the queue.  He/she is always added to the last line of the queue.

The user will then be instructed to press a key of their choice in Step 1.
If the user pressed [F2] Next Recipient
 For demonstration, this is the queue before the button is pressed.  Note that Trisha Mae Gahol is currently being served by the program.

After pressing the button, the program automatically removes Ms. Gahol from the queue and proceeds to Mr. Moral as the current recipient.  The program also provides additional information.

The program also checks for the number of supplies before dequeuing recipients.  In this case, there is an insufficient amount of instant coffee to be distributed.  The dequeuing fails and the user will be informed that this item is out of stock.  To continue, the user has to add the amount of supply or delete it.	

The user will then be instructed to press a key of their choice in Step 1. 
If the user pressed [F3] View Recipients
The option says as it is, it simply displays the list of recipients.

The user will then be instructed to press a key of their choice in Step 1. 
If the user pressed [F4] Add Supply,
The user is instructed to enter the name of the supply.  The program features an input verifier and detects if there’s no input, and the names will format automatically.
There are two cases: 
If the item already exists
The program simply instructs the user to enter the amount to be added.

If the item is not yet on the list.
The program will tell the user that it is a new item and requires input on the number of supplies.
				
And then the amount per person to be distributed.
					
The program will tell the user that the item has been added to the list.

The user will then be instructed to press a key of their choice in Step 1. 
If the user pressed [F5] Remove Supply
The program will ask the user to enter the name of the item.  If it is on the list, it will be removed.  If not, it displays an error.


The user will then be instructed to press a key of their choice in Step 1. 
If the user pressed [F6] View Supply
The option says as it is, it simply displays the list of supplies.

The user will then be instructed to press a key of their choice in Step 1. 
If the user pressed [F7] Location Finder
The user has presented a map of the island of their choice.

The user has to choose for the initial destination either the evacuation area or a destination of their choice.

If the user chooses the evacuation area:
The program will automatically assign the evacuation area available on the map.

If the user chooses a custom destination:
The program will instruct the user to select the municipality of their choice.  The list can be seen by the user below…

After selecting a municipality, the user has to select the list of available barangays.  Note that for convenience purposes, the user may enter the number associated with it.

Then the user will be instructed to choose the final destination.  Like in the initial destination, the user can also opt to either choose the evacuation area or a destination of their choice.
After choosing the initial and final destination, the user is presented the following information:
The shortest (and fastest) route available to be traversed from the initial and final destination.
The minimum time needed before reaching the final destination (in normal conditions).
And the highlighted route (white background).

The user will then be instructed to press a key of their choice in Step 1.

If the user pressed [F8] Change Location,
The user is instructed to press the key of their chosen province. 

Then the queues and supplies lists will update accordingly.
The user will then be instructed to press a key of their choice in Step 1.
If the user pressed [F9] Exit the program.
The program will exit accordingly.	

