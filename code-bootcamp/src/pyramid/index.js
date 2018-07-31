// --- Directions
// Write a function that accepts a positive number N.
// The function should console log a pyramid shape
// with N levels using the # character.  Make sure the
// pyramid has spaces on both the left *and* right hand sides
// --- Examples
//   pyramid(1)
//       '#'
//   pyramid(2)
//       ' # '
//       '###'
//   pyramid(3)
//       '  #  '
//       ' ### '
//       '#####'

function pyramid(n) {
    //S1 O(n)
    let size = n + (n-1)
    for(let i=1; i<=n; i++){
        let stepSize = i + (i-1)
        let side = Math.floor((size-stepSize)/2)
        let step = Array(side).fill(' ')
            .concat(Array(stepSize).fill('#'))
            .concat(Array(side).fill(' '))
            .join('')
        console.log(step)
    }
}

module.exports = pyramid;
