bigger(eight, six).
bigger(six, five).
bigger(five, two).
bigger(five, one).
bigger(ten, eight).

is_bigger(X, Y) :- bigger(X,Y).
is_bigger(X, Y) :- bigger(X,Z), is_bigger(Z,Y).

