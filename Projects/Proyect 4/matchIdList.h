#ifndef matchIdList_h
#define matchIdList_h





//Declare the types tMatchId and tMatchIdList to manage the list of ongoing matches of
//the users.The type tMatchId must have the following fields :
//-Id : The match identifier.
//- Link : The index of the match in the match list.
//The type tMatchId is so simple that has no own module nor associated operations.
//The list tMatchIdList will be a variable length list with a maximum number of elements
//(MAX_MATCHES = 10).It is IMPORTANT to take into account that there is no specific order
//in the list.It will be sorted in different ways for each situation.
//Implement at least the following subprograms :
//void init(tMatchIdList &list) : Initializes an empty list.
//bool full(const tMatchIdList &list) : Tells if the list is full.
//bool insert(tMatchIdList &list, tMatchId id) : Adds a new match id at the end of
//the list.Returns false if there is no room in the list.When a new match is created, the
//match information needs to be stored in the list of both players.
//bool erase(tMatchIdList &list, const string &id) : Given an id, deletes the match
//with that id from the list.Returns false if no match with that id is found.ATENTION : This
//operation only deletes matches from the user’s lists, not from the match list.







#endif //matchIdList_h