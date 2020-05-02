package concurrency

import(
  "reflect"
  "testing"
  "strings"
  "time"
  "net/http/httptest"
  "net/http"
)

func mockWebsiteChecker(url string) bool {
  if strings.HasPrefix(url, "waat://") {
    return false
  }
  return true
}

func slowStubWebsiteChecker(_ string) bool {
  time.Sleep(20 * time.Millisecond)
  return true
}

func TestCheckWebsites(t*testing.T) {
  websites := []string{
    "http://google.com",
    "waat://future.com",
    "http://blog.alex.io",
  }

  got := CheckWebsites(mockWebsiteChecker, websites)
  want := map[string]bool {
    "http://google.com": true,
    "waat://future.com": false, 
    "http://blog.alex.io": true,
  }

  if !reflect.DeepEqual(want, got) {
    t.Fatalf("wanted %v gto %v", want, got)
  }
  
}


func BenchmarkCheckWebsites(b *testing.B) {
  urls := make([]string, 100)
  for i :=0; i < len(urls); i++ {
    urls[i] = "a url"
  }

  for i := 0; i < b.N; i++ {
    CheckWebsites(slowStubWebsiteChecker, urls)
  }
}


func makeDelayedServer(delay time.Duration) *httptest.Server {
  return httptest.NewServer(http.HandlerFunc(
    func(w http.ResponseWriter, r *http.Request){
      time.Sleep(delay)
      w.WriteHeader(http.StatusOK)
  }))
} 

func TestRacer(t *testing.T) {
  
  t.Run("pick fastest server", func(t *testing.T) {
    slowServer := makeDelayedServer(20 * time.Millisecond)
    fastServer := makeDelayedServer(0 * time.Millisecond)
   
    defer slowServer.Close()
    defer fastServer.Close()

    want := fastServer.URL
    got, _ := Racer(slowServer.URL, fastServer.URL)

    if got != want {
      t.Errorf("got %q want %q", got, want)
    }
  })

  t.Run("return an error  after 10s timeout", func(t *testing.T){
    slowServer := makeDelayedServer(11 * time.Second)
    fastServer := makeDelayedServer(12 * time.Second)
   
    defer slowServer.Close()
    defer fastServer.Close()
    
    _, err := Racer(slowServer.URL, fastServer.URL)
    if err == nil {
      t.Error("expected an error but didn't get one")
    }
  })


}



