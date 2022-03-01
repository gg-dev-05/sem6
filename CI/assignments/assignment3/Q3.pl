% if Pos is 1 => Insert in the beginning, cut to prevent backtracking
insert_at(Elem,L,1,[Elem|L]):-
        !.

% For any case in which pos is not 1, set Pos1 as Pos-1 and recurse over the tail
% of the list and append head of the list to new list
insert_at(Elem, [H|T], Pos, [H|X]) :-
        Pos1 is Pos-1,
        insert_at(Elem, T, Pos1, X).