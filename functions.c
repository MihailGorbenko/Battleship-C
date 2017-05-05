#include "header.h"


int fieldPoint[2]; // coordinates first deck of ship  1-X;  0-Y;
//****************************
void playerShipsAutoPlacing(int field[][SIZE], FLEET * playerFleet){
	int D3_shipID = 0;
	int D2_shipID = 0;
	int D1_shipID = 0;
	for (int i = 0; i < 10; i++){
		switch (i){
		case 0:   //four deck ship (1)
		{
			shipPlace(4, field, playerFleet, 0);
			break;
		}
		case 1:
		case 2: //three deck ship (2)
		{
			shipPlace(3, field, playerFleet, D3_shipID);
			D3_shipID++;
			break;
		}
		case 3:
		case 4:
		case 5: // two eck ship (3)
		{
			shipPlace(2, field, playerFleet, D2_shipID);
			D2_shipID++;
			break;
		}
		default: //one deck ship (4)
		{
			shipPlace(1, field, playerFleet, D1_shipID);
			D1_shipID++;
			break;
		}
		}
	}
}
//*******************************************
void shipPlace(int deck_count , int field[][SIZE], FLEET * currentFleet, int shipID){
	
	if (deck_count == 4){  //four deck ship without  collision detection
		int direction = rand() % 2;
		if (direction == HORISONT){
			fieldPoint[0] = rand() % 10; // Y coordinate
			fieldPoint[1] = rand() % 7; // X coordinate
			currentFleet->fourDeckShip.locationY[0] = (fieldPoint[0]);
			for (int i = 0; i < deck_count; i++){
				//WRITING COORDINATES ON SHIPS
				currentFleet->fourDeckShip.locationX[i] = (fieldPoint[1] + i);
				//placing
				field[(fieldPoint[0])][(fieldPoint[1]) + i] = 4;
			}
		}
		else{                    // VERTICAL
			fieldPoint[0] = rand() % 7; // Y coordinate
			fieldPoint[1] = rand() % 10; // X coordinate
			currentFleet->fourDeckShip.locationX[0] = (fieldPoint[1]);
			for (int i = 0; i < deck_count; i++){
				//WRITING COORDINATES ON SHIPS
				currentFleet->fourDeckShip.locationY[i] = (fieldPoint[0] + i);
				//placing
				field[(fieldPoint[0] + i)][(fieldPoint[1])] = 4;
			}
		}
	}
	else if (deck_count == 1){
		bool permitionToPlace = false;
		do{
			fieldPoint[0] = rand() % 10; // Y coordinate
			fieldPoint[1] = rand() % 10; // X coordinate
			if (collisionDetection(field, deck_count, 0, fieldPoint[0], fieldPoint[1]))
			{
				permitionToPlace = true;
				break;
			}
			else continue;
		} while (!permitionToPlace);
		if (permitionToPlace){
			//WRITING COORDINATES  Y & X ON SHIPS
			currentFleet->oneDeckShip[shipID].locationY[0] = (fieldPoint[0]);
			currentFleet->oneDeckShip[shipID].locationX[0] = (fieldPoint[1]);
			//placing
			field[(fieldPoint[0])][(fieldPoint[1])] = deck_count;
		}
	}
	else {                         //2,3 - deck ships with collision detection

		int direction = rand() % 2;
		if (direction == HORISONT){
			bool permitionToPlace = false;
			do{
				fieldPoint[0] = rand() % 10; // Y coordinate
				fieldPoint[1] = rand() % (SIZE - deck_count + 1); // X coordinate
				if (collisionDetection(field, deck_count, HORISONT, fieldPoint[0], fieldPoint[1]))
				{
					permitionToPlace = true;
					break;
				}
				else continue;
			} while (!permitionToPlace);
			if (permitionToPlace){
				//WRITING COORDINATES Y ON SHIPS
				if (deck_count == 2){
					currentFleet->twoDeckShip[shipID].locationY[0] = (fieldPoint[0]);
				}
				else{
					currentFleet->threeDeckShip[shipID].locationY[0] = (fieldPoint[0]);
				}
				for (int i = 0; i < deck_count; i++){
					//WRITING COORDINATES X ON SHIPS
					if (deck_count == 2){
						currentFleet->twoDeckShip[shipID].locationX[i] = (fieldPoint[1] + i);
					}
					else{
						currentFleet->threeDeckShip[shipID].locationX[i] = (fieldPoint[1] + i);
					}
					//placing
					field[(fieldPoint[0])][(fieldPoint[1] + i)] = deck_count;
				}
			}
		}
		else{                    // VERTICAL
			bool permitionToPlace = false;
			do{
				fieldPoint[0] = rand() % (SIZE - deck_count + 1); // Y coordinate
				fieldPoint[1] = rand() % 10; // X coordinate
				if (collisionDetection(field, deck_count, VERTICAL, fieldPoint[0], fieldPoint[1])){
					permitionToPlace = true;
					break;
				}
				else continue;
			} while (!permitionToPlace);
			if (permitionToPlace){
				//WRITING COORDINATES X ON SHIPS
				if (deck_count == 2){
					currentFleet->twoDeckShip[shipID].locationX[0] = (fieldPoint[1]);
				}
				else{
					currentFleet->threeDeckShip[shipID].locationX[0] = (fieldPoint[1]);
				}
				for (int i = 0; i < deck_count; i++){
					//WRITING COORDINATES Y ON SHIPS
					if (deck_count == 2){
						currentFleet->twoDeckShip[shipID].locationY[i] = (fieldPoint[0] + i);
					}
					else{
						currentFleet->threeDeckShip[shipID].locationY[i] = (fieldPoint[0] + i);
					}
					//placing
					field[(fieldPoint[0] + i)][(fieldPoint[1])] = deck_count;
				}
			}
		}
	}
}
//***********************************************
bool collisionDetection(int field[][SIZE], int deck_quantity, int direction, int y, int x){
	for (int i = 0; i < deck_quantity; i++){
		if (field[y][x]>0){
			return false;
		}
		if (x > 0){
			if (field[y][x - 1] > 0){
				return false;
			}
			if (y > 0){
				if (field[y - 1][x - 1] > 0){
					return false;
				}
			}
			if (y < 9){
				if (field[y + 1][x - 1]>0){
					return false;
				}
			}
		}
		if (x < 9){
			if (field[y][x + 1]>0){
				return false;
			}
			if (y > 0){
				if (field[y - 1][x + 1] > 0){
					return false;
				}
			}
			if (y < 9){
				if (field[y + 1][x + 1]>0){
					return false;
				}
			}
		}
		if (y > 0){

			if (field[y - 1][x] > 0){ return false; }

		}
		if (y < 9){
			if (field[y + 1][x]>0){
				return false;
			}
		}

		if (direction == HORISONT)x++;
		else y++;
	}
	return true;
}

