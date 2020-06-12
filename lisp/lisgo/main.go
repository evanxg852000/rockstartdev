package main

import (
	"errors"
	"fmt"
	"strconv"
	"strings"

	"github.com/chzyer/readline"
)

// Type represent the type tag
type Type int

const (
	// Number ...
	Number Type = iota
	// List ...
	List
	// Symbol ...
	Symbol
	// Function ...
	Function
)

// LispVal represents a lisp Value
type LispVal struct {
	Type  Type
	Value interface{}
}

// NewLispVal construct a new LispVal
func NewLispVal(t Type, v interface{}) *LispVal {
	return &LispVal{
		Type:  t,
		Value: v,
	}
}

// ToString returns a string representation of LispVal
func (v *LispVal) ToString() string {
	switch v.Type {
	case List:
		lst := make([]string, 0)
		for _, v := range v.Value.([]*LispVal) {
			lst = append(lst, v.ToString())
		}
		return fmt.Sprintf("(%s)", strings.Join(lst, " "))
	case Number:
		return fmt.Sprintf("%f", v.Value.(float64))
	default:
		return fmt.Sprintf("%v", v.Value)
	}
}

// Tokenize return a list of token string from lisp code
func Tokenize(code string) []string {
	code = strings.ReplaceAll(code, "(", " ( ")
	code = strings.ReplaceAll(code, ")", " ) ")
	code = strings.TrimSpace(code)
	return strings.Split(code, " ")
}

// Parse parse a lisp code
func Parse(code string) (*LispVal, error) {
	tokens := Tokenize(code)
	return parseTokens(&tokens)
}

// parseTokens is the recursive decent parser
func parseTokens(tokens *[]string) (*LispVal, error) {
	if len(*tokens) == 0 {
		return nil, errors.New("Unexpected EOF")
	}

	//pop
	token := (*tokens)[0]
	*tokens = (*tokens)[1:]
	if token == "(" {
		lst := make([]*LispVal, 0)
		for (*tokens)[0] != ")" {
			exp, err := parseTokens(tokens)
			if err != nil {
				return nil, err
			}
			lst = append(lst, exp)
		}
		//get rid of last ')'
		*tokens = (*tokens)[1:]
		return NewLispVal(List, lst), nil
	} else if token == ")" {
		return nil, errors.New("Unexpected token `)`")
	} else {
		return parseAtom(token)
	}
}

// parseAtom parses atom form
func parseAtom(token string) (*LispVal, error) {
	if v, err := strconv.ParseFloat(token, 64); err == nil {
		return NewLispVal(Number, v), nil
	}
	return NewLispVal(Symbol, token), nil
}

// Env ...
type Env struct {
	Data   map[string]*LispVal
	Parent *Env
}

// NewEnv create a new environement
func NewEnv(params []string, args []*LispVal, parent *Env) *Env {
	data := make(map[string]*LispVal)
	for i := range params {
		data[params[i]] = args[i]
	}
	return &Env{
		Data:   data,
		Parent: parent,
	}
}

//Find find an object in the env
func (env *Env) Find(v string) *Env {
	if _, ok := env.Data[v]; ok {
		return env
	}
	if env.Parent != nil {
		return env.Parent.Find(v)
	}
	return nil
}

// StandardEnv return a standard global env for lisp interpreter
func StandardEnv() *Env {
	env := &Env{
		Data:   make(map[string]*LispVal),
		Parent: nil,
	}
	env.Data["+"] = NewLispVal(Function, newNativeCallable(func(args []*LispVal) *LispVal {
		return NewLispVal(Number, args[0].Value.(float64)+args[1].Value.(float64))
	}))
	env.Data["-"] = NewLispVal(Function, newNativeCallable(func(args []*LispVal) *LispVal {
		return NewLispVal(Number, args[0].Value.(float64)-args[1].Value.(float64))
	}))
	env.Data["*"] = NewLispVal(Function, newNativeCallable(func(args []*LispVal) *LispVal {
		return NewLispVal(Number, args[0].Value.(float64)*args[1].Value.(float64))
	}))
	env.Data["/"] = NewLispVal(Function, newNativeCallable(func(args []*LispVal) *LispVal {
		return NewLispVal(Number, args[0].Value.(float64)/args[1].Value.(float64))
	}))

	//TODO add remaining
	return env
}

// Callable represent a lisp lambda function or procedure
type Callable struct {
	Params []string
	Body   *LispVal
	Env    *Env
	Func   func([]*LispVal) *LispVal
}

func newNativeCallable(f func([]*LispVal) *LispVal) *Callable {
	return &Callable{
		Params: make([]string, 0),
		Body:   nil,
		Env:    nil,
		Func:   f,
	}
}

//Call execute a call to the lisp procedure
func (c *Callable) Call(args []*LispVal) *LispVal {
	if c.Func != nil {
		return c.Func(args)
	}
	return Eval(c.Body, NewEnv(c.Params, args, c.Env))
}

//Eval evaluate Lisp expression
func Eval(x *LispVal, env *Env) *LispVal {
	switch x.Type {
	case Symbol:
		e := env.Find(x.Value.(string))
		if e != nil {
			return e.Data[x.Value.(string)]
		}
		return nil
	case Number:
		return x
	case List:
		lst := x.Value.([]*LispVal)
		switch lst[0].Value.(string) {
		case "quote":
			return lst[1]
		case "if":
			test := lst[1]
			conseq := lst[2]
			exp := lst[3]
			if Eval(test, env).Value.(bool) {
				exp = conseq
			}
			return Eval(exp, env)
		case "define":
			v := lst[1]
			exp := lst[2]
			env.Data[v.Value.(string)] = Eval(exp, env)
		case "set!":
			v := lst[1]
			if e := env.Find(v.Value.(string)); e != nil {
				exp := lst[2]
				e.Data[v.Value.(string)] = Eval(exp, env)
			}
			return nil
		case "lambda":
			params := make([]string, 0)
			for _, v := range lst[1].Value.([]*LispVal) {
				params = append(params, v.Value.(string))
			}
			body := lst[2]
			return NewLispVal(Function, &Callable{
				Params: params,
				Body:   body,
				Env:    env,
			})
		default:
			proc := Eval(lst[0], env)
			args := make([]*LispVal, 0)
			for _, exp := range lst[1:] {
				args = append(args, Eval(exp, env))
			}
			return proc.Value.(*Callable).Call(args)
		}
	}
	return nil
}

func repl(prompt string) {
	rl, err := readline.New(prompt)
	if err != nil {
		panic(err)
	}
	defer rl.Close()

	global := StandardEnv()

	for {
		code, err := rl.Readline()
		if err != nil || code == ".exit" { // io.EOF
			break
		}
		ast, err := Parse(code)
		if err != nil {
			fmt.Printf("RuntimeError %v \n", err)
			continue
		}
		val := Eval(ast, global)
		if val != nil {
			println(val.ToString())
		} else {
			println("nil")
		}
	}
}

func main() {
	repl("lisgo> ")
}
