use std::ops::Deref;
use std::rc::Rc;

#[derive(Debug)]
pub enum List {
    Cons(i32, Box<List>),
    Nil
}

#[derive(Debug)]
pub enum List2 {
    Cons(i32, Rc<List2>),
    Nil
}

#[derive(Debug)]
pub struct MyBox<T>(T);

impl<T> MyBox<T> {
    pub fn new(x: T) -> MyBox<T> {
        MyBox(x)
    }
}

impl<T> Deref for MyBox<T> {
    type Target = T;

    fn deref(&self) -> &T {
        &self.0
    }
}


pub trait Messenger {
    fn send(&self, msg: &str);
}

pub struct LimitTracker<'a , T: 'a + Messenger> {
    messenger: &'a T,
    value: usize,
    max: usize,
}

impl<'a, T> LimitTracker<'a, T> 
where T: Messenger {

    pub fn new(messenger: &T, max: usize) -> LimitTracker<T>{
        LimitTracker {
            messenger,
            value: 0,
            max,
        }
    }

    pub fn set_value(&mut self, value: usize) {
        self.value = value;
        let percent_of_max = self.value as f64 / self.max as f64;

        if percent_of_max > 0.75 && percent_of_max < 0.9 {
            self.messenger.send("Warning: you have used up over 75% of of your quota!");
        } else if percent_of_max >= 0.9 && percent_of_max < 1.0 {
            self.messenger.send("Urgent Warning: you have used up over 90% of of your quota!");
        } else if percent_of_max >= 1.0 {
            self.messenger.send("Error: you are over your quota!");
        }
    }


}

#[cfg(test)]
mod tests {
    use super::*;
    use std::cell::RefCell;

    #[derive(Debug)]
    struct MockMessenger {
        sent_messenges: RefCell<Vec<String>>,
    }

    impl MockMessenger {
        fn new() -> Self {
            MockMessenger{
                sent_messenges: RefCell::new(vec![])
            }
        }
    }

    impl Messenger for MockMessenger {
        fn send(&self, msg: &str){
            self.sent_messenges.borrow_mut().push(String::from(msg));
            // folowwing 2 line will panic as it break the borrow rules
            // let first_borrow = self.sent_messenges.borrow_mut();
            // let second_borrow = self.sent_messenges.borrow_mut();
        }
    }

    #[test]
    fn it_sends_an_over_75_percent_warning_message() {
        let mock_messenger = MockMessenger::new();
        let mut limit_tracker = LimitTracker::new(&mock_messenger, 100);

        limit_tracker.set_value(80);
        assert_eq!(mock_messenger.sent_messenges.borrow().len(), 1);
    }

}