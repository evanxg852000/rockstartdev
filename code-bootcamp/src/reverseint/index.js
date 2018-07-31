// --- Directions
// Given an integer, return an integer that is the reverse
// ordering of numbers.
// --- Examples
//   reverseInt(15) === 51
//   reverseInt(981) === 189
//   reverseInt(500) === 5
//   reverseInt(-15) === -51
//   reverseInt(-90) === -9

function reverseInt(n) {
    hasSign = (n<0) ? true : false
    n = Math.abs(n)
    //S1
    // rev = parseInt(n.toString().split('').reverse().join(''))
    // return (hasSign)? -rev: rev

    //S2
    rev =0
    while(n>0){
        rev = rev*10 + n%10
        n = Math.floor(n/10)
    }
    return (hasSign)? -rev: rev
}

reverseInt(-5)

module.exports = reverseInt;
