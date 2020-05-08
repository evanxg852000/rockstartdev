package main

// ID ..
type ID int

const (
	REG ID = iota // REG ..
	JOIN
	LEAVE
	MSG
	CHNS
	USRS
)

type command struct {
	id        ID
	recipient string
	sender    string
	body      []byte
}
