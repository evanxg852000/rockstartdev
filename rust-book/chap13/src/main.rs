use std::thread;
use std::time::Duration;
use std::collections::HashMap;
use std::hash::Hash;
use std::cmp::Eq;

fn simulated_expive_calculation(){
    println!("Calculating slowly...");
    thread::sleep(Duration::from_secs(2));
}

#[derive(Debug)]
struct Cacher<T, U> 
where T: Fn(U) -> U,
      U: Hash + Eq + Copy
{
    calculation: T,
    values: HashMap<U, U>,
}

impl<T, U> Cacher<T, U>
where T: Fn(U) -> U ,
      U: Hash + Eq + Copy
{
    fn new(calculation: T) -> Cacher<T, U> {
        Cacher{
            calculation,
            values: HashMap::new(),
        }
    }

    fn value(&mut self, arg: U) -> U {
        match self.values.get(&arg) {
            Some(v) => *v,
            None => {
                let v = (self.calculation)(arg);
                self.values.insert(arg, v);
                v
            },
        }
    }
}

#[derive(Debug, PartialEq)]
struct Shoe {
    size: u32,
    style: String,
}

fn shoes_in_my_size(shoes: Vec<Shoe>, shoe_size: u32) -> Vec<Shoe> {
    shoes.into_iter()
        .filter(|s| s.size == shoe_size)
        .collect()
}

#[test]
fn filter_by_size() {
    let shoes = vec![
        Shoe{size: 10, style: String::from("Sneaker")},
        Shoe{size: 13, style: String::from("Sandal")},
        Shoe{size: 10, style: String::from("Boot")},
        Shoe{size: 12, style: "Babouche".to_string()},
    ];

    let in_my_size = shoes_in_my_size(shoes, 10);
    assert_eq!(
        in_my_size,
        vec![
            Shoe{size: 10, style: String::from("Sneaker")},
            Shoe{size: 10, style: String::from("Boot")},
        ]
     );
}

#[derive(Debug)]
struct Counter {
    count: u32,
}

impl Counter {
    fn new() -> Counter {
        Counter{ count: 0 }
    }
}

impl Iterator for Counter {
    type Item = u32;

    fn next(&mut self) -> Option<Self::Item> {
        self.count += 1;
        if self.count <= 5 {
            Some(self.count)
        } else {
            None
        }
    }
}

#[test]
fn calling_next_directly() {
    let mut ctr = Counter::new();
    assert_eq!(ctr.next(), Some(1));
    assert_eq!(ctr.next(), Some(2));
    assert_eq!(ctr.next(), Some(3));
    assert_eq!(ctr.next(), Some(4));
    assert_eq!(ctr.next(), Some(5));
    assert_eq!(ctr.next(), None);
}

#[test]
fn using_other_iter_trait_methods() {
    let sum: u32 = Counter::new().zip(Counter::new().skip(1))
        .map(|(a, b)| a * b)
        .filter(|x| x % 3 == 0)
        .sum();
    assert_eq!(18, sum);
}

fn main() {
    // let mut cacher = Cacher::new(|num| {
    //     println!("Calculating slowly...");
    //     thread::sleep(Duration::from_secs(2));
    //     num
    // });

    // println!("{}", cacher.value(23));
    // println!("{}", cacher.value(55));
    // println!("{}", cacher.value(23));

    // let x = 4;
    // let equal_to_x = |z| z == x;
    // assert!(equal_to_x(4)); 

    // let v1 = vec![1, 2, 3];
    // let v1_iter = v1.iter();
    // for v in v1_iter {
    //     println!("Got {}", v);
    // }

    // let v1 = vec![1, 2, 3, 4, 5];
    // let v1_iter = v1.iter();
    // let s: u32 = v1_iter.sum();
    // assert_eq!(s, 15);

    let v1: Vec<i32> = vec![1, 2, 3, 4, 5];
    let v2: Vec<_> = v1.iter().map(|x| x+ 1).collect();
    assert_eq!(v2, vec![2, 3, 4, 5, 6]);
    
}
