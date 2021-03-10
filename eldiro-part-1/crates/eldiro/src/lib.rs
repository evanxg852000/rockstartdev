mod expr;
mod binding_def;
mod val;
mod stmt;
mod env;
mod utils;
mod func_def;

pub use env::Env;
pub use val::Val;

#[derive(Debug)]
pub struct Parse(stmt::Stmt);

impl Parse {
  pub fn eval(&self, env: &mut Env) -> Result<Val, String> {
    self.0.eval(env)
  }
}

pub fn parse(s: &str) -> Result<Parse, String> {
  let (s, stmt) = stmt::Stmt::new(s)?;

  if s.is_empty() {
    Ok(Parse(stmt))
  } else {
    Err("input was not consumed fully by parser". to_string())
  }
}

