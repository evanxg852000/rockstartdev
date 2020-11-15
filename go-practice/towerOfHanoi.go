package main

import (
	"fmt"
)

func hanoi(n int, A, B, C string) {
	if n == 1 {
		fmt.Printf("Move %d %s to %s \n", n, A, C)
	} else {
		hanoi(n-1, A, C, B)
		fmt.Printf("Move %d, from %s to %s \n", n, A, C)
		hanoi(n-1, B, A, C)
	}
}

func main() {
	fmt.Printf("Please enter the number of discs: \n")
	var n int
	fmt.Scanf("%d", &n)
	hanoi(n, "A", "B", "C")
}
