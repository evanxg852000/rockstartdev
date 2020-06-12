mod ast;
mod err;
mod parser;
mod env;
mod eval;

use std::io;

use crate::ast::LispExp;
use crate::err::LispErr;
use crate::parser::{tokenize, parse};
use crate::env::LispEnv;
use crate::eval::eval;

fn parse_eval(expr: String, env: &mut LispEnv) -> Result<LispExp, LispErr> {
  let (parsed_exp, _) = parse(&tokenize(expr))?;
  let evaled_exp = eval(&parsed_exp, env)?;

  Ok(evaled_exp)
}

fn slurp_expr() -> String {
  let mut expr = String::new();
  
  io::stdin().read_line(&mut expr)
    .expect("Failed to read line");
  
  expr
}

fn main() {
  let env = LispEnv::default();
  loop {
    println!("risp >");
    let expr = slurp_expr();
    match parse_eval(expr, env) {
      Ok(res) => println!("// 🔥 => {}", res),
      Err(e) => match e {
        LispErr::Reason(msg) => println!("// 🙀 => {}", msg),
      },
    }
  }
}

