#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_CONSTITUENCIES 10
#define MAX_CANDIDATES 50
#define MAX_VOTERS 100
#define MAX_PASSWORD_LENGTH 20
#define MAX_ADMIN_TRIES 3
#define MAX_VOTER_LOGIN_TRIES 3

struct ElectionSchedule {
    char constituency[50];
    char date[9];  // yyyymmdd format
};

struct Candidate {
    char name[50];
    char party[50];
    char constituency[50];
};

struct Voter {
    int sno;
    char name[50];
    char dob[11];  // yyyy/mm/dd format
    char address[50];
    char password[MAX_PASSWORD_LENGTH];
};

#endif
