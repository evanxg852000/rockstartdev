extern crate chap20;

use chap20::ThreadPool;

use std::io::prelude::*;
use std::fs::File;
use std::net::{TcpListener, TcpStream};

use std::thread;
use std::time::Duration;


fn handle_connection(mut stream: TcpStream){
    let mut buffer= [0; 512];
    stream.read(&mut buffer).unwrap();
    //println!("Request: {}", String::from_utf8_lossy(&buffer[..]));

    //let response = "HTTP/1.1 200 OK\r\n\r\n";
    //stream.write(response.as_bytes()).unwrap();
    //stream.flush().unwrap();

    let get = b"GET / HTTP/1.1\r\n";
    let sleep = b"GET /sleep HTTP/1.1\r\n";
    let (status, filename) = if buffer.starts_with(get){
        ("HTTP/1.1 200 OK\r\n\r\n", "hello.html")
    } else if buffer.starts_with(sleep) {
        thread::sleep(Duration::from_secs(5));
        ("HTTP/1.1 200 OK\r\n\r\n", "hello.html")
    } else {
        ("HTTP/1.1 404 NOT FOUND\r\n\r\n", "404.html")
    };

    let mut file = File::open(filename).unwrap();
    let mut content = String::new();
    file.read_to_string(&mut content).unwrap();
    let response = format!("{}{}", status, content);

    stream.write(response.as_bytes()).unwrap();
    stream.flush().unwrap();
}

fn main() {
    let listener = TcpListener::bind("127.0.0.1:7878").unwrap();
    let pool = ThreadPool::new(4);
    for stream in listener.incoming() {
        let stream = stream.unwrap();
        pool.execute(|| {
            handle_connection(stream);
        });
        // println!("Connection etablished!");
    }


}
