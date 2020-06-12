mod parser;

use std::io;
use std::io::prelude::*;
use std::collections::HashMap;
use std::f64;

fn evaluate(input: &str, env: &mut HashMap<String, f64>) -> Result<f64, String> {
  let mut p = parser::Parser::new(input);
  let ast = p.parse()?;
  match ast.eval(env) {
    Some(r) => Ok(r),
    None => Err("No value for that expression!".to_string()),
  }
}

fn main() {
  let mut env = HashMap::new();
  env.insert("this".to_string(), 35.0f64);
  env.insert("pi".to_string(), f64::consts::PI);
  
  let stdin = io::stdin();
  loop {
    print!(">> ");
    io::stdout().flush().ok();

    let mut input = String::new();
    match stdin.read_line(&mut input) {
      Ok(_) => {
        if input.len() == 0 {
          println!("");
          return;
        }

        let code = input.trim_right();
        let result = evaluate(code, &mut env);
        match result {
          Ok(v) => println!("=> {}", v),
          Err(s) => println!("Error: {}", s),
        };
        io::stdout().flush().ok();
      },
      Err(_) => {
        println!("");
        return;
      }
    }
  }
    println!("Hello, world!");
}
