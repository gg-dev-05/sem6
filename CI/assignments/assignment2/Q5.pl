reverse_list([], []). % empty list

reverse_list([X], [X]). % list with single element

reverse_list([H|T], X) :-
	reverse_list(T, Y), % reverse the Tail and output it to Y
	append(Y, [H], X). % append Y to Head and output to X

	