% if pos is 1 => remove the first element 
% thus set R as the tail of the list
remove_at(X, [X|R], 1, R) :- !.
	
% if pos is not 1 set P1 as Pos-1, and append head of 
% list to the new list and recurse over tail
remove_at(X, [H|T], Pos, [H|R]) :-
	Pos1 is Pos-1,
	remove_at(X, T, Pos1, R).
