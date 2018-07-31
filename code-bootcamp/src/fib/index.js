// --- Directions
// Print out the n-th entry in the fibonacci series.
// The fibonacci series is an ordering of numbers where
// each number is the sum of the preceeding two.
// For example, the sequence
//  [0, 1, 1, 2, 3, 5, 8, 13, 21, 34]
// forms the first ten entries of the fibonacci series.
// Example:
//   fib(4) === 3

function fib(n, cache ={}) {
    //S1
    // let res = [0,1]
    // for(let i=2; i<=n; i++){
    //     res.push(res[i-1]+res[i-2])
    // }
    // return res[n]
    
    //S2
    // let prev=0, next =1;
    // for(let i=2; i<=n; i++){
    //     temp = prev + next
    //     prev = next
    //     next = temp
    // }
    // return next

    //S3
    // if(n<2) return n
    // return fib(n-1) + fib(n-2)

    //S4
    if(cache[n]) return cache[n]
    if(n<2) {
        cache[n]= n
        return cache[n]
    }
    cache[n]= fib(n-1, cache) + fib(n-2, cache)
    return cache[n]
}

module.exports = fib;
