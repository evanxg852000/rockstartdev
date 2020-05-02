package maps

import "errors"

// Dictionary represents a dictionary type
type Dictionary map[string]string

// ErrNoFound represents not fpund error
var ErrNoFound = errors.New("could not find the word you were looking for")

// Search searches the value of a key in a dictionary
func (d *Dictionary) Search(key string) (string, error) {
  found, ok := (*d)[key]
  if !ok {
    return "", ErrNoFound
  }

  return found, nil
}
