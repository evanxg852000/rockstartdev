package depinjects

import(
  "fmt"
  "io"
)

// Greet greets someone
func Greet(writer io.Writer, name string) {
  fmt.Fprintf(writer, "Hello, %s", name)
}
