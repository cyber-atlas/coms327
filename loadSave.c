#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <endian.h>


//Makes the directory. Ignores the error that occurs if it walready exists.
int makeDirectory(){
	mkdir ~/.
}

void reader(char *path){
	//Still not sure about this next line, look into it some more
	FILE *file;
	//Saves the mode as rb for read bianry
	char *mode = "rb";
	file = fopen(char *filePath, char *mode);
	if (file == NULL){
		fprintf(stderr, "Could not open file");
		exit(1);
	}
	
	fread(file, 12,);

}

void writer(){
	
	FILE *file;



}




void dungeon (){
	FILE *file;	
}



int main(){
	
	//gets the lenght of the file name
	//the +1 accounts for the null character
	int length = strlen(getenv("HOME"))+strlen("/.rlg327/dungeon")+1;
	//pointer to the string of the file name.
	char *p = malloc(length *sizeof (char));
	
}




//TODO check the home directory and make sure that there is the directory .rlg327. If not, create it
//TODO if switch --save is called. Save the state HOW 
//TODO two functions. fopen, gives you a file struct pointer which is an argument to (FILE) fwrite
//
/
//
//TODO make a rock array that is the size of the dungeon and generate all values to be larger than 0. Then go through and change all the hardness of rooms and corridors to 0. 
//
//TODO for the last part each room has 4 8 bits unsigned. 
