// --- Directions
// 1) Create a node class.  The constructor
// should accept an argument that gets assigned
// to the data property and initialize an
// empty array for storing children. The node
// class should have methods 'add' and 'remove'.
// 2) Create a tree class. The tree constructor
// should initialize a 'root' property to null.
// 3) Implement 'traverseBF' and 'traverseDF'
// on the tree class.  Each method should accept a
// function that gets called with each element in the tree

class Node {
    constructor(data){
        this.data = data
        this.children =[]
    }

    add(data){
        this.children.push(new Node(data))
    }

    remove(data){
        this.children.splice(this.children.find((it)=> it.data === data),1)
    }

}

class Tree {
    constructor(){
        this.root = null
    }

    traverseBF(fn){
        if(!this.root) return
        let q=[]
        q.unshift(this.root)
        while(q.length !== 0){
            let curr = q.pop()
            fn(curr)
            for(let node of curr.children){
                q.unshift(node)
            }
        }
    }

    traverseDF(fn, n){
        if(!n) {
            if(!this.root) return
            n = this.root
        }
        fn(n)
        for(let node of n.children){
            this.traverseDF(fn, node)
        }
    }

}

module.exports = { Tree, Node };
