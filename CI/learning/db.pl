loves(romeo, juliet).

loves(juliet, romeo) :- loves(romeo, juliet).

male(alebert).
male(bob).
male(bill).
male(carl).
male(charlie).
male(dan).
male(edward).

female(alice).
female(betsy).
female(diana).

parent(alebert, bob).
parent(alebert, betsy).
parent(alebert, bill).

parent(alice, bob).
parent(alice, betsy).
parent(alice, bill).

parent(bob, carl).
parent(bob, charlie).

grand_parent(X,Y) :-
	parent(Z,X),
	parent(Y,Z).

get_grandparent :-
	parent(X, carl),
	parent(X, charlie),
	format('~w ~s grandparent ~n', [X, "is the"]).


what_grade(5) :-
	write('Go to KG').

what_grade(6) :-
	write('Go to Ist').

what_grade(Other) :-
	Grade is Other - 5,
	format('Go to grade ~w', [Grade]).