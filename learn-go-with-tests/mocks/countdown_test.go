package mocks

import(
  "testing"
  "reflect"
  "time"
)

type CountdownSpy struct {
  Calls []string
}

func (s *CountdownSpy) Sleep(t time.Duration) {
  s.Calls =  append(s.Calls, "sleep")
}

func (s *CountdownSpy) Write(p []byte) (n int, err error){
  s.Calls = append(s.Calls, "write")
  return len(p), nil
}

func TestCountdown(t *testing.T) {
  spy := &CountdownSpy{}

  Countdown(spy, spy)

  want := []string{
    "sleep",
    "write",
    "sleep",
    "write",
    "sleep",
    "write",
    "sleep",
    "write",
  }

  if !reflect.DeepEqual(want, spy.Calls) {
    t.Errorf("got %q want %q", spy.Calls , want)
  }
}
