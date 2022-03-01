element_at(X,[X|_],1) :- 
	!. % if K is 1 => X is the first element of the list

element_at(X, [_|T], K) :-
	(
		% K is more than 1 => assign K1 as K-1 
		% and find element at K-1 in the Tail of the List
		K > 1, 
		K1 is K-1,
		element_at(X, T, K1)
	);
	(
		% K is < 1 => Not possible for given list
		write('\nValue of K out of bounds'),
		X is -1
	).