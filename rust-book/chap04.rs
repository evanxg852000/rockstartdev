use std::iter::Iterator;

fn calc_len(s: &String) -> usize {
    let len = s.len();
    len
}

fn change_str(s: &mut String) {
    s.push_str(", world!");
}

fn first_word(s: &String) -> &str {
    let bytes = s.as_bytes();
    for (i, &b) in bytes.iter().enumerate() {
        if b == b' ' {
            return &s[0..i];
        }
    }
    &s[..]
}
