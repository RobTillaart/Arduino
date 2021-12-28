

As the formula for combinations is symmetrical one knows that:

- if it works for (N, 0..k) it will also work for (N, n-k..n)
- if it works for (N, 0..k) it will also work for (N-1, 0..k)
- (n, 0) = 1; (n, 1) = n; (n, 2) = n \* (n+1) / 2;  
- from the latter a rule of thumb states that nCr(n,k) < n^k

assume nCr(n,k) > MAXVAL && nCr(n,k-1) <= MAXVAL

k = 2log(MAXVAL) / 2log(n);
zoiets.
 
 

 



