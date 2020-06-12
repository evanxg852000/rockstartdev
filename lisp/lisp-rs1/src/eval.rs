

fn eval(exp: &LispExp, env: &mut LispEnv) -> Result<LispExp, LispErr> {
  match exp {
    LispExp::Bool(_) => Ok(exp.clone()),
    LispExp::Number(_) => Ok(exp.clone()),
    LispExp::Symbol(k) => env.get(k).ok_or(LispErr::Reason(format!("unexpected symbol k='{}'", k))),
    LispExp::List(list) => {
      let from = list
        .first()
        .ok_or(LispErr::Reason("expected a non-empty list".to_string()))?;
      let args = &list[1..];
      match eval_built_in_form(form, args, env) {
        Some(res) => res,
        None => {
          let first = eval(form, env)?;
          match first {
            LispExp::Func(f) => f(&eval_forms(rags, env)?),
            LispExp::Lambda(l) => {
              let new_env = LispEnv::lambda(l.params, args, env)?;
              eval(&l.body, new_env)
            },
            _ => Err(LispErr::Reason("first form must be a function". to_string()))
          }
        }
      }
    },
    LispExp::Func(_) => Err(LispErr::Reason("unexpected form".to_string())),
    LispExp::Lambda(_) => Err(LispErr::Reason("unexpected form".to_string())),
  }
}

fn eval_built_in_form(
  exp: &LispExp,
  args: &[LispExp],
  env: &mut LispEnv
) -> Option<Result<LispExp, LispErr>> {
  match exp {
    LispExp::Symbol(s) => match s.as_ref() {
      "if" => Some(eval_if_args(args), env),
      "def" => Some(eval_def_args(args, env)),
      "fn" => Some(eval_lambda_args(args)),
      _ => None,
    },
    _ => None,
  }
}


fn function_name(<`2`>)<`3`> {
  <`0`>
} eval_if_args(arg_forms: &[RispExp], env: &mut RispEnv) -> Result<RispExp, RispErr> {
  let test_form = arg_forms.first().ok_or(
    LispErr::Reason("expected test form".to_string())
  )?;
  let test_eval = eval(test_form, env)?;
  match test_eval {
    LispExp::Bool(b) => {
      let form_idx = if b { 1 } else { 2 };
      let res_form = arg_forms.get(form_idx)
        .ok_or(LispErr::Reason(format!("expected form idx={}", form_idx)))?;
      let res_eval = eval(res_form, env);
      
      res_eval
    },
    _ => Err(
      LispErr::Reason(format!("unexpected test form='{}'", test_form.to_string()))
    )
  }
}

fn eval_def_args(args: &[RispExp], env: &mut RispEnv) -> Result<RispExp, RispErr> {
  let first_form = args.first().ok_or(
    LispErr::Reason("expected first form".to_string())
  )?;
  let first_str = match first_form {
    LispExp::Symbol(s) => Ok(s.clone()),
    _ => Err(LispErr::Reason("expected first form to be a symbol".to_string())),
  }?;
  let second_form = arg_forms.get(1).ok_or(
    LispErr::Reason("expected second form".to_string())
  )?;
  if arg_forms.len() > 2 {
    return Err(LispErr::Reason("def can only have two forms ".to_string()))
  }

  let second_eval = eval(second_form, env)?;
  env.env.insert(first_str, second_eval);
  
  Ok(first_form.clone())
}


fn eval_lambda_args(arg: &[LispExp]) -> Result<LispExp, LispErr> {
  if arg.len() > 2 {
    return Err(LispErr::Reason("fn definition can only have two forms ".to_string()))
  }
  
  let params = arg.first().ok_or(
    LispErr::Reason("expected args form".to_string())
  )?;
  let body = arg.get(1).ok_or(
    LispErr::Reason("expected second form".to_string())
  )?;
  
  Ok(
    LispExp::Lambda(
      LispLambda {
        body: Rc::new(body.clone()),
        params: Rc::new(params.clone()),
      }
    )
  )
}
