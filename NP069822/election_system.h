#ifndef ELECTION_SYSTEM_H
#define ELECTION_SYSTEM_H

// Include necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include structures
#include "structures.h"

// Function prototypes/ declarations
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

// Global variables
struct ElectionSchedule electionSchedule[MAX_CONSTITUENCIES];
struct Candidate candidateList[MAX_CANDIDATES];
struct Voter voterList[MAX_VOTERS];
int candidateCount;
int voterCount;
int voteCount[MAX_CANDIDATES];

// Main function
int main();

#endif