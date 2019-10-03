extern crate chap15;

// use chap15::List::{Cons, Nil};
use chap15::List2::{Cons, Nil};
use chap15::MyBox;

use std::ops::Deref;
use std::rc::Rc;

fn hello(name: &str) {
    println!("Hello, {}!", name);
}

#[derive(Debug)]
struct CustomSmartPointer {
    data: String
}

impl Drop for CustomSmartPointer {
    fn drop(&mut self) {
        println!("Droping CustomSmartPointer with data `{}` !", self.data);
    }
}

fn main() {
    // let b = Box::new(5);
    // println!("b = {}", b);

    // let list = Cons(1, 
    //     Box::new(Cons(2, 
    //         Box::new(Cons(3, 
    //         Box::new(Nil))))));
    // println!("{:?}", list);

    // let x = 5;
    // let y = &x;
    // assert_eq!(5, x);
    // assert_eq!(5, *y);

    // let x = 5;
    // let y = Box::new(x);
    // assert_eq!(5, x);
    // assert_eq!(5, *y);

    // let x = 5;
    // let y = MyBox::new(x);
    // assert_eq!(5, x);
    // assert_eq!(5, *y);

    // let m = MyBox::new(String::from("Rust"));
    // hello(&m);
    // hello((m.deref()));

    // let c = CustomSmartPointer{data: String::from("my stuff")};
    // let d = CustomSmartPointer{data: String::from("other stuff")};
    // drop(c);
    // println!("CustomSmartPointers created.");

    // let a = Rc::new(Cons(5, Rc::new(Cons(10, Rc::new(Nil)))));
    // println!("a count: {}", Rc::strong_count(&a));
    // let b = Cons(3, Rc::clone(&a));
    // println!("a count: {}", Rc::strong_count(&a));
    // let c = Cons(4, Rc::clone(&a));
    // println!("a count: {}", Rc::strong_count(&a));
    // {
    //     let d = Cons(12, Rc::clone(&a));
    //     println!("a count: {}", Rc::strong_count(&a));
    // }
    // println!("a count: {}", Rc::strong_count(&a));
    // println!("b -> {:?}", b);
    // println!("c -> {:?}", c);

    // wont compile
    // let x = 5;
    // let y = &mut x;
    
}
