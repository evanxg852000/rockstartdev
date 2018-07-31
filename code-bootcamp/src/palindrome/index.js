// --- Directions
// Given a string, return true if the string is a palindrome
// or false if it is not.  Palindromes are strings that
// form the same word if it is reversed. *Do* include spaces
// and punctuation in determining if the string is a palindrome.
// --- Examples:
//   palindrome("abba") === true
//   palindrome("abcdefg") === false

function palindrome(str) {
    //S1
    //return str === str.split('').reverse().join('')

    //S2
    // rev=''
    // for(let c of str){
    //     rev = c + rev
    // }
    // return rev === str

    //S3 stack
    // let stk=str.split('')
    // for(let c of str){
    //     if(stk.pop() !== c)
    //         return false
    // }
    // return true

    //S4 l +(h-l)/2
    let mid = str.length/2
    for(let i=0; i<mid; i++){
        if(str.charAt(i) !== str.charAt(str.length-i-1))
            return false
    }
    return true
}

module.exports = palindrome;
