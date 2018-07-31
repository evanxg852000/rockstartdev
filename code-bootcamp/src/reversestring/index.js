// --- Directions
// Given a string, return a new string with the reversed
// order of characters
// --- Examples
//   reverse('apple') === 'leppa'
//   reverse('hello') === 'olleh'
//   reverse('Greetings!') === '!sgniteerG'

function reverse(str) {
    //S1
    //return str.split('').reverse().join('')

    //S2
    // let stk =[]
    // for(let c of str)
    //     stk.push(c)
    // str=''
    // while(stk.length !== 0)
    //     str += stk.pop()
    // return str

    //S3
    // let s=''
    // for(let i=str.length; i > 0; i--){
    //     s += str.charAt(i-1)
    // }
    // return s

    //S4
    let s=''
    for(let c of str){
        s = c + s
    }
    return s
}

module.exports = reverse;
