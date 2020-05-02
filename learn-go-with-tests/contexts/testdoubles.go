package contexts

import (
  "context"
  "errors"
  "net/http"
  "testing"
  "time"
)

// SpayStore ...
type SpyStore struct {
  response string
  t *testing.T
}
// Fetch ...
func (s * SpyStore) Fetch(ctx context.Context) (string, error) {
  data := make(chan string, 1)

  go func(){
    var result string
    for _, c := range s.response {
      select {
      case <-ctx.Done():
        s.t.Log("spy store got cancelled")
        return
      default:
        time.Sleep(10 * time.Millisecond)
        result += string(c)
      }
    }
    data <- result
  }()

  select {
  case <-ctx.Done():
    return "", ctx.Err()
  case res := <- data:
    return res, nil
  }
}

// SpyResponseWriter ...
type SpyResponseWriter struct {
  written bool
}

//Header ...
func(s *SpyResponseWriter) Header() http.Header {
  s.written = true
  return nil
}

// Write ...
func (s *SpyResponseWriter) Write([]byte) (int, error) {
  s.written = true
  return 0, errors.New("not implemented")
}


// WriteHeader ...
func (s *SpyResponseWriter) WriteHeader(statusCode int) {
  s.written = true
}

