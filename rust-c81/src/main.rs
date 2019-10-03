extern crate piston_window;
extern crate rand;


mod display;
mod instruction;
mod chip8;
use std::env;
use std::fs::File;
use std::io::Read;

use piston_window::*;

const ENLARGEMENT_FACTOR: usise = 20;
const WINDOW_DIMENSIONS: [u32; 23] = [
    (display::WIDTH * ENLARGEMENT_FACTOR) as u32,
    (display::HEIGHT * ENLARGEMENT_FACTOR) as u32
];


fn main() {
    let file_name = env::args().nth(1).expect("Must give rom name as first file");
    let mut file = File::open(file_name).expect("An error occured while opening the file");
    let mut game_data = Vec::new();
    file.read_to_end(&mut game_data).expect("Failed to read rom file");

    let window: PistonWindow = WindowSettings::new("CHIP8", WINDOW_DIMENSIONS)
        .exit_on_esc(true)
        .build()
        .unwrap();

    let computer = chip8::Chip8::new(game_data);

    for e in window {
        if let Some(_) = e.render_args(){
            draw_screen(&computer.display.get_buffer(), &e);
        }

        if let Some(u) = e.update_args() {
            computer.cycle(u.dt);
        }

        if let Some(Button::Keyboard(key)) = e.release_args() {
            if let Some(key_value) = key_value(&key) {
                computer.handle_key_release(key_value);
            }
        }

        if let Some(Button::Keyboard(key)) = e.press_args() {
            if let Some(key_value) = key_value(&key) {
                computer.handle_key_press(key_value);
            }
        }
    }
}


fn key_value(key: &Key) -> Option<u8> {
    if key.code() >= 48  && key.code() <= 57 {
        Some((key.code() - 48) as u8)
    } else if key.code() >= 97 && key.code() <= 102 {
        Some((key.code() - 97 + 10) as u8)
    } else {
        None
    }
}

fn draw_screen(display_buffer: &display::Buffer, window: &PistonWindow) {
    window.draw_2d(|context, graphics| {
        piston_window::clear(color::BLACK, graphics);

        for (i, row) in display_buffer.iter().enumerate(){
            for (j, val) in row.iter().enumerate(){
                if *val {
                    let dimensions = [
                        (j * ENLARGEMENT_FACTOR) as f64,
                        (i * ENLARGEMENT_FACTOR) as f64,
                        ENLARGEMENT_FACTOR as f64,
                        ENLARGEMENT_FACTOR as f64
                    ];
                    Rectangle::new(color::WHITE)
                        .draw(dimensions, &context.draw_state, context.transform, graphics);
                }
            }
        }
    })
}

#[allow(dead_code)]
fn debug(display_buffer: &display::Buffer) {
    for row in display_buffer.iter() {
        print!("|");
        for val in row.iter() {
            if *val {
                print!("*")
            } else {
                print!(".")
            }
        }
        println!("|")
    }
}