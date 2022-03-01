concat_lists([], List, List).
concat_lists([Elem|List1], List2, [Elem|List3]) :- concat_lists(List1, List2, List3).

show(List) :-
	member(Elem, List),
	write(Elem),
	nl,
	fail.

len([], 0).
len([_|Tail], N):-
	len(Tail, N1),
	N is N1+1.
