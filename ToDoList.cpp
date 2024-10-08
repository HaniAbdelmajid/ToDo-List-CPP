//Creator of Code - Hani Abdelmajid

//ToDO list program allows user to create tasks and mark them complete if they completed that task.
//ToDo list will get more features implemented but as of now you can add tasks, mark them complete, and display all your tasks (might have new features soon).
//Program showing fundamental knowledge of object oriented programming.

#include<iostream>
#include<ctime> 
#include<vector>
#include<string> 
#include<algorithm>

class Task{
	public:
		
	std::string description;
	bool iscompleted;

	time_t currentDate;
	time_t startDate;
	time_t dueDate;
	
	//List constructor for intializing the variables
	Task(time_t start, time_t due):description(""),startDate(start),dueDate(due),iscompleted(false){};
	
	//To compare if what im looking for through std::find is matching, returing either true (it is) or false(it is not matching)
	bool operator==(const Task& other)const{
		if(other.description == description){
			
			return true;
			
		}
		else{
			
			return false;
			
		}
	}
	
	//Method to mark task complete or if user trys marking incomplete it will cout past due date if that is the case
	void markCompleted(){
		
		currentDate=(time(nullptr));
		
		if(dueDate<currentDate){
		
		//current value will stay false and print past due date (not completed on time)
		std::cerr<<"Task is past due date!"<<std::endl;
		
		}
		else if(currentDate<=dueDate){
			
			//Mark iscompleted to true and print out to the user that it has been done so
			std::cout<<"Task was marked complete!"<<std::endl;
			iscompleted=true;
			
		}
	}
};

	//Function to set time format input for user then returning (will call this function in main for startDate and dueDate)
	//While loops that will keep looping if user inputs invalid numbers for the date
	time_t inputDate(){
		struct tm timeinfo={0};
		
		while(true){
		std::cout<<"Enter the year (Ex. 2024): ";
		std::cin>>timeinfo.tm_year;	
		if(timeinfo.tm_year<2024){
			std::cerr<<"That is an invalid year! Try again!"<<std::endl<<std::endl; //double skip just for organization
			
			continue;
		}
		
		/*
			Time function starts at year 1900 sinces thats when its system was made. 
			So we should subtract 1900 from user input to be equal to todays date.
		*/
		timeinfo.tm_year-=1900;
		std::cout<<std::endl;
		
		break;
	}
	
		while(true){
		std::cout<<"Enter the month (1-12): ";
		std::cin>>timeinfo.tm_mon;
		if(timeinfo.tm_mon>12||timeinfo.tm_mon<1){
			std::cerr<<"That is an invalid month! Try again!"<<std::endl;
			
			continue;
		}
		timeinfo.tm_mon-=1;
		std::cout<<std::endl;
		
		break;
	}
	
		while(true){
		
		std::cout<<"Enter the day: ";
		std::cin>>timeinfo.tm_mday;
		
		/*Subtracting one in the if statement because time functions work from 0-11 in months, january starting at 0 to match how tm_month is also -1 above
		*/
		if(timeinfo.tm_mday>31){
			std::cout<<"Not a valid day! Try again!"<<std::endl;
			
			continue;
		}
		if((timeinfo.tm_mon==4-1||timeinfo.tm_mon==6-1||timeinfo.tm_mon==9-1||timeinfo.tm_mon==11-1) && timeinfo.tm_mday==31){
			std::cerr<<"Not a valid day in this month. Try again!"<<std::endl;
			
			continue;
		}
		//Assuming the last day is 28 not including leap year in february
		if((timeinfo.tm_mday==29||timeinfo.tm_mday==30||timeinfo.tm_mday==31) && timeinfo.tm_mon==2-1){
			std::cerr<<"Not a valid day in this month. Try again!"<<std::endl;
			
			continue;
		}
		std::cout<<std::endl;
		
		break;
	}
	
		while(true){
		
		std::cout<<"Enter the hour (0-23): ";
		std::cin>>timeinfo.tm_hour;
		if(timeinfo.tm_hour<0||timeinfo.tm_hour>23){
			std::cerr<<"Not a valid hour. Try again!"<<std::endl;
			continue;
		}
		std::cout<<std::endl;
		break;
	}

		while(true){
		
		std::cout<<"Enter the minute (1-59): ";
		std::cin>>timeinfo.tm_min;
		if(timeinfo.tm_min>59 || timeinfo.tm_min<1){
			std::cerr<<"Not a valid minute. Try again!"<<std::endl;
			continue;
		}
		std::cout<<std::endl;
		break;
}

		while(true){
		
		std::cout<<"Enter the second (1-59): ";
		std::cin>>timeinfo.tm_sec;
			if(timeinfo.tm_sec>59 || timeinfo.tm_sec<1){
			std::cerr<<"Not a valid second. Try again!"<<std::endl;
			continue;
		}
		std::cout<<std::endl;
		break;
	}
		//returns user input using mktime function (the & is referencing timeinfo directly)
		return mktime(&timeinfo);
	}
	
