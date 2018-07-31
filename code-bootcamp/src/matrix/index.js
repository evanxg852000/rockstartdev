// --- Directions
// Write a function that accepts an integer N
// and returns a NxN spiral matrix.
// --- Examples
//   matrix(2)
//     [[1, 2],
//     [4, 3]]
//   matrix(3)
//     [[1, 2, 3],
//     [8, 9, 4],
//     [7, 6, 5]]
//  matrix(4)
//     [[1,   2,  3, 4],
//     [12, 13, 14, 5],
//     [11, 16, 15, 6],
//     [10,  9,  8, 7]]  

function matrix(n) {
    // let res =Array(n).fill(Array(n).fill(0))
    
    // let sr = 0, sc = 0, ctr = 1
    // let er = n-1, ec = n-1
    // while(sc <= ec && sr <= er){
    //     // top row
    //     for(let i=sc; i<=ec; i++){
    //         res[sr][i]=ctr
    //         ctr++
    //     }
    //     sr++
        
    //     // right column
    //     for(let i=sr; i<=er; i++){
    //         res[i][ec]=ctr
    //         ctr++
    //     }
    //     ec--
        
    //     // bottom row
    //     for (let i = ec; i >= sc; i--) {
    //         res[er][i] = ctr;
    //         ctr++;
    //     }
    //     er--;
  
    //     // start column
    //     for (let i = er; i >= sr; i--) {
    //         res[i][sc] = ctr;
    //         ctr++;
    //     }
    //     sc++;

    // }
    // return res

    const results = [];

  for (let i = 0; i < n; i++) {
    results.push([]);
  }

  let counter = 1;
  let startColumn = 0;
  let endColumn = n - 1;
  let startRow = 0;
  let endRow = n - 1;
  while (startColumn <= endColumn && startRow <= endRow) {
    // Top row
    for (let i = startColumn; i <= endColumn; i++) {
      results[startRow][i] = counter;
      counter++;
    }
    startRow++;

    // Right column
    for (let i = startRow; i <= endRow; i++) {
      results[i][endColumn] = counter;
      counter++;
    }
    endColumn--;

    // Bottom row
    for (let i = endColumn; i >= startColumn; i--) {
      results[endRow][i] = counter;
      counter++;
    }
    endRow--;

    // start column
    for (let i = endRow; i >= startRow; i--) {
      results[i][startColumn] = counter;
      counter++;
    }
    startColumn++;
  }

  return results;
}

matrix(4)

module.exports = matrix;
