package iteration

import (
	"fmt"
	"testing"
)

func ExampleReapeat() {
	str := Repeat("b", 4)
	fmt.Println(str)
	//Output: bbbb
}

func TestRepeat(t *testing.T) {
	got := Repeat("a", 5)
	want := "aaaaa"

	if want != got {
		t.Errorf("expeceted %q but got %q", want, got)
	}
}

func BenchmarkRepeat(b *testing.B) {
	for i := 0; i < b.N; i++ {
		Repeat("a", 4)
	}
}
