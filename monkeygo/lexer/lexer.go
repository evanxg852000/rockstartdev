package lexer

import "monkeygo/token"

// Lexer ...
type Lexer struct {
	input string
	pos   int
	peek  int
	ch    byte
}

func New(input string) *Lexer {
	l := &Lexer{input: input}
	l.readChar()
	return l
}

func (l *Lexer) NextToken() token.Token {
	var tok token.Token

	l.skipWhitespace()

	switch l.ch {
	case '=':
		if l.peekChar() == '=' {
			ch := l.ch
			l.readChar()
			literal := string(ch) + string(l.ch)
			tok = token.Token{Type: token.EQ, Literal: literal}
		} else {
			tok = newToken(token.ASSIGN, l.ch)
		}
	case '+':
		tok = newToken(token.PLUS, l.ch)
	case '-':
		tok = newToken(token.MINUS, l.ch)
	case '!':
		if l.peekChar() == '=' {
			ch := l.ch
			l.readChar()
			literal := string(ch) + string(l.ch)
			tok = token.Token{Type: token.NOT_EQ, Literal: literal}
		} else {
			tok = newToken(token.BANG, l.ch)
		}
	case '/':
		tok = newToken(token.SLASH, l.ch)
	case '*':
		tok = newToken(token.ASTERISK, l.ch)
	case '<':
		tok = newToken(token.LT, l.ch)
	case '>':
		tok = newToken(token.GT, l.ch)
	case ';':
		tok = newToken(token.SEMICOLON, l.ch)
	case ':':
		tok = newToken(token.COLON, l.ch)
	case ',':
		tok = newToken(token.COMMA, l.ch)
	case '{':
		tok = newToken(token.LBRACE, l.ch)
	case '}':
		tok = newToken(token.RBRACE, l.ch)
	case '(':
		tok = newToken(token.LPAREN, l.ch)
	case ')':
		tok = newToken(token.RPAREN, l.ch)
	case '"':
		tok = token.Token{Type: token.STRING, Literal: l.readString()}
	case '[':
		tok = newToken(token.LBRACKET, l.ch)
	case ']':
		tok = newToken(token.RBRACKET, l.ch)
	case 0:
		tok = token.Token{Type: token.EOF, Literal: ""}
	default:
		if isLetter(l.ch) {
			ident := l.readIdentifier()
			tok = token.Token{Type: token.LookupIdent(ident), Literal: ident}
			return tok
		} else if isDigit(l.ch) {
			tok = token.Token{Type: token.INT, Literal: l.readNumber()}
			return tok
		} else {
			tok = newToken(token.ILLEGAL, l.ch)
		}
	}

	l.readChar()
	return tok
}

func (l *Lexer) skipWhitespace() {
	for l.ch == ' ' || l.ch == '\t' || l.ch == '\n' || l.ch == '\r' {
		l.readChar()
	}
}

func (l *Lexer) readChar() {
	if l.peek >= len(l.input) {
		l.ch = 0
	} else {
		l.ch = l.input[l.peek]
	}

	l.pos = l.peek
	l.peek += 1
}

func (l *Lexer) peekChar() byte {
	if l.peek >= len(l.input) {
		return 0
	}
	return l.input[l.peek]
}

func (l *Lexer) readIdentifier() string {
	pos := l.pos
	for isLetter(l.ch) {
		l.readChar()
	}
	return l.input[pos:l.pos]
}

func (l *Lexer) readNumber() string {
	pos := l.pos
	for isDigit(l.ch) {
		l.readChar()
	}
	return l.input[pos:l.pos]
}
func (l *Lexer) readString() string {
	pos := l.pos + 1
	for {
		l.readChar()
		if l.ch == '"' || l.ch == 0 {
			break
		}
	}
	return l.input[pos:l.pos]
}
func isLetter(ch byte) bool {
	return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || (ch == '_')
}

func isDigit(ch byte) bool {
	return '0' <= ch && ch <= '9'
}

func newToken(tokType token.Type, ch byte) token.Token {
	return token.Token{Type: tokType, Literal: string(ch)}
}
