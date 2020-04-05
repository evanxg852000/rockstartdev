//! This module provides various thread pools. All thread pools should implement
//! the `ThreadPool` trait.


mod naive;
mod rayon;
mod shared_queue;

use crate::Result;

pub use self::naive::NaiveThreadPool;
pub use self::rayon::RayonThreadPool;
pub use self::shared_queue::SharedQueueThreadPool;


/// The trait that all thread pools should implement.
pub trait ThreadPool {
    /// Created a new thread pool, immediatly spwaning the specified
    /// number of threads.
    /// 
    /// Returns an error if any thread fails to spawn. All previously-spawned 
    /// threads are terminated
    fn new(threads: u32) -> Result<Self>
    where
        Self: Sized;

    /// Spwnas a function into the thread pool
    /// 
    /// Spawning always succeeds, but if the function panics the threadpool
    /// continues to operate with the same number of threads -; the thread 
    /// count is not reduces nor is the thread pool destroyed, corrupted or invalidated.
    fn spawn<F>(&self, job: F)
    where
        F: FnOnce() + Send + 'static;
}