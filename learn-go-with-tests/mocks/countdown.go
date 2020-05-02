package mocks

import(
  "fmt"
  "os"
  "io"
  "time"
)

//Sleeper represents and delay object
type Sleeper interface {
  Sleep(t time.Duration)
}

// Countdown count downward
func Countdown(out io.Writer, sleeper Sleeper) {
  for i := 3; i > 0; i-- { 
    sleeper.Sleep(1 * time.Second)
    fmt.Fprintln(out, i)
  }
  
  sleeper.Sleep(1 * time.Second)
  fmt.Fprint(out, "Go!")
}

// DefaultSleeper ...
type DefaultSleeper struct {}

// Sleep ..
func (d *DefaultSleeper) Sleep(t time.Duration) {
  time.Sleep(t)
}

func main(){
  sleeper :=  &DefaultSleeper{}
  Countdown(os.Stdout, sleeper)
}