//List class which will create a vector array to make functions to add, mark complete, and display tasks
class List{
public:

//vector array to hold tasks
std::vector<Task> tasks;
	
	//Function to add a task to the vector
	void addTask(const Task& addTK){
		tasks.push_back(addTK); //pushes new task to vector array
	}
	
	//Function for user to mark their task complete
	void markTasksComplete(const Task& searchTask){
		
		//Using std::find to iterate through tasks to find the task we are seeking
		auto findTask=std::find(tasks.begin(), tasks.end(),searchTask);
		
		//if the iterator(findTask) does not reach tasks.end then we found said task
		if(findTask != tasks.end()){
			(*findTask).markCompleted();
		}
		else{
			std::cout<<"Task was not found unfortunatley!"<<std::endl;
		}
	}
	
	//Returning time string format thats human readable
	std::string formatTime(time_t displayformat){
		
		std::tm* timeInfo = std::localtime(&displayformat);
		char buffer[80];
		std::strftime(buffer,80,"%Y-%m-%d %H:%M:%S",timeInfo);
		
		return buffer;
	}
	
	//Function for displaying tasks
	void displayTasks(){
		//Checking if task is empty
		if(tasks.empty()){
			std::cout<<"Their is No tasks Available to view!"<<std::endl;
		}
		
		else{	
		int i=0;
		
		//For loop to iterate through the tasks vector
		for(const auto& display:tasks){
	
		i++; // Increment i so that it will label tasks like Task 1: and so on for user organization
		
		std::cout<<"Task "<<i<<": "<<display.description<<std::endl;
		std::cout<<"Start Date: "<<formatTime(display.startDate)<<std::endl;
		std::cout<<"Due Date: "<<formatTime(display.dueDate)<<std::endl;
		
		// If iscompleted is true it will display Completed under task
		if(display.iscompleted==true){
			std::cout<<"Completed!"<<std::endl;
		}
		else{
			std::cout<<"Not Completed!"<<std::endl;
		}
		//Extra line space
		std::cout<<std::endl;
	
		}
	}
	}
	
};

int main(){
	
	int choice;
	List list;
	
	//bool variable that will be used for while loop condition initialized to true to repeat the while loop till further notice
	bool loopRunning=true;
	
	//The while loop wont end unless the user chooses number 4
	while(loopRunning){
	
	//Menu for options
	std::cout<<"    --ToDo list--"<<std::endl;
	std::cout<<"1. Add Task to track."<<std::endl;
	std::cout<<"2. Mark Complete."<<std::endl;
	std::cout<<"3. Display all Tasks."<<std::endl;
	std::cout<<"4. End Program."<<std::endl;
	
	//User choice input
	std::cin>>choice;
	std::cin.fail();   
	
	//Switch to allow user to pick an option of their choice(last option being exit);
	switch(choice){
		case 1:{
			std::string taskDescription;
			time_t startDate;
			time_t dueDate;
			
			std::cout<<"Enter Task description: "<<std::endl;
			std::cin.ignore();
			std::getline(std::cin, taskDescription);
			
			std::cout<<"Enter the start date: "<<std::endl;
		
			startDate=inputDate();
			
			//Checking if due date is earlier then start date
			while(true){
			
			std::cout<<std::endl<<"Enter the due date: "<<std::endl;
			dueDate=inputDate();
			if(startDate>=dueDate){
				std::cout<<"Your due date cannot be a date before start date or the same!"<<std::endl;
				continue;
			}
			break;
	}
			Task task(startDate,dueDate);
			task.description=taskDescription;
			
			std::cout<<"The task \""<<task.description<<"\" has been added."<<std::endl;
		 	list.addTask(task);
			break;	
	}
		case 2:{
			
			time_t startDate;
			time_t dueDate;
			
			//Creating task object
			Task taskDescription(startDate,dueDate);
			
			std::cout<<"Enter the Task Description to mark done(completed): ";
			std::cin.ignore();
			std::getline(std::cin,taskDescription.description);
			
			//Calling markTasksComplete function
			list.markTasksComplete(taskDescription);
			break;
			
		}
		case 3:{
			
			//List vector calling the display tasks function
			std::cout<<"--Tasks--"<<std::endl;
			list.displayTasks();
			break;
			
		}
		
		case 4:{
			
			//Will mark loopRunning false ending the loop
			std::cout<<"Goodbye. ToDo list has ended.";
			loopRunning=false;
			break;
			
		}

		default:
			//If cin.fail() is true it means user tried inputting letters, message will be sent to user accordingly. Informing what went wrong.
			if(std::cin.fail()==true){
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr<<"Invalid: Letters not allowed as a choice. Pick a number between 1-4. "<<std::endl;
			continue;
		}
		
		//If user inputted wrong number they will be informed accordingly
		std::cerr<<"Invalid: Please enter between a number between 1-4."<<std::endl;
		continue;
			
		break;
	
		}
}
	
return 0;
}