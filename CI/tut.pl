remove_duplicates([], []).
remove_duplicates([Head | Tail], Result) :-
	member(Head, Tail),!,
	remove_duplicates(Tail, Result).
remove_duplicates([Head | Tail], [Head | Result]) :-
	remove_duplicates(Tail, Result).

add(Element, List, Result) :-
	member(Element, List),
	Result = List,
	add(Element, List, [Element | List]).
	
married(john, mary).
married(X,Y) :- married(Y,X).