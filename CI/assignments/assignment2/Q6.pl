pallindrome([]). % empty list is pallindrome

pallindrome([_]). % list with single element is pallindrome

pallindrome(L) :-
	% H|Rem assigns H = first element, Rem = 2nd to last element
	% H => last element 
	% if H from both the statements is same => Check if Rem is pallindrome or not
	append([H|Rem], [H], L), 
	pallindrome(Rem).