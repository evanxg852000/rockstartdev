use std::rc::Rc;

use crate::ast::LispExp;
use crate::err::LispErr;

fn tokenize(code: String) -> Vec<String> {
  code
    .replace("(", " ( ")
    .replace(")", " ) ")
    .split_whitespace()
    .map(|x| x.to_string())
    .collect()
}

fn parse<'a>(tokens: &'a [String]) -> Result<(LispExp, &'a [String]), LispErr> {
  let (token, rest) = tokens.split_first()
    .ok_or(LispErr::Reason("could not get token".to_string()))?;
  match &token[..] {
    "(" => parse_seq(rest),
    ")" => Err(LispErr::Reason("unexpected `)`".to_string())),
    _ => Ok((parse_atom(token), rest))
  }
}

fn parse_seq<'a>(tokens: &'a [String]) -> Result<(LispExp, &'a [String]), LispErr> {
  let mut res: Vec<LispExp> = vec![];
  let mut xs = tokens;
  loop {
    let (next_token, rest) = xs
        .split_first()
        .ok_or(LispErr::Reason("could not find closing `)`".to_string()))?;
    if next_token == ")" {
      return Ok((LispExp::List(res), rest)) //skip `)`
    }
    let (exp, new_xs) = parse(&xs)?;
    res.push(exp);
    xs = new_xs;
  }
}

fn parse_atom(token: &str) -> LispExp {
  match token {
    "true" => LispExp::Bool(true),
    "false" => LispExp::Bool(false),
    _ => {
      let num = token.parse::<f64>();
      match num {
        Ok(v) => LispExp::Number(v),
        Err(_) => LispExp::Symbol(token.to_string().clone())
      }
    }
  }
}

fn parse_list_of_symbol_strings(form: Rc<LispExp>) -> Result<Vec<String>, LispErr> {
  let list = match form.as_ref() {
    LispExp::List(l) => Ok(l.clone()),
    _ => Err(LispErr::Reason("expected args from to be a list".to_string())),
  }?;

  list
    .iter()
    .map(|x| {
      match x {
        LispExp::Symbol(s) => Ok(s.clone()),
        _ => Err(LispErr::Reason("expected symbols in the agrs list".to_string())),
      }
    }).collect()
}
