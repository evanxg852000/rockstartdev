// --- Directions
// Given an array and chunk size, divide the array into many subarrays
// where each subarray is of length size
// --- Examples
// chunk([1, 2, 3, 4], 2) --> [[ 1, 2], [3, 4]]
// chunk([1, 2, 3, 4, 5], 2) --> [[ 1, 2], [3, 4], [5]]
// chunk([1, 2, 3, 4, 5, 6, 7, 8], 3) --> [[ 1, 2, 3], [4, 5, 6], [7, 8]]
// chunk([1, 2, 3, 4, 5], 4) --> [[ 1, 2, 3, 4], [5]]
// chunk([1, 2, 3, 4, 5], 10) --> [[ 1, 2, 3, 4, 5]]

function chunk(array, size) {
    //S1  n^2
    // var res = []
    // var temp = []
    // for(let c of array){
    //     if(temp.length == size){
    //         res.push(temp)
    //         temp = []
    //     }
    //     temp.push(c)
    // }
    // res.push(temp)
    // return res

    //S2
    // res = []
    // for(let i=0; i<Math.ceil(array.length/size); i++){
    //     temp =[]
    //     for(let j=0; j<size; j++){
    //         idx = (i*size)+j
    //         if(idx < array.length){
    //             temp.push(array[idx])
    //         }
    //     }       
    //     res.push(temp) 
    // }
    // return res

    //S3
    // res =[]
    // for(let c of array){
    //     last = res[res.length - 1]
    //     if(!last || last.length === size){
    //         res.push([c])
    //     } else{
    //         last.push(c)
    //     }
    // }
    // return res

    //S4
    res = []
    i=0
    while(i < array.length){
        res.push(array.slice(i, i+size))
        i +=size
    }
    return res


}

module.exports = chunk;
