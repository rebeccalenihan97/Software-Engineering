#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#define DESCRIPTION 30
#define TYPE 3

char slot_type[TYPE][DESCRIPTION] = {"Ground", "Hill", "City"}; // Global variable which can be accessed by any function

// Initializing struct for players which contains information on each player's name, type, life points and their capabilities
struct players
{
	char type[7]; 											// player's type
	char name[10];											// player's name
	int life_points;										// player's life points
	int smartness, strength, magic_skills, luck, dexterity; // player's capabilities
	int slots;												// player's position in the slot
	int shift_slot;											// keeps track if player moved or not, if moved shift_slot == 1, if not shift_slot == 0
};

// Initializing struct for slots which contains random slot type for each slot position, and the player number in a slot
struct slots
{
	char type[DESCRIPTION]; // slot type
	int player;				// player number at particular slot
};

//FUNCTIONS
void Elf(struct players *structname);		// assigns specific capabilities to player type Elf
void Human(struct players *structname);		// assigns specific capabilities to player type Human
void Ogre(struct players *structname);		// assigns specific capabilities to player type Ogre
void Wizard(struct players *structname);	// assigns specific capabilities to player type Wizard

void slotType_random(struct slots slot_main[], int slot_size); 												 // assigns a random slot type to each slot position
void players_to_slots(struct players newplayers[], struct slots slot_main[], int playernos, int slot_size);	 // assigns each player to a random slot
void playerInfo(struct players newplayers[], int playernos);												 // prints each player's information
void slotInfo(struct slots slot_main[],struct players newplayers[],int slot_size);							 // prints each slot's information and the players at assigned slots
void choice(struct players newpayers[], struct slots slot_main[], int playernos, int slot_size);   			 // asks user to make a choice,whether he wants to move or attack with a player
void capabilities(int playernos, int slot_size, struct players newplayers[], struct slots slot_main[]);		 // reduces player's capabilities depending on the slot type which they're on
void movePlayer(struct players newplayers[], struct slots slot_main[], int playernos, int slot_size, int player_no); // asks user whether he wants to move or attack with chosen player


int main(void)
{

	setvbuf(stdout, NULL, _IONBF, 0); // fixes eclipse buffer errors on WINDOWS OS

// Asking for user input for number of players to include in game

	int playernos; // Identifier for the number of players in the game
	A:printf("Please enter how many players to include in game (Max 6): ");
	scanf("%d", &playernos);

	if(playernos < 2 || playernos > 6) // Minimum number of players = 2, Maximum number of players = 6
	{
		printf("\nPlease enter a valid number of players.\n\n");
		goto A; // Repeats the process
	}

// Initializing the size of array of structs depending on user input
	struct players newplayers[playernos];

// Applying the player type, name and initial capabilities to each player
	int i, type;

	for(i=0;i<playernos;i++)
	{

		printf("\nPlease choose a player type for player %d:\n", i+1);
		printf("-------------------------------------------\n");

		do{
		printf("Type '1' for Elf\nType '2' for Human\nType '3' for Ogre\nType '4' for Wizard\n");
		scanf("%d", &type);
		}while(type<1 || type>4); // Ensures user does not enter any other value

	switch(type) // Enters the name of player type into char type array inside the struct
	{
	case 1:
		strcpy(newplayers[i].type, "Elf");
	break;
	case 2:
		strcpy(newplayers[i].type, "Human");
	break;
	case 3:
		strcpy(newplayers[i].type, "Ogre");
	break;
	case 4:
		strcpy(newplayers[i].type, "Wizard");
	break;
	}

	if(type == 1) // Initializes the capabilities of each player depending on their player type
		{
			Elf(&newplayers[i]);
		}

	else if(type == 2)
		{
			Human(&newplayers[i]);
		}

	else if(type == 3)
		{
			Ogre(&newplayers[i]);
		}

	else if(type == 4)
		{
			Wizard(&newplayers[i]);
		}
	}

	for(i=0;i<playernos;i++) //Naming each player
		{
			printf("\nPlease enter a name for player %d: ", i+1);
			scanf("%s", newplayers[i].name);
		}


// Asking user input for number of slots to include in the game
	int slot_size;
	REPEAT:printf("\nPlease enter the number of slots to run the game on (Max 20):  ");
	scanf("%d", &slot_size);

//Initializing the size of struct array
	struct slots slot_main[slot_size];


	if(slot_size<=0 || slot_size>20) // Ensures slot size does not exceed stated amount
	{
		printf("\nEnter a valid number of slots.\n\n");
		goto REPEAT; // Repeats the process
	}
	else if(slot_size<=playernos) // Ensures slot size is not less than or equal to number of players
	{
		printf("\nError, the number of slots can't be less than number of players.\n\n");
		goto REPEAT; // Repeats the process
	}

	printf("\n\n");

	slotType_random(slot_main, slot_size); // APPLYING A RANDOM SLOT TYPE TO EACH SLOT

	players_to_slots(newplayers, slot_main, playernos, slot_size); // APPLYING PLAYERS TO RANDOM SLOTS

	slotInfo(slot_main, newplayers, slot_size); // PRINTING SLOT INFORMATION AND PLAYER'S POSITIONS

	printf("\n\n");

	playerInfo(newplayers,playernos); // PRINTING THE PLAYER's INFORMATION CONTAINING PLAYER NUMBER, NAME, TYPE, LIFEPOINTS, ALL CAPABILITIES

	choice(newplayers, slot_main, playernos, slot_size); // ASK USER TO MAKE A DECISION WHETHER HE WANTS TO MOVE OR ATTACK WITH CHOSEN PLAYER

	slotInfo(slot_main, newplayers, slot_size); // PRINTING SLOT INFORMATION AND PLAYER'S POSITIONS

	return 0;
}


