/*
Disclaimer:  This program belongs to Denis Nadarevic and is used for educational purposes at
			 the University of Windsor.

Description: This program creates a binary ppm file with 1000 by 1000 pixels. It uses five input
             colors to draw a picture. The input colors can be: red, green, blue, yellow, orange, cyan, magenta, ocean, violet.
			 This program implements signals.
			 
			 
Date due:    March 17th, 2019
*/
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

//input ex: kindergarten drawing.ppm blue green red yellow magenta


//Stores the RGB values of a specific color
typedef struct color {
	int r; //red
	int g; //green
	int b; //blue
}Color;

//Prototypes
void stringToColor(char * str, Color * color);
void sigHandler() {}


int main (int arg_c, char * arg_v[])
{
	signal(SIGUSR1, sigHandler);
	pid_t IDkids[10];
	Color colors[5]; //hold all of the user's color choices;
	int len = 1000; //for specifying the size
	int kids = 10; //for specifying how many kids will be made
	
	if (arg_c != 7) return 0;
	
	//convert all the inputs into actual colors
	for (int i = 0 ; i < 5 ; i++) {stringToColor(arg_v[i+2], colors + i);}
	char* name = arg_v[1];
	int finalImage = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	int finalLength;
	
	//will only run if the user inputs exactly 7 arguments to the console
	if (arg_c == 7)
	{
		char * temp = "P6\n1000 1000\n255\n";
		write(finalImage, temp, strlen(temp)); //writes in the bitmap information into the final image
		finalLength = strlen(temp);
	}
	
	close(finalImage); //finished preparing image
	
	char c[3]; //temporary storage for colors being written into the final image
	//following forloop writes in the colors in their respective locations
	
	int m; //for storing when needed
	int dia;
	int pid;
	int status;
	for (int i = 0 ; i < kids ; i++)
	{
		if ((IDkids[i] = fork()) == 0)
		{
			sleep(1);
			kill(getppid(), SIGUSR1); //wake up the parent
			pause();
			int finalImage = open(name, O_WRONLY, 0777);
			lseek(finalImage, (len/kids) * len * 3 * i + finalLength, SEEK_SET);
			
			for (int j = 0; j < (len/kids) ; j++)
			{
				if (i < kids/2)
				{
					//store first second colour inputted into a temp array and write the temp array colour information into the final image
					*c = colors[1].r;
					*(c+1) = colors[1].g;
					*(c+2) = colors[1].b;
					
					for (int b = 0 ; b < (len/2) ; b++)
					{
						write(finalImage, c, 3); //writes the colours until it reaches half the screen size
					}
					
					//set temp array to second color inputted
					//since there has been no reset to the writing pointer, we can
					//continue writing until we complete the first row
					*c = colors[2].r;
					*(c+1) = colors[2].g;
					*(c+2) = colors[2].b;
					
					for (int b = 0 ; b < (len/2) ; b++)
					{
						write(finalImage, c, 3); //writes the colours until it reaches half the screen size
					}
					
					if ((dia = 2 * (i * (len / kids) + j - (len/4))) >= 0)
					{
						//set temp array to centre color
						*c = colors[0].r;
						*(c + 1) = colors[0].g;
						*(c + 2) = colors[0].b;
						lseek(finalImage, (-1 * len * 3) + (len / 2) * 3 - dia * 3 / 2, SEEK_CUR);
						
						for (int b = 0; b < dia; b++) 
						{
							write(finalImage, c, 3);
						}
						lseek(finalImage, len/2*3 - dia*3/2, SEEK_CUR);
					}
					
				}
				
				else {
					*c = colors[3].r;
					*(c + 1) = colors[3].g;
					*(c + 2) = colors[3].b;
					
					for(int m = 0; m < len / 2; m++) {
						write(finalImage, c, 3);
					}
					
					*c = colors[4].r;
					*(c + 1) = colors[4].g;
					*(c + 2) = colors[4].b;

					for (int m = 0; m < len / 2; m++) {
						write(finalImage, c, 3);
					}
					
					if ((dia = 2 * (3 * len / 4 - i * (len / kids) - j)) > 0) {
						*c = colors[0].r;
						*(c + 1) = colors[0].g;
						*(c + 2) = colors[0].b;
						
						lseek(finalImage, (-1 * len * 3) + len / 2 * 3 - dia * 3 / 2, SEEK_CUR);

						for(int x=0; x < dia ; x++){
							write(finalImage, c, 3);
						}

						lseek(finalImage, len / 2 * 3 - dia * 3 / 2, SEEK_CUR);
					}
				}
			}
			close(finalImage);

			sleep(1);
			kill(getppid(), SIGUSR1);
			exit(0);
		}
		else {
			pause();
		}
		
	}
	
	for (int i =0 ; i < kids ; i++)
		{
			kill(IDkids[i], SIGUSR1);
			pause();
		}
	return 0;
}


/*
* Function takes in a string to convert and the location to store the color and changes the colors to properly fit the data types of the struct above.
* Parameters: array pointer, pointer to color
* Return: void
*/
void stringToColor(char * str, Color * color)
{
	Color buff; //temporary for storing
	if (strcmp(str, "red") == 0) 		  {buff.r = 255; buff.g = 0; buff.b = 0;}
	else if (strcmp(str, "green") == 0)   {buff.r = 0; buff.g = 255; buff.b = 0;}
	else if (strcmp(str, "blue") == 0)    {buff.r = 0; buff.g = 0; buff.b = 255;}
	else if (strcmp(str, "yellow") == 0)  {buff.r = 255; buff.g = 255; buff.b = 0;}
	else if (strcmp(str, "orange") == 0)  {buff.r = 255; buff.g = 165; buff.b = 0;}
	else if (strcmp(str, "cyan") == 0)    {buff.r = 0; buff.g = 255; buff.b = 255;}
	else if (strcmp(str, "magenta") == 0) {buff.r = 255; buff.g = 0; buff.b = 255;}
	else if (strcmp(str, "ocean") == 0)   {buff.r = 0; buff.g = 119; buff.b = 190;}
	else if (strcmp(str, "violet") == 0)  {buff.r = 238; buff.g = 130; buff.b = 238;}
	else    {buff.r = 0; buff.g = 0; buff.b = 0;}
	
	*color = buff;
}