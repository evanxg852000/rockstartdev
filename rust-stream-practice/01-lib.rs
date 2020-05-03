// https://www.youtube.com/watch?v=2mwwYbBRJSo
use std::sync::mpsc::{channel, Sender};
use std::sync::{Arc, Mutex};

pub struct ThreadPool{
  _handles: Vec<std::thread::JoinHandle<()>>,
  _sender: Sender<Box<dyn Fn() + Send>>
}


impl ThreadPool {
  pub fn new(num_threads: u8) -> Self {
    let (_sender, receiver) = channel::<Box<dyn Fn() + Send>>(); 
    let receiver = Arc::new(Mutex::new(receiver));
    let _handles = (0..num_threads).map(|_| {
      let clone = receiver.clone();
      std::thread::spawn(move | | {
        loop {
          let work = match clone.lock().unwrap().recv() {
            Ok(work) => work,
            Err(_) => break,
          };
          println!("start");
          work();
          println!("finish");
        }
      })
    }).collect();

    Self{
      _handles,
      _sender,
    }
  }

  pub fn execute<T: Fn() + Send + 'static>(&self, work: T){
    self._sender.send(Box::new(work)).unwrap();
  }
  
}


#[cfg(test)]
mod tests {
  use super::*;

  #[test]
  fn it_works() {
    let pool = ThreadPool::new(10);
    pool.execute(|| println!("hello from thread"));
    pool.execute(|| println!("hello from thread"));
  }

}
