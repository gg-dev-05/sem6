% empty list nothing to replace
replace([],_, _, []).

% head of the list matches the elment to be replaced
% thus add replaced element to the list and recurse on tail
replace([H|T], H, Y, [Y|List]) :-
	replace(T, H, Y, List),!.

% head of the list does not match the element to be replace
% thus add head to the new list and recurse on tail 
replace([H|T], X, Y, [H|List]) :-
	replace(T, X, Y, List).