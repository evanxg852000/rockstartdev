
#[derive(Debug)]
enum IpAddrKind {
    V4(String),
    V6(String),
}

#[derive(Debug)]
enum Message {
    Quit,
    Move{x: u32, y: u32},
    Write(String),
    ChangeColor(u8, u8, u8),
}

impl Message {
    fn call(&self) {
        match self {
            Message::Quit => println!("Quit"),
            Message::Move{x, y} => println!("Move{{x:{}, y:{} }}", x, y),
            Message::Write(s) => println!("{}", s),
            Message::ChangeColor(r, g, b) => println!("ChangeColor({}, {}, {})", r, g, b),
        }

    }
}

enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter,
}

fn value_in_cents(coin: Coin) -> u32 {
    match coin {
        Coin::Penny => {
            println!("Lucky Penny !");
            1
        },
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter => 25,
    }
}

fn plus_one(v: Option<u32>) -> Option<u32> {
    match v {
        Some(n) => Some(n + 1),
        None => None,
    }
}

fn main() {
    let v4 = IpAddrKind::V4;
    println!("{:?}", v4(String::from("127.0.0.1")));

    let m = Message::Write(String::from("Hello"));
    m.call();

    let some_num = Some(4);
    let some_string = Some("a string");

    let no_num : Option<u32> = None;

    println!("Value of Dime is: {}", value_in_cents(Coin::Dime));

    println!("{:?}", plus_one(Some(32)));
    println!("{:?}", plus_one(None));

    if let Some(x) = plus_one(Some(5)) {
        println!("{}", x);
    }
}
