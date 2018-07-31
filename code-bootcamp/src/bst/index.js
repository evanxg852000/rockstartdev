// --- Directions
// 1) Implement the Node class to create
// a binary search tree.  The constructor
// should initialize values 'data', 'left',
// and 'right'.
// 2) Implement the 'insert' method for the
// Node class.  Insert should accept an argument
// 'data', then create an insert a new node
// at the appropriate location in the tree.
// 3) Implement the 'contains' method for the Node
// class.  Contains should accept a 'data' argument
// and return the Node in the tree with the same value.

class Node {
    constructor(val, leftVal, rightVal){
        this.data = val
        this.left = leftVal? new Node(leftVal) : null
        this.right = rightVal? new Node(rightVal) : null
    }

    // insert(data){
    //     let node = this
    //     do {
    //         if(node.data == data)
    //             return
    //         if(node.data > data){
    //             if(node.left)
    //                 node = node.left
    //             else
    //                 node.left = new Node(data)
    //         } else {
    //             if(node.right)
    //                 node = node.right
    //             else
    //                 node.right = new Node(data)
    //         }
    //     } while(node)
    // }

    // contains(data){
    //     let node = this
    //     while(node){
    //         if(node.data === data) 
    //             return node
    //         if(node.data > data)
    //             node = node.left
    //         else
    //             node = node.right
    //     }
    //     return null
    // }

    insert(data){
        if(this.data === data) return
        if(this.data > data){
            if(this.left){
                this.left.insert(data)
            } else{
                this.left = new Node(data)
            }
        } else {
            if(this.right){
                this.right.insert(data)
            } else{
                this.right = new Node(data)
            }
        }
    }

    contains(data){
        if(this.data === data) return this
        if(this.data > data) 
            return this.left? this.left.contains(data) : null
        else
            return this.right? this.right.contains(data) : null
    }


}

module.exports = Node;
