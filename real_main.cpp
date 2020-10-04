#include<bits/stdc++.h>
#include"BRS.h"
#include"Accounts.h"
using namespace std;
using namespace Bus_namespace;
using namespace Accounts_namespace;
//Varrible to hold screen
char stop;
//For Administrator Profile
void AdminChoice(string usr_nm,string password)
{
	//If the wrong Id and Password regarding to Admin has been entered it will show this error message,
	//and is returned back.
    if(usr_nm!="Admin" || password!="Admin")
    {
    	system("clear");
        cout<<"\a\a\a\n";
        cout<<"\t\t\tValid Identity not found\n"
            <<"\t\t\tfor Administrator Portal\n";
        return;
    }
    Bus bus;
    char choice;
    string num;
    while(1)
    {
    	//Menu that will appear on the screen
        system("clear");
        again:
        cout<<"\n\n\n";
        cout<<"\t\tBUS RESERVATION SYSTEM\n"
        	<<"\t\t  ADMIN PORTAL\n ";
        cout<<"\t\t\t1.Allot Bus\n\t\t\t"
            <<"2.Remove Bus\n\t\t\t"
            <<"3.Reservation\n\t\t\t"
            <<"4.Check seats\n\t\t\t"
            <<"5.Check bus\n\t\t\t"
            <<"6.Show all users\n\t\t\t"
            <<"7.Make a user Profile\n\t\t\t"
            <<"8.Modify a user Profile\n\t\t\t"
            <<"9.Delete a user Profile\n\t\t\t"
            <<"0.Logout";
        cout<<"\n\t\t\tEnter your choice:-> ";
        cin>>choice;
        switch(choice)
        {
            case '1':
                //To allot a bus
            	//Allot_Bus procedure of BRS.h file has been called.
                num=bus.Allot_Bus(bus);
                //Allocation of entry in map, bus number as key and object of bus class as object. 
                Bus_data[num]=bus;
            break;
            case '2':
                //Remove bus by checking the bus number
            	//Remove_Bus() procedure of BRS.h file has been called.
                bus.Remove_Bus();
            break;
            case '3':
               //Reservation of seats in a bus
            	//Allot_Seat() procedure of BRS.h file has been called
                bus.Allot_Seat();
            break;
            case '4':
                //Show availble seats in a bus
            	//Show_seats() procedure of BRS.h file has been called.
                bus.Show_seats();
            break;
            case '5':
                //Show availble buses
            	//Show_Buses() procedure of BRS.h file has been called.
                bus.Show_Buses();
            break;
            case '6':
            	//Admin specialized procedure for showing all the registered profile of users in this portal.
                //showallProfile() procedure of Accounts.h file has been called. 
                showallProfile();
            break;
            case '7':
            	//It is basicaly a user specialized function
            	//makeAccount() procedure of Accounts.h file has been called
                makeAccount();
            break;
            case '8':
            {
            	//modifyProfile() procedure of Accounts.h file has been called.
            	//For admin first username of the user has been asked.
            	//And then profile of that user has been modified.
            	string user_name;
            	cout<<"\nEnter the username of user : ";
            	cin>>user_name;
            	modifyProfile(user_name);
            }
            break;
            case '9':
            {
            	//deleteProfile() procedure of Accounts.h file has been called.
            	//For admin first username of the user has been asked.
            	//And then profile of that user has been deleted.
            	string user_name;
            	cout<<"\nEnter the username of user : ";
            	cin>>user_name;
            	deleteProfile(user_name);
            }
            break;
            case '0':
            	//In this case Admin has been returned back
            	//It is basically logout.
            	system("clear");
            	return;
            break;
            default:
                cout<<"\t\t\tYou pressed a wrong key\n";
            break;
        }
        cout<<"\n\t\t\tPress any key then hit enter to continue : ";
      	cin>>stop;
    }
}
//For User Profile
void UserChoice(string usr_nm)
{
   Bus bus;
   char choice;
   string num;
   while(1)
   {
       system("clear");
       again:
       cout<<"\n\n\n";
       cout<<"\t\tWELCOME TO BUS RESERVATION SYSTEM"
       		<<"\n\t\t   ALOT YOUR SEAT WITH US\n";
       cout<<"\t\t\t1.Reserve Seats\n\t\t\t"
           <<"2.Check seats\n\t\t\t"
           <<"3.Check buses\n\t\t\t"
           <<"4.View own Profile\n\t\t\t"
           <<"5.Edit Profile\n\t\t\t"
           <<"6.Delete Profile\n\t\t\t"
           <<"7.Logout";
       cout<<"\n\t\t\tEnter your choice:-> ";
       cin>>choice;
       switch(choice)
        {
            case '1':
            //Reserve of seats in a bus
            //Allot_Seat() procedure of BRS.h has been called
                bus.Allot_Seat();
            break;
            case '2':
                //Show availble seats in a bus
            	//Show_seats() procedure of BRS.h file has been called
                bus.Show_seats();
            break;
            case '3':
                //Show availble buses
            	//Show_Buses() procedure of BRS.h file has been called
                bus.Show_Buses();
            break;
            case '4':
            	//showProfile() procedure of accounts.h file has been called
            	//Used to show profile of user
                showProfile(usr_nm);
                showProfile(usr_nm);
            break;
            case '5':
            	//modifyProfile() procedure of accounts.h file has been called
            	//Option to modify user profile
                modifyProfile(usr_nm);
            break;
            case '6':
            	//deleteProfile() procedure of accounts.h file has been called
            	//Option to delete user profile
            	deleteProfile(usr_nm);
            	return;
            break;
            case '7':
            	//It is an option for user to logout from the portal
            	system("clear");
                return;
            break;
            default:
                cout<<"\t\t\tYou pressed a wrong key\n";
            break;
        }
		cout<<"\n\t\t\tPress any key then hit enter to continue : ";
		cin>>stop;
    }
}
//Driver Function
int main()
{
	//Function to display main menu
	char choice;
	string usr_name,password;
	while(1)
	{
		system("clear");
		again:
		cout<<"\n\t\tPress 0 to enter through Admin Portal\n"
			<<"\t\t\tPress 1 to Login \n"
			<<"\t\t\tPress 2 to Register\n"
			<<"\t\t\tOr any key to exit.\n"
			<<"\t\t\tEnter your choice :";
		cin>>choice;
		switch(choice)
		{
			//Special case when Admin wants to login
			case '0':
				system("clear");
				cout<<"\t\t\tEnter the admin username :";
				cin>>usr_name;
				cout<<"\t\t\tEnter the password :";
				cin>>password;
				AdminChoice(usr_name,password);
				goto again;
			break;
			case '1':
			{
				//In this case user has been asked to login
				while(1)
				{
					usr_name=Login();
					//If the account with specified user name exist User_module has been called.
					if(usr_name!="\0")
					{
						UserChoice(usr_name);
						goto again;
					}
					//Else this menu will prompt and ask user to register 
					//if he/she does not want to register he will be forced to go to main menu.
					else
					{
						cout<<"\n\t\t\tPress 1 to Register \n"
							<<"\t\t\tOr any key to exit\n"
							<<"\t\t\tEnter your choice :";
						cin>>choice;
						switch(choice)
						{
							//For registration of user this module will be called.
							case '1':
								makeAccount();
								cout<<"\n\t\t\tNow,Login to Continue.";
								goto again;
							default:
								exit(0);
						}
					}
				}
			}
			break;
			case '2':
				//Simply ask user to register.
				makeAccount();
				goto again;		
			break;
			default:
				exit(0);
		}
	}
	return 0;
}
