use std::env;
use std::error::Error;
use std::fs::File;
use std::io::prelude::*;

#[derive(Debug)]
pub struct Config {
    pub query: String,
    pub filename: String,
    pub case_sensitive: bool,
}

impl Config {
    // pub fn new(args: &[String]) -> Result<Config, &'static str> {
    pub fn new(mut args: impl Iterator<Item = String>) -> Result<Config, &'static str> {
        // if args.len() < 3 {
        //     return Err("not enough arguments");
        // }
        // let query = args[1].clone();
        // let filename = args[2].clone();

        args.next();

        let query = match args.next() {
            Some(arg) => arg,
            None => return Err("Didn't get a query string."),
        };
        let filename = match args.next() {
            Some(arg) => arg,
            None => return Err("Didn't get a filename."),
        };

        let case_sensitive = env::var("CASE_INSENSITIVE").is_err();

        Ok(Config{query, filename, case_sensitive})
    }
}

pub fn search<'a>(query: &str, contents: &'a str, case_sensitive: bool) -> Vec<&'a str> {
    // let mut results = Vec::new();
    // for line in contents.lines() {
    //     if !case_sensitive {
    //         if line.to_lowercase().contains(&query.to_lowercase()) {
    //             results.push(line);
    //         }
    //         continue;
    //     }

    //     if line.contains(query) {
    //         results.push(line);
    //     }
    // }
    // results

  
    contents.lines()
        .filter(|line| {
            match case_sensitive {
                true => line.contains(query),
                false => line.to_lowercase().contains(&query.to_lowercase()),
            } 
        })
        .collect()
}

pub fn run(config:Config) -> Result<(), Box<Error>>{
    let mut f = File::open(config.filename).expect("file not found");
    let mut contents = String::new();
    f.read_to_string(&mut contents)?;

    for line in search(&config.query, &contents, config.case_sensitive) {
        println!("{}", line);
    }

    Ok(())
}





#[cfg(test)]
mod test {
    use super::*;


    #[test]
    fn check_less_args() {
        let args = vec![
            "./minigrep".to_string()
        ];
        let cfg = Config::new(env::args());
        assert!(cfg.is_err());
    }

    #[test]
    fn check_config() {
        let args = vec![
            "./minigrep".to_string(), 
            "test".to_string(),
            "poem.txt".to_string()
        ];
        let cfg = Config::new(args.into_iter()).unwrap();
        assert_eq!(cfg.query, "test");
        assert_eq!(cfg.filename, "poem.txt");
    }

    #[test]
    fn case_sensitive() {
        let query = "duct";
        let contents = "\
Rust:
safe, fast, productive.
Pick three.
Duct tape.";

        assert_eq!(
            vec!["safe, fast, productive."], 
            search(query, contents, true)
        );

    }

    #[test]
    fn case_insensitive() {
        let query = "rUsT";
        let contents = "\
Rust:
safe, fast, productive.
Pick three.
Trust me.";
        assert_eq!(
            vec!["Rust:", "Trust me."],
            search(query, contents, false)
        )
    }


}