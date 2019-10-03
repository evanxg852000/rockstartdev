// 1.
// unsafe fn dangerous() -> i32{
//     let mut num = 4;
//     let r1 = &mut num as *mut i32;
//     *r1 += 5;
//     *r1
// }

// fn main() {
//     let mut num = 5;

//     let r1 = &num as *const i32;
//     let r2 = &mut num as *mut i32;
//     unsafe {
//         println!("dangerous() = {}", dangerous());

//         println!("r1 = {}", *r1);
//         *r2 = 6;
//         println!("r2 = {}", *r2);
//     }

// }

// 2.
// use std::slice;
// fn split_at_mut(slc: &mut [i32], mid: usize) -> (&mut [i32], &mut [i32]) {
//     let len = slc.len();
//     let ptr = slc.as_mut_ptr();

//     assert!(mid <= len);
//     unsafe {(
//         slice::from_raw_parts_mut(ptr, mid),
//         slice::from_raw_parts_mut(ptr.offset(mid as isize), len - mid )
//     )}
// } 

// 3.
// extern "C" {
//     fn abs(input: i32) -> u32;
// }
// fn main() {
//     unsafe{
//         println!("Abs(-3) = {}", abs(-3));
//     }
// }

// 4.
// static mut COUNTER: u32 = 0;
// fn add_to_count(inc: u32) {
//     unsafe {
//         COUNTER += inc ;
//     }
// }

// fn main() {
//     add_to_count(3);
//     unsafe{
//         println!("COUNTER = {}", COUNTER);
//     }
// }

fn add_one(x: i32) -> i32 {
    x + 1
}

fn do_twice(f: fn(i32)->i32, x: i32) ->i32 {
    f(x) + f(x)
}

fn main() {
    let ans = do_twice(add_one, 5);
    println!("Answer : {}", ans);
}