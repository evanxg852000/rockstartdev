#[derive(Debug)]
pub struct Rectangle {
    length: u32,
    width: u32, 
}

impl Rectangle {
    pub fn can_hold(&self, other: &Rectangle) -> bool {
        self.length > other.length && self.width > other.width
    }
}

pub fn add_two(i: i32) -> i32 {
    i + 2
}

pub fn greeting(name: &str) -> String{
    format!("Hello, {}", name)
}

fn to_panic(){
    unimplemented!("TODO");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn larger_can_hold_smaller() {
        let l = Rectangle{length:8, width:7};
        let s = Rectangle{length:5, width:1};
        assert!(l.can_hold(&s));
    }

    #[test]
    fn smaller_cannot_hold_larger() {
        let l = Rectangle{length:8, width:7};
        let s = Rectangle{length:5, width:1};
        assert!(!s.can_hold(&l));
    }

    #[test]
    fn exploration() {
        assert_eq!(2 + 2, 4);
    }

    #[test]
    fn it_adds_two() {
        assert_eq!(add_two(5), 7);
        assert_ne!(add_two(4), 7);
    }

    #[test]
    fn greeting_contains_name(){
        let r = greeting("Evance");
        assert!(r.contains("Evance"), "failed as value was `{}`", r);
    }

    #[test]
    #[should_panic(expected="TO")]
    fn expect_panic(){
        to_panic();
    }


    #[test]
    #[ignore]
    fn another() {
        panic!("d'hoo");
    }
}
