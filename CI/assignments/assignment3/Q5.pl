% if X and Y are same => List will contain a single element
% i.e X
range(X,X,[X]) :- !.

% append X to the list and increment X to reach Y
range(X, Y, [X|L]) :-
	% if X > Y => invalid
	X < Y,
	X1 is X+1,
	range(X1, Y, L).