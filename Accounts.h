#include<bits/stdc++.h>
using namespace std;
namespace Accounts_namespace
{
	//Object of ofstream and ifstream class for input and output data in file.
	//The file that has been used here is Accounts_info file.
	ofstream fout;
	ifstream fin;
	//This class is used to create an object of registered user.
	//This will store all the information about user.
	//And the object of that file has been written to file. 
	class Register
	{
		public :
			pair<string,string>name; //This is a pair used for storing the first and last name of the user.
			pair<string,string>id_pass;	//This will store the Id-password of a particular user.
			string email,phone_no; //These will  stores the additional information about user.
	};
	//Contains all the validation functions of user account.(P)
	namespace Account_validation_namespace
	{
		//This method is used to check weater the user has entered his email in correct format or not.
		//It returns a true value if the format is correct otherwise false.
		//Here I have used regular expressions popularly known as regex.
		bool isValidEmail(string email)
		{
			const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
		    return regex_match(email,pattern);
		}
		//Same as above
		//This method is used to check weater the user has entered his phonenumber in correct format or not.
		//It returns a true value if the format is correct otherwise false.
		//Here I have used regular expressions popularly known as regex.
		bool isValidPhone(string pno) 
		{ 
		    const regex pattern("[0/91]?[6-9][0-9]{9}");
		    return regex_match(pno,pattern);
		}
		//To check for file is empty.
		// This procedure is used to check for empty files,when not any user is registered.
		bool is_empty(std::ifstream& pFile)
		{
	    	return pFile.peek() == std::ifstream::traits_type::eof();
		}
		//This procedure is made to avoid duplicacy of username.
		//If username already exist and someone try to make account with the same username.
		//It will return a false value. 
		bool isExist(string usr)
		{
			Register ob;
			fin.open("Accounts_info", ios::in);
	 		while(fin >> ob.id_pass.first)
	 			if(ob.id_pass.first==usr)
	 				return 1;
	 		fin.close();
	 		return 0;
	 	}
	}
	using namespace Account_validation_namespace;
	//To create horizontal lines as data seperator.
	void hline(char ch)
	{
	  for (int i=120;i>0;i--)
	    cout<<ch;
	}
	//User Function	to make his/her account(K)
	//This function is used to make profile of user while registering (him/her)self.
 	void makeAccount()
 	{
 		//All the data is merged into an object of class register and then that object has been written to file.
 		//Validation procedure regarding to entry of duplicate username misformatted phone number and email 
 		//has been used so that enterd data is not corrupted.
 		Register ob;
 		cin.ignore();
 		fout.open("Accounts_info", ios::app);
 		cout<<"Enter your first name :";
 		getline(cin,ob.name.first);
 		cout<<"Enter your second name :";
 		getline(cin,ob.name.second);
 		USERNAME :
	 		cout<<"Enter the user name : ";
	 		getline(cin,ob.id_pass.first);
	 		if(isExist(ob.id_pass.first))
	 		{
	 			cout<<"This user name already exist!!! Try another\n";
	 			goto USERNAME;
	 		}
 		cout<<"Enter the password : ";
 		getline(cin,ob.id_pass.second);
 		PHONE :
	 		cout<<"Enter the phone number : ";
	 		getline(cin,ob.phone_no);
	 		if(!isValidPhone(ob.phone_no))
	 		{
	 			cout<<"Phone number not correct!!! Try again\n";
	 			goto PHONE;
	 		}
 		EMAIL :
 			cout<<"Enter your email address : ";
 			getline(cin,ob.email);
 			if(!isValidEmail(ob.email))
 			{
 				cout<<"Email not correct!!! Try again\n";
 				goto EMAIL;
 			}
 		fout<<ob.name.first<<" "<<ob.name.second<<" "<<ob.id_pass.first<<" "
 			<<ob.id_pass.second<<" "<<ob.phone_no<<" "<<ob.email<<"\n";
 		system("clear");
 		cout<<"\n\t\t\tAccount created succesfully,\n\t\t\tLogin to continue\n";
 		fout.close(); 
 	}
 	//User Function to show his own profile it will take the username as input.(K)
 	void showProfile(string usr_nm)
 	{
 		Register ob;
 		system("clear");
 		fin.open("Accounts_info",ios::in);
 		while(fin >> ob.name.first >> ob.name.second >> ob.id_pass.first >>ob.id_pass.second >>ob.phone_no>>ob.email)
 			if(ob.id_pass.first==usr_nm)
 				cout<<"\nName : "<<ob.name.first<<" "<<ob.name.second
 					<<"\nUsername : "<<ob.id_pass.first
 					<<"\nPassword : "<<ob.id_pass.second
 					<<"\nPhone Number : "<<ob.phone_no
 					<<"\nEmail : "<<ob.email
 					<<endl;	
 		fin.close();
 	}
 	//Admin Funtction to show all the registered user of system.(K)
 	void showallProfile()
 	{
 		Register ob;
 		fflush(stdin);
 		fin.open("Accounts_info", ios::in);
 		if(is_empty(fin))
 		{
 			cout<<"\n\t\t\tNot any user registered till now.\n";
 			return;
 		}
 		cout<<"\n\n\t\tThese are the users profile who registered.\n\n";
 		hline('*');
 		while(fin >> ob.name.first >> ob.name.second >> ob.id_pass.first >>ob.id_pass.second >>ob.phone_no>>ob.email)
 		{
 			cout<<endl;
 			cout<<" Name : "<<ob.name.first<<" "<<ob.name.second
 				<<" Username : "<<ob.id_pass.first
 				<<" Password : "<<ob.id_pass.second
 				<<" Phone Number : "<<ob.phone_no
 				<<" Email : "<<ob.email
 				<<endl;
 			hline('-');
 		}
 		cout<<endl;
 		hline('*');
 		fin.close();
 	}
 	//User Function to Login if he/she already made his/her account.(P)
 	//Note this function return the string as username if user is registered otherwise  null has been returned.
 	string Login()
 	{
 		system("clear");
 		cout<<"\n\t\t\tPlease,Login to continue.\n";
 		string usr_nm,password;
 		cout<<"\t\tEnter your user name : ";
 		cin>>usr_nm;
 		cout<<"\t\tEnter your password : ";
 		cin>>password;
 		Register ob;
 		fflush(stdin);
 		fin.open("Accounts_info", ios::in);
 		while(fin >> ob.id_pass.first >>ob.id_pass.second)
 		{
 			if(ob.id_pass.first==usr_nm && ob.id_pass.second==password)
 				return usr_nm;	
 			else if(ob.id_pass.first==usr_nm && ob.id_pass.second!=password)
 			{
 				cout<<ob.id_pass.first<<"  "<<ob.id_pass.second<<endl;
 				fin.close();
 				cout<<"\t\t\tPassword Incorrect\n";
 				return "\0";
 			}
 		}
 		cout<<"\t\tYour account doesn't exist\n\t\tRegister to continue";
 		fin.close();
 		return "\0";
 	}
 	//User Function to modify his/her profile.(K)
 	//It takes user_name as input and modify account data of particular user.
 	//Note user is not permitted to modify his/her username
 	void modifyProfile(string usr_nm)
 	{
 		Register ob;
 		fin.open("Accounts_info",ios::in);
 		fout.open("temp",ios::out);
 		while(fin >> ob.name.first >> ob.name.second >> ob.id_pass.first >>ob.id_pass.second >>ob.phone_no>>ob.email)
 		{
 			if(ob.id_pass.first!=usr_nm)
 				fout<<ob.name.first<<" "<<ob.name.second<<" "<<ob.id_pass.first<<" "
 					<<ob.id_pass.second<<" "<<ob.phone_no<<" "<<ob.email<<"\n";
 			else
 			{
 				//Here also validation procedures has been used to keep track of valid data.
 				//Username of the user can not be modified as it is the key or the session value by which 
 				//user has been logged in.
 				cout<<"\t\tNote : You can't modify your username\n";
 				cin.ignore();
 				cout<<"Enter your first name :";
 				getline(cin,ob.name.first);
 				cout<<"Enter your second name :";
 				getline(cin,ob.name.second);
 				cout<<"Enter the password : ";
 				getline(cin,ob.id_pass.second);
 				PHONE :
			 		cout<<"Enter the phone number : ";
			 		getline(cin,ob.phone_no);
			 		if(!isValidPhone(ob.phone_no))
			 		{
			 			cout<<"Phone number not correct!!! Try again\n";
			 			goto PHONE;
			 		}
		 		EMAIL :
		 			cout<<"Enter your email address : ";
		 			getline(cin,ob.email);
		 			if(!isValidEmail(ob.email))
		 			{
		 				cout<<"Email not correct!!! Try again\n";
		 				goto EMAIL;
		 			}
 				fout<<ob.name.first<<" "<<ob.name.second<<" "<<ob.id_pass.first<<" "
 					<<ob.id_pass.second<<" "<<ob.phone_no<<" "<<ob.email<<"\n";
 			}
 		}
 		fin.close();
 		fout.close();
 		remove("Accounts_info");
 		rename("temp","Accounts_info");
 		cout<<"\n\t\tAccount data modified";
 	}
 	//User Function if he/she wants to delete his profile.(K)
 	//This will take user name as input and profile with that user name will be deleted.
 	void deleteProfile(string usr_nm)
 	{
 		Register ob;
 		fin.open("Accounts_info",ios::in);
 		fout.open("temp",ios::out);
 		while(fin >> ob.name.first >> ob.name.second >> ob.id_pass.first >>ob.id_pass.second >>ob.phone_no>>ob.email)
 		{
 			if(ob.id_pass.first!=usr_nm)
 				fout<<ob.name.first<<" "<<ob.name.second<<" "<<ob.id_pass.first<<" "
 					<<ob.id_pass.second<<" "<<ob.phone_no<<" "<<ob.email<<"\n";
 		}
 		fin.close();
 		fout.close();
 		remove("Accounts_info");
 		rename("temp","Accounts_info");
 		cout<<"\n\t\tProfile with username : "<<usr_nm<<" deleted";
 	}
}