//*************************************
void PCshipsPlacing(int field[][SIZE], FLEET * PCfleet){
	int D3_shipID = 0;
	int D2_shipID = 0;
	int D1_shipID = 0;
	for (int i = 0; i < 10; i++){
		switch (i){
		case 0:   //four deck ship (1)
		{
			shipPlace(4, field, PCfleet, 0);
			break;
		}
		case 1:
		case 2: //three deck ship (2)
		{
			shipPlace(3, field, PCfleet, D3_shipID);
			D3_shipID++;
			break;
		}
		case 3:
		case 4:
		case 5: // two eck ship (3)
		{
			shipPlace(2, field, PCfleet, D2_shipID);;
			D2_shipID++;
			break;
		}
		default: //one deck ship (4)
		{
			shipPlace(1, field, PCfleet, D1_shipID);
			D1_shipID++;
			break;
		}
		}
	}
}
//***********************************
void playerShipsHandlePlacing(int field[][SIZE], FLEET * playerFleet, int PCfield[][SIZE]){
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position = { 3, 3 };
	int direction;
	//four deck ship placing
	SetConsoleCursorPosition(Console, Position);
	displayPole(PCfield, field, 0);
	printGameStatus("Choose direction of four-deck ship: (1--Horisontal; 0--Vertical;)   ", NO_ARG);
	while (true){
		scanf("%d", &direction);
		if (direction > 1 || direction < 0){
			printGameStatus("$> Not valid choise! Enter again                            ", PLSTAT_MSG);
		}
		else break;
		while (getchar() != '\n')continue;
	}

	do {
		int y = 0;
		char x = '\0';
		printGameStatus("Enter Y coordinates:(1-10)                                              ", NO_ARG);
		while (true){
			scanf("%d", &y);
			if (y > 10 || y< 1){
				printGameStatus("$> Not valid choise! Enter again                            ", PLSTAT_MSG);
			}
			else if (direction == 0 && y >7)
				printGameStatus("$> Not valid choise! Enter again                       ", PLSTAT_MSG);
			else break;
			while (getchar() != '\n')continue;
		} 
		printGameStatus("Enter X coordinates:(A-J - In upper case)                        ", NO_ARG);
		while (getchar() != '\n')continue;
		while (true){
			scanf("%c", &x);
			if ((int)x <65 || (int)x>74){
				printGameStatus("$> Not valid choise! Enter again                        ", PLSTAT_MSG);
			}
			else if (direction == 0 && (int)x>72)
				printGameStatus("$> Not valid choise! Enter again                       ", PLSTAT_MSG);
			else break;
			while (getchar() != '\n')continue;
		}
		fieldPoint[0] = y - 1;
		fieldPoint[1] = turnInInt(x);
	} while (!handleShipPlace(4, field, playerFleet, direction, 0));
	system("cls");
	SetConsoleCursorPosition(Console, Position);
	displayPole(PCfield, field, 0);
	//three deck ship placing
	for (int i = 0; i < 2; i++){
		int y = 0;
		char x = '\0';
		printGameStatus("Choose direction of  three-deck ship: (1--Horisontal; 0--Vertical;)   ", NO_ARG);
		while (true){
			scanf("%d", &direction);
			if (direction > 1 || direction < 0){
				printGameStatus("$> Not valid choise! Enter again                               ", PLSTAT_MSG);
			}
			else break;
			while (getchar() != '\n')continue;
		}
		int trying = 0;
		do {
			if (trying > 0)printGameStatus("Collision!!!Enter another coordinates                ",  PLSTAT_MSG);
			printGameStatus("Enter Y coordinates:(1-10)                                          ",NO_ARG);
			while (true){
				if (scanf("%d", &y) == 0)printGameStatus("$> Not valid choise! Enter again        ", PLSTAT_MSG);
				if (y > 10 || y< 1){
					printGameStatus("$> Not valid choise! Enter again                             ", PLSTAT_MSG);
				}
				else break;
				while (getchar() != '\n')continue;
			}
			printGameStatus("Enter X coordinates:(A-J - In upper case)                              ",NO_ARG);
			while (getchar() != '\n')continue;
			while (true){
				if (scanf("%c", &x) == 0)printGameStatus("$> Not valid choise! Enter again       ", PLSTAT_MSG);
				if ((int)x < 65 || (int)x > 74){
					printGameStatus("$> Not valid choise! Enter again                             ", PLSTAT_MSG);
				}
				else break;
				while (getchar() != '\n')continue;
			}
			fieldPoint[0] = y - 1;
			fieldPoint[1] = turnInInt(x);
			trying++;
		} while (!handleShipPlace(3, field, playerFleet, direction, i));
		system("cls");
		SetConsoleCursorPosition(Console, Position);
		displayPole(PCfield, field, 0);
	}
	// two deck ship placing
	for (int i = 0; i < 3; i++){
		int y = 0;
		char x = '\0';
		printGameStatus("Choose direction of  two-deck ship: (1--Horisontal; 0--Vertical;)      ", NO_ARG);
		while (true){
			scanf("%d", &direction);
			if (direction > 1 || direction < 0){
				printGameStatus("$> Not valid choise! Enter again                                 ",PLSTAT_MSG);
			}
			else break;
			while (getchar() != '\n')continue;
		}
		int trying = 0;
		do {
			if (trying > 0)printGameStatus("Collision!!!Enter another coordinates                 ", PLSTAT_MSG);

			printGameStatus("Enter Y coordinates:(1-10)                                               ",NO_ARG);
			while (true){
				if (scanf("%d", &y) == 0)printGameStatus("$> Not valid choise! Enter again         ", PLSTAT_MSG);
				if (y > 10 || y< 1){
					printGameStatus("$> Not valid choise! Enter again                              ", PLSTAT_MSG);
				}
				else break;
				while (getchar() != '\n')continue;
			}
			printGameStatus("Enter X coordinates:(A-J - In upper case)                             ",NO_ARG);
			while (getchar() != '\n')continue;
			while (true){
				if (scanf("%c", &x) == 0)printGameStatus("$> Not valid choise! Enter again           ", PLSTAT_MSG);
				if ((int)x < 65 || (int)x > 74){
					printGameStatus("$> Not valid choise! Enter again                              ", PLSTAT_MSG);
				}
				else break;
				while (getchar() != '\n')continue;
			}
			fieldPoint[0] = y - 1;
			fieldPoint[1] = turnInInt(x);
			trying++;
		} while (!handleShipPlace(2, field, playerFleet, direction, i));
		system("cls");
		SetConsoleCursorPosition(Console, Position);
		displayPole(PCfield, field, 0);
	}
	//one deck ship placing
	for (int i = 0; i < 4; i++){
		int y = 0;
		char x = '\0';
		printGameStatus(" one deck ship:                                                          ", NO_ARG);
		int trying = 0;
		do {
			if (trying > 0) printGameStatus("Collision!!!Enter another coordinates                 ", PLSTAT_MSG);
			printGameStatus("Enter Y coordinates:(1-10)                                             ", PLSTAT_MSG);
			while (true){
				if (scanf("%d", &y) == 0)printGameStatus("$> Not valid choise! Enter again        ", PLSTAT_MSG);
				if (y > 10 || y< 1){
					printGameStatus("$> Not valid choise! Enter again                             ", PLSTAT_MSG);
				}
				else break;
				while (getchar() != '\n')continue;
			}
			printGameStatus("Enter X coordinates:(A-J - In upper case)                             ",NO_ARG);
			while (getchar() != '\n')continue;
			while (true){
				if (scanf("%c", &x) == 0)printGameStatus("$> Not valid choise! Enter again         ", PLSTAT_MSG);
				if ((int)x < 65 || (int)x > 74){
					printGameStatus("$> Not valid choise! Enter again                              ", PLSTAT_MSG);
				}
				else break;
				while (getchar() != '\n')continue;
			}
			fieldPoint[0] = y - 1;
			fieldPoint[1] = turnInInt(x);
			trying++;
		} while (!handleShipPlace(1, field, playerFleet, -1, i));
		system("cls");
		SetConsoleCursorPosition(Console, Position);
		displayPole(PCfield, field, 0);
	}
}
//*********************************
bool handleShipPlace(int deck_count, int field[][SIZE], FLEET * currentFleet, int direction, int shipID){
	if (deck_count == 4){  //four deck ship without  collision detection
		if (direction == HORISONT){
			currentFleet->fourDeckShip.locationY[0] = (fieldPoint[0] + 1);
			for (int i = 0; i < deck_count; i++){
				//WRITING COORDINATES ON SHIPS
				currentFleet->fourDeckShip.locationX[i] = (fieldPoint[1] + i + 1);
				//placing
				field[(fieldPoint[0])][(fieldPoint[1]) + i] = 4;
			}
		}
		else{                    // VERTICAL
			currentFleet->fourDeckShip.locationX[0] = (fieldPoint[1] + 1);
			for (int i = 0; i < deck_count; i++){
				//WRITING COORDINATES ON SHIPS
				currentFleet->fourDeckShip.locationY[i] = (fieldPoint[0] + i + 1);
				//placing
				field[(fieldPoint[0] + i)][(fieldPoint[1])] = 4;
			}
		}
		return true;
	}
	else if (deck_count == 1){ //ONE DECK
		bool permitionToPlace = false;
		do{
			if (collisionDetection(field, deck_count, 0, fieldPoint[0], fieldPoint[1]))
			{
				permitionToPlace = true;
				break;
			}
			else return false;
		} while (!permitionToPlace);
		if (permitionToPlace){
			//WRITING COORDINATES  Y & X ON SHIPS
			currentFleet->oneDeckShip[shipID].locationY[0] = (fieldPoint[0] + 1);
			currentFleet->oneDeckShip[shipID].locationX[0] = (fieldPoint[1] + 1);
			//placing
			field[(fieldPoint[0])][(fieldPoint[1])] = deck_count;
		}
		return true;
	}
	else {                         //2,3 - deck ships with collision detection
		if (direction == HORISONT){
			bool permitionToPlace = false;
			do{
				if (collisionDetection(field, deck_count, HORISONT, fieldPoint[0], fieldPoint[1]))
				{
					permitionToPlace = true;
					break;
				}
				else return false;
			} while (!permitionToPlace);
			if (permitionToPlace){
				//WRITING COORDINATES Y ON SHIPS
				if (deck_count == 2){
					currentFleet->twoDeckShip[shipID].locationY[0] = (fieldPoint[0] + 1);
				}
				else{
					currentFleet->threeDeckShip[shipID].locationY[0] = (fieldPoint[0] + 1);
				}
				for (int i = 0; i < deck_count; i++){
					//WRITING COORDINATES X ON SHIPS
					if (deck_count == 2){
						currentFleet->twoDeckShip[shipID].locationX[i] = (fieldPoint[1] + i + 1);
					}
					else{
						currentFleet->threeDeckShip[shipID].locationX[i] = (fieldPoint[1] + i + 1);
					}
					//placing
					field[(fieldPoint[0])][(fieldPoint[1] + i)] = deck_count;
				}
			}
		}
		else{                    // VERTICAL
			bool permitionToPlace = false;
			do{
				if (collisionDetection(field, deck_count, VERTICAL, fieldPoint[0], fieldPoint[1])){
					permitionToPlace = true;
					break;
				}
				else return false;
			} while (!permitionToPlace);
			if (permitionToPlace){
				//WRITING COORDINATES X ON SHIPS
				if (deck_count == 2){
					currentFleet->twoDeckShip[shipID].locationX[0] = (fieldPoint[1] + 1);
				}
				else{
					currentFleet->threeDeckShip[shipID].locationX[0] = (fieldPoint[1] + 1);
				}
				for (int i = 0; i < deck_count; i++){
					//WRITING COORDINATES Y ON SHIPS
					if (deck_count == 2){
						currentFleet->twoDeckShip[shipID].locationY[i] = (fieldPoint[0] + i + 1);
					}
					else{
						currentFleet->threeDeckShip[shipID].locationY[i] = (fieldPoint[0] + i + 1);
					}
					//placing
					field[(fieldPoint[0] + i)][(fieldPoint[1])] = deck_count;
				}
			}
		}
		return true;
	}
	return false;
}

