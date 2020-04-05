#![deny(missing_docs)]

//! A simple key/value store

mod client;
mod common;
mod engines;
mod error;
mod server;
pub mod thread_pool;

pub use client::KvsClient;
pub use engines::{KvsStore, KvsEngine, SledKvsEngine};
pub use error::{KvsError, Result};
pub use server::KvsServer;