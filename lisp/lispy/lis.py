import math
import operator as op

Symbol = str
List = list
Number = (int, float)


def parse(code):
    '''Read a lisp expression from a string'''
    return read_from_tokens(tokenize(code))

def tokenize(code):
    '''Converts a lisp code source into list of tokens'''
    return code.replace('(', ' ( ').replace(')', ' ) ').split()

def read_from_tokens(tokens):
    '''Build expression from sequence of tokens'''
    if len(tokens) == 0:
        raise SyntaxError('Unexpected EOF')
    
    token = tokens.pop(0)
    if token == '(':
        lst = []
        while tokens[0] != ')':
            lst.append(read_from_tokens(tokens))
        tokens.pop(0)        # get rid of last ')'
        return lst
    elif token == ')':
        raise SyntaxError('Unexpected token `)`')
    else:
        return atom(token)

def atom(token):
    '''parse int or float as Number and anything else as Symbols'''
    try:
        return int(token)
    except ValueError:
        try: 
            return float(token)
        except ValueError:
            return Symbol(token)


class Env(dict):
    '''Environement is dict of symbol/value pairs with a parent Env'''
    
    def __init__(self, params=(), args=(), parent=None):
        self.update(zip(params, args))
        self.parent = parent

    def find(self, var):
        '''Find innermost Env where var appears.'''
        return self if (var in self) else self.parent.find(var)

def standard_env():
    '''Builds the global environement with Lisp standard procedures.'''
    env = Env()
    env.update(vars(math)) # sin, cos, sqrt, pi ...
    env.update({
        '+': op.add,
        '-': op.sub,
        '*': op.mul,
        '/': op.truediv,
        '>': op.gt,
        '<': op.lt,
        '>=': op.ge,
        '<=': op.le,
        '=': op.eq,
        'abs': abs,
        'append': op.add,
        #  'apply': apply,
        'begin': lambda *x: x[-1],
        'car': lambda x: x[0],
        'cdr': lambda x: x[1:],
        'cons': lambda x, y: [x] + y,
        'eq?': op.is_,
        'equal?': op.eq,
        'length': len,
        'list': lambda *x: list(x),
        'list?': lambda x: isinstance(x, list),
        'map': map,
        'max': max,
        'min': min,
        'not': op.not_,
        'null?': lambda x: x == [],
        'number?': lambda x: isinstance(x, Number),
        'procedure?': callable,
        'round': round,
        'symbol?': lambda x: isinstance(x, Symbol),
    })
    return env

class Procedure(object):
    '''User define lisp procedure.'''
    def __int__(self, params, body, env):
        self.params = params
        self.body = body
        self.env = env

    def __call__(self, *args):
        return eval(self.body, Env(self.params, args, self.env))

global_env = standard_env()

def eval(x, env=global_env):
    '''Evaluate an ast in an environement.'''
    if isinstance(x, Symbol):       # variable reference
        return env.find(x)[x]
    elif not isinstance(x, List):   # constant literal
        return x
    elif x[0] == 'quote':           # (quote exp)
        (_, exp) = x
        return exp
    elif x[0] == 'if':              # (if test conseq alt)
        (_, test, conseq, alt) = x
        exp = (conseq if eval(test, env) else alt)
        return eval(exp, env)
    elif x[0] == 'define':          # (define var exp)
        (_, var, exp) = x
        env[var] = eval(exp, env)
    elif x[0] == 'set!':            # (set! var exp)
        (_, var, exp) = x
        env.find(var)[var] = eval(exp, env)
    elif x[0] == 'lambda':          # (lambda (var...) body)
        (_, params, body) = x
        return Procedure(params, body, env)
    else:                           # (proc arg...)
        proc = eval(x[0], env)
        args = [eval(exp, env) for exp in x[1:]]
        return proc(*args)

def schemestr(v):
    '''Converts a lisp type into its string represenation'''
    if isinstance(v, List):
        return '(' + ' '.join(map(schemestr, v)) + ')'
    else:
        return str(v)

def repl(prompt='lis.py> '):
    "A read-eval-print-loop"
    while True:
        code = input(prompt)
        if code == '.exit':
            break

        val = eval(parse(code))
        if val != None:
            print(schemestr(val))


if __name__ == '__main__':
    repl()
