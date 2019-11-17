mod config;
mod core;
mod helper;

use ggez;
use ggez::conf;
use ggez::event;

use crate::core::Game;


pub fn main() -> ggez::GameResult { 
    let cb = ggez::ContextBuilder::new("com.evansofts.snake", "evanxg852000")
        .window_setup(conf::WindowSetup::default().title("Snake"))
        .window_mode(conf::WindowMode::default().dimensions(config::WIDTH, config::HEIGHT));

    let (ctx, event_loop) = &mut cb.build()?;
    let game = &mut Game::new()?;
    game.init(ctx)?;
    event::run(ctx, event_loop, game)
}