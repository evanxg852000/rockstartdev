extern crate chap17;

use chap17::AveragedCollection;

use chap17::gui::{Screen, Button, Draw};

#[derive(Debug)]
struct SelectBox {
    width: u32,
    height: u32,
    options: Vec<String>,
}

impl Draw for SelectBox{
    fn draw(&self) {
        println!("SelectBox({}, {}, {:?})", self.width, self.height, self.options);
    }
}

fn main() {
    // let mut c = AveragedCollection::new();
    // c.add(3);
    // c.add(5);
    // c.add(6);
    // println!("c.average = {}", c.average());
    // c.remove();
    // println!("c.average = {}", c.average());
    // println!("Hello, world!");

    let screen = Screen {
        components: vec![
            Box::new(SelectBox{
                width: 75,
                height: 10,
                options: vec![
                    String::from("Yes"),
                    String::from("Maybe"),
                    String::from("No"),
                ]
            }),
            Box::new(Button {
                width: 50,
                height:10,
                label: String::from("OK"),
            }),
        ]
    };

    screen.run();
    
}
