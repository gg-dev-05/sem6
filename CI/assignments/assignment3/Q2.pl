% fib of 0 is 1, cut is added to prevent any backtracking
fibonacci(0, 1) :- !.

% fib of 1 is 1, cut is added to prevent any backtracking
fibonacci(1, 1) :- !.

% recursive fibonacci function
fibonacci(N, F) :-
        % only recurse if N is more than 1
        N > 1,

        % calculate both N1 and N2
        N1 is N-1,
        N2 is N-2,

        % store answer of N1 and N2 in F1 and F2
        fibonacci(N1, F1),
        fibonacci(N2, F2),

        % set F as sum of previously calculated F1 and F2
        F is F1+F2.