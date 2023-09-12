#include <iostream>
#include<fstream>
#include<windows.h>

using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);//color related

//initializing board arrays
int Board[9][9], changeable[9][9];

//menus
void load_game();
void showboard();
int options_menu();

//user input for index and value
int enter_value();

//check functions
bool column(int c, int& value);
bool row(int r, int& value);
bool box(int r, int c, int& value);
bool is_out_of_range(int Min, int Max, int value);


int main()
{

	int a;  //variable for loop, disregard
	int opt;//option entered by user


//game start menu
here:
	load_game();
	system("cls");
	showboard();

//game options menu
menu:
	opt=options_menu();

	//switch case to carry out users selected options
	switch (opt)
	{
	case 1:
		{
			do
			{
				a=enter_value();
				system("cls");
				showboard();
			}while(a!=-1);
			goto menu;
		}
		break;

	case 2:
		{
			system("cls");
			goto here;
		}
		break;

	case 3:
	    {
	        break;
	    }

	default : break;

	}

	return 0;

}

//_____________________________________________________________________________________
//FUNCTION BODIES

void load_game()
{
	int no, game, pass;
	ifstream CIN;
	CIN.open("games.txt");

	if(!CIN.is_open())
	{
		cout<<"File error"<<endl;
		return;
	}
	CIN>>no;


		cout<<"Please enter the difficulty level\n"
			<<"1. School of Education\n"
			<<"2. SDSB\n"
			<<"3. SAHSOL\n"
			<<"4. HSS\n"
			<<"5. SSE"<<endl;
    do
    {
		cout<<"Difficulty: ";
		cin>>game;
        if(game==5)
        {
            cout<<"\nYou must Really hate your life.\n";
            system("pause");
        }
	}while(is_out_of_range(1,5,game)==true);


	for(int i=0; i<((game-1)*9*9); i++)
	{
		CIN>>pass;
	}

	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			CIN>>Board[i][j];
			if(Board[i][j]==0)
				changeable[i][j]=1;
			else
				changeable[i][j]=0;
		}
	}
	CIN.close();
}
void showboard()
{
	cout<<"********************Sudoku*******************\n";
	cout<<"\t  ";

	for(int i=0; i<9; i++)
	{
		if(i%3==0 && i!=0)
		{
			cout<<" "<<i+1<<"  ";
		}
		else
			cout<<i+1<<"  ";
	}
	cout<<"\n\n\t";

	for(int j=0; j<30; j++)
    {
        cout<<"-";
    }
	cout<<"\n";

	for(int i=0; i<9; i++)
	{
		if(i%3==0 && i!=0)
		{
			cout<<"\t";
			for(int j=0; j<30; j++)
            {
                cout<<"-";
            }

			cout<<endl;
			cout<<i+1<<"\t|";
		}
		else
			cout<<i+1<<"\t|";
		for(int j=0; j<9; j++)
		{
			if(j%3==0&& j!=0)
				cout<<"|";
			if(Board[i][j]==0)
				cout<<"   ";
			else
			{
				cout<<" ";
				if(changeable[i][j]==0)
					SetConsoleTextAttribute(console, 6);
				cout<<Board[i][j];
				if(changeable[i][j]==0)
					SetConsoleTextAttribute(console, 15);
				cout<<" ";

			}
		}
		if(i!=8)
			cout<<"|"<<endl<<endl;
		else
		{
			cout<<"|"<<endl;
			cout<<"\t";
			for(int j=0; j<30; j++)
				cout<<"-";
		}
	}
	cout<<endl;
}
int options_menu()
{
    int option;
    cout<<"1. Enter Values in game.\n"
		<<"2. Start new game.\n"
		<<"3. to exit."<<endl;
	cout<<"Option: ";
	cin>>option;
    is_out_of_range(1,3,option);
return option;
}

/*function that takes the row and column index of value to be changed
  and then assigns that value to said index*/
int enter_value()
{
	//initilizing the values of the row, column and the value fetched from the user
	int r, c, value;

    //fetching the indexes for the position user wants to change
	do
	{
		//Row Input
		do
        {
            cout<<"\nEnter the row number to enter/change value(-1 to go back to menu)\n";
            cout<<"Row: ";
            cin>>r;
            //in case user changed their mind and wants to return to menu
            if(r==-1)
            {
                return -1;
            }
        }while(is_out_of_range(0,9,r)==true);

        //Column Input
		do
        {
            cout<<"Enter the column number to enter/change value(-1 to go back to menu)\n";
            cout<<"Column: ";
            cin>>c;
            //in case user changed their mind and wants to return to menu
            if(c==-1)
            {
                return -1;
            }
        }while(is_out_of_range(1,9,c)==true);


        //checking if the value at the user entered index is changeable or not
		if(changeable[r-1][c-1]==0)
		{
			cout<<"You can not change this value"<<endl;
		}
	}while(changeable[r-1][c-1]==0);



//fetching the value to be assigned
do
{
    	cout<<"\nPlease enter the value  ";
        cin>>value;

        //we check if value entered is within the range
        is_out_of_range(1,9,value);

        //check is if the value exists in the entered column
        if (column(c, value)==1)
        {
            cout<<"\nThe value you entered already exists in the column no. "<<c;

        }

        //check is if the value exists in the entered row
        else if (row(r, value)==1)
        {
            cout<<"\nThe value you entered already exists in the row no."<<r;

        }

        //check is if the value exists in the entered box (3x3 box)
        else if (box(r, c, value)==1)
        {
            cout<<"\nThe value you entered already exists in the box";

        }

        //if all checks pass the value is assigned to the board
        else
        {
            Board[r-1][c-1]=value;
            break;

        }
}while(true);

	return 0;
}
//range check function, takes lower bound, upper bound and the value to be checked(in)
bool is_out_of_range(int Min, int Max, int value)
{
    if (value<Min||value>Max)
    {
        cout<<"\nValue is out of Range!!";
        cout<<"\nEnter Values Between "<< Min << " & " << Max<<endl;
        return 1;
    }
    else
    {
        return 0;
    }

}
//function to enter column values to the board
bool column(int c, int& value)
{
	for (int i=0; i<9; i++)
	{
		if (Board[i][c-1]==value)
		{
			return 1;
		}
	}
	return 0;
}
//function to enter column values to the board
bool row(int r, int& value)
{
	for (int j=0; j<9; j++)
	{
		if (Board[r-1][j]==value)
		{
			return 1;
		}
	}
	return 0;
}
bool box(int r, int c, int & value)
{
	//basic functionality of suduko
	//code checks if the box contains the value
	int SC, SR;
	if (r==1 || r==2 || r==3)
	{
		SR=0;
	}
	else if (r==4 || r==5 || r==6)
	{
		SR=3;
	}
	else if (r==7 || r==8 || r==9)
	{
		SR=6;
	}

	if (c==1 || c==2 || c==3)
	{
		SC=0;
	}
	else if (c==4 || c==5 || c==6)
	{
		SC=3;
	}
	else if (c==7 || c==8 || c==9)
	{
		SC=6;
	}

	for( int i=SR; i< SR+3; i++)
	{
		for (int j=SC; j< SC+3; j++)
		{
			if (Board[i][j]==value)
			{
				return 1;
			}

		}

	}

	return 0;
}


