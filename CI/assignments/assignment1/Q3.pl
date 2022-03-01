female(mary).
female(sandra).
female(juliet).
female(lisa).
male(peter).
male(paul).
male(john).
male(bob).
male(harry).
parent(bob, lisa).
parent(bob, paul).
parent(bob, mary).
parent(juliet, lisa).
parent(juliet, paul).
parent(juliet, mary).
parent(peter, harry).
parent(lisa, harry).
parent(mary, john).
parent(mary, sandra).

father(X,Y) :-
	parent(X,Y),
	male(X).

sister(X,Y) :-
	parent(Z, X),
	parent(Z, Y),
	female(X),
	X \= Y.

grandmother(X, Y) :-
	female(X),
	parent(X, Z),
	parent(Z, Y).

cousin(X, Y) :- 
	X \= Y,
	parent(Z, X),
	parent(W, Y),
	Z \= W,
	parent(V, Z),
	parent(V, W).
