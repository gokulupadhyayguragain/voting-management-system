#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "election_system.h"

#define MAX_CONSTITUENCIES 10
#define MAX_CANDIDATES 50
#define MAX_VOTERS 100
#define MAX_PASSWORD_LENGTH 20
#define MAX_ADMIN_TRIES 3
#define MAX_VOTER_LOGIN_TRIES 3

// Function prototypes
void adminLogin();
void createElectionSchedule();
void displayElectionSchedule();
void candidateRegistration();
void displayCandidateList();
void voterRegistration();
void voterLogin();
void endProgram();
void displayVoterList();
void updateVoterDetails();
void searchVoterDetails();
void allowToCastVote();
void displayVoteResult();
void returnToMainMenu();
void clearInputBuffer();
void saveElectionScheduleToFile(struct ElectionSchedule *schedule, int count);
void saveCandidateToFile(struct Candidate *candidate, int count);
void saveVoterToFile(struct Voter *voter, int count);
void saveVoteResultToFile(int *voteCount, int candidateCount);

int main() {
    int choice;

    do {
        printf("\nMain Menu\n");
        printf("1. Admin Login\n");
        printf("2. Voter Login\n");
        printf("3. Voter Registration\n");
        printf("4. End Program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminLogin();
                break;
            case 2:
                voterLogin();
                break;
            case 3:
                voterRegistration();
                break;
            case 4:
                endProgram();
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}

void adminLogin() {
    char adminUsername[] = "admin";
    char adminPassword[MAX_PASSWORD_LENGTH] = "admin";
    char enteredUsername[50];
    char enteredPassword[MAX_PASSWORD_LENGTH];
    int tries = 0;
    int adminChoice;

    printf("\nAdmin Login\n");

    do {
        printf("Enter Username: ");
        scanf("%s", enteredUsername);
        printf("Enter Password: ");
        scanf("%s", enteredPassword);

        if (strcmp(enteredUsername, adminUsername) == 0 && strcmp(enteredPassword, adminPassword) == 0) {
            printf("Login successful!\n");

            do {
                printf("\nAdmin Menu\n");
                printf("1. Create Election Schedule\n");
                printf("2. Display Election Schedule\n");
                printf("3. Candidate Registration\n");
                printf("4. Display Candidate List\n");
                printf("5. Voter Registration\n");
                printf("6. Display Voter List\n");
                printf("7. Update Voter Details\n");
                printf("8. Search Voter Details\n");
                printf("9. Allow to Cast Vote\n");
                printf("10. Display Vote Result\n");
                printf("11. Back to Main Menu\n");
                printf("12. End Program\n");
                printf("Enter your choice: ");
                scanf("%d", &adminChoice);

                switch (adminChoice) {
                    case 1:
                        createElectionSchedule();
                        break;
                    case 2:
                        displayElectionSchedule();
                        break;
                    case 3:
                        candidateRegistration();
                        break;
                    case 4:
                        displayCandidateList();
                        break;
                    case 5:
                        voterRegistration();
                        break;
                    case 6:
                        displayVoterList();
                        break;
                    case 7:
                        updateVoterDetails();
                        break;
                    case 8:
                        searchVoterDetails();
                        break;
                    case 9:
                        allowToCastVote();
                        break;
                    case 10:
                        displayVoteResult();
                        break;
                    case 11:
                        printf("Returning to Main Menu.\n");
                        return;  // Return to main menu
                    case 12:
                        printf("Exiting the program. Goodbye!\n");
                        exit(EXIT_SUCCESS);
                    default:
                        printf("Invalid choice. Please enter a valid option.\n");
                }
            } while (adminChoice != 11);
        } else {
            printf("Invalid username or password. Please try again.\n");
            tries++;
            if (tries == MAX_ADMIN_TRIES) {
                printf("Exceeded maximum login attempts. Returning to Main Menu.\n");
                return;
            }
        }
    } while (1);  // Infinite loop for multiple login attempts
}



void createElectionSchedule() {
    int scheduleCount = 0;
    FILE *file = fopen("schedule.txt", "a");

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    do {
        printf("\nEnter details for Constituency %d:\n", scheduleCount + 1);
        printf("Constituency: ");
        scanf("%s", electionSchedule[scheduleCount].constituency);
        printf("Date of Election (yyyymmdd): ");
        scanf("%s", electionSchedule[scheduleCount].date);
        fprintf(file, "%s\t%s\n", electionSchedule[scheduleCount].constituency, electionSchedule[scheduleCount].date);
        scheduleCount++;

        // Ask the user if they want to add more entries
        char choice;
        printf("Do you want to add more entries? (y/n): ");
        scanf(" %c", &choice);

        if (choice != 'y' && choice != 'Y') {
            break;
        }
    } while (scheduleCount < MAX_CONSTITUENCIES);

    fclose(file);
}



void saveElectionScheduleToFile(struct ElectionSchedule *schedule, int count) {
    FILE *file = fopen("schedule.txt", "a");  // Open file in append mode to keep existing records
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\t%s\n", schedule[i].constituency, schedule[i].date);
    }

    fclose(file);
}

void displayElectionSchedule() {
    printf("\nDisplay Election Schedule\n");
    FILE *file = fopen("schedule.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char constituency[50];
    char date[9];

    // Read the header line (if any) and discard it
    fscanf(file, "%*[^\n]\n");

    printf("Constituency\tDate of Election\n");
    while (fscanf(file, "%s\t%s", constituency, date) == 2) {
        printf("%s\t%s\n", constituency, date);
    }

    fclose(file);

    // Ask the user to press any key to go back to the admin menu
    printf("\nPress any key to go back to the Admin Menu...");
    getchar();  // Consume the newline character left in the input buffer
    getchar();  // Wait for any key press
}



void candidateRegistration() {
    printf("\nCandidate Registration\n");

    do {
        // Ensure that the number of candidates doesn't exceed the maximum limit
        if (candidateCount >= MAX_CANDIDATES) {
            printf("Maximum number of candidates reached.\n");
            return;
        }

        printf("Enter details for Candidate %d:\n", candidateCount + 1);
        
        printf("Name: ");
        scanf("%s", candidateList[candidateCount].name);

        printf("Political Party: ");
        scanf("%s", candidateList[candidateCount].party);

        printf("Constituency: ");
        scanf("%s", candidateList[candidateCount].constituency);

        candidateCount++;

        saveCandidateToFile(candidateList, candidateCount);

        // Ask the user if they want to register another candidate
        char addAnother;
        printf("Do you want to add another candidate? (y/n): ");
        scanf(" %c", &addAnother);  // Notice the space before %c to consume the newline character

        if (addAnother != 'y' && addAnother != 'Y') {
            return;  // Return to admin menu if the user chooses not to add another candidate
        }

    } while (1);  // Infinite loop, will break when the user chooses not to add another candidate
}

void saveCandidateToFile(struct Candidate *candidate, int count) {
    FILE *file = fopen("candidatelist.txt", "a+");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\t%s\t%s\n", candidate[i].name, candidate[i].party, candidate[i].constituency);
    }

    fclose(file);
}


void displayCandidateList() {
    printf("\nDisplay Candidate List\n");
    FILE *file = fopen("candidatelist.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Local variable to track the number of candidates
    int candidateCount = 0;

    printf("Candidate List:\n");
    printf("No.\tName\tParty\tConstituency\n");

    while (fscanf(file, "%s %s %s", candidateList[candidateCount].name, candidateList[candidateCount].party, candidateList[candidateCount].constituency) == 3) {
        printf("%d\t%s\t%s\t%s\n", candidateCount + 1, candidateList[candidateCount].name, candidateList[candidateCount].party, candidateList[candidateCount].constituency);
        candidateCount++;
    }

    fclose(file);

    // Ask the user to press any key to go back to the admin menu
    printf("\nPress any key to go back to the Admin Menu...");
    getchar();  // Consume the newline character left in the input buffer
    getchar();  // Wait for any key press
}




void voterRegistration() {
    printf("\nVoter Registration\n");
    printf("Enter the number of voters: ");
    int numVoters;
    scanf("%d", &numVoters);

    for (int i = 0; i < numVoters; i++) {
        // Auto-generate SNO starting from 120 and find a unique one
        int sno;
        do {
            sno = 120 + voterCount;
            int snoExists = 0;

            // Check if the SNO is already used
            for (int j = 0; j < voterCount; j++) {
                if (voterList[j].sno == sno) {
                    snoExists = 1;
                    break;
                }
            }

            if (!snoExists) {
                break;
            }

        } while (1);

        printf("Voter SNO: %d\n", sno);
        
        // Continue with the voter details input
        printf("Enter details for Voter %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", voterList[voterCount].name);
        printf("Date of Birth (yyyy/mm/dd): ");
        scanf("%s", voterList[voterCount].dob);
        printf("Address: ");
        scanf(" %s", voterList[voterCount].address);
        printf("Password: ");
        scanf("%s", voterList[voterCount].password);

        voterList[voterCount].sno = sno;  // Assign the generated SNO

        voterCount++;
    }

    saveVoterToFile(voterList, voterCount);
}





void saveVoterToFile(struct Voter *voter, int count) {
    FILE *file = fopen("voterlist.txt", "a+");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "SNO\tName\tDate of Birth\tAddress\tPassword\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\t%s\t%s\t%s\t%s\n", voter[i].sno, voter[i].name, voter[i].dob, voter[i].address, voter[i].password);
    }

    fclose(file);
}

