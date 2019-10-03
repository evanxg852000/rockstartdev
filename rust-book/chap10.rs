use std::fmt::{Display, Debug};


fn largest(list: &[i32]) -> i32 {
    let mut largest = list[0];
    for &item in list.iter() {
        if item > largest {
            largest = item
        }
    }
    largest
}

// with clone
fn largest<T: PartialOrd + Clone>(list: &[T]) -> T {
   let mut l = &list[0];
   for item in list.iter() {
       if item > l {
           l = item
       }
   } 
   (*l).clone()
}

// with Copy
fn largest<T: PartialOrd + Copy>(list: &[T]) -> T {
   let mut l = list[0];
   for &item in list.iter() {
       if item > l {
           l = item
       }
   } 
   l
}


fn longest_str<'a>(s1: &'a str, s2: &'a str) -> &'a str {
    if s1.len() > s2.len(){
        s1
    } else {
        s2
    }
}

fn longest_with_annon<'a, T>(s1: &'a str, s2: &'a str, ann: T) -> &'a str 
where T: Display
{
    println!("Annoncement {}!", ann);
    if s1.len() > s2.len() {
        s1
    } else {
        s2
    } 
}

struct Point<T> {
    x: T,
    y: T,
}

impl<T> Point<T>{
    fn x(&self) -> &T {
        &self.x
    }
    fn y(&self) -> &T {
        &self.y
    }
}

pub trait Summary {
    fn summarize(&self) -> String;
}

#[derive(Debug)]
struct NewsArticle {
    headline: String,
    location: String,
    author: String,
    content: String,
}

impl Summary for NewsArticle {
    fn summarize(&self) -> String {
        format!("{} by {}, ({})", self.headline, self.author, self.location)
    }
}

#[derive(Debug)]
struct Tweet {
    pub username: String,
    pub content: String,
    pub reply: bool,
    pub retweet: bool,
}

impl Summary for Tweet {
    fn summarize(&self) -> String {
        format!("{}: {}", self.username, self.content)
    }
}

pub fn notify<T: Summary>(item: T) {
    println!("Breaking news! {}", item.summarize());
}

fn some_func<T, U>(t: T, u: U) 
where T: Display + Clone,
      U: Clone + Debug
{

}


pub trait Summary2 {
    fn summarize(&self) -> String{
        String::from("Read more...")
    }
}
struct Test;
impl Summary2 for Test{
}


fn main() {
    let nums = vec![34, 50, 25, 100, 65];
    let l = largest(&nums);
    println!("{}", l);

    let t = Test{};
    println!("{}", t.summarize());

}
