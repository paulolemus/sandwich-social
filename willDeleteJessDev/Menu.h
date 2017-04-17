//intro stuff
//

#ifndef _MENU_H
#define _MENU_H

#define NUM_C 5
#include<ncurses.h>
#include<string>
using namespace std;

class myMenus{
	private: 
		int yMax;
		int xMax;
		int yBeg;	
		int xBeg;
		int Depth;
		int Width;
		int Fraction; 
	
		int num_choices;
		string choices [NUM_C]; 
		
		WINDOW * menuTemplate;
	public:
		myMenus();
		myMenus(int a, int b); 

		void setyMax(int a); 
		void setxMax(int a); 

		//double inputs
		void setyBeg(int a, int b); 
		void setxBeg(int a, int b); 
		void setDepth(int a, int b); 
		void setWidth(int a, int b);

		void setFraction (int a); 
		void setmenuTemplate(int a, int b, int c, int d);

		//getters
		int getyMax(); 
		int getxMax(); 
		int getyBeg(); 
		int getxBeg(); 
		int getDepth(); 
		int getWidth(); 	
		WINDOW * getmenuTemplate();

		//print
		void print_menu(WINDOW * w, int h, int n, string s[], int d); 	
}; 




#endif // _MENU_H
