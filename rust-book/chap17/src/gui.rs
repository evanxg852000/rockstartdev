use std::fmt::Debug;

pub trait Draw : Debug {
    fn draw(&self);
}

#[derive(Debug)]
pub struct Screen {
    pub components: Vec<Box<Draw>>,
}

impl Screen {
    pub fn run(&self) {
        for comp in self.components.iter() {
            comp.draw();
        }
    }
}

#[derive(Debug)]
pub struct Button {
    pub width: u32,
    pub height: u32,
    pub label: String,
}

impl Draw for Button {
    fn draw(&self){
        println!("Button({}, {}, {})", self.width, self.height, self.label);
    }
}