void Human(struct players *structname)
{
    int sum = 300;
    srand((unsigned)time(NULL));

    (*structname).life_points = 100;

    while(sum >= 300)
    {
        (*structname).smartness = rand() % 100 + 1;
        (*structname).strength = rand() % 100 + 1;
        (*structname).magic_skills = rand() % 100 + 1;
        (*structname).luck = rand() % 100 + 1;
        (*structname).dexterity = rand() % 100 + 1;

        sum = (*structname).smartness + (*structname).strength + (*structname).magic_skills + (*structname).luck + (*structname).dexterity;
    }
}

void Ogre(struct players *structname)
{
    int sum = 51;
    srand((unsigned)time(NULL));

    (*structname).life_points = 100;
    (*structname).magic_skills = 0;
    (*structname).strength = rand() % 22 + 79;
    (*structname).dexterity = rand() % 22 + 79;

    while(sum >= 50)
    {
        (*structname).smartness = rand() % 21;
        (*structname).luck = rand() % 50;

        sum = (*structname).luck + (*structname).smartness;
    }
}

void Elf(struct players *structname)
{
	srand((unsigned)time(NULL));

    (*structname).life_points = 100;
    (*structname).smartness = rand() % 32 + 69;
    (*structname).strength = rand() % 50 + 1;
    (*structname).magic_skills = rand() % 30 + 50;
    (*structname).luck = rand() % 42 + 59;
    (*structname).dexterity = rand() % 100 + 1;
}

void Wizard(struct players *structname)
{
    (*structname).life_points = 100;
    (*structname).smartness = rand() % 12 + 89;
    (*structname).strength = rand() % 21 + 1;
    (*structname).magic_skills = rand() % 22 + 79;
    (*structname).luck = rand() % 52 + 49;
    (*structname).dexterity = rand() % 100 + 1;
}

void slotType_random(struct slots slot_main[], int slot_size)
{
	srand((unsigned)time(NULL));
	int random,i;

	for(i=0;i<slot_size;i++)
	{
		random=rand()%3;
		strcpy(slot_main[i].type, slot_type[random]); // ASSIGNING ONE OF THE SLOT TYPES TO CHAR ARRAY TYPE IN STRUCT SLOT_MAIN FROM GLOBAL VARIABLE SLOT_TYPE
	}
}

void players_to_slots(struct players newplayers[], struct slots slot_main[], int playernos, int slot_size)
{
	srand((unsigned)time(NULL));
	int random;

	int i;

	for(i=0;i<slot_size;i++)
	{
		random=rand()%3;
		strcpy(slot_main[i].type, slot_type[random]);
	}


	//ASSIGNING EACH PLAYER TO A SLOT IN STRUCT SLOT ARRAY
	for (i=0;i<playernos;i++)
	{
		slot_main[i].player = i;
	}

	//FILLING THE REST OF POSITIONS IN STRUCT SLOT ARRAY WITH -1 I.E NO PLAYER
	for(i=playernos;i<slot_size;i++)
	{
		slot_main[i].player = -1;
	}

	//SHUFFLING THE STRUCT SLOT ARRAY TO PUT PLAYERS INTO RANDOM SLOTS
	int temp;
	int random_index;
	for (i=slot_size-1;i>0;i--) // shuffling the struct slot array to put players into random slots
	{
		random_index = rand()%(i+1);
		temp = slot_main[random_index].player;
		slot_main[random_index].player = slot_main[i].player;
		slot_main[i].player = temp;

		if(slot_main[i].player>-1)
		{
		    newplayers[slot_main[i].player].slots=i; // keeps track of each players position in the slot
		}
	 }

}

void playerInfo(struct players newplayers[], int playernos)
{

	int k;

	printf("------------------------------------------");
	printf("\n           PLAYER INFORMATION            \n");
	printf("------------------------------------------");

	for(k=0;k<playernos;k++)
	{
		printf("\n\nPlayer %d details:\n", k+1);
		printf("-------------------------------------\n");
		printf("Name: %s\n",newplayers[k].name);
		printf("Type: %s\n",newplayers[k].type);
		printf("Life points: %d\n",newplayers[k].life_points);
		printf("Smartness: %d\n",newplayers[k].smartness);
		printf("Strength: %d\n",newplayers[k].strength );
		printf("Magic Skills: %d\n",newplayers[k].magic_skills);
		printf("Luck: %d\n",newplayers[k].luck);
		printf("Dexterity: %d\n",newplayers[k].dexterity);
		sleep(1.5);
	}
}

void slotInfo(struct slots slot_main[],struct players newplayers[],int slot_size)
{
	int i,j;

	printf("\n\n------------------------------------------");
	printf("\n           SLOT INFORMATION            \n");
	printf("------------------------------------------\n");

	for(i=0;i<slot_size;i++)
	{
		if(slot_main[i].player > -1)
			{
				j = slot_main[i].player;
				printf("%d. %-8s->Player %d: %s\n", i, slot_main[i].type, slot_main[i].player+1, newplayers[j].name);
			}
		else
			{
				printf("%d. %-8s\n", i, slot_main[i].type);
			}
	}
}

void capabilities(int playernos, int slot_size, struct players newplayers[], struct slots slot_main[])
{
	int i,k,x;

	for(i=0;i<slot_size;i++)
	{
		k=slot_main[i].player;// ASSIGNING THE PLAYER NUMBER TO IDENTIFIER K OF TYPE INT

		if(k>=0) // if it's a player ( 0 -> 5 )
		{
			if(newplayers[k].shift_slot == 1) // if player has moved
			{
				x=newplayers[k].slots; // ASSIGNING THE SLOT POSITION OF PLAYER K TO X
				if(strcmp(slot_main[x].type, slot_type[1]) == 0) //If the player is in slot type Hill
					{
						if(newplayers[k].dexterity < 50)
							{
								if(newplayers[k].strength - 10 < 0)
								{
									newplayers[k].strength = 0;
									newplayers[k].shift_slot = 0; // once capability changed, reset movement back to 0
								}
								else
								{
									newplayers[k].strength -= 10;
									newplayers[k].shift_slot = 0; // once capability changed, reset movement back to 0
								}
							}
						else if(newplayers[k].dexterity >= 60)
							{
								if(newplayers[k].strength + 10 > 100)
								{
									newplayers[k].strength = 100;
									newplayers[k].shift_slot = 0; // once capability changed, reset movement back to 0
								}
								else{
									newplayers[k].strength += 10;
									newplayers[k].shift_slot = 0; // once capability changed, reset movement back to 0
								}
							}
					}


				else if(strcmp(slot_main[x].type, slot_type[2]) == 0) // If the player is in slot type City
					{
						if(newplayers[k].smartness > 60)
							{
								if(newplayers[k].magic_skills + 10 > 100)
								{
									newplayers[k].magic_skills = 100;
									newplayers[k].shift_slot = 0; // once capability changed, reset movement back to 0
								}
								else
								{
									newplayers[k].magic_skills += 10;
									newplayers[k].shift_slot = 0; // once capability changed, reset movement back to 0
								}

							}

						else if(newplayers[k].smartness <= 50)
							{
								if(newplayers[k].dexterity - 10 < 0)
								{
									newplayers[k].dexterity = 0;
									newplayers[k].shift_slot = 0; // once capability changed, reset movement back to 0
								}
								else
								{
									newplayers[k].dexterity -= 10;
									newplayers[k].shift_slot = 0; // once capability changed, reset movement back to 0
								}
							}
					}

				}
			}
		}
}