//******************************
int turnInInt(char symb){
	int result;
	if (symb == 'A') result = 0;
	else if (symb == 'B')  result = 1;
	else if (symb == 'C')  result = 2;
	else if (symb == 'D')  result = 3;
	else if (symb == 'E')  result = 4;
	else if (symb == 'F')  result = 5;
	else if (symb == 'G')  result = 6;
	else if (symb == 'H')  result = 7;
	else if (symb == 'I')  result = 8;
	else if (symb == 'J')  result = 9;
	return result;
}
//********************************
void displayPole(int PC_field[][SIZE], int player_field[][SIZE], int mode){
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);

	printf("\n%s", "  ABCDEFGHIJ");
	if (mode == 1){
		printf("\t\t\t\t");
		printf("%s\n", "  ABCDEFGHIJ");
	}
	else
	{
		putchar('\n');
	}
	for (int i = 0; i < SIZE; i++){
		
		//*******player field**************
		(i == 9 ? printf("%d", (i + 1)) : printf("%d ", (i + 1)));

		for (int j = 0; j < SIZE; j++){
			if (player_field[i][j] == 0){
				SetConsoleTextAttribute(Console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				printf("%c", (char)176);   //SEA
				SetConsoleTextAttribute(Console, FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
			}
			else if (player_field[i][j] == 1 || player_field[i][j] == 2 || player_field[i][j] == 3 || player_field[i][j] == 4){
				SetConsoleTextAttribute(Console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				printf("%c", 'S');  //SHIP
				SetConsoleTextAttribute(Console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
			else if (player_field[i][j] == 5){
				SetConsoleTextAttribute(Console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				printf("%c", 'O');  // MISS
				SetConsoleTextAttribute(Console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
			else if (player_field[i][j] == 100){
				SetConsoleTextAttribute(Console, FOREGROUND_RED | FOREGROUND_INTENSITY);
				printf("%c", 'X');    //HIT
				SetConsoleTextAttribute(Console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
		}
		if (mode == 1){
			//***********PC FIELD***************
			printf("\t\t\t\t");
			(i == 9 ? printf("%d", (i + 1)) : printf("%d ", (i + 1)));
			for (int j = 0; j < SIZE; j++){
				if (PC_field[i][j] == 100){
					SetConsoleTextAttribute(Console, FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf("%c", 'X');  //HIT
					SetConsoleTextAttribute(Console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				}
				else if (PC_field[i][j] == 5){
					SetConsoleTextAttribute(Console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					printf("%c", 'O');  //MISS
					SetConsoleTextAttribute(Console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				}

		     /* else if (PC_field[i][j] == 1 || PC_field[i][j] == 2 || PC_field[i][j] == 3 || PC_field[i][j] == 4){
					SetConsoleTextAttribute(Console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					printf("%c", 'S');  //SHIP
					SetConsoleTextAttribute(Console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				} */ 
				// UNCOMENT TO SEE PC SHIPS <--------------<------<<---------|

				else  {
					SetConsoleTextAttribute(Console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					printf("%c", (char)176);// SEA
					SetConsoleTextAttribute(Console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				}
			}
			//**************************
		}

		printf("\n");
	}
	printf("\n\n");
}

void printGameStatus(char * message, int mode)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position_YX = {4,20};
	
	SetConsoleCursorPosition(Console, Position_YX);
	if (mode == NO_ARG)
	{
		SetConsoleTextAttribute(Console,  FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf(message, mode);
		SetConsoleTextAttribute(Console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
	else if (mode == ACT_MSG){
		Position_YX.Y--;
		SetConsoleCursorPosition(Console, Position_YX);
		SetConsoleTextAttribute(Console, FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf(message);
		SetConsoleTextAttribute(Console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
	else if (mode == PLSTAT_MSG){
		Position_YX.Y +=3;
		SetConsoleCursorPosition(Console, Position_YX);
		SetConsoleTextAttribute(Console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf(message);
		SetConsoleTextAttribute(Console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
	else if (mode == PCSTAT_MSG){
		Position_YX.Y += 4;
		SetConsoleCursorPosition(Console, Position_YX);
		SetConsoleTextAttribute(Console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf(message);
		SetConsoleTextAttribute(Console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
	else if (mode == KILL_MSG){
		Position_YX.Y += 5;
		SetConsoleCursorPosition(Console, Position_YX);
		printf(message);
	}
	else 
	printf(message);
	
}
	