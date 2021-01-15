#include "match.h"


void newMatch(tMatch &match, const std::string &player1, const std::string &player2){

	match.player1 = player1;
	match.player2 = player2;

	match.startDate = currDate();

	match.matchState = Ongoing;

	iniciar(match.connect4);

}/*Given the players’ ids, it returns a new match with all the needed information.*/

void finish(tMatch &match) {

	match.matchState = Finished;

} /*Sets the match status to Finished.*/

void close(tMatch &match, const std::string &player) {

	if (player == match.player1)
		match.matchState = Closed1;
	else
		match.matchState = Closed2;
	
} /*Given a player id and the match to be closed, sets the match state to Closed.*/

void save(const tMatch &match, std::ofstream &file) {

	//

} /*Given an output file already opened and a match, writes match information in the file(see example in Section 3.2).*/

bool load(tMatch &match, std::ifstream &file) {
	bool correct;

	//
	
	return correct;
} /*Given an input file already opened, reads from the file the information for one match and returns the match.Returns false if the match could not be read.*/