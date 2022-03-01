% if any one of A or B is zero set gcd as the non zero one
gcd(0,B,B):-!.
gcd(A,0,A):-!.

% if both A and B are same set gcd as A or B
gcd(X,X,X):-!.

% if A > B gcd(A,B) is same as gcd(A-B,B) else gcd(A,B) is same as gcd(A,B-A)
gcd(A,B,X):-
	( A > B,P is A-B, gcd(P,B,X),!);
	( P is B-A, gcd(A,P,X)).
	