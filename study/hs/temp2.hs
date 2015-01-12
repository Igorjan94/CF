f[]=""
f(x:y)=show x++" "++f y
solve[n,k]=take n((take k(foldr(\(y,z)x->y:z:x)[][(a,n+1-a)|a<-[1..k]]))++(if mod k 2==1 then[d+2..]else[n-d,n-d-1..]))where d=k`div`2
main=interact$f.solve.map read.words
