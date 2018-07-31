// --- Directions
// Write a function that returns the number of vowels
// used in a string.  Vowels are the characters 'a', 'e'
// 'i', 'o', and 'u'.
// --- Examples
//   vowels('Hi There!') --> 3
//   vowels('Why do you ask?') --> 4
//   vowels('Why?') --> 0

function vowels(str) {
    //S1
    // let vowels = 'aeiou'
    // let ct =0
    // for(c of str.toLowerCase()){
    //     if(vowels.includes(c))
    //         ct++
    // }
    // return ct
    //S1
    let m = str.match(/[aeiou]/ig)
    return m? m.length : 0
}

module.exports = vowels;
