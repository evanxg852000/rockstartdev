extern crate image;
extern crate rand;

use rand::Rng;
use std::fs::File;
use std::path::Path;


const WIDTH: u32 = 800;
const HEIGHT: u32 = 600;

#[derive(Debug)]
pub struct Point {
    x: u32,
    y: u32,
}


fn main() {
    let mut img = image::ImageBuffer::from_fn(WIDTH, HEIGHT, |x, y| {
        if x == 0 && y == 0 {
            image::Luma([0u8])
        } else {
            image::Luma([255u8])
        }
    });

    let edges: [Point; 3] = [
        Point{x: WIDTH/2, y: 0},
        Point{x: 0, y: HEIGHT},
        Point{x: WIDTH, y: HEIGHT},
    ];
    let mut counter = 1_000_000;

    let mut num: usize;
    let mut p = Point{x: 350, y: 350};
    let pixel = img[(0, 0)];

    while counter > 0 {
        counter -= 1;
        num = rand::thread_rng().gen_range(0,3);

        p.x = (p.x + edges[num].x) / 2;
        p.y = (p.y + edges[num].y) / 2;

        img.put_pixel(p.x, p.y, pixel);
    }

    img.save(&Path::new("output.png")).expect("Saving image failed");
    //let _ = image::ImageLuma8(img).save(&file);

}
