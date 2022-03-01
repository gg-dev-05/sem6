% only 2 elements are present in the list, assign first one to X
last_but_one([X,_], X) :-
	!. 

% first case fails => recurse the function over tail of the list
last_but_one([_|T], X) :- 
	last_but_one(T, X).