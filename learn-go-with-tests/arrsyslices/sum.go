package arrsyslices

// Sum sums up values from an array
func Sum(numbers []int)  int {
  sum := 0
  for _, number := range numbers {
    sum += number
  }
  return sum
}

// SumAll sums up all arrays passed in
func SumAll(args ...[]int) []int {
  sums := make([]int, len(args))
  for i, nums := range args {
    sums[i] = Sum(nums) 
  }
  return sums
}

// SumAllTails return the tails or all arrys
func SumAllTails(args ...[]int) []int {
  sums := make([]int, len(args))
  for i, arg := range args {
    if len(arg) == 0 {
      sums[i] = 0 
    } else {
      sums[i] = Sum(arg[1:])
    }
  }
  return sums
}
