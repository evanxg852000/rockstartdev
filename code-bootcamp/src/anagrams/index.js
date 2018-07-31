// --- Directions
// Check to see if two provided strings are anagrams of each other.
// One string is an anagram of another if it uses the same characters
// in the same quantity. Only consider characters, not spaces
// or punctuation.  Consider capital letters to be the same as lower case
// --- Examples
//   anagrams('rail safety', 'fairy tales') --> True
//   anagrams('RAIL! SAFETY!', 'fairy tales') --> True
//   anagrams('Hi there', 'Bye there') --> False

function anagrams(stringA, stringB) {
    stringA = stringA.toLowerCase();
    stringB = stringB.toLowerCase();

    //first strategy
    // stringA = stringA.replace(/[^a-z]/, '').split('').sort().join('');
    // stringB = stringB.replace(/[^a-z]/, '').split('').sort().join('');
    // return stringA === stringB;

    // second strategy O(3n) => O(n)
    // const alpha='abcdefghijklmnopqrstuvwxyz'
    // var dic ={}
    // for(let c of stringA){
    //     if(alpha.includes(c)){
    //         dic[c] = dic[c]? dic[c]+1 : 1
    //     }
    // }
    // for(let c of stringB){
    //     if(alpha.includes(c)){
    //         if(!dic[c]) return false
    //         dic[c] = dic[c] - 1
    //     }
    // }
    // for(let prop of Object.keys(dic)){
    //     if(dic[prop] !== 0) return false
    // }
    // return true

    //third strategy
    const alpha='abcdefghijklmnopqrstuvwxyz';
    const buildMap = (str)=> {
        var dict={}
        for(let c of str){
            if(alpha.includes(c)){
                dict[c] = dict[c] + 1 || 1
            }
        }
        return dict
    }
    dictA = buildMap(stringA)
    dictB = buildMap(stringB)
    
    if(Object.keys(dictA).length !== Object.keys(dictB).length)
        return false
    for(let prop of Object.keys(dictA)){
        if(dictA[prop] !== dictB[prop]) 
            return false
    }
    return true
}

module.exports = anagrams;
