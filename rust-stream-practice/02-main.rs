// https://www.youtube.com/watch?v=7I11degAElQ
use std::collections::HashMap;

fn process<'a>(string: &'a str) -> HashMap<&'a str, Vec<&'a str>> {
  let mut result: HashMap<&str, Vec<&str>> = HashMap::new();
  for line in string.lines() {
    for sentence in line.split_terminator('.') {
      for word in sentence.trim().split_whitespace() {
        if word.chars().next().unwrap().is_uppercase() {
          result.entry(word).or_default().push(sentence);
        }
      }
    }
  }
  result
}

fn main() {
  let contents: Vec<u8> = std::fs::read("pride-and-prejudice.txt").unwrap();
  let contents = String::from_utf8(contents).unwrap();
  let _ = process(&contents);
  println!("{}", contents);
}
