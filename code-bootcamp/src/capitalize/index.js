// --- Directions
// Write a function that accepts a string.  The function should
// capitalize the first letter of each word in the string then
// return the capitalized string.
// --- Examples
//   capitalize('a short sentence') --> 'A Short Sentence'
//   capitalize('a lazy fox') --> 'A Lazy Fox'
//   capitalize('look, it is working!') --> 'Look, It Is Working!'

function capitalize(str) {
    //S1
    // res = ''
    // word =''
    // for(c of str){
    //     if(word.trim() === '' && c.match(/[\w]/)){
    //         word += c.toUpperCase()
    //     }else if(c === ' '){
    //         res += word + c
    //         word = ''
    //     } else {
    //         word +=c
    //     }
    // }
    // res += word
    // return res

    //S2
    // str = str.split('')
    // for(let i=0; i<str.length; i++){
    //     if(i==0 && str[i].match(/[\w]/))
    //         str[i]= str[i].toUpperCase();
    //     if(str[i] === ' '){
    //         str[i+1] = str[i+1]? str[i+1].toUpperCase() : ''
    //         i++
    //     }
    // }
    // return str.join('')

    //S3
    return str.split(' ').map((word)=>{
        if(word[0])
            return word.replace(word[0], word[0].toUpperCase())
    }).join(' ')
}

module.exports = capitalize;
