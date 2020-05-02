package structs

import (
  "testing"
  "math"
)

func TestPerimeter(t *testing.T) {
  rectangle := Rectangle{10.0, 10.0}
  got := Perimeter(rectangle)
  want := 40.0

  if got != want {
    t.Errorf("got %.2f want %.2f", got, want)
  }
}

func TestArea(t *testing.T) {

  checkArea := func(t *testing.T, shape Shape, want float64) {
    t.Helper()
    got := math.Round(shape.Area()*100)/100

    if got != want {
      t.Errorf("got %.2f want %.2f", got, want)
    }
  }
  
  areaTests := []struct {
    shape Shape
    want float64
  } {
    {&Rectangle{12, 6}, 72.0},
    {&Circle{10}, 314.16},
    {&Triangle{12, 6}, 36},
  }

  for _, tt := range areaTests {
    checkArea(t, tt.shape, tt.want)
  }
  
}
