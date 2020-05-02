package synchronisation

import "sync"

// Counter ...
type Counter struct {
  mu sync.Mutex
  value int
}

// NewCounter  ...
func NewCounter() *Counter {
  return &Counter{}
}

// Inc ...
func (c *Counter) Inc() {
  c.mu.Lock()
  defer c.mu.Unlock()
  c.value++
}

// Value ...
func (c *Counter) Value() int {
  return c.value
}
