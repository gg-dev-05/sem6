memberr(X, [X | _]).
memberr(X, [_ | T]) :- memberr(X, T).