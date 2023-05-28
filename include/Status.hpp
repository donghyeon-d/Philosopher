#ifndef STATUS_HPP
#define STATUS_HPP

typedef enum e_PhiloStatus {
	EATTING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DIE = 3,
	GETFORK = 4,
    END = 10
}	PhiloStatus;

typedef enum e_ForkStatus {
    USED = 0,
    NOTUSED = 1
} ForkStatus;

#define FALSE 0
#define TRUE 1

#endif