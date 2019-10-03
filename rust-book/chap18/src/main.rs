fn main() {
    // let fav_color: Option<&str> = None;
    // let is_tuesday = false;
    // let age: Result<u8, _> = "34".parse(); 
    // if let Some(color) = fav_color {
    //     println!("Using your favorite color {}, as the background color.", color);
    // } else if is_tuesday {
    //     println!("Tuesday is a green day.");
    // } else if let Ok(age) = age {
    //     if age > 30 {
    //         println!("Using purlple as the background color.");
    //     } else {
    //         println!("Using orange as the background color.");
    //     }
    // } 

    // let mut stack = vec![2,3,5,4,6];
    // while let Some(top) = stack.pop() {
    //     println!("{}", top);
    // }

    // let letters: Vec<u8> = (23..43).collect();
    // for (i, v) in letters.iter().enumerate() {
    //     println!("{} is at index {}", v, i);
    // }

    // let (x, y, z) = (23, 5, 33);
    // println!("(x, y, z) => ({}, {}, {})", x, y, z);

    // let x  = 5;
    // match x {
    //     1 => println!("First"),
    //     2 => println!("Second"),
    //     3 => println!("Third"),
    //     _ => println!("Other"),
    // }

    // let x = Some(5);
    // let y = 10;
    // match x {
    //     Some(50) => println!("Got 50"),
    //     Some(y) => println!("Matched, y = {:?}", y),
    //     _ => println!("Default case, x = {:?}", x),
    // };
    // println!("at the end x ={:?} , y = {:?}", x, y);

    // let x  = 1;
    // match x {
    //     1 | 2 => println!("one or two"),
    //     3 => println!("three"),
    //     _ => println!("anything"),
    // }

    // let x  = 5;
    // match x {
    //     1...5 => println!("one through five"),
    //     _ => println!("anything"),
    // }

    #[derive(Debug)]
    struct Point {
        x: i32,
        y: i32,
    }
    let p = Point{x:0, y:7};
    let Point{x: a, y: b} = p;
    assert_eq!(a, 0);
    assert_eq!(b, 7);
    match p {
        Point{x, y:0} => println!("On the x axis at {}", x),
        Point{x:0, y} => println!("On the y axis at {}", y),
        Point{x, y} => println!("On neither axis at ({}, {})", x, y),
    }

    let points = vec![
        Point{x:0, y:0},
        Point{x:1, y:5},
        Point{x:10, y: -3},
    ];
    let sum_of_squares: i32 = points
        .iter()
        .map(|&Point{x, y}| x*x + y * y)
        .sum(); 

    let nums = (2,4,8,16,32);
    match nums {
        (first, _, third, _, fifth) => {
            println!("Some numbers  {}, {}, {}", first, third, fifth);
        },
    };
    match nums {
        (first, .., last) => println!("Some numbers {},  {}", first, last)
    }

    let name = Some(String::from("Evance"));
    match name {
        Some(ref n) => println!("Found a string: {}", n),
        None => (),
    }
    println!("name is {:?}", name);

    let mut name = Some(String::from("Evance"));
    match name {
        Some(ref mut n) => *n = String::from("Alex"),
        None => (),
    }
    println!("name is {:?}", name);

    let num = Some(4);
    match num {
        Some(x) if x < 5 => println!("less than five: {}", x),
        Some(x) => println!("x = {}", x),
        None => (),
    };
    
}
