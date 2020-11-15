package main

import (
	"fmt"
)

const MAX_VERTEX_SIZE = 5
const STACK_SIZE = 1000

type Vertex struct {
	data    string
	visited bool
}

var top = -1
var stacks = make([]int, STACK_SIZE)

func push(elem int) {
	top++
	stacks[top] = elem
}

func pop() int {
	if isEmpty() {
		return -1
	}
	var data = stacks[top]
	top--
	return data
}

func peek() int {
	if isEmpty() {
		return -1
	}
	return stacks[top]
}

func isEmpty() bool {
	if top <= -1 {
		return true
	}
	return false
}

var size = 0
var vertices = make([]Vertex, MAX_VERTEX_SIZE)
var adjacencyMatrix [MAX_VERTEX_SIZE][MAX_VERTEX_SIZE]int

func addVertex(data string) {
	var vertex Vertex
	vertex.data = data
	vertex.visited = false
	vertices[size] = vertex
	size++
}

func addEdge(from, to int) {
	adjacencyMatrix[from][to] = 1
}

func clear() {
	for i := 0; i < size; i++ {
		vertices[i].visited = false
	}
}

func depthFirstSearch() {
	vertices[0].visited = true
	fmt.Printf("%s", vertices[0].data)
	push(0)
	for {
		if isEmpty() {
			break
		}
		var row = peek()
		var col = findAdjacencyUnvisitedVertex(row)
		if col == -1 {
			pop()
		} else {
			vertices[col].visited = true
			fmt.Printf(" ->%s", vertices[col].data)
			push(col)
		}
	}
	clear()
}

func findAdjacencyUnvisitedVertex(row int) int {
	for col := 0; col < size; col++ {
		if adjacencyMatrix[row][col] == 1 && !vertices[col].visited {
			return col
		}
	}
	return -1
}

func printGraph() {
	fmt.Printf("Two-dimensional array traversal vertex edge and adjacent array: \n ")

	for i := 0; i < MAX_VERTEX_SIZE; i++ {
		fmt.Printf("%s ", vertices[i].data)
	}
	fmt.Printf("\n")

	for i := 0; i < MAX_VERTEX_SIZE; i++ {
		fmt.Printf("%s ", vertices[i].data)
		for j := 0; j < MAX_VERTEX_SIZE; j++ {
			fmt.Printf("%d ", adjacencyMatrix[i][j])
		}
		fmt.Printf("\n")
	}
}

func main() {
	addVertex("A")
	addVertex("B")
	addVertex("C")
	addVertex("D")
	addVertex("E")

	addEdge(0, 1)
	addEdge(0, 2)
	addEdge(0, 3)
	addEdge(1, 2)
	addEdge(1, 3)
	addEdge(2, 3)
	addEdge(3, 4)

	printGraph()
	fmt.Printf("\n Depth-first search traversal\n")

	depthFirstSearch()
	fmt.Printf("\n")
}
