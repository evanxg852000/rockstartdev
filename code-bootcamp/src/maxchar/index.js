// --- Directions
// Given a string, return the character that is most
// commonly used in the string.
// --- Examples
// maxChar("abcccccccd") === "c"
// maxChar("apple 1231111") === "1"

function maxChar(str) {
    //S1
    let dict = {}
    for(let c of str){
        dict[c] = dict[c]+1 || 1
    }
    keys= Object.keys(dict).sort((a,b) => dict[b] - dict[a])
    return keys[0]
}

module.exports = maxChar;
