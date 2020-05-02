package iteration

// Repeat repeats the string n time
func Repeat(str string, n int) string {
	rst := ""
	for i := 0; i < n; i++ {
		rst += str
	}
	return rst
}
