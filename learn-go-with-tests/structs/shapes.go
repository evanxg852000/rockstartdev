package structs

import "math"

// Shape represents a shape with area
type Shape interface {
  Area() float64
}

// Rectangle respresents a rectange shape
type Rectangle struct {
  Width float64
  Height float64
}

// Circle represents a cirlce shape
type Circle struct {
  Radius float64
}

// Triangle represents a triangle shape
type Triangle struct {
  Base float64
  Height float64
}

// Perimeter computes the perimeter of shape
func Perimeter(rect Rectangle) float64 {
  return (rect.Width + rect.Height) * 2
}

// Area computes the area of a rectangle
func (r *Rectangle) Area() float64 {
  return r.Width * r.Height
}

// Area computes the area of a circle
func (c *Circle) Area() float64 {
  return c.Radius * c.Radius * math.Pi
}

// Area computes the area of a triangle
func (t *Triangle) Area() float64 {
  return (t.Base * t.Height) / 2
}
