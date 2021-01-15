#include "matchList.h"


void init(tMatchList &matches) {

	for (int i = 0; i < DIM; i++)
		newMatch(matches.matchList[i], "Player1", "Player2");

} /*Initializes an empty match list.*/

void save(const tMatchList &matches, const std::string &name) {

	//

} /*Saves the match list in the file with the given name(see example in Section 3.2).*/

bool load(tMatchList &matches, const std::string &name) {

	//

} /*Loads a match list from the file with the given name.*/

bool insert(tMatchList &matches, const tMatch &match) {
	bool correct = false;

	if (matches.counter < (DIM - 1)){
		correct = true;
		matches.counter++; //Adds the value before to use
		matches.matchList[matches.counter] = match;
	}

	return correct;
} /*Given a match, adds the match at the end of the match list, if there is enough room. Returns false if the match could not be inserted.*/