#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#pragma warning (disable:4996)
#define PNEW 9
#define PTOTAL 100
#define PDEATH 2
#define PRECOVER 10
#define PTREATMENT 88

typedef struct dailyCases {
	int newCases;
	int total;
	int totaldeath;
	int totalrecover;
	int totalut;
	float deathRate;
	float recoverRate;
	float utRate;
} dailyCases;

dailyCases dc[365];

// Function declaration
void record(int todayTotal, int currentTotal, int currentDeath, int currentRecover, int currentUt, float deathRate, float recoverRate, float utRate);
void lookback();
void header(int todayTotal, int currentTotal, int currentDeath, int currentRecover);
int getNewLocalCases();
int getNewImportCases();
int getNewDeath(int currentTotal);
int getNewRecover(int currentTotal);
void printSummary(int todayLocalCase, int todayImportCase, int todayTotal, int currentTotal, int currentDeath, int currentRecover);
void printCompare(int ytdTotal, int ytdCurrentTotal, int ytdDeath, int ytdRecover, int todayTotal, int todayCurrentTotal, int todayDeath, int tdyRecover);
int days = 9;
int checkInt(int num);

void main() {


	printf("##############################################################################################\n");
	printf("#                               COVID 19 CASES TRACKING SYSTEM                               #\n");
	printf("##############################################################################################\n\n");

	// Print out yesterday cases
	header(PNEW, PTOTAL, PDEATH, PRECOVER);

	// Local declaration 
	int todayLocalCase, todayImportCase, todayDeath, todayRecover;
	int currentTotal, currentDeath, currentRecover;

	int yesterdayNew, yesterdayTotal, yesterdayDeath, yesterdayRecover;
	int todayTotal;
	int highCase, highDay, lowCase, lowDay;
	char editC;

	// Assign the constant variable's value to yesterday data
	yesterdayNew = PNEW;
	yesterdayTotal = PTOTAL;
	yesterdayDeath = PDEATH;
	yesterdayRecover = PRECOVER;

	char name[50];
	int workerID;
	char nameCon;
	char temp;

	// Getting personal particular of the user.
	// It will continue loop until valid inputs are given.
	printf("\tPlease enter your name > ");
	scanf("%[^\n]", name);
	rewind(stdin);
	do {
		printf("\tPlease enter your worker id (4-digit) > ");
		scanf("%d%c", &workerID, &temp);
		rewind(stdin);
		if (workerID < 1000 || workerID >9999) {
			printf("\tERROR: You need to enter at least 4 digits only !!\n");
		}
		else if (checkInt(workerID) == 0) {
			printf("\tERROR: Only number is acceptable!\n");
		}
		else if (temp != '\n') {
			printf("\tERROR: You cannot enter more than two value, or invalid value\n");
		}
	} while (workerID < 1000 || workerID > 9999 || checkInt(workerID) == 0 || temp != '\n');

	// Check whether the user is willing to submit his / her personal particular.
	do {
		printf("Confirm to submit? (Yes = Y) > ");
		scanf("%c%c", &nameCon, &temp);
		rewind(stdin);
		if (temp != '\n')
			printf("Invalid choice!\n");
	} while (temp != '\n');

	while (nameCon != 'Y' && nameCon != 'y') {
		printf("\tPlease enter your name > ");
		scanf("%[^\n]", name);
		rewind(stdin);
		do {
			printf("\tPlease enter your worker id (4-digit) > ");
			scanf("%d%c", &workerID, &temp);
			rewind(stdin);
			if (workerID < 1000 || workerID >9999) {
				printf("\tERROR: You need to enter at least 4 digits only !!\n");
			}
			else if (checkInt(workerID) == 0) {
				printf("\tERROR: Only number is acceptable!\n");
			}
			else if (temp != '\n') {
				printf("\tERROR: You cannot enter more than two value, or invalid value\n");
			}
		} while (workerID < 1000 || workerID > 9999 || checkInt(workerID) == 0 || temp != '\n');


		do {
			printf("Confirm to submit? (Yes = Y) > ");
			scanf("%c%c", &nameCon, &temp);
			rewind(stdin);
			if (temp != '\n')
				printf("Invalid choice!\n");
		} while (temp != '\n');

	}

	// The main program start here
	// Keep on looping to allow user to enter and check multiple days data

	do {
		// Getting input for new cases
		todayLocalCase = getNewLocalCases();
		todayImportCase = getNewImportCases();

		// Calculate total
		todayTotal = todayLocalCase + todayImportCase;
		printf("\nTotal no. of new cases = %d", todayTotal);

		// Compare the total case with the previous one.
		if (todayTotal > PNEW) {
			int difference = todayTotal - PNEW;
			printf("\t( Increase by %d from yesterday )\n", difference);
		}
		else if (todayTotal < PNEW) {
			int difference = PNEW - todayTotal;
			printf("\t( Decrease by %d from yesterday )\n", difference);
		}
		else {
			printf("\t( No change from yesterday )\n");
		}

		// Getting input for new deaths and recover

		currentTotal = PTOTAL + todayTotal;
		todayDeath = getNewDeath(currentTotal);
		todayRecover = getNewRecover(currentTotal - todayDeath);

		currentDeath = PDEATH + todayDeath;
		currentRecover = PRECOVER + todayRecover;


		// Ask for edit or not?
		do {
			printf("Do you want to edit? (Y/N) > ");
			scanf("%c%c", &editC, &temp);
			rewind(stdin);
			if ((editC != 'Y' && editC != 'y' && editC != 'N' && editC != 'n') || temp != '\n') {
				printf("ERROR: Please enter Y for yes, N for no\n");
			}
		} while ((editC != 'Y' && editC != 'y' && editC != 'N' && editC != 'n') || temp != '\n');
	} while (editC == 'Y' || editC == 'y');
	days++;

	// Menu choose which report user want!
	printf("##############################################################################################\n");
	printf("#                                         Report Type                                        #\n");
	printf("##############################################################################################\n");
	printf("#                                                                                            #\n");
	printf("#                1 - Daily Summary Report   2 - Daily Comparative Report                     #\n");
	printf("#                                                                                            #\n");
	printf("##############################################################################################\n");
	int choice;
	// Getting user's choice and make sure it is either 1 or 2
	do {
		printf("\nWhat type of report you want to view? ");
		scanf("%d", &choice);
		rewind(stdin);
		if (choice != 1 && choice != 2) {
			printf("ERROR: Please enter either 1 or 2! \n");
		}
	} while (choice != 1 && choice != 2);

	// Check choice
	if (choice == 1) {
		// Print summary report
		printSummary(todayLocalCase, todayImportCase, todayTotal, currentTotal, currentDeath, currentRecover);
	}
	else {
		// Print comparative report
		printCompare(yesterdayNew, yesterdayTotal, yesterdayDeath, yesterdayRecover, todayTotal, currentTotal, currentDeath, currentRecover);
	}

	// If today is larger than Day 9, then the highest daya tentatively is today and vice versa
	if (todayTotal > PNEW) {
		highCase = todayTotal;
		highDay = days;
	}
	else {
		highCase = PNEW;
		highDay = days - 1;
	}

	// If today is larger than Day 9, then the lowest days tentatively is today and vice versa.
	if (todayTotal < PNEW) {
		lowCase = todayTotal;
		lowDay = days;
	}
	else {
		lowCase = PNEW;
		lowDay = days - 1;
	}
	// Repeat prompt for inputing data
	char con;
	do {
		printf("Continue to next day? (Yes = y) > ");
		scanf("%c%c", &con, &temp);
		rewind(stdin);
		if (temp != '\n') {
			printf("Invalid input\n");
		}
	} while (temp != '\n');

	// Print yesterday datas
	if (con == 'Y' || con == 'y') {
		header(todayTotal, currentTotal, currentDeath, currentRecover);
	}
	// Repeate input
	while (con == 'Y' || con == 'y') {

		// Assign today data to yesterday's variable
		// So that a new data can be store inside the today variable
		yesterdayNew = todayTotal;
		yesterdayTotal = currentTotal;
		yesterdayDeath = currentDeath;
		yesterdayRecover = currentRecover;
		do {
			// Getting input for new cases
			todayLocalCase = getNewLocalCases();
			todayImportCase = getNewImportCases();

			// Calculate total
			todayTotal = todayLocalCase + todayImportCase;
			printf("\nTotal no. of new cases = %d", todayTotal);

			// Compare the total case with the previous one.
			if (todayTotal > yesterdayNew) {
				int difference = todayTotal - yesterdayNew;
				printf("\t( Increase by %d from yesterday )\n", difference);
			}
			else if (todayTotal < yesterdayNew) {
				int difference = yesterdayNew - todayTotal;
				printf("\t( Decrease by %d from yesterday )\n", difference);
			}
			else {
				printf("\t( No change from yesterday )\n");
			}

			// Getting input for new deaths and recover
			todayDeath = getNewDeath(todayTotal + currentTotal);
			todayRecover = getNewRecover(todayTotal + currentTotal - todayDeath);


			// Ask for edit or not?
			do {
				printf("Do you want to edit? (Y/N) > ");
				scanf("%c%c", &editC, &temp);
				rewind(stdin);
				if ((editC != 'Y' && editC != 'y' && editC != 'N' && editC != 'n') || temp != '\n') {
					printf("ERROR: Please enter Y for yes, N for no\n");
				}
			} while ((editC != 'Y' && editC != 'y' && editC != 'N' && editC != 'n') || temp != '\n');
		} while (editC == 'Y' || editC == 'y');
		days++;

		// calculate the current Total, Death, and Recover.
		currentTotal += todayTotal;
		currentDeath += todayDeath;
		currentRecover += todayRecover;

		// Menu choose which report user want!
		printf("##############################################################################################\n");
		printf("#                                         Report Type                                        #\n");
		printf("##############################################################################################\n");
		printf("#                                                                                            #\n");
		printf("#                1 - Daily Summary Report   2 - Daily Comparative Report                     #\n");
		printf("#                                                                                            #\n");
		printf("##############################################################################################\n");

		// Get the user chocie and repeat until a valid choice is given.
		do {
			printf("\nWhat type of report you want to view? ");
			scanf("%d", &choice);
			rewind(stdin);
			if (choice != 1 && choice != 2) {
				printf("ERROR: Please enter either 1 or 2! \n");
			}
		} while (choice != 1 && choice != 2);

		// Check choice
		if (choice == 1) {
			// Print summary report
			printSummary(todayLocalCase, todayImportCase, todayTotal, currentTotal, currentDeath, currentRecover);
		}
		else {
			// Print comparative report
			printCompare(yesterdayNew, yesterdayTotal, yesterdayDeath, yesterdayRecover, todayTotal, currentTotal, currentDeath, currentRecover);
		}

		// Repeat prompt for inputing data

		do {
			printf("Continue to next day? (Yes = y) > ");
			scanf("%c%c", &con, &temp);
			rewind(stdin);
			if (temp != '\n') {
				printf("Invalid input\n");
			}
		} while (temp != '\n');

		// Check highest
		// If today's data is larger than the current highest case, update it!
		if (todayTotal > highCase) {
			highCase = todayTotal;
			highDay = days;
		}

		// Check lowest
		// If today's data is lower than the current lowest case, update it!
		if (todayTotal < lowCase) {
			lowCase = todayTotal;
			lowDay = days;
		}

		// Print yesterday data when user is trying to proceed to next day.
		if (con == 'Y' || con == 'y') {
			header(todayTotal, currentTotal, currentDeath, currentRecover);
		}
	}

	// Displaying the total day recorded, highest number of cases and lowest number of cases.
	printf("\n\t\tTotal days recorded     > %d (Day 10 to Day %d)\n", days - 9, days);
	printf("\t\tHighest number of cases > %d (Occur at Day %d)\n", highCase, highDay);
	printf("\t\tLowest number of cases  > %d (Occur at Day %d)\n", lowCase, lowDay);

	printf("##############################################################################################\n");

	// Calculation on averages.
	float dayAmount = days - 9;
	float average = ((float)currentTotal - (float)PTOTAL) / dayAmount;
	float deathAverage = ((float)currentDeath - (float)PDEATH) / dayAmount;
	float recoverAverage = ((float)currentRecover - (float)PRECOVER) / dayAmount;

	// Display average.
	printf("\tAverage cases   = %.2f\n", average);
	printf("\tAverage deaths  = %.2f\n", deathAverage);
	printf("\tAverage recover = %.2f\n", recoverAverage);

	// Average larger than 500 = Print orange warning.
	// Average larger than 100 = Print yellow warning.
	// Average is lower than 100 = Print green warning.

	if (average > 500) {
		printf("\n\tOrange warning (xxx), government must carry out necessary actions!\n");
	}
	else if (average > 100) {
		printf("\n\tYellow warning (xx), government should carry out some actions!\n");
	}
	else {
		printf("\n\tGreen warning (x), it is under control but still require monitor!\n");
	}
	printf("##############################################################################################\n");

	// Print the user personal particular and submission time.
	printf("\n\tKey in by %s (Worker ID: %d) \n", name, workerID);
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("\tOn: %d-%02d-%02d %02d:%02d:%02d\n\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	
	// Run the lookback function that allow user to look back the previous data.
	lookback();
	printf("\n\n##############################################################################################\n");
	printf("\tThank you for choosing us <3 Have a nice day!\n\tAuthor: Poh Choo Han\n");


	system("pause");
}

// Print header (Yesterday report)
void header(int todayTotal, int currentTotal, int currentDeath, int currentRecover) {
	/*

	###########################################################################################
	#                             COVID 19 CASES TRACKING SYSTEM                              #
	###########################################################################################
	#            # New Cases # Total Cases # Total Deaths # Total Recovered # Under Treatment #
	###########################################################################################
	# Local    1 #           #             #              #                 #                 #
	# Imported 2 #           #             #              #                 #                 #
	#            #           #             #              #                 #                 #
	###########################################################################################
	*/
	int underTreatment = currentTotal - currentDeath - currentRecover;

	printf("\n\n\n##############################################################################################\n");
	printf("#                                 Yesterday's Total (Day %2d)                                 #\n", days);
	printf("##############################################################################################\n");
	printf("#               # New Cases # Total Cases # Total Deaths # Total Recovered # Under Treatment #\n");
	printf("##############################################################################################\n");
	printf("#               #   %5d   #    %5d    #     %5d    #      %5d      #       %5d     #\n", todayTotal, currentTotal, currentDeath, currentRecover, underTreatment);
	printf("##############################################################################################\n");

	// Calculate rates before print
	float deathRate = (float)currentDeath / (float)currentTotal * 100.0;
	float recoverRate = (float)currentRecover / (float)currentTotal * 100.0;
	float utRate = (float)underTreatment / (float)currentTotal * 100.0;

	printf("#               #           #             #    %6.2f%%   #     %6.2f%%     #      %6.2f%%    #\n", deathRate, recoverRate, utRate);
	printf("##############################################################################################\n");

	// Record current data into structure array.
	record(todayTotal, currentTotal, currentDeath, currentRecover, underTreatment, deathRate, recoverRate, utRate);
}
// Get input for new local cases
int getNewLocalCases() {
	printf("\n\nDay %2d\n------\n", days + 1);
	printf("Please key in today's data:\n");
	char temp;
	// Loop until user input a valid value which is larger or equal than 0
	// Only integer is accept in this case.
	int n;
	do {
		printf("\t\tNo. of new local cases    : ");
		scanf("%d%c", &n, &temp);
		rewind(stdin);
		if (checkInt(n) == 0) {
			printf("ERROR: Please enter a number!\n");
		}
		else if (n < 0) {
			printf("ERROR: New local cases cannot be negative!\n");
		}
		else if (temp != '\n') {
			printf("\tERROR: You cannot enter more than two value, or invalid value\n");
		}
	} while (n < 0 || checkInt(n) == 0 || temp != '\n');

	return n;
}

// Get input for new imported cases
int getNewImportCases() {

	// Loop until user input a valid value which is larger or equal than 0
	// Only integer is accept in this case.
	int n;
	char temp;
	do {
		printf("\t\tNo. of new imported cases : ");
		scanf("%d%c", &n, &temp);
		rewind(stdin);
		if (checkInt(n) == 0) {
			printf("ERROR: Please enter a number!\n");
		}
		else if (n < 0) {
			printf("ERROR: New import cases cannot be negative!\n");
		}
		else if (temp != '\n') {
			printf("\tERROR: You cannot enter more than two value, or invalid value\n");
		}
	} while (n < 0 || checkInt(n) == 0 || temp != '\n');

	return n;
}
// Get input for new deaths
int getNewDeath(int currentTotal) {

	// Loop until user input a valid value which is larger or equal than 0
	// Only integer is accept in this case.
	// It will reject unreasonable new death, if the new death is beyond the Current Total cases.
	int n;
	char temp;
	do {
		printf("No. of deaths          = ");
		scanf("%d%c", &n, &temp);
		rewind(stdin);
		if (checkInt(n) == 0) {
			printf("ERROR: Please enter a number!\n");
		}
		else if (n < 0) {
			printf("ERROR: New death cases cannot be negative!\n");
		}
		else if (n > currentTotal) {
			printf("ERROR: New death will not more than total cases!\n");
		}
		else if (temp != '\n') {
			printf("\tERROR: You cannot enter more than two value, or invalid value\n");
		}
	} while (n < 0 || checkInt(n) == 0 || n > currentTotal || temp != '\n');

	return n;
}

// Get input for new recovers
int getNewRecover(int currentTotal) {

	// Loop until user input a valid value which is larger or equal than 0
	// Only integer is accept in this case.
	// It will reject unreasonable new recover, if the new recover is beyond the Current Total cases.
	int n;
	char temp;
	do {
		printf("No. recovered          = ");
		scanf("%d%c", &n, &temp);
		rewind(stdin);
		if (checkInt(n) == 0) {
			printf("ERROR: Please enter a number!\n");
		}
		else if (n < 0) {
			printf("ERROR: New recover cases cannot be negative!\n");
		}
		else if (n > currentTotal) {
			printf("ERROR: New recover will not more than total cases!\n");
		}
		else if (temp != '\n') {
			printf("\tERROR: You cannot enter more than two value, or invalid value\n");
		}
	} while (n < 0 || checkInt(n) == 0 || n > currentTotal || temp != '\n');

	return n;

}

void printSummary(int todayLocalCase, int todayImportCase, int todayTotal, int currentTotal, int currentDeath, int currentRecover) {
	// Calculate amount of people that under treatment
	int underTreatment = currentTotal - currentDeath - currentRecover;

	// Print summary structure
	printf("##############################################################################################\n");
	printf("#                               Daily Summary Report (Day %2d)                                #\n", days);
	printf("##############################################################################################\n");
	printf("#               # New Cases # Total Cases # Total Deaths # Total Recovered # Under Treatment #\n");
	printf("##############################################################################################\n");
	printf("# Local    %3d  #           #             #              #                 #                 #\n", todayLocalCase);
	printf("# Imported %3d  #           #             #              #                 #                 #\n", todayImportCase);
	printf("#               #   %5d   #    %5d    #     %5d    #      %5d      #       %5d     #\n", todayTotal, currentTotal, currentDeath, currentRecover, underTreatment);
	printf("##############################################################################################\n");

	// Calculate rates before print
	float deathRate = (float)currentDeath / (float)currentTotal * 100.0;
	float recoverRate = (float)currentRecover / (float)currentTotal * 100.0;
	float utRate = (float)underTreatment / (float)currentTotal * 100.0;

	printf("#               #           #             #    %6.2f%%   #     %6.2f%%     #      %6.2f%%    #\n", deathRate, recoverRate, utRate);
	printf("##############################################################################################\n");

	// Record current day data into the structure array.
	record(todayTotal, currentTotal, currentDeath, currentRecover, underTreatment, deathRate, recoverRate, utRate);

}
void printCompare(int ytdTotal, int ytdCurrentTotal, int ytdDeath, int ytdRecover, int todayTotal, int todayCurrentTotal, int todayDeath, int tdyRecover) {
	// Calculate rate
	float ytdDeathRate = (float)ytdDeath / (float)ytdCurrentTotal * 100.0;
	float ytdRecoverRate = (float)ytdRecover / (float)ytdCurrentTotal * 100.0;
	float tdyDeathRate = (float)todayDeath / (float)todayCurrentTotal * 100.0;
	float tdyRecoverRate = (float)tdyRecover / (float)todayCurrentTotal * 100.0;

	// Print table
	printf("##############################################################################################\n");
	printf("#                             Daily comparative Report (Day %2d)                              #\n", days);
	printf("##############################################################################################\n");
	printf("#                #     Yesterday (Day %2d)     #     Today (Day %2d)     #     Differences     #\n", days - 1, days);
	printf("##############################################################################################\n");
	if (todayTotal > ytdTotal)
		printf("# New Cases      #            %5d           #          %5d         #        +%5d       #\n", ytdTotal, todayTotal, todayTotal - ytdTotal);
	else
		printf("# New Cases      #            %5d           #          %5d         #        -%5d       #\n", ytdTotal, todayTotal, ytdTotal - todayTotal);
	printf("##############################################################################################\n");
	if (todayCurrentTotal > ytdCurrentTotal)
		printf("# Total Cases    #            %5d           #          %5d         #        +%5d       #\n", ytdCurrentTotal, todayCurrentTotal, todayCurrentTotal - ytdCurrentTotal);
	else
		printf("# Total Cases    #            %5d           #          %5d         #        -%5d       #\n", ytdCurrentTotal, todayCurrentTotal, ytdCurrentTotal - todayCurrentTotal);
	printf("##############################################################################################\n");
	if (tdyDeathRate > ytdDeathRate)
		printf("# Death Rate     #            %6.2f          #         %6.2f         #        +%6.2f      #\n", ytdDeathRate, tdyDeathRate, tdyDeathRate - ytdDeathRate);
	else
		printf("# Death Rate     #            %6.2f          #         %6.2f         #        -%6.2f      #\n", ytdDeathRate, tdyDeathRate, ytdDeathRate - tdyDeathRate);
	printf("##############################################################################################\n");
	if (tdyRecoverRate > ytdRecoverRate)
		printf("# Recover Rate   #            %6.2f          #         %6.2f         #        +%6.2f      #\n", ytdRecoverRate, tdyRecoverRate, tdyRecoverRate - ytdRecoverRate);
	else
		printf("# Recover Rate   #            %6.2f          #         %6.2f         #        -%6.2f      #\n", ytdRecoverRate, tdyRecoverRate, ytdRecoverRate - tdyRecoverRate);
	printf("##############################################################################################\n");
	// Record current day data into the structure array
	record(todayTotal, todayCurrentTotal, todayDeath, tdyRecover, todayCurrentTotal - todayDeath - tdyRecover, tdyDeathRate, tdyRecoverRate, (float)(todayCurrentTotal - todayDeath - tdyRecover) / (float) todayCurrentTotal * 100.0);
}

// A function that allow system to check user's input whether is it a number.
int checkInt(int num) {
	char test[50];
	// Parse it into string so that it is convenience to check it one by one
	sprintf(test, "%d", num);
	int length = strlen(test);

	// Check each character one by one.
	for (int i = 0; i < length; i++) {
		if (!isdigit(test[i])) {
			return 0;
			break;
		}
	}
	return 1;
}

// Saving data intu the structure array.
void record(int todayTotal, int currentTotal, int currentDeath, int currentRecover, int currentUt, float deathRate, float recoverRate, float utRate) {
	int index = days - 9;
	dc[index].total = currentTotal;
	dc[index].newCases = todayTotal;
	dc[index].totaldeath = currentDeath;
	dc[index].totalrecover = currentRecover;
	dc[index].totalut = currentUt;
	dc[index].deathRate = deathRate;
	dc[index].recoverRate = recoverRate;
	dc[index].utRate = utRate;
}

// This will prompt user for looking back the previous day data.
void lookback() {
	int choice;
	char temp;
	do {
		// User can view any day by inputing the day number
		// Any input that are invalid, beyond the limit will been rejected
		// User need to key in -1 to exit the loop.
		printf("Which day's data you want to look for? Day 9 to Day %d (Enter -1 to exit) > ", days);
		scanf("%d%c", &choice, &temp);
		rewind(stdin);

		while (checkInt(choice) == 0 || temp != '\n' || choice < 9 || choice > days) {
			if (choice == -1) {
				break;
			}
			printf("ERROR: Invalid date\n");
			printf("Which day's data you want to look for? Day 9 to Day %d (Enter -1 to exit) > ", days);
			scanf("%d%c", &choice, &temp);
			rewind(stdin);
		}
		
		// Print the requested day's data.
		int index = choice - 9;
		if (choice != -1) {
			printf("\n\n##############################################################################################\n");
			printf("#                                      Day %2d's Total                                       #\n", choice);
			printf("##############################################################################################\n");
			printf("#               # New Cases # Total Cases # Total Deaths # Total Recovered # Under Treatment #\n");
			printf("##############################################################################################\n");
			printf("#               #   %5d   #    %5d    #     %5d    #      %5d      #       %5d     #\n", dc[index].newCases, dc[index].total, dc[index].totaldeath, dc[index].totalrecover, dc[index].totalut);
			printf("##############################################################################################\n");
			printf("#               #           #             #    %6.2f%%   #     %6.2f%%     #      %6.2f%%    #\n", dc[index].deathRate, dc[index].recoverRate, dc[index].utRate);
			printf("##############################################################################################\n");
		}
	} while (choice != -1);
}
/*
##############################################################################################
#                               COVID 19 CASES TRACKING SYSTEM                               #
##############################################################################################




##############################################################################################
#                                 Yesterday's Total (Day  9)                                 #
##############################################################################################
#               # New Cases # Total Cases # Total Deaths # Total Recovered # Under Treatment #
##############################################################################################
#               #       9   #      100    #         2    #         10      #          88     #
##############################################################################################
#               #           #             #      2.00%   #      10.00%     #       88.00%    #
##############################################################################################
		Please enter your name > Choo Han
		Please enter your worker id (4-digit) > 1
		ERROR: You need to enter at least 4 digits only !!
		Please enter your worker id (4-digit) > 1234 1
		ERROR: You cannot enter more than two value, or invalid value
		Please enter your worker id (4-digit) > 1234
Confirm to submit? (Yes = Y) > y


Day 10
------
Please key in today's data:
				No. of new local cases    : 10
				No. of new imported cases : 20

Total no. of new cases = 30     ( Increase by 21 from yesterday )
No. of deaths          = 30
No. recovered          = 40
Do you want to edit? (Y/N) > n
##############################################################################################
#                                         Report Type                                        #
##############################################################################################
#                                                                                            #
#                1 - Daily Summary Report   2 - Daily Comparative Report                     #
#                                                                                            #
##############################################################################################

What type of report you want to view? 1
##############################################################################################
#                               Daily Summary Report (Day 10)                                #
##############################################################################################
#               # New Cases # Total Cases # Total Deaths # Total Recovered # Under Treatment #
##############################################################################################
# Local     10  #           #             #              #                 #                 #
# Imported  20  #           #             #              #                 #                 #
#               #      30   #      130    #        32    #         50      #          48     #
##############################################################################################
#               #           #             #     24.62%   #      38.46%     #       36.92%    #
##############################################################################################
Continue to next day? (Yes = y) > y



##############################################################################################
#                                 Yesterday's Total (Day 10)                                 #
##############################################################################################
#               # New Cases # Total Cases # Total Deaths # Total Recovered # Under Treatment #
##############################################################################################
#               #      30   #      130    #        32    #         50      #          48     #
##############################################################################################
#               #           #             #     24.62%   #      38.46%     #       36.92%    #
##############################################################################################


Day 11
------
Please key in today's data:
				No. of new local cases    : 50
				No. of new imported cases : 60

Total no. of new cases = 110    ( Increase by 80 from yesterday )
No. of deaths          = 80
No. recovered          = 1000
ERROR: New recover will not more than total cases!
No. recovered          = 100
Do you want to edit? (Y/N) > y


Day 11
------
Please key in today's data:
				No. of new local cases    : 90
				No. of new imported cases : 100

Total no. of new cases = 190    ( Increase by 160 from yesterday )
No. of deaths          = 30
No. recovered          = 20
Do you want to edit? (Y/N) > n
##############################################################################################
#                                         Report Type                                        #
##############################################################################################
#                                                                                            #
#                1 - Daily Summary Report   2 - Daily Comparative Report                     #
#                                                                                            #
##############################################################################################

What type of report you want to view? 2
##############################################################################################
#                             Daily comparative Report (Day 11)                              #
##############################################################################################
#                #     Yesterday (Day 10)     #     Today (Day 11)     #     Differences     #
##############################################################################################
# New Cases      #               30           #            190         #        +  160       #
##############################################################################################
# Total Cases    #              130           #            320         #        +  190       #
##############################################################################################
# Death Rate     #             24.62          #          19.38         #        -  5.24      #
##############################################################################################
# Recover Rate   #             38.46          #          21.88         #        - 16.59      #
##############################################################################################
Continue to next day? (Yes = y) > y



##############################################################################################
#                                 Yesterday's Total (Day 11)                                 #
##############################################################################################
#               # New Cases # Total Cases # Total Deaths # Total Recovered # Under Treatment #
##############################################################################################
#               #     190   #      320    #        62    #         70      #         188     #
##############################################################################################
#               #           #             #     19.38%   #      21.88%     #       58.75%    #
##############################################################################################


Day 12
------
Please key in today's data:
				No. of new local cases    : 70
				No. of new imported cases : 80

Total no. of new cases = 150    ( Decrease by 40 from yesterday )
No. of deaths          = 90
No. recovered          = 100
Do you want to edit? (Y/N) > n
##############################################################################################
#                                         Report Type                                        #
##############################################################################################
#                                                                                            #
#                1 - Daily Summary Report   2 - Daily Comparative Report                     #
#                                                                                            #
##############################################################################################

What type of report you want to view? 1
##############################################################################################
#                               Daily Summary Report (Day 12)                                #
##############################################################################################
#               # New Cases # Total Cases # Total Deaths # Total Recovered # Under Treatment #
##############################################################################################
# Local     70  #           #             #              #                 #                 #
# Imported  80  #           #             #              #                 #                 #
#               #     150   #      470    #       152    #        170      #         148     #
##############################################################################################
#               #           #             #     32.34%   #      36.17%     #       31.49%    #
##############################################################################################
Continue to next day? (Yes = y) > y



##############################################################################################
#                                 Yesterday's Total (Day 12)                                 #
##############################################################################################
#               # New Cases # Total Cases # Total Deaths # Total Recovered # Under Treatment #
##############################################################################################
#               #     150   #      470    #       152    #        170      #         148     #
##############################################################################################
#               #           #             #     32.34%   #      36.17%     #       31.49%    #
##############################################################################################


Day 13
------
Please key in today's data:
				No. of new local cases    : 90
				No. of new imported cases : 100

Total no. of new cases = 190    ( Increase by 40 from yesterday )
No. of deaths          = 20
No. recovered          = 10
Do you want to edit? (Y/N) > n
##############################################################################################
#                                         Report Type                                        #
##############################################################################################
#                                                                                            #
#                1 - Daily Summary Report   2 - Daily Comparative Report                     #
#                                                                                            #
##############################################################################################

What type of report you want to view? 2
##############################################################################################
#                             Daily comparative Report (Day 13)                              #
##############################################################################################
#                #     Yesterday (Day 12)     #     Today (Day 13)     #     Differences     #
##############################################################################################
# New Cases      #              150           #            190         #        +   40       #
##############################################################################################
# Total Cases    #              470           #            660         #        +  190       #
##############################################################################################
# Death Rate     #             32.34          #          26.06         #        -  6.28      #
##############################################################################################
# Recover Rate   #             36.17          #          27.27         #        -  8.90      #
##############################################################################################
Continue to next day? (Yes = y) > n

				Total days recorded     > 4 (Day 10 to Day 13)
				Highest number of cases > 190 (Occur at Day 11)
				Lowest number of cases  > 9 (Occur at Day 9)
##############################################################################################
		Average cases   = 140.00
		Average deaths  = 42.50
		Average recover = 42.50

		Yellow warning (xx), government should carry out some actions!
##############################################################################################

		Key in by Choo Han (Worker ID: 1234)
		On: 2020-08-26 16:34:17

Which day's data you want to look for? Day 9 to Day 13 (Enter -1 to exit) > 13


##############################################################################################
#                                      Day 13's Total                                       #
##############################################################################################
#               # New Cases # Total Cases # Total Deaths # Total Recovered # Under Treatment #
##############################################################################################
#               #     190   #      660    #       172    #        180      #         308     #
##############################################################################################
#               #           #             #     26.06%   #      27.27%     #       46.67%    #
##############################################################################################
Which day's data you want to look for? Day 9 to Day 13 (Enter -1 to exit) > 12


##############################################################################################
#                                      Day 12's Total                                       #
##############################################################################################
#               # New Cases # Total Cases # Total Deaths # Total Recovered # Under Treatment #
##############################################################################################
#               #     150   #      470    #       152    #        170      #         148     #
##############################################################################################
#               #           #             #     32.34%   #      36.17%     #       31.49%    #
##############################################################################################
Which day's data you want to look for? Day 9 to Day 13 (Enter -1 to exit) > 11


##############################################################################################
#                                      Day 11's Total                                       #
##############################################################################################
#               # New Cases # Total Cases # Total Deaths # Total Recovered # Under Treatment #
##############################################################################################
#               #     190   #      320    #        62    #         70      #         188     #
##############################################################################################
#               #           #             #     19.38%   #      21.88%     #       58.75%    #
##############################################################################################
Which day's data you want to look for? Day 9 to Day 13 (Enter -1 to exit) > 10


##############################################################################################
#                                      Day 10's Total                                       #
##############################################################################################
#               # New Cases # Total Cases # Total Deaths # Total Recovered # Under Treatment #
##############################################################################################
#               #      30   #      130    #        32    #         50      #          48     #
##############################################################################################
#               #           #             #     24.62%   #      38.46%     #       36.92%    #
##############################################################################################
Which day's data you want to look for? Day 9 to Day 13 (Enter -1 to exit) >
9


##############################################################################################
#                                      Day  9's Total                                       #
##############################################################################################
#               # New Cases # Total Cases # Total Deaths # Total Recovered # Under Treatment #
##############################################################################################
#               #       9   #      100    #         2    #         10      #          88     #
##############################################################################################
#               #           #             #      2.00%   #      10.00%     #       88.00%    #
##############################################################################################
Which day's data you want to look for? Day 9 to Day 13 (Enter -1 to exit) > 8
ERROR: Invalid date
Which day's data you want to look for? Day 9 to Day 13 (Enter -1 to exit) > 14
ERROR: Invalid date
Which day's data you want to look for? Day 9 to Day 13 (Enter -1 to exit) > a
ERROR: Invalid date
Which day's data you want to look for? Day 9 to Day 13 (Enter -1 to exit) > -1


##############################################################################################
		Thank you for choosing us <3 Have a nice day!
		Author: Poh Choo Han
Press any key to continue . . .
*/