void updateVoterDetails() {
    printf("\nUpdate Voter Details\n");
    int sno;
    char oldPassword[MAX_PASSWORD_LENGTH];

    for (int attempt = 1; attempt <= MAX_ADMIN_TRIES; attempt++) {
        printf("Attempt %d:\n", attempt);
        printf("Enter Voter SNO: ");
        scanf("%d", &sno);
        printf("Enter Old Password: ");
        scanf("%s", oldPassword);

        // Search for the voter by SNO and old password
        int index = -1;
        for (int i = 0; i < voterCount; i++) {
            if (voterList[i].sno == sno && strcmp(voterList[i].password, oldPassword) == 0) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            printf("\nCurrent Voter Details:\n");
            printf("SNO: %d\n", voterList[index].sno);
            printf("Name: %s\n", voterList[index].name);
            printf("Date of Birth: %s\n", voterList[index].dob);
            printf("Address: %s\n", voterList[index].address);

            // Allow the user to update each detail
            printf("\nEnter New Details:\n");
            printf("Name: ");
            scanf("%s", voterList[index].name);
            printf("Date of Birth (yyyy/mm/dd): ");
            scanf("%s", voterList[index].dob);
            printf("Address: ");
            scanf("%s", voterList[index].address);

            char newPassword[MAX_PASSWORD_LENGTH];
            printf("Enter New Password: ");
            scanf("%s", newPassword);

            // Update the password
            strcpy(voterList[index].password, newPassword);

            // Save the updated voter details to file
            saveVoterToFile(voterList, voterCount);
            printf("Voter details updated successfully.\n");

            // Exit the loop if the update is successful
            break;
        } else {
            printf("Voter not found or incorrect old password. ");
            if (attempt < MAX_ADMIN_TRIES) {
                printf("Please try again.\n");
            } else {
                printf("Exceeded maximum attempts. Returning to Admin Menu.\n");
                break;
            }
        }
    }

    // Ask the user to press any key to continue
    printf("\nPress any key to go back to the Admin Menu...");
    getchar();  // Consume the newline character left in the input buffer
    getchar();  // Wait for any key press
}



void searchVoterDetails() {
    printf("\nSearch Voter Details\n");
    int sno;
    printf("Enter Voter SNO: ");
    scanf("%d", &sno);

    FILE *file = fopen("voterlist.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int fileSNO;
    char name[50], dob[11], address[50], password[MAX_PASSWORD_LENGTH];

    // Read the header line (if any) and discard it
    fscanf(file, "%*[^\n]\n");

    // Search for the voter by SNO
    while (fscanf(file, "%d\t%s\t%s\t%s\t%s", &fileSNO, name, dob, address, password) == 5) {
        if (fileSNO == sno) {
            printf("Voter Details:\n");
            printf("SNO: %d\n", fileSNO);
            printf("Name: %s\n", name);
            printf("Date of Birth: %s\n", dob);
            printf("Address: %s\n", address);
            // Do not display password for security reasons
            fclose(file);

            // Ask the user to press any key to continue
            printf("\nPress any key to go back to the Admin Menu...");
            getchar();  // Consume the newline character left in the input buffer
            getchar();  // Wait for any key press
            return;
        }
    }

    fclose(file);
    printf("Voter not found.\n");

    // Ask the user to press any key to continue
    printf("\nPress any key to go back to the Admin Menu...");
    getchar();  // Consume the newline character left in the input buffer
    getchar();  // Wait for any key press
}


void displayVoterList() {
    printf("\nDisplay Voter List\n");
    FILE *file = fopen("voterlist.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int sno;
    char name[50], dob[11], address[50], password[20];

    // Read the header line (if any) and discard it
    fscanf(file, "%*[^\n]\n");

    printf("SNO\tName\tDate of Birth\tAddress\n");
    while (fscanf(file, "%d\t%s\t%s\t%s\t%s", &sno, name, dob, address, password) == 5) {
        printf("%d\t%s\t%s\t%s\n", sno, name, dob, address);
    }

    fclose(file);

    // Ask the user to press any key to go back to the admin menu
    printf("\nPress any key to go back to the Admin Menu...");
    getchar();  // Consume the newline character left in the input buffer
    getchar();  // Wait for any key press
}


void allowToCastVote() {
    // Implement allowing to cast vote logic
    printf("\nAllow to Cast Vote\n");
    int sno;
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Voter SNO: ");
    scanf("%d", &sno);
    printf("Enter Password: ");
    scanf("%s", password);

    // Authenticate the voter
    int index = -1;
    for (int i = 0; i < MAX_VOTERS; i++) {
        if (voterList[i].sno == sno && strcmp(voterList[i].password, password) == 0) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        // Check if the voter has already cast a vote
        if (strcmp(voterList[index].password, "Voted") == 0) {
            printf("You have already cast a vote. Multiple votes are not allowed.\n");
        } else {
            // Display candidates for the voter's constituency
            char constituency[50];
            strcpy(constituency, voterList[index].address);  // Assuming address is the same as the constituency
            printf("Candidates for Constituency %s:\n", constituency);

            // Implement logic to display candidates based on the voter's constituency
            for (int i = 0; i < candidateCount; i++) {
                if (strcmp(candidateList[i].constituency, constituency) == 0) {
                    printf("%d. Name: %s, Party: %s\n", i + 1, candidateList[i].name, candidateList[i].party);
                }
            }

            // Get the candidate number for the vote
            int candidateNumber;
            printf("Enter the number of the candidate you want to vote for: ");
            scanf("%d", &candidateNumber);

            // Increment the vote count for the selected candidate
            voteCount[candidateNumber - 1]++;

            // Update the voter's password to indicate that they have cast a vote
            strcpy(voterList[index].password, "Voted");

            // Save the updated data to files
            saveVoterToFile(voterList, voterCount);
            saveCandidateToFile(candidateList, candidateCount);

            printf("Vote cast successfully.\n");
        }
    } else {
        printf("Authentication failed. Voter not found or invalid password.\n");
    }
}

void displayVoteResult() {
    // Implement displaying vote result logic
    printf("\nDisplay Vote Result\n");

    // Sort candidates based on vote count (bubble sort)
    for (int i = 0; i < candidateCount - 1; i++) {
        for (int j = 0; j < candidateCount - i - 1; j++) {
            if (voteCount[j] < voteCount[j + 1]) {
                // Swap candidates and their vote counts
                int temp = voteCount[j];
                voteCount[j] = voteCount[j + 1];
                voteCount[j + 1] = temp;

                struct Candidate tempCandidate = candidateList[j];
                candidateList[j] = candidateList[j + 1];
                candidateList[j + 1] = tempCandidate;
            }
        }
    }

    // Display the sorted result
    printf("Vote Result (Top 5):\n");
    for (int i = 0; i < 5 && i < candidateCount; i++) {
        printf("%d. %s (%s) - Votes: %d\n", i + 1, candidateList[i].name, candidateList[i].party, voteCount[i]);
    }

    // Save the vote result to file
    saveVoteResultToFile(voteCount, candidateCount);
}

// ...


void saveVoteResultToFile(int *voteCount, int candidateCount) {
    FILE *file = fopen("voteresult.txt", "a+");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Vote Result (Top 5):\n");
    for (int i = 0; i < 5 && i < candidateCount; i++) {
        fprintf(file, "%d. %s (%s) - Votes: %d\n", i + 1, candidateList[i].name, candidateList[i].party, voteCount[i]);
    }

    fclose(file);
}

void endProgram() {
    // Implement logic for ending the program
    printf("\nProgram ended.\n");

    // Save voter and candidate data to files before exiting
    saveVoterToFile(voterList, voterCount);
    saveCandidateToFile(candidateList, candidateCount);

    exit(EXIT_SUCCESS);  // Terminate the program
}

// Implementation of voterLogin function
void voterLogin() {
    int sno;
    char password[MAX_PASSWORD_LENGTH];
int tries = 0;
    int maxTries = MAX_VOTER_LOGIN_TRIES;

    do {
        printf("\nVoter Login\n");
        printf("Enter Voter SNO: ");
        scanf("%d", &sno);
        printf("Enter Password: ");
        scanf("%s", password);

        // Authenticate the voter
        int index = -1;
        for (int i = 0; i < MAX_VOTERS; i++) {
            if (voterList[i].sno == sno && strcmp(voterList[i].password, password) == 0) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            // Check if the voter has already cast a vote
            if (strcmp(voterList[index].password, "Voted") == 0) {
                printf("You have already cast a vote. Multiple votes are not allowed.\n");
            } else {
                // ... (Previous code remains the same)

                // Update the voter's password to indicate that they have cast a vote
                strcpy(voterList[index].password, "Voted");

                // Save the updated data to files
                saveVoterToFile(voterList, voterCount);
                saveCandidateToFile(candidateList, candidateCount);

                printf("Vote cast successfully.\n");
            }

            // Successfully logged in, exit the loop
            break;
        } else {
            printf("Authentication failed. Voter not found or invalid password.\n");
            tries++;

            if (tries == maxTries) {
                printf("Exceeded maximum login attempts. Returning to Main Menu.\n");
                returnToMainMenu();
                return;
            }

            printf("Remaining attempts: %d\n", maxTries - tries);
        }
    } while (1);  // Infinite loop for multiple login attempts
}

void returnToMainMenu() {
    // Function to clear the input buffer
    void clearInputBuffer() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // Ask the user to press any key to return to the main menu
    printf("\nPress any key to go back to the Main Menu...");
    clearInputBuffer();
    getchar();  // Wait for any key press
}

