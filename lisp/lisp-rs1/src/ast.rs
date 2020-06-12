use std::rc::Rc;
use std::fmt;

use crate::err::LispErr;

pub(crate) enum LispExp {
  Bool(bool),
  Symbol(String),
  Number(f64),
  List(Vec<LispExp>),
  Func(fn(&[LispExp]) -> Result<LispExp, LispErr>),
  Lambda(LispLambda),
}

struct LispLambda {
  pramas: Rc<LispExp>,
  body: Rc<LispExp>
}

impl fmt::Display for LispExp {
  fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
    let s = match self {
      LispExp::Bool(b) => b.to_string(),
      LispExp::Symbol(s) => s.clone(),
      LispExp::Number(n) => n.to_string(),
      LispExp::List(l) => {
        let ls: Vec<String> = l
          .iter()
          .map(|x| x.to_string())
          .collect();
        format!("({})", ls.join(","))
      },
      LispExp::Func(_) => "<function>".to_string(),
      LispExp::Lambda(_) => "<lambda>".to_string(),
    };
    write!(f, "{}", s)
  }
}
