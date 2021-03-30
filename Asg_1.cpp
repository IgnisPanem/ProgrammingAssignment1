//This program can take a url and split it up into its parts. If the url is not valid, it will display what is wrong.
#include <iostream>
#include <string.h>
#include <cstdlib>
#include "version.cpp"
using namespace std;

//split URL prototype.
void splitURL(string url,string &protocol, string &domain, string &port, string &file_path, string &parameters, bool &valid);
//checking the domain prototype.
void validDomain (bool &valid, string domain);
//printing the valid parts
void printValid (string protocol, string domain, string port, string file_path, string parameters);

int main()
{
	//Display version	
	displayVersion();
	//Create Variables
	string url, protocol, domain, port, file_path, parameters;
	bool valid = true;

	//Get the URL
	cout << "Enter a URL:\n";
	getline (cin, url);
	splitURL(url,protocol,domain,port,file_path,parameters,valid);
	
	//if the url was valid
	if (valid == true)
	{
		//print the parts of the url
		printValid(protocol,domain,port,file_path,parameters);
	}
	return 0;
}

//This function splits up a url, and also checks for some errors.
void splitURL(string url,string &protocol, string &domain, string &port, string &file_path, string &parameters, bool &valid)
{
	int counter = 0;
	int start = 0;
	char found;
	bool portFound = false;
	
	//Check every character in the url
	while (found != '\n')
	{
		found = url[counter];
		//check for ":"
		if (found == ':')
		{
			//check for "://"
			if (url[counter + 1] == '/')
			{
				//create a substring for the protocol
				protocol = url.substr (start, (counter) - start);
				
				// check for a valid protocol
				if (protocol != "http" && protocol != "https" && protocol != "ftp" && protocol != "ftps")
				{
					// check if this is the first error.
					if (valid == true)
					{
						cout << endl << "Invalid URL with the following erroneous components:" << endl;
					}
					valid = false;
					cout << "Protocol:\t" + protocol + " is an invalid protocol." << endl;
					
				}
				//put the counter past the "://"
				counter += 2;
				//put the start past the "://"
				start = counter + 1;
			}
			//else it is the colon before the port;
			else 
			{
				portFound = true;
				
				//create a substring for the domain
				domain = url.substr (start, (counter) - start);
				
				//check the domain for validity
				validDomain(valid, domain);
				
				//find the port
				start = counter + 1;
				while (found != '/')
				{
					counter ++;
					found = url[counter];
				}
				
				//create the port substring;
				port = url.substr(start, (counter) - start);
				counter --;
				
				int portInt;
				//convert port string to an into
				try
				{
					portInt = stoi(port);
					if (portInt < 1 || portInt > 65535)
					{
						if (valid == true)
						{
							cout << endl << "Invalid URL with the following erroneous components:" << endl;
						}
						valid = false;
						cout << "Port:\t\tport number must be between 1 and 65535" << endl;
					}
				}
				catch(exception e)
				{
				// check if this is the first error.
					if (valid == true)
					{
						cout << endl << "Invalid URL with the following erroneous components:" << endl;
					}
					valid = false;
					cout << "Port:\t\t" + port + " is an invalid port." << endl;
				}
				
			}
		}
		else if (found == '/') 
		{
			//If there was no port, find the domain.
			if(portFound == false)
			{
				//create a substring for the domain
				domain = url.substr (start, (counter) - start);
				
				//check the domain for validity
				validDomain(valid, domain);
			}
			
			start = counter;
			// find the length of the file path
			while (found != '?' && found != '\0')
			{ 
				found = url[counter];
				counter++;
			}
			
			// create the file path
			file_path = url.substr(start, (counter - 1) - start);
			
			//check the file path validity.
			string ending = file_path.substr(file_path.length() - 4, 4);
			if (ending != ".htm")
			{
				string ending = file_path.substr(file_path.length() - 5, 5);
				if (ending != ".html")
				{
					// check if this is the first error.
					if (valid == true)
					{
						cout << endl << "Invalid URL with the following erroneous components:" << endl;
					}
					valid = false;
					cout << "File path:\tFile path ending is not .htm or .html" << endl;
				}
			}
			
			// if there were parameters
			if(found == '?')
			{
				start = counter;
				parameters = url.substr(start, (url.length()) - start);
			}
			found = '\n';
		}
		
		counter++;
	}
	//check for no Protocol
	if (protocol == "")
	{
	// check if this is the first error.
		if (valid == true)
		{
			cout << endl << "Invalid URL with the following erroneous components:" << endl;
		}
		valid = false;
		cout << "File path:\tthere is no file path." << endl;
				
	}
	return;
}

//This function checks the validity of a domain.
void validDomain (bool &valid, string domain)
{
	int start = 0;
	int dotNum = 0;
	char found;
	string domEnd;
	
	// find the amount of "." in the domain
	for (int i = 0; i < domain.length() - 1; i++)
	{
		found = domain[i];
		if (found == '.' && domain[i-1] != '.' && domain [i+1] != '.' && i != 0)
		{
			dotNum += 1;
			start = i;
		}
	}
	//check for valid format
	if (dotNum != 2)
	{
		// check if this is the first error.
		if (valid == true)
		{
			cout << endl << "Invalid URL with the following erroneous components:" << endl;
		}
			valid = false;
			cout << "Domain:\t\tDomain is in improper format: <x>.<y>.<z>" << endl;
			return;
	}
	//check for valid domain final
	domEnd = domain.substr(start + 1, (domain.length()) - (start + 1));
	if (domEnd != "com" && domEnd != "net" && domEnd != "edu" && domEnd != "biz" && domEnd != "gov")
	{
		// check if this is the first error.
		if (valid == true)
		{
			cout << endl << "Invalid URL with the following erroneous components:" << endl;
		}
			valid = false;
			cout << "Domain:\t\tDomain has an improper ending: " + domEnd << endl;
	}
	return;
}

void printValid (string protocol, string domain, string port, string file_path, string parameters)
{
	//Print all the url parts
	cout << endl << "Protocol:\t" + protocol << endl;	
	cout << "Domain:\t\t" + domain << endl;
	if (port != "")	//check for a Port
	cout << "Port:\t\t" + port << endl;
	cout << "File path:\t" + file_path << endl;
	if (parameters != "")	//check for parameters
	cout << "Parameters:\t" + parameters << endl;
	
	return;
}
