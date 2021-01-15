#ifndef match_h
#define match_h

#include "date.h"
#include "connect4.h"

typedef enum tMatchState { Ongoing, Finished, Closed1, Closed2 };

typedef struct {

	std::string player1;
	std::string player2;
	tDate startDate;
	tDate lastUpdate;
	tMatchState matchState;
	tConecta4 connect4; //tConnect4

} tMatch;

void newMatch(tMatch &match, const std::string &player1, const std::string &player2); /*Given
the players’ ids, it returns a new match with all the needed information.*/

void finish(tMatch &match);/*Sets the match status to Finished.*/

void close(tMatch &match, const std::string &player);/*Given a player id and the match
to be closed, sets the match state to Closed.*/

void save(const tMatch &match, std::ofstream &file);/*Given an output file already opened
and a match, writes match information in the file(see example in Section 3.2).*/

bool load(tMatch &match, std::ifstream &file);/*Given an input file already opened, reads
from the file the information for one match and returns the match.Returns false if the
match could not be read.*/



#endif //match_h