use rand::{self, Rng};
use rand_distr::{Normal, Distribution};


pub fn random(low: i32, high: i32) -> i32 {
    rand::thread_rng().gen_range(low, high)
}

pub fn next_rand_gaussian(mean: f64, std_dev: f64) -> f64{
    let normal = Normal::new(mean, std_dev).unwrap();
    normal.sample(&mut rand::thread_rng())
}

