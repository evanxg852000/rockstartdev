#[derive(Debug)]
struct User {
    username: String,
    email: String,
    sign_in_count: u64,
    active: bool,
}

impl User {
    fn new (username: String, email: String) -> User {
        User {
            username,
            email,
            sign_in_count: 0,
            active:true,
        }
    }
}

#[derive(Debug)]
struct Color(u8, u8, u8);

#[derive(Debug)]
struct Point(f64, f64);

#[derive(Debug)]
pub struct Rect {
    width: f64,
    height: f64,
}

impl Rect {
    fn new(w: f64, h: f64) -> Rect {
        Rect{width: w, height: h}
    }

    fn square(w: f64) -> Rect {
        Rect{width: w, height: w}
    }

    fn area(&self) -> f64 {
        self.width * self.height
    }

    fn can_hold(&self, rec: &Rect) -> bool {
       self.width >= rec.width && self.height >= rec.height  
    }
}

fn area(rect: &Rect) -> f64 {
    rect.height * rect.width
}

fn main() {

    let user1 = User::new(String::from("evanxg852000"),
        String::from("evanxg852000@gmail.com"));

    let user2 = User{
        username: String::from("alex"),
        email: String::from("alex@yahoo.fr"),
        ..user1
    };

    let white = Color(255, 255, 255);
    let fenix = Point(65.05, 70.04);

    println!("{:?}", user1);
    println!("{:?}", user2);

    println!("Color: {:?}", white);
    println!("Point: {:?}", fenix);

    let rec = Rect::new(34.8, 56.0);
    println!("Area: {}", rec.area());

    println!("Area: {}", area(&Rect{width: 32.0, height: 20.4}));

    println!("can hold: {}", rec.can_hold(&Rect::square(12.0)));
}
