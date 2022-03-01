remove_duplicates([], []). %empty list as input

remove_duplicates([H | T], L) :-
	% Head is a member of Tail => H is repeating => remove head from list
    member(H, T),
    remove_duplicates(T, L),!. % use cut to prevent backtracking 
    
remove_duplicates([H | T], [H | L]) :-
	% As Head is not a member of Tail => Add Head to List
    remove_duplicates(T, L).


