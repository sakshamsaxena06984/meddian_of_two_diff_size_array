#include<bits/stdc++.h>
using namespace std;
namespace Bus_namespace
{
	//Definition of class Bus
	class Bus
	{
	    private:
	        string busn,driver,date;      //To store bus number and driver name and date
	        string seat[8][4];		  //A string array to store the information of the reserved seats of bus.
	        pair<string,string>src_dest; //A pair which will store the source and destination of bus.
	        vector<string> stations;	//A vectore which contains all the intermediate stations between source and destination.
	        pair<string,string>arr_dep; //A pair which contains arrival and departure time of a bus from a station.
	    public:
	    	//A constructor which allocates vacant seats when object is created.
	        Bus()
	        {
	            for(int i=0; i<8;i++)
	                for(int j=0;j<4;j++)
	                    seat[i][j]="Empty";
	        }
	        string Allot_Bus(Bus&);	//This functions allocate the bus and returns the bus number.
	        void Remove_Bus();  //This function will remove the busses.
	        void Show_Buses();	//This method will show the available busses.
	        void Allot_Seat();	//This method is used to alot the seat in a bus.(Reservation)
	        void Show_seats();	//Show seats will show you the vacant+occupied seats of an availble bus.
	        bool Search_Busses(); //This procedure is made for searching for bus in map.
	        void check_seats(int,Bus&); //Check for availbility of particular seat in an availble bus.
	        int availble(string,vector<string>);	//Check for availbility of bus for stations.
	};
	//Declaration of Map
	map<string,Bus>Bus_data;
	//A namespace in which all the validation procedures are written
	namespace Bus_validation_namespace
	{
		//This is a validation method used to validate arival and departure time format. (P)
		//Time should be in hh:mm format and 24 hour time format is acceptable.
		bool isValidTime(string str)
		{
			if(str.length()<5||str.length()>5)
				return 0;
			if(str[0]!='0'&&str[0]!='1'&&str[0]!='2')
				return 0;
			else if(str[1]!='0'&&str[1]!='1'&&str[1]!='2'&&str[1]!='3'&&str[1]!='4'&&str[1]!='5'&&str[1]!='6'&&str[1]!='7'&&str[1]!='8'&&str[1]!='9')
				return 0;
			else if(str[2]!=':')
				return 0;
			else if(str[3]!='0'&&str[3]!='1'&&str[3]!='2'&&str[3]!='3'&&str[3]!='4'&&str[3]!='5')
				return 0;
			else if(str[4]!='0'&&str[4]!='1'&&str[4]!='2'&&str[4]!='3'&&str[4]!='4'&&str[4]!='5'&&str[4]!='6'&&str[4]!='7'&&str[4]!='8'&&str[4]!='9')
				return 0;
			else
				return 1;
		}
		//This is also a validation method used to validate date format.(P)
		//Date should be entered through dd/mm/yyyy format otherwise it will no be accepted
		bool isValidDate(string str)
		{
			if(str.length()!=10)
				return false;
			if(str[2]!='/'||str[5]!='/')
				return false;
			//Converting string to integer
			int d=abs(('0'-str[0])*10+('0'-str[1]));
			int m=abs(('0'-str[3])*10+('0'-str[4]));
			int y=abs(('0'-str[6])*1000+('0'-str[7])*100+('0'-str[8])*10+('0'-str[9]));
			
			//gregorian dates started in 1582
			if (! (1582<= y )  )//comment these 2 lines out if it bothers you
				return false;
			if (! (1<= m && m<=12) )
				return false;
			if (! (1<= d && d<=31) )
				return false;
			if ( (d==31) && (m==2 || m==4 || m==6 || m==9 || m==11) )
				return false;
			if ( (d==30) && (m==2) )
				return false;
			if ( (m==2) && (d==29) && (y%4!=0) )
				return false;
			if ( (m==2) && (d==29) && (y%400==0) )
				return true;
			if ( (m==2) && (d==29) && (y%100==0) )
				return false;
			if ( (m==2) && (d==29) && (y%4==0)  )
				return true;

			return true;
		}
	}
	using namespace Bus_validation_namespace;
	//To draw lines as data seperator
	void vline(char ch)
	{
	  for (int i=100;i>0;i--)
	    cout<<ch;
	}
	//Admin Function to alot a bus with relevant details like driver,(K)
	//its arrival and departure time its source and destination 
	//the intermediate stations between source and destination.
	//It returns the bus number.
	string Bus::Allot_Bus(Bus &bus)
	{
	    bus.stations.clear();
	    string arr,dep,from,to;
	    cin.ignore();
	    cout<<"Enter bus no: ";
	    getline(cin,bus.busn);
	    cout<<"Enter Driver's name: ";
	    getline(cin,bus.driver);
	    DATE:
	    	cout<<"Enter the date (dd/mm/yyyy) :";
	    	getline(cin,bus.date);
	    	if(!isValidDate(bus.date))
	    	{
	    		cout<<"Enter valid date in dd/mm/yyyy format\n";
	    		goto DATE;
	    	}
	    //Validations of date and time have been done here.
	    ARRIVAL:
	    	cout<<"Enter the arrival time(hh:mm): ";
	    	getline(cin,arr);
	    	if(!isValidTime(arr))
	    	{
	    		cout<<"Enter valid date in hh:mm format\n";
	    		goto ARRIVAL;
	    	}
	    DEPARTURE:
	    	cout<<"Enter the departure time(hh:mm): ";
	    	getline(cin,dep);
	    	if(!isValidTime(dep))
	    	{
	    		cout<<"Enter valid time in hh:mm format\n";
	    		goto DEPARTURE;
	    	}
	    cout<<"From: ";
	    getline(cin,from);
	    cout<<"To: ";
	    getline(cin,to);
	    bus.stations.push_back(from);
	    int count;
	    //Vector has been used to keep details of intermediate cities
	    cout<<"Enter the number of stations between "<<from<<" and "<<to<<" where the bus will stop :";
	    cin>>count;
	    for(int i=0;i<count;i++)
	    {
	    	string city;
	    	cout<<"Enter the name of station : ";
	    	getline(cin,city);
	    	bus.stations.push_back(city);
	    }
	    bus.stations.push_back(to);
	    bus.src_dest=make_pair(from,to);
	    bus.arr_dep=make_pair(arr,dep);
	    return bus.busn;
	}
	//See destination and arrival position(P)
	//It is used as internal function to check for the location between source and destination. 
	//It returns the position of that location if found else return -1.
	//It is used when we want to check weather the entered city is in vector or not.
	int Bus::availble(string s,vector<string>v)
	{
			auto it= find(v.begin(),v.end(),s);
			if(it!=v.end())
				return(it-v.begin());
			else
				return -1; 
	}
	//User+Admin function to search for buses.
	//It searches in two ways either by bus number or by the station names.(P)
	bool Bus::Search_Busses()
	{
	    char ch;
	    cout<<"Press 1 to search Busses by Bus number\nPress 2 to search Busses by cities\n";
	    cout<<"Enter your choice : ";
	    cin>>ch;
	    if(ch=='1')
	    {
	    	//Here Bus number is entered if bus ith that bus number is availble it will
	    	//return true otherwise it displays the message that bus with this number is not avilble
	    	//and return false
	        string num;
	        cout<<"Enter the bus number : ";
	        cin>>num;
	        if(Bus_data.find(num)!=Bus_data.end())
	        {
	            auto x=Bus_data.find(num);
	            Bus bus=x->second;
	            cout<<"\nBus no: "<<bus.busn<<"\nDriver: "<<bus.driver
	            	<<"\t\tDate: "<<bus.date
	                <<"\t\tArrival time: "<<bus.arr_dep.first<<"\tDeparture Time: "
	                <<bus.arr_dep.second<<"\nSource: "<<bus.src_dest.first<<"\t\tDestination: "
	                <<bus.src_dest.second<<"\nRoute: ";
	            bool flag=true;
                for(auto it:bus.stations)
                {
                	if(flag)
            		{
            			cout<<it;
            			flag=false;
            		}
            		else
            			cout<<" -> "<<it;
            	}
	            cout<<endl;
	            return 1;
	        }
	        else
	        {
	            cout<<"Sorry,no bus with this number availble";
             	return 0;
            } 
	        vline('*');
	    }
	    else if(ch=='2')
	    {
	    	//In this the user has been asked to enter the cities from where he wants to travel and til where he 
	    	//wants to travel.
	        int flag=0;
	        string src,dest;
	        cin.ignore();
	        cout<<"Enter the source city : ";
	        getline(cin,src);
	        cout<<"Enter the destination city : ";
	        getline(cin,dest);
	        //If source and destination cities entered by user is same it will display this error message.
	        if(src==dest)
	        {
	        	cout<<"Source and Destination can't be same.\n";
	        	return 0;
	        }
	        //If not it will check for every bus for the entered cities
	        for(auto x : Bus_data)
	    	{
	            Bus bus=x.second;
	            fflush(stdin);
	            //Here availble() function is used to check for availble source and destination between intermediate cities
	            int s=bus.availble(src,bus.stations);
	            int d=bus.availble(dest,bus.stations);
	            //Parameters used for checking is
	            //If s==-1 or d==-1 it shows that location is not availble where the user wants to go.
	            //s<d signifies that source station should come before destination
	            if((s!=-1)&&(d!=-1)&&(s<d))
	            {
	            	cout<<"\nBus no: "<<bus.busn<<"\nDriver: "<<bus.driver
	            		<<"\t\tDate: "<<bus.date
	                    <<"\t\tArrival time: "<<bus.arr_dep.first<<"\tDeparture Time: "
	                    <<bus.arr_dep.second<<"\nSource: "<<bus.src_dest.first<<"\t\tDestination: "
	                    <<bus.src_dest.second<<"\nRoute :";
	                bool f=true;
	                for(auto it:bus.stations)
	                {
	                	if(flag)
	            		{
	            			cout<<it;
	            			f=false;
	            		}
	            		else
	            			cout<<" -> "<<it;
	            	}
	            	cout<<endl;
	                flag=1;
	        		vline('*');
	            }
	        }
	        //If not availble it shows this messagge to console.
	        if(!flag)
	        {
	            cout<<"No bus from "<<src<<" to "<<dest<<" availble";
	            return 0;
	        }
	        else
	        	return 1;
	    }
	    //This block will run if user enter a wrong choice. 
	    else
	    {
	    	cout<<"\n\t\t\tWrong Choice\n";
		}
	}
	//Admin Function It is used to remove a particular bus.(K)
	void Bus::Remove_Bus()
	{
	    if(Bus_data.empty())
	    {
	        cout<<"\n\t\t\tSorry no bus availble now\n";
	        return;
	    }
	    //It ask for bus number and remove that key value pair from map.
	    string number;
	    cout<<"Enter the bus number to be removed :";
	    cin.ignore();
	    getline(cin,number);
	    if(Bus_data.find(number)==Bus_data.end())
	        cout<<"No bus of number :"<<number<<" exist \n";
	    else
	    {
	        auto it=Bus_data.find(number);
	        Bus_data.erase(number);
	        cout<<"Bus with bus number : "<<number<<" has been removed \n";
	    }
	}
	//This method is used for reservation purpose to book seats by the passenger(K)
	//This method is used to book a seat in bus.
	void Bus::Allot_Seat()
	{
	    if(Bus_data.empty())
	    {
	        cout<<"\n\t\t\tSorry no bus availble now\n";
	        return;
	    }
	    int seat;
	    string number;
	    Bus bus;
	    cout<<"\nCheck your bus is availble or not\n";
	    //Here search procedure is used if it return the true value.
	    //We will take the bus number from user and book the dezired seat.
	    if(bus.Search_Busses())
	    {
	    top:
	        cin.ignore();
	        cout<<"\nBus no: ";
	        getline(cin,number);
	        int n;
	        //If bus with that bus number is not availble then this message will be displayed.
	        if(Bus_data.find(number)==Bus_data.end())
	        {
	            char ch;
	            cout<<"No bus availble with bus number "<<number<<endl;
	            cout<<"Press 1 to check again else to cancel : ";
	            cin>>ch;
	            //If user mistakenly entered a wrong number he/she could again enter the bus number by presseing 1.
	            if(ch=='1')
	                goto top;
	        }
	        else
	        {
	            auto x=Bus_data.find(number);
	            bus=(*x).second;
	        }
	        while(Bus_data.find(number)!=Bus_data.end())
	        {
	            cout<<"\nSeat Number: ";
	            cin>>seat;
	            //Since a bus have only 32 seats so seat number more than 32 is not availble.
	            if(seat>32)
	                cout<<"\nThere are only 32 seats availble in this bus.";
	            else
	            {
	            	//If the seat is empty then only seat can be booked.
	            	//If any seat has already been booked by anyone then seat
	            	//will not be availble for booking by other users.
	                if (bus.seat[seat/4][(seat%4)-1]=="Empty")
	                {
	                    cout<<"Enter passanger's name: ";
	                    cin>>bus.seat[seat/4][(seat%4)-1];
	                    Bus_data[number]=bus;
	                    break;
	                }
	                else
	                    cout<<"The seat no. is already reserved.\n";
	            }
	        }
	    }
	}
	//User +Admin function to check the availble seats in a bus.(K)
	//This procedure works on taking bus number.
	void Bus::Show_seats()
	{
	    if(Bus_data.empty())
	    {
	        cout<<"\n\t\t\tSorry no bus availble now\n";
	        return;
	    }
	    int n;
	    char number[15];
	    cout<<"Enter bus no: ";
	    cin>>number;
	    //Bus number has been taken and if no bus with that bus number is availble this error message will prompt.
	    if(Bus_data.find(number)==Bus_data.end())
	        cout<<"No bus availble with this number";
	    //Else bus with that number has been showed.
	    else
	    {
	        auto x= Bus_data.find(number);
	        Bus bus=(*x).second;
	        vline('*');
	        cout<<"\nBus no: "<<bus.busn<<"\nDriver: "<<bus.driver
	        	<<"\t\tDate: "<<bus.date
	            <<"\t\tArrival time: "<<bus.arr_dep.first<<"\tDeparture Time: "
	            <<bus.arr_dep.second<<"\nSource: "<<bus.src_dest.first<<"\t\tDestination: "
	            <<bus.src_dest.second<<"\nRoute: ";
	        bool flag=true;
            for(auto it:bus.stations)
            {
            	if(flag)
        		{
        			cout<<it;
        			flag=false;
        		}
        		else
        			cout<<" -> "<<it;
        	}
	            cout<<endl;
	        vline('*');
	        //To check seats
	        bus.check_seats(n,bus);
	    }
	}
	//This procedure is used to print the seats.(P)
	//It will keep count of the empty seats in a bus.
	//And show which seat has already been booked by which user.
	void Bus::check_seats(int l,Bus &bus)
	{
	    int seat_no=0,emp_seats=0;
	    //Rows
	    for (int i =0; i<8;i++)
	    {
	        cout<<"\n";
	        //Columns
	        for (int j = 0;j<4; j++)
	        {
	            seat_no++;
	            //If seat is not booked by any of the user then "Empty" will be printed.
	            if(bus.seat[i][j]=="Empty")
	            {
	                cout.width(5);
	                cout.fill(' ');
	                cout<<seat_no<<".";
	                cout.width(10);
	                cout.fill(' ');
	                cout<<bus.seat[i][j];
	                emp_seats++;
	            }
	            //Else the name of the person for whom seat is booked will be printed.
	            else
	            {
	                cout.width(5);
	                cout.fill(' ');
	                cout<<seat_no<<".";
	                cout.width(10);
	                cout.fill(' ');
	                cout<<bus.seat[i][j];
	            }
	        }
	    }
	    cout<<"\n\nThere are "<<emp_seats<<" seats empty in Bus No: "<<bus.busn;
	}
	//This procedure shows the deatils of all the buses availble by the portal.(K)
	void Bus::Show_Buses()
	{
	    if(!Bus_data.empty())
	    {
	        for(auto x : Bus_data)
	        {
	            Bus bus=x.second;
	            fflush(stdout);
	            vline('*');
	           	cout<<"\nBus no: "<<bus.busn<<"\nDriver: "<<bus.driver
	           		<<"\t\tDate: "<<bus.date
	                <<"\t\tArrival time: "<<bus.arr_dep.first<<"\tDeparture Time: "
	                <<bus.arr_dep.second<<"\nSource: "<<bus.src_dest.first<<"\t\tDestination: "
	                <<bus.src_dest.second<<"\nRoute : ";
	            bool flag=true;
                for(auto it:bus.stations)
                {
                	if(flag)
            		{
            			cout<<it;
            			flag=false;
            		}
            		else
            			cout<<" -> "<<it;
            	}
	            cout<<endl;
	            vline('*');
	        }
	    }
	    else
	        cout<<"\n\t\t\tSorry no bus availble now";
	}
}//End of namespace BUS
