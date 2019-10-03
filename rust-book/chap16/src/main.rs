// ======== PART I ==========
// use std::thread;
// use std::time::Duration;
// fn main() {
//     let handle = thread::spawn(move || {
//         for i in 1..10 {
//             println!("hi number {} from spawned thread", i);
//             thread::sleep(Duration::from_millis(1))
//         }
//     });

//     for i in 1..5 {
//         println!("hi number {} from main thread", i);
//         thread::sleep(Duration::from_millis(1))
//     }
//     handle.join().unwrap();

// }

// use std::thread;
// use std::time::Duration;
// fn main() {
//     let v = vec![1, 2, 3];

//     let handle = thread::spawn(move || {
//         println!("here is a vector {:?}", v);
//     });

//     handle.join().unwrap();
// }

// ======== PART II ==========
// use std::thread;
// use std::sync::mpsc;

// fn main() {
//     let (tx, rx) = mpsc::channel();
//     thread::spawn(move || {
//         let val = String::from("Hi");
//         tx.send(val).unwrap();
//         // println!("val is {}", val); wont compile
//     });

//     let received = rx.recv().unwrap();
//     println!("Got: {}", received);
// }

// ======== PART III ==========
// use std::thread;
// use std::sync::mpsc;
// use std::time::Duration;

// fn main() {
//     let (tx, rx) = mpsc::channel();
//     let tx1 = mpsc::Sender::clone(&tx);

//     thread::spawn(move || {
//         let vals = vec![
//             String::from("hi"),
//             String::from("from"),
//             String::from("the"),
//             String::from("thread"),
//         ];
//         for val in vals {
//             tx1.send(val).unwrap();
//             thread::sleep(Duration::from_secs(1));
//         }
//     });

//     thread::spawn(move || {
//         let vals = vec![
//             String::from("more"),
//             String::from("message"),
//             String::from("for"),
//             String::from("you"),
//         ];
//         for val in vals {
//             tx.send(val).unwrap();
//             thread::sleep(Duration::from_secs(1));
//         }
//     });

//     for received in rx {
//         println!("Got: {}", received);
//     }

// }

// ======== PART IV ==========
// use std::sync::Mutex;

// fn main() {
//     let  m = Mutex::new(5);
//     {
//         let mut num = m.lock().unwrap();
//         *num = 6;
//     }

//     println!("m = {:?}", m);
// }
// ======== PART V ==========
use std::thread;
use std::sync::{Arc, Mutex};

fn main() {
    let counter = Arc::new(Mutex::new(0));
    let mut handels = vec![];
    for _ in 0..10 {
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move|| {
            let mut num = counter.lock().unwrap();
            *num += 1;
        });
        handels.push(handle);
    }

    for handel in handels {
        handel.join().unwrap();
    }

    println!("Result: {}", *counter.lock().unwrap())
}