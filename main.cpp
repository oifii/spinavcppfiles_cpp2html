/*
 * Copyright (c) 2010-2016 Stephane Poirier
 *
 * stephane.poirier@oifii.org
 *
 * Stephane Poirier
 * 3532 rue Ste-Famille, #3
 * Montreal, QC, H2X 2L1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <string>
#include <fstream>
#include <vector>

#include <iostream>
#include <sstream>
using namespace std;
//#include <stdlib.h>


#include <ctime>

int main(int argc, char *argv[])
{
	///////////////////
	//read in arguments
	///////////////////
	//char charBuffer[2048] = {"."}; //usage: spinavcppfiles "."
	char charBuffer[2048] = {"C:\\oifii-org\\httpdocs\\ns-org\\nsd\\ar\\cp\\audio_spi"}; 
	//char charBuffer[2048] = {"testmidfolder"}; 
	if(argc>1)
	{
		//first argument is the folder name where to find .mid files
		sprintf_s(charBuffer,2048-1,argv[1]);
	}

	/////////////////////////////////////////////////////
	//execute cmd line to get all folder's .mid filenames
	/////////////////////////////////////////////////////
	string quote = "\"";
	string pathfilter;
	string path=charBuffer;
	string systemcommand;
	pathfilter = path + "\\*.cpp";
	systemcommand = "DIR " + quote + pathfilter + quote + "/S /B /O:N > filenames1.txt";
#ifdef _DEBUG
	cout << systemcommand << endl;
#endif //_DEBUG
	system(systemcommand.c_str());

	pathfilter = path + "\\*.c";
	systemcommand = "DIR " + quote + pathfilter + quote + "/S /B /O:N > filenames2.txt";
#ifdef _DEBUG
	cout << systemcommand << endl;
#endif //_DEBUG
	system(systemcommand.c_str());

	pathfilter = path + "\\*.h";
	systemcommand = "DIR " + quote + pathfilter + quote + "/S /B /O:N > filenames3.txt";
#ifdef _DEBUG
	cout << systemcommand << endl;
#endif //_DEBUG
	system(systemcommand.c_str());


	///////////////////////////////////////
	//load filenames.txt into string vector
	///////////////////////////////////////
	vector<string> filenames;
	string temp;
	ifstream ifs1("filenames1.txt");
	while(getline(ifs1,temp))
		filenames.push_back(temp);
	ifstream ifs2("filenames2.txt");
	while(getline(ifs2,temp))
		filenames.push_back(temp);
	ifstream ifs3("filenames3.txt");
	while(getline(ifs3,temp))
		filenames.push_back(temp);


	////////////////////////////////////////////////
	//browse through filenames and call cpp2html.exe
	////////////////////////////////////////////////
	vector<string>::iterator it;
	//cout << "filenames.txt contains:";
	
	it=filenames.begin();
	for ( it=filenames.begin() ; it < filenames.end(); it++ )
	{
		//cout << *it << endl; //*it is a .mid filename

		systemcommand = "cpp2html.exe " + quote + *it + quote + " ";
		cout << systemcommand << endl;
		system(systemcommand.c_str()); 
	}
	cout << endl;	
	return 0;
}