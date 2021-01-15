#ifndef matchList_h
#define matchList_h

#include "match.h"

const int DIM = 10;

typedef tMatch tMatchArray[DIM];

typedef struct {

	tMatchArray matchList;
	int counter; //Points to the last used space

} tMatchList;


void init(tMatchList &matches);/*Initializes an empty match list.*/

void save(const tMatchList &matches, const std::string &name);/*Saves the match list in
the file with the given name(see example in Section 3.2).*/

bool load(tMatchList &matches, const std::string &name);/*Loads a match list from the
file with the given name.*/

bool insert(tMatchList &matches, const tMatch &match);/*Given a match, adds the
match at the end of the match list, if there is enough room.Returns false if the match
could not be inserted.*/

#endif //matchList_h