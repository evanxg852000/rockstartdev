
#[derive(Debug, PartialEq, Clone)]
pub enum Token {
  LPAREN,
  RPAREN,
  ADD,
  SUB,
  MUL,
  DIV,
  CARET,
  EQUALS,
  NUMBER(f64),
  SYMBOL(String),
  EOF,
}

impl Token {
  
  // returns (prec, associativity) where 0 is left and 1 is right
  pub fn info(&self) -> Option<(usize, usize)> {
    match *self {
      Token::ADD | Token::SUB => Some((10, 0)),
      Token::MUL | Token::DIV => Some((20, 0)),
      Token::CARET => Some((30, 1)),
      _ => None,
    }
  }

  pub fn to_char(&self) -> char {
    match *self {
      Token::LPAREN => '(',
      Token::RPAREN => ')',
      Token::ADD => '+',
      Token::SUB => '-',
      Token::MUL => '*',
      Token::DIV => '/',
      Token::CARET => '^',
      Token::EQUALS => '=',
      Token::EOF => 'E',
      Token::NUMBER(_) => 'N',
      Token::SYMBOL(_) => 'S',

    }
  }

}

pub fn is_eof(t: &Token) -> bool {
  match t {
    &Token::EOF => true,
    _ => false,
  }
}
