package synchronisation

import (
  "sync"
  "testing"
)

func TestCounter(t *testing.T) {
  t.Run("it runs safely concurrently", func(t *testing.T) {
    wantedCounted := 1000
    counter := NewCounter()

    var wg sync.WaitGroup
    wg.Add(wantedCounted)

    for i := 0; i < wantedCounted; i++ {
      go func(w *sync.WaitGroup) {
        counter.Inc()
        wg.Done()
      }(&wg)
    }
    wg.Wait()

    assertCounter(t, counter, wantedCounted)
  })
}

func assertCounter(t *testing.T, got *Counter, want int) {
  t.Helper()
  if got.Value() != want {
    t.Errorf("got %d, want %d", got.Value(), want)
  }
}
