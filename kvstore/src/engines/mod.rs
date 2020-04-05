mod kvs;
mod sled;

pub use self::KvsStore;
pub use self::sled::SledKvsEngine;
use crate::Result;


/// Trait for key value storage engine.
pub trait KvsEngine: Clone + Send + 'static {
    /// Sets the value of a string key to a string
    ///
    /// if the key alreadys exists, the previous value will be overwritten.
    fn set(&self, key: String, value: String) -> Result<()>;

    /// gets the string value of a given string key.
    /// 
    /// Rwturns `None` if the given key does not exist.
    fn get(&self, key: String) -> Result<Option<String>>;

    /// Removes a give key.
    /// 
    /// # Errors
    /// 
    /// It resturns `KvsError::KeyNotFound` if the given key is not found.
    fn remove(&self, key:String) -> Result<()>;

}
