analyse_list([]) :-
	% input is an empty list
	write('This is an empty list'),!.

analyse_list(L) :-
	% seprate head and tail of the list and write output to screen
	[H | T] = L,
	format('This is the head of your list: ~w ~n', [H]),
	format('This is the tail of your list: ~w ~n', [T]).