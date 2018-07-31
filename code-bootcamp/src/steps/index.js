// --- Directions
// Write a function that accepts a positive number N.
// The function should console log a step shape
// with N levels using the # character.  Make sure the
// step has spaces on the right hand side!
// --- Examples
//   steps(2)
//       '# '
//       '##'
//   steps(3)
//       '#  '
//       '## '
//       '###'
//   steps(4)
//       '#   '
//       '##  '
//       '### '
//       '####'

function steps(n) {
    //S1 O(n)
    // for(let i=1; i<=n; i++){
    //     let step = Array(i).fill('#').concat(Array(n-i).fill(' ')).join('')
    //     console.log(step)
    // }

    //S2  O(n^2)
    for(let i=1; i<=n; i++){
        let step =''
        for(let u=0; u<i; u++)
            step +='#'
        for(let v=0; v<n-i; v++)
            step +=' '
        console.log(step)
    }
}

// function steps(n, s=0, line=''){
//     if(s == n) return
//     if(line.length == n){
//         console.log(line)
//         steps(n, s+1, '')
//         return
//     } 

//     if(line.length <= s){
//         line +='#'
//     } else{
//         line +=' '
//     }
//     steps(n, s, line)
// }

module.exports = steps;