void choice(struct players newplayers[], struct slots slot_main[], int playernos, int slot_size)
{
	int i;
	int k=0;
	int l=0;
	int player_no;
	int choice;
	int check;
	int players[playernos];

	for(i=0;i<playernos;i++) // FILLS THE ARRAY WITH -1 BEFORE CHECKING IF USER ENTERED SAME PLAYER NUMBER TWICE
	{
		players[i]=-1;
	}

	for(i=0;i<playernos;i++)
	{
		REPLAY:do{
		printf("\n\nType the number of the player which you'd like to interact with: ");
		scanf("%d", &player_no);
		}while(player_no>playernos || player_no<0);

		check=player_no-1; // -1 as in struct arrays, instead of players being 1 -> 6, they're 0 -> 5. Thus, this fits with the code, although output is user friendly.

		for(k=0;k<playernos;k++) // Loop which ensures no same player is chosen more than once
		{
			if(check==players[k])
			{
				printf("\nThis player has already completed an action, please choose a different player.\n");
				goto REPLAY;
			}
		}

		players[l]=check; // fills players array with user inputs, for future checks
		l++;

		printf("If you would like to move player %d, press '0'.\n", player_no);
		printf("If you would like to attack with player %d, press '1'.\n", player_no);
		do{
		scanf("%d", &choice);
		}while(choice<0 || choice>1);

		if(choice == 0)
		{
			movePlayer(newplayers, slot_main, playernos, slot_size, player_no);
			capabilities(playernos, slot_size, newplayers, slot_main);
		}
		else if(choice == 1)
		{
			printf("ATTACK");
		}
	}
}

void movePlayer(struct players newplayers[], struct slots slot_main[], int playernos, int slot_size, int player_no)
{
	int move;
	int temp;

	RETRY:printf("If you would like to move 1 slot forward press '2'.\n");
	printf("If you would like to move 1 slot back press '3'. \n");
	do{
	scanf("%d", &move);
	}while(move<2 || move>3);

	if(move == 2)
	{
		if(newplayers[player_no-1].slots+1 >= slot_size) // If condition with error saying can't move further than slot_size, or if player ahead
		{
			printf("Can't move forwards, please move backwards.\n\n");
			goto RETRY;
		}
		else if(slot_main[newplayers[player_no-1].slots+1].player >= 0) // if moving forward, and player ahead
		{
			printf("\nPlayer %d is ahead of you! Attack him instead!", slot_main[newplayers[player_no-1].slots+1].player+1);
			printf("ATTACK");//ATTACK PLAYER AHEAD (pass on slot_main[newplayers[player_no-1].slots+1].player by passing on player_no)
		}
		else if(slot_main[newplayers[player_no-1].slots+1].player == -1) // if moving forward and empty space ahead /*WHEN PRESS 2 IT MOVES BACK, WHEN PRESS 3 IT MOVES FORWARD*/
		{
			temp = slot_main[newplayers[player_no-1].slots].player; // places players ID to identifier temp
			slot_main[newplayers[player_no-1].slots].player = -1; // makes players initial position empty
			slot_main[newplayers[player_no-1].slots+1].player = temp; // moving current player to a new position
			newplayers[player_no-1].slots += 1; // keeping track of the slot in whih the player is in
			newplayers[player_no-1].shift_slot = 1; // keeps track if player has moved or not
		}
	}

	else if(move == 3) // if user wants to move player backwards
	{
		if(newplayers[player_no-1].slots-1 < 0) // error saying can't move back less than slot position 0
		{
			printf("Can't move backwards, please move forwards.\n\n");
			goto RETRY;
		}

		else if(slot_main[newplayers[player_no-1].slots-1].player >= 0) // if there's a player behind
		{
			printf("\nPlayer %d is behind you! Attack him instead!", slot_main[newplayers[player_no-1].slots-1].player+1);
			printf("ATTACK");//ATTACK PLAYER BEHIND (pass on slot_main[newplayers[player_no-1].slots-1].player by passing on player_no)
		}

		else if(slot_main[newplayers[player_no-1].slots-1].player == -1) // if there's an empty space, then move
		{
			temp = slot_main[newplayers[player_no-1].slots].player; // places players ID to identifier temp
			slot_main[newplayers[player_no-1].slots].player = -1; // makes players initial position empty
			slot_main[newplayers[player_no-1].slots-1].player = temp; // moving player to a new position
			newplayers[player_no-1].slots -= 1; // keeping track of the slot in which the player is in
			newplayers[player_no-1].shift_slot = 1; // keeps track if player has moved or not
		}
	}
}
