//EVANXG BRAIN FUCK INTERPRETER
// Ref: https://en.wikipedia.org/wiki/Brainfuck
/*
    INTRCUTION SET
>	move to next cell
<	move to previous cell
+	increment the value of the current cell by 1
-	decrement the value of the current cell by 1
.	print the ascii character of the current cell to stdout
,	get a character from stdin and store it in the current cell
[	if the current cell is 0, jump to the matching ]
]	if the current cell is not 0, jump to the matching [
*/

use std::io::Read;

fn getchar() -> u8 {
    return match std::io::stdin().bytes().next() {
        Some(v) => v.ok().unwrap(),
        None => 0u8,
    }
}

#[derive(Copy, Debug, Clone, PartialEq)]    
enum OpCode {
    MoveRight,
    MoveLeft,
    Increment,
    Decrement,
    Print,
    Read,
    JumpIfZero(usize),
    JumpIfNotZero(usize),
}

fn compile(src: &str) ->Vec<OpCode> {
    let mut program: Vec<OpCode> = Vec::new();
    let mut itr = src.chars();
     
    let mut pc: usize = 0;
    let mut loop_checker:Vec<(char, usize)> = Vec::new();
    while let Some(c) = itr.next() {
        match c {
            '>' => program.push(OpCode::MoveRight),
            '<' => program.push(OpCode::MoveLeft),
            '+' => program.push(OpCode::Increment),
            '-' => program.push(OpCode::Decrement),
            '.' => program.push(OpCode::Print),
            ',' => program.push(OpCode::Read),
            '[' => {
                loop_checker.push(('[', pc));
                // just store 0 for now as we don't know the matching ] location 
                program.push(OpCode::JumpIfZero(0)); 
            },
            ']' => {
                //extract previous loop start
                match loop_checker.pop() {
                    Some((chr, matching_loop)) => {
                        assert!(chr == '[', "No matching `]` for ]!");
                        
                        // jump to loop start intruction
                        program.push(OpCode::JumpIfNotZero(matching_loop));

                        // now update the previous loop jump location
                        program[matching_loop] = OpCode::JumpIfZero(pc);
                    },
                    None => assert!(false, "No matching `]` for ]!"),
                }
                
            },
            _ => {},
        }
        pc += 1;
    }
    program
}

fn interpret(program: & mut Vec<OpCode>){
    //30000 is the standard tape size of bf
    let mut tape: [u8; 30000] = [0; 30000];

    let mut pc: usize = 0; // pc: program counter
    let mut sp: usize = 0; // sp: stack pointer (- tape pointer)
    let mut op;
    while pc < program.len() {
        op = program[pc];
        match op {
            OpCode::MoveRight => sp += 1,
            OpCode::MoveLeft => sp -= 1,
            OpCode::Increment => tape[sp] += 1,
            OpCode::Decrement => tape[sp] -= 1,
            OpCode::Print => print!("{}", (tape[sp] as char)),
            OpCode::Read => tape[sp] = getchar(),
            OpCode::JumpIfZero(target) => {
                if tape[sp] == 0 {
                    pc = target;
                    continue;
                }
            },
            OpCode::JumpIfNotZero(target) => {
                if tape[sp] != 0 {
                    pc = target;
                    continue;
                }
            }
        }
        pc += 1;
    }

}


fn main() {
    println!("-----[ Welcome to EvanXG BF! ]-----");
    println!("");
    let input = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
    let mut prog = compile(input);
    interpret(& mut prog);
}
