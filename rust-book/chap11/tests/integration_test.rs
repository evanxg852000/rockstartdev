extern crate chap11;

mod common;

#[test]
fn it_adds_two() {
    common::setup();
    assert_eq!(chap11::add_two(3),5);
    assert_ne!(chap11::add_two(5), 6);
}