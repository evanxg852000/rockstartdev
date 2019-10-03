pub const WIDTH: usize = 64;
pub const HEIGHT: usize = 32;


pub const SPRITES: [u8; 80] = [0xF0, 0x90, 0x90, 0x90, 0xF0 /* 0 */, 0x20, 0x60, 0x20, 0x20,
                               0x70 /* 1 */, 0xF0, 0x10, 0xF0, 0x80, 0xF0 /* 2 */, 0xF0,
                               0x10, 0xF0, 0x10, 0xF0 /* 3 */, 0x90, 0x90, 0xF0, 0x10,
                               0x10 /* 4 */, 0xF0, 0x80, 0xF0, 0x10, 0xF0 /* 5 */, 0xF0,
                               0x80, 0xF0, 0x90, 0xF0 /* 6 */, 0xF0, 0x10, 0x20, 0x40,
                               0x40 /* 7 */, 0xF0, 0x90, 0xF0, 0x90, 0xF0 /* 8 */, 0xF0,
                               0x90, 0xF0, 0x10, 0xF0 /* 9 */, 0xF0, 0x90, 0xF0, 0x90,
                               0x90 /* a */, 0xE0, 0x90, 0xE0, 0x90, 0xE0 /* b */, 0xF0,
                               0x80, 0x80, 0x80, 0xF0 /* c */, 0xE0, 0x90, 0x90, 0x90,
                               0xE0 /* d */, 0xF0, 0x80, 0xF0, 0x80, 0xF0 /* e */, 0xF0,
                               0x80, 0xF0, 0x80, 0x80];// f


pub type Buffer = [[bool; WIDTH]; HEIGHT];

pub struct Display {
    buffer: Buffer,
}

impl Display {
    pub fn new() -> Display {
        Display{buffer: [[false; WIDTH]; HEIGHT]}
    }

    pub fn draw(&self, sx: u8, sy: u8, mem: &[u8]) -> bool{
        let mut pixel_turned_off = false;

        for (byte_number, block) in mem.iter().enumerate(){
           let y = (sy as usize + bit_number) % HEIGHT;
            for but_number in 0..8 {
                let x = (sx as usize + bit_number) % WIDTH;
                let current_pixel = self.buffer[x][y] as u8;

                let current_bit = (block >> (7 - bit_number)) & 1;
                let new_pixel = current_bit ^ current_pixel;

                self.buffer[x][y] = new_pixel != 0;

                if current_pixel == 1 && new_pixel == 0 {
                    pixel_turned_off = true;
                }
            }
        }
        pixel_turned_off
    }

    pub fn get_buffer(&self) -> Buffer {
        self.buffer
    }

    pub fn clear(&self) {
        self.buffer = [[false; WIDTH]; HEIGHT];
    }

}