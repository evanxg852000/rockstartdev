// --- Directions
// Given the root node of a tree, return
// an array where each element is the width
// of the tree at each level.
// --- Example
// Given:
//     0
//   / |  \
// 1   2   3
// |       |
// 4       5
// Answer: [1, 3, 2]

function levelWidth(root) {
    // if(!root) return []
    // res = []
    // let q1 = [root], q2 = []
    // while(q1.length !==0 || q2.length !== 0){
    //     if(q2.length !== 0){
    //         res.push(q2.length)
    //         while(q2.length!==0){
    //             let it = q2.pop()
    //             for(let c of it.children){
    //                 q1.unshift(c)
    //             }
    //         }
    //     }
    //     if(q1.length !== 0){
    //         res.push(q1.length)
    //         while(q1.length!==0){
    //             let it = q1.pop()
    //             for(let c of it.children){
    //                 q2.unshift(c)
    //             }
    //         }
    //     }
    // }
    // return res

    if(!root) return []
    res = []
    let q = ['s', root]
    ctr = 0;
    while(q.length !== 0){
        let it = q.pop()
        if(it === 's'){
            q.unshift(it)
            res.push(ctr)
            ctr = 0
            if(q.length ===1){
                break
            }
            continue
        }
        for(let c of it.children){
            q.unshift(c)
        }
        ctr++
    }
    return res
}

module.exports = levelWidth;
