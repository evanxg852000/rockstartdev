
use std::time::Duration;

use ggez::event;
use ggez::{Context, GameResult};
use ggez::graphics::{self, DrawMode, DrawParam, Color};
use ggez::timer;
use ggez::event::{ KeyCode, KeyMods};

use ggez::nalgebra as na;

use crate::config;
use crate::helper;


const TILE_SIZE: i32 = 20;
const NROWS: i32 = config::HEIGHT as i32 / TILE_SIZE;
const NCOLS: i32 = config::WIDTH as i32 / TILE_SIZE;


pub struct Game {
    grid: Vec<graphics::Mesh>,
    snake: Snake,
}

impl Game {
    pub fn new() -> GameResult<Game> {
        let game = Game { 
            grid: vec![],
            snake: Snake::new(),
        };
        Ok(game)
    }

    pub fn init(&mut self, ctx: &mut Context) -> GameResult<()> {
        let c = Color::new(1.0, 1.0, 1.0, 0.02);
        //rows
        for y in 1..NROWS {
            let line =  graphics::Mesh::new_line(ctx, 
                &[ 
                    na::Point2::new( 0.0, (y*TILE_SIZE) as f32),
                    na::Point2::new( config::WIDTH/2.0, (y*TILE_SIZE)  as f32),
                    na::Point2::new( config::WIDTH, (y*TILE_SIZE) as f32),
                ], 
                1.0,
                c
            )?;
            self.grid.push(line);
        }

        //columns
        for x in 1..NCOLS {
           let line =  graphics::Mesh::new_line(ctx, 
                &[ 
                    na::Point2::new( (x*TILE_SIZE) as f32, 0.0),
                    na::Point2::new( (x*TILE_SIZE)  as f32, config::HEIGHT/2.0 ),
                    na::Point2::new( (x*TILE_SIZE) as f32, config::HEIGHT ),
                ], 
                1.0, 
                c
            )?;
            self.grid.push(line); 
        }

        self.snake.init(NCOLS/2, NROWS/2);
        Ok(())
    }    

}

impl event::EventHandler for Game {

    fn update(&mut self, ctx: &mut Context) -> GameResult<()> {
        self.snake.update(ctx)?;
        Ok(())
    }

    fn draw(&mut self, ctx: &mut Context) -> GameResult<()> {
        graphics::clear(ctx, graphics::BLACK);

        //draw grid
        for ln in &self.grid {
            graphics::draw(ctx, ln, DrawParam::default())?;
        }

        //draw snake
        self.snake.draw(ctx)?;

        graphics::present(ctx)?;
        Ok(())
    }

    fn key_up_event(&mut self, _ctx: &mut Context, keycode: KeyCode, keymod: KeyMods) {
        match keycode {
            KeyCode::Up => {
                self.snake.turn(1);
            },
            KeyCode::Right => {
                self.snake.turn(2);
            },
            KeyCode::Down => {
                self.snake.turn(3);
            },
            KeyCode::Left => {
                self.snake.turn(4);
            },
            _ => {}
        }
    }

}



pub struct Snake {
    body: Vec<(i32, i32)>, // (x, y)
    speed: u32,
    elapsed: Duration,
    direction: i32, //(1, 2, 3, 4) -> (up, right, down, left) 
    snack: (i32, i32),
}

impl Snake {
    pub fn new() -> Self {
        Snake { 
            body: vec![(0, 0)],
            speed: 3,
            elapsed: Duration::new(0, 0),
            direction: 1, 
            snack: (0, 0),
        }
    }

    fn init(&mut self, x:i32, y:i32) {
        self.body[0] = (x, y);
        self.snack = (x, y-5);
    }

    fn turn(&mut self, dir: i32) {
        self.direction = dir;
    }

    pub fn update(&mut self, ctx: &mut Context) -> GameResult<()> {
        self.elapsed += timer::delta(ctx);
        let delay = 1000 / self.speed as u128;
        if self.elapsed.as_millis() < delay  {
            return Ok(());
        }

        //move body from tail
        let len = self.body.len();
        for i in (1..len).rev(){
            self.body[i].0 = self.body[i-1].0;
            self.body[i].1 = self.body[i-1].1; 
        }

        //change direction
        if self.direction == 1 { self.body[0].1 -= 1; } //up
        if self.direction == 2 { self.body[0].0 += 1; } //right
        if self.direction == 3 { self.body[0].1 += 1; } //down
        if self.direction == 4 { self.body[0].0 -= 1; } //left 

        //check collison with snack
        if (self.body[0].0, self.body[0].1) == self.snack {
            let tail = self.body[self.body.len()-1];
            self.body.push((-1, -1));

            //randomly change snack position
            self.snack = (helper::random(1, NCOLS), helper::random(1, NROWS));
        } 

        //wrap around location
        self.body[0].0 = if self.body[0].0 < 0 { NCOLS } else { self.body[0].0 };
        self.body[0].0 = if self.body[0].0 > NCOLS { 0 } else { self.body[0].0 };
        self.body[0].1 = if self.body[0].1 < 0 { NROWS } else { self.body[0].1 };
        self.body[0].1 = if self.body[0].1 > NROWS { 0 } else { self.body[0].1 };

        //check for self colision
        let len = self.body.len();
        for i in 1..len {
            if (self.body[0].0, self.body[0].1) == (self.body[i].0, self.body[i].1){
                self.body.drain(i..);
                break;
            }
        }

        self.elapsed = Duration::new(0,0);
        Ok(())
    }

    pub fn draw(&mut self, ctx: &mut Context) -> GameResult<()> {
        for (x, y) in &self.body {
            let dot = graphics::Mesh::new_rectangle(ctx, 
                DrawMode::fill(), 
                graphics::Rect::new((x*TILE_SIZE) as f32, 
                (y*TILE_SIZE) as f32, TILE_SIZE as f32, TILE_SIZE as f32),  
                graphics::WHITE
            )?;
            graphics::draw(ctx, &dot, DrawParam::default())?;
        }

        //draw eyes
        let (x, y) = &self.body[0];
        let eye = graphics::Mesh::new_rectangle(ctx, 
            DrawMode::fill(),
            graphics::Rect::new( (x*TILE_SIZE) as f32 + 5.0, (y*TILE_SIZE) as f32 + 5.0, 10.0, 10.0 ),
            Color::new(0.7, 0.0, 0.0, 1.0)
        )?;
        graphics::draw(ctx, &eye, DrawParam::default())?;

        //draw snack
        let snck = graphics::Mesh::new_rectangle(ctx, 
            DrawMode::fill(),
            graphics::Rect::new( (self.snack.0*TILE_SIZE) as f32, (self.snack.1*TILE_SIZE) as f32, TILE_SIZE as f32, TILE_SIZE as f32 ),
            Color::new(0.0, 0.8, 0.0, 1.0)
        )?;
        graphics::draw(ctx, &snck, DrawParam::default())?; 
        
        Ok(())
    }
}