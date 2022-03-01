happy(X) :- parent(X,_). 

hasTwoChildren(X) :- 
	parent(X,Y), 
	sister(Y,_).

grandChild(Z,X) :- 
	parent(X,Y), 
	parent(Y,Z).

aunt(X,Y) :- 
	parent(Z,Y),
	sister(X,Z).
		