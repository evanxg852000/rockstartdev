// Vectors
let v = vec![1,2,3,4];
println!("{:?}", v);    

let mut v2: Vec<i32> = Vec::new();
v2.push(2);
v2.push(4);
println!("{:?}", v2); 

let third: &i32 = &v[2];
let third: Option<&i32> = v.get(4);
println!("{:?}", third); 

let mut v = vec![1, 2, 3, 4, 5];
let first = &v[0];
v.push(6);
println!("{}", first); // will not compile as 2nd previous line declares an immutable ref

let v = vec![100, 32, 57];
for i in &v {
    println!("{}", i);
}

let mut v = vec![100, 32, 57];
for i in &mut v{
    *i += 50;
}
println!("{:?}", v);

    #[derive(Debug)]
enum SpreadSheetCell {
    Int(i32),
    Float(f64),
    Text(String),
    Empty,
}

let row = vec![
    SpreadSheetCell::Int(3),
    SpreadSheetCell::Text(String::from("blue")),
    SpreadSheetCell::Float(10.12),
    SpreadSheetCell::Empty,
];

for cell in row {
    println!("{:?}", cell);
}


// Strings 
let str1 = "Hello,";
let mut s = str1.to_string();
s.push_str(" World!");
println!("{}", s);

s.push('!');
println!("{}", s);

let s1 = String::from("Hello, ");
let s2 = String::from("world!");
let s3 = s1 + &s2;
println!("s3 is {}", s3);
println!("{}", s1); // won't work as s1 has been move in s1+ &s2 => s1.Add(&s2)
println!("{}", s2);

let s = format!("{}-{}-{}", "tic", "tac", "toe");
println!("{}", s);

for c in s.chars() {
    print!("{}, ", c);
}

// HashMap
use std::collections::HashMap;

let mut scores = HashMap::new();
scores.insert("Blue".to_string(), 10);
scores.insert("Yellow".to_string(), 15);
println!("Blue => {:?}", scores.get("Blue"));

let teams = vec![String::from("Blue"), String::from("Yellow")];
let points = vec![10, 15];
let scores: HashMap<_, _> = teams.iter().zip(points.iter()).collect();
println!("{:?}", scores);
for (key, val) in &scores {
    println!("{} -> {}", key, val);
}

let mut scores = HashMap::new();
scores.insert(String::from("Blue"), 15);
scores.insert(String::from("Blue"), 10);

scores.entry(String::from("Blue")).or_insert(45);
scores.entry(String::from("Yellow")).or_insert(50);
for (k, v) in &scores {
    println!("{} -> {}", k, v); 
}

let text = "hello world wonderful world".to_string();
let mut word_count = HashMap::new();
for word in text.split_whitespace() {
    let count = word_count.entry(word).or_insert(0);
    *count += 1;
}
println!("{:?}", word_count);

