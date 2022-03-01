parent(alebert, bob).
parent(alebert, betsy).
parent(alebert, bill).

parent(alice, bob).
parent(alice, betsy).
parent(alice, bill).

parent(bob, carl).
parent(bob, charlie).

related(X, Y) :-
	parent(X, Z),
	related(Z, Y).

say_hi :-
	write('What is your name? '),
	read(X),
	format('Hello ~w', [X]).

fav_char :-
	write('What is your fav char? '),
	get(X), 
	format('The ASCII value of ~c is ~w ~n', [X,X]).