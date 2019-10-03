pub mod gui;

#[derive(Debug)]
pub struct AveragedCollection {
    list: Vec<i32>,
    average: f64,
}

impl AveragedCollection {
    pub fn new() -> Self {
        AveragedCollection{
            list: vec![],
            average: 0f64,
        }
    }

    pub fn add(&mut self, v: i32){
        self.list.push(v);
        self.update_average();
    }

    pub fn remove(&mut self) -> Option<i32>{
        let last = self.list.pop();
        match last {
            Some(val) => {
                self.update_average();
                Some(val)
            },
            None => None,
        }
    }

    pub fn average(&self) -> f64 {
        self.average
    }

    fn update_average(&mut self) {
        let total: i32 = self.list.iter().sum();
        self.average = total as f64 / self.list.len() as f64;
    }

}