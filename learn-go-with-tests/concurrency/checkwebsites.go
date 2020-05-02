package concurrency

import(
  "fmt"
  "time"
  "net/http"
)

// WebsiteChecker ...
type WebsiteChecker func(string) bool

type result struct {
  string
  bool
}

// CheckWebsites ...
func CheckWebsites(wc WebsiteChecker, urls []string) map[string]bool {
  results := make(map[string]bool)
  resultChannel := make(chan result)

  for _, url := range urls {
    go func(u string){
      resultChannel <- result{u, wc(u)}
    }(url)
  }

  for i := 0; i < len(urls); i++{
    result := <- resultChannel
    results[result.string] = result.bool
  }
  
  return results
}

// Racer ...
func Racer(a, b string) (string, error) {
  select {
  case <-ping(a):
    return a, nil
  case <-ping(b):
    return b, nil
  case <-time.After(10 * time.Second):
    return "", fmt.Errorf("timed out waiting for %s and %s", a, b)
  }
}

func ping(url string) chan struct{} {
  ch := make(chan struct{})
  go func() {
    http.Get(url)
    close(ch)
  }()
  return ch
}
