/*
Program:	reformat
Author:		Gerardo Valtazar
Date:		2019
Compiler:	g++
About:
	The purpose of this program is to reformat the file, applist.
	applist is populated by the application gtk_menu via a terminal command
	the terminal command used to populate the file is currently 
	ls -D1 /usr/share/applications > applist
*/

#include "stdio.h"
#include <string>
#include <iostream>
#include <regex>
#include <fstream>

using std::cout; using std::string; using std::endl;
int row_count();
void store_text(int l_count);

int main(){
	int line_count = row_count(); //counts length of the file "applist"
	store_text(line_count); //writes application names to file "applist"
return 0;
}

int row_count(){

	std::ifstream in_text;
	in_text.open("applist");
	string r_line;
	int l_count=0;

	if(in_text.is_open()){
		while(in_text.good()){
			getline(in_text, r_line);
			l_count++;
		} in_text.close();
	}
// for testing purposes cout<<"installed apllication count:\t"<<l_count<<endl;
	return l_count;
}

void store_text(int l_count){

	/* the temp_buffer array is created to avoid data races it also allows us to 
	wright over the same file and avoid creating another file, we use l_count+10
	to avoid out of bounds errors, it isn't constant because application numbers 
	can varry allot, while the 2nd input of 200 is also to avoid out of bounds errors
	it also seems like a reasonable character count for any application name */
	char temp_buffer[l_count+10][200];

	std::ifstream in_text; //creates input stream object
	std::ofstream out_text;//creates output stream object
	string r_line; //will hold line of text while itterating through the file

	int c_line = 0; //will hold the number of the current line being read in
	in_text.open("applist");//opens file for reading
	if(in_text.is_open()){
		while(in_text.good()){ //in_text.good() is best practice 
			getline(in_text, r_line); //reads in file line by line
				for(int i=0;i<r_line.length();i++){
		temp_buffer[c_line][i] = r_line[i];} c_line++; }	
	} in_text.close(); //closes stream
	
	out_text.open("applist"); //opens file for writing
	std::regex reg_exp(".desktop"); //this pattern will be replaced in the file 
	for(int i=0;i<l_count-1;i++){
		/*replaces the regex expression with an empty string using the command
		std::regex_replace and then writes changes to the file via out_text" */
		out_text <<  std::regex_replace(temp_buffer[i], reg_exp, "") <<'\n';
// for testing purposes std::printf("%s\n",temp_buffer[i]);
	} out_text.close(); //closes stream
}
