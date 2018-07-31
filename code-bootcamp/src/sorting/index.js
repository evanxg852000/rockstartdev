// --- Directions
// Implement bubbleSort, selectionSort, and mergeSort

function bubbleSort(arr) {
    for(let i=0; i<arr.length; i++){
        for(let j=0; j<arr.length-i-1; j++){
            if(arr[j]>arr[j+1]){
                temp = arr[j]
                arr[j] = arr[j+1]
                arr[j+1] = temp
            }
        }
    }
    return arr
}

function selectionSort(arr) {
    let max;
    for(let i=0; i<arr.length; i++){
        max = 0
        for(let j=arr.length-i-1; j>0; j--){
            if(arr[j]> arr[max]){
                max =j
            }
        }
        temp = arr[max]
        arr[max] =arr[arr.length-i-1]
        arr[arr.length-i-1] = temp
    }
    return arr
}

function mergeSort(arr) {

}

function merge(left, right) {

}

module.exports = { bubbleSort, selectionSort, mergeSort };
