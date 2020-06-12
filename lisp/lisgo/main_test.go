package main

import "testing"

func TestTokenize(t *testing.T) {
	expected := []string{""}
	got := Tokenize("")
	if len(got) != len(expected) {
		t.Errorf("expected %v got %v", len(expected), len(got))
	}

	expected = []string{"(", "+", "2", "3", ")"}
	got = Tokenize("(+ 2 3)")
	if len(got) != len(expected) {
		t.Errorf("expected %v got %v", len(expected), len(got))
	}

	for i := range got {
		if got[i] != expected[i] {
			t.Errorf("expected %v got %v", expected[i], got[i])
		}
	}
}

func TestParse(t *testing.T) {

}

func TestToString(t *testing.T) {
	lv := NewLispVal(Number, 23)
	expected := "23"
	got := lv.ToString()
	if got != expected {
		t.Errorf("expected %s got %s", expected, got)
	}

	lv = NewLispVal(Symbol, "define")
	expected = "define"
	got = lv.ToString()
	if got != expected {
		t.Errorf("expected %s got %s", expected, got)
	}

	lv = NewLispVal(List, []*LispVal{
		NewLispVal(Symbol, "+"),
		NewLispVal(Number, 23),
		NewLispVal(Number, 12),
	})
	expected = "(+ 23 12)"
	got = lv.ToString()
	if got != expected {
		t.Errorf("expected %s got %s", expected, got)
	}

}
