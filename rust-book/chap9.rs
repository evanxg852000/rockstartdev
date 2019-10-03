use std::io;
use std::fs::File;
use std::io::Read;
use std::io::ErrorKind;

panic!("crash and burn");

let v = vec![1,2,4,4];
&v[6]; //should panic

let f = File::open("hello.txt");
if let Ok(file) = f {
    println!("{:?}", file);
} else {
    panic!("There was a blem opening the file {}");
}

let f = File::open("hello.txt").unwrap();
let f = File::open("hello.txt").expect("unable to open the file!");

let f = File::open("hello.txt");
let f = match f {
    Ok(file) => file,
    Err(error) => {
        panic!("There was a blem opening the file {}", error);
    },
};

let f = File::open("hello.txt");
let f = match f {
    Ok(file) => file,
    Err(ref error) if error.kind() == ErrorKind::NotFound => { 
        match File::create("hello.txt") {
            Ok(fc) => fc,
            Err(e) => panic!("Unable to create the file!, {}", e),
        } 
    },
    Err(error) => {
        panic!("There was a blem opening the file {}", error);
    },
};


fn read_username() -> Result<String, io::Error> {
    let f =File::open("users.db");
    let mut f = match f {
        Ok(file) => file,
        Err(e) => return Err(e),
    };
    let mut s = String::new();
    match f.read_to_string(&mut s) {
        Ok(_) => Ok(s),
        Err(e) => Err(e),
    }
}

fn read_username2() -> Result<String, io::Error> {
    let mut f = File::open("users.db")?;
    let mut s = String::new();
    f.read_to_string(&mut s)?;
    Ok(s)
}

fn read_username3() -> Result<String, io::Error> {
    let mut s = String::new();
    File::open("users.db")?.read_to_string(&mut s)?;
    Ok(s)
}