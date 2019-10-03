use std::string::ToString;
use std::str::FromStr;

#[derive(Debug, Clone, Copy, PartialEq)]
enum ByteCode {
    IADD = 1, // int add
    ISUB,     // int substraction
    IMUL,     // int multiplication
    ILT,      // int less than
    IEQ,      // int equal
    BR,       // branch
    BRT,      // branch if true
    BRF,      // branch if true
    ICONST,   // push constant integer
    LOAD,     // load from local context
    GLOAD,    // load from global memory
    STORE,    // store in local context
    GSTORE,   // store in global memory
    PRINT,    // print stack top
    POP,      // throw away top of stack
    CALL,     // function call
    RET,      // return with/without value
    HALT,     // halt execution
}

impl ByteCode {
    fn from_i32(value: i32) -> ByteCode {
        match value {
            1 => ByteCode::IADD, 
            2 => ByteCode::ISUB,
            3 => ByteCode::IMUL,
            4 => ByteCode::ILT,
            5 => ByteCode::IEQ,
            6 => ByteCode::BR,
            7 => ByteCode::BRT,
            8 => ByteCode::BRF,
            9 => ByteCode::ICONST,
            10 => ByteCode::LOAD,
            11 => ByteCode::GLOAD,
            12 => ByteCode::STORE,
            13 => ByteCode::GSTORE,
            14 => ByteCode::PRINT,
            15 => ByteCode::POP,
            16 => ByteCode::CALL,
            17 => ByteCode::RET,
            18 => ByteCode::HALT,
            _ => panic!("Unknow bytecode: {}!", value),
        }
    }

    fn to_i32(&self) -> i32 {
        *self as i32
    }
}

// #[derive(Debug)]
// struct Instruction {
//     opcode: ByteCode,
//     name: String,
//     arg_count: u32,
// }

// impl Instruction {
//     fn new(opcode: ByteCode, name: &str, arg_count: u32) -> Self {
//         Instruction{ opcode,  name: String::from(name), arg_count }
//     }

//     pub fn translate(program: Vec<u32>) -> Vec<Instruction> {
//         program.iter().map(|code| {
//             match code {
//                 1 => Instruction::new(ByteCode::IADD, "iadd", 0), 
//                 2 => Instruction::new(ByteCode::ISUB, "isub", 0),
//                 3 => Instruction::new(ByteCode::IMUL, "imul", 0),
//                 4 => Instruction::new(ByteCode::ILT, "ilt", 0),
//                 5 => Instruction::new(ByteCode::IEQ, "ieq", 0),
//                 6 => Instruction::new(ByteCode::BR, "br", 1),
//                 7 => Instruction::new(ByteCode::BRT, "brt", 1),
//                 8 => Instruction::new(ByteCode::BRF, "brf", 1),
//                 9 => Instruction::new(ByteCode::ICONST, "iconst", 1),
//                 10 => Instruction::new(ByteCode::LOAD, "load", 1),
//                 11 => Instruction::new(ByteCode::GLOAD, "gload", 1),
//                 12 => Instruction::new(ByteCode::STORE, "store", 1),
//                 13 => Instruction::new(ByteCode::GSTORE, "gstore", 1),
//                 14 => Instruction::new(ByteCode::PRINT, "print", 0),
//                 15 => Instruction::new(ByteCode::POP, "pop", 0),
//                 16 => Instruction::new(ByteCode::CALL, "call", 2),
//                 17 => Instruction::new(ByteCode::RET, "ret", 0),
//                 18 => Instruction::new(ByteCode::HALT, "halt", 0),
//                 _ => panic!("Unknow bytecode!"),
//             }
//         }).collect()
//     }
// }

// impl ToString for Instruction {
//     fn to_string(&self) -> String {
//         format!("<{:?} {} {}>", self.opcode, self.name, self.arg_count)
//     }
// }

struct Assembler;

impl Assembler {

    pub fn assemble(src: Vec<String>) -> Vec<i32> {
        let mut program = Vec::new();
        for line in src {
            let tokens = line.split_whitespace().collect::<Vec<&str>>();
            if line.len() == 0 || tokens.len() == 0 {
                continue;
            }
            let keyword = tokens[0];
            let mut operand1 = 0;
            let mut operand2 = 0;
            match tokens.len() {
                2 => operand1 = tokens[1].trim().parse()
                    .expect("Expect a number!"),
                3 => {
                    operand1 = tokens[1].trim().parse()
                        .expect("Expect a number!");
                    operand2 = tokens[2].trim().parse()
                        .expect("Expect a number!");
                }
                _ => (),
            };
            match keyword {
                "IADD" => program.push(ByteCode::IADD.to_i32()),
                "ISUB" => program.push(ByteCode::ISUB.to_i32()),
                "IMUL" => program.push(ByteCode::IMUL.to_i32()),
                "ILT"  => program.push(ByteCode::ILT.to_i32()),
                "IEQ"  => program.push(ByteCode::IEQ.to_i32()),
                "BR"   => {
                    program.push(ByteCode::BR.to_i32());
                    program.push(operand1);
                },
                "BRT" => {
                    program.push(ByteCode::BRT.to_i32());
                    program.push(operand1);
                },
                "BRF" => {
                    program.push(ByteCode::BRF.to_i32());
                    program.push(operand1);
                },
                "ICONST" => {
                    program.push(ByteCode::ICONST.to_i32());
                    program.push(operand1);
                },
                "LOAD" => {
                    program.push(ByteCode::LOAD.to_i32());
                    program.push(operand1);
                },
                "GLOAD" => {
                    program.push(ByteCode::GLOAD.to_i32());
                    program.push(operand1);
                },
                "STORE" => {
                    program.push(ByteCode::STORE.to_i32());
                    program.push(operand1);
                },
                "GSTORE" => {
                    program.push(ByteCode::GSTORE.to_i32());
                    program.push(operand1);
                },
                "PRINT" => program.push(ByteCode::PRINT.to_i32()),
                "POP" => program.push(ByteCode::POP.to_i32()),
                "CALL" => {
                    program.push(ByteCode::CALL.to_i32());
                    program.push(operand1);
                    program.push(operand2);
                },
                "RET" => program.push(ByteCode::RET.to_i32()),
                "HALT" => program.push(ByteCode::HALT.to_i32()),
                _ => panic!("Unknow assembly instruction {}!", keyword),
            }
        }
        program
    }

    pub fn disassemble(program: Vec<i32>) -> Vec<String> {
        let mut src = Vec::new();
        let mut i = 0;
        loop {
            if i >= program.len() {
                break;
            }
            let bytecode = ByteCode::from_i32(program[i]);
            match bytecode {
                ByteCode::IADD => src.push("IADD".to_string()), 
                ByteCode::ISUB => src.push("ISUB".to_string()),
                ByteCode::IMUL => src.push("IMUL".to_string()),
                ByteCode::ILT  => src.push("ILT".to_string()),
                ByteCode::IEQ  => src.push("IEQ".to_string()),
                ByteCode::BR => { 
                    src.push("BR".to_string());
                    i += 1;
                    src.push(program[i].to_string());
                },
                ByteCode::BRT => { 
                    src.push("BRT".to_string()); 
                    i += 1;
                    src.push(program[i].to_string());
                },
                ByteCode::BRF => { 
                    src.push("BRF".to_string());
                    i += 1;
                    src.push(program[i].to_string());
                },
                ByteCode::ICONST => { 
                    src.push("ICONST".to_string()); 
                    i += 1;
                    src.push(program[i].to_string());
                },
                ByteCode::LOAD => { 
                    src.push("LOAD".to_string()); 
                    i += 1;
                    src.push(program[i].to_string());
                },
                ByteCode::GLOAD => { 
                    src.push("GLOAD".to_string());
                    i += 1;
                    src.push(program[i].to_string());
                },
                ByteCode::STORE => { 
                    src.push("STORE".to_string());
                    i += 1;
                    src.push(program[i].to_string());
                },
                ByteCode::GSTORE => { 
                    src.push("GSTORE".to_string());
                    i += 1;
                    src.push(program[i].to_string());
                },
                ByteCode::PRINT => src.push("RPINT".to_string()),
                ByteCode::POP => src.push("POP".to_string()),
                ByteCode::CALL => {
                    src.push("GSTORE".to_string());
                    i += 1;
                    src.push(program[i].to_string());
                    i += 1;
                    src.push(program[i].to_string());
                },
                ByteCode::RET => src.push("RET".to_string()),
                ByteCode::HALT => src.push("HALT".to_string()),
            }
            i += 1;
        }
        src.iter().map(|s| s.to_string()).collect()
    }

}


const DEFAULT_SIZE: usize = 1024;

struct Svm {
    stack: [i32; DEFAULT_SIZE],
    code: [i32; DEFAULT_SIZE],
    globals: [i32; DEFAULT_SIZE],
    code_size: usize,
    ip: usize,
    sp: i32,
    fp: i32,
}

impl Svm {
    pub fn new(program: Vec<i32>, main: usize) -> Svm {
        let mut code = [0; DEFAULT_SIZE];
        for (i, v) in program.iter().enumerate() {
            code[i] = *v
        }
        Svm{
            stack: [0; DEFAULT_SIZE],
            globals: [0; DEFAULT_SIZE],
            code,
            code_size: program.len(),
            ip: main,
            sp: -1,
            fp: 0,
        }
    }

    pub fn run(&mut self) {
        let mut opcode = ByteCode::from_i32(self.code[self.ip]);
        let mut a;
        let mut b;
        let mut addr;
        let mut offset;
        while opcode != ByteCode::HALT && self.ip < self.code_size {
            self.ip += 1;
            match  opcode {
                ByteCode::IADD => {
                    b = self.stack[self.sp as usize];
                    self.sp -= 1;
                    a = self.stack[self.sp as usize];
                    self.sp -= 1;

                    self.sp += 1;
                    self.stack[self.sp as usize] = a + b;
                }, 
                ByteCode::ISUB => {
                    b = self.stack[self.sp as usize];
                    self.sp -= 1;
                    a = self.stack[self.sp as usize];
                    self.sp -= 1;
                    
                    self.sp += 1;
                    self.stack[self.sp as usize] = a - b;
                },
                ByteCode::IMUL => {
                    b = self.stack[self.sp as usize];
                    self.sp -= 1;
                    a = self.stack[self.sp as usize];
                    self.sp -= 1;
                    
                    self.sp += 1;
                    self.stack[self.sp as usize] = a * b;
                },
                ByteCode::ILT  => {
                    b = self.stack[self.sp as usize];
                    self.sp -= 1;
                    a = self.stack[self.sp as usize];
                    self.sp -= 1;

                    self.sp += 1;
                    self.stack[self.sp as usize] = if a < b { 1 } else { 0 };
                },
                ByteCode::IEQ  => {
                    b = self.stack[self.sp as usize];
                    self.sp -= 1;
                    a = self.stack[self.sp as usize];
                    self.sp -= 1;

                    self.sp += 1;
                    self.stack[self.sp as usize] = if a == b { 1 } else { 0 }; 
                },
                ByteCode::BR => {
                    self.ip = self.code[self.ip] as usize;
                },
                ByteCode::BRT => {
                    addr = self.code[self.ip];
                    self.ip += 1;
                    
                    if self.stack[self.sp as usize] == 1 {
                        self.ip = addr as usize;
                    }
                },
                ByteCode::BRF => { 
                    addr = self.code[self.ip];
                    self.ip += 1;
                    
                    if self.stack[self.sp as usize] == 0 {
                        self.ip = addr as usize;
                    } 
                },
                ByteCode::ICONST => {
                    let op = self.code[self.ip];
                    self.ip += 1;

                    self.sp += 1;
                    self.stack[self.sp as usize] = op;
                },
                ByteCode::LOAD => {
                    offset = self.code[self.ip as usize];
                    self.ip += 1;

                    self.sp += 1;
                    self.stack[self.sp as usize] = self.stack[(self.fp + offset) as usize];
                },
                ByteCode::GLOAD => {
                    addr = self.code[self.ip];
                    self.ip += 1;

                    self.sp += 1;
                    self.stack[self.sp as usize] = self.globals[addr as usize];
                },
                ByteCode::STORE => {
                    offset = self.code[self.ip as usize];
                    self.ip += 1;

					self.stack[(self.fp + offset) as usize] = self.stack[self.sp as usize];
                    self.sp -= 1;
                },
                ByteCode::GSTORE => {
                    addr = self.code[self.ip as usize];
                    self.ip += 1;
                    
                    self.globals[addr as usize] = self.stack[self.sp as usize];
                    self.sp -= 1;
                },
                ByteCode::PRINT => {
                    let v = self.stack[self.sp as usize];
                    self.sp -= 1;
                    println!("{}", v);
                },
                ByteCode::POP => {
                    self.sp -= 1;
                },
                ByteCode::CALL => {
                    //get func address
                    addr = self.code[self.ip as usize];
                    self.ip += 1;

                    // get num args
                    let nargs = self.code[self.ip as usize];
                    self.ip += 1;

                    // push num args on stack
                    self.sp += 1;
                    self.stack[self.sp as usize] = nargs;
                    
                    //push current fp on stack
                    self.sp += 1;
                    self.stack[self.sp as usize] = self.fp;

                    // push current ip as func return addresse
                    self.sp += 1;
                    self.stack[self.sp as usize] = self.ip as i32;

                    //fp points at retu addr on stack
                    self.fp = self.sp;

                    // jump to function addr
                    self.ip = addr as usize;
                },
                ByteCode::RET => {
                    // pop return val from stack
                    let retval = self.code[self.ip as usize];
                    self.ip -= 1;

                    //jump over locals to fp which point at ret addr
                    self.sp = self.fp;

                    //pop ret addr and jump to it
                    self.ip = self.stack[self.sp as usize] as usize;
                    self.sp -= 1; 

                    //restore fp
                    self.fp = self.stack[self.sp as usize];
                    self.sp -= 1; 

                    // get num args to throw away
                    let nargs = self.stack[self.sp as usize]; 
                    self.sp -= 1;

                    // pop by nargs: throw away args 
                    self.sp -= nargs;

                    //push ret value on stack
                    self.sp += 1;
                    self.stack[self.sp as usize] = retval; 
                },
                ByteCode::HALT => {
                    break;
                },
            }
            opcode = ByteCode::from_i32(self.code[self.ip]);
        }
    }

}


#[cfg(test)]
mod tests {
    use super::*;
    use super::ByteCode::*;

    #[test]
    fn hello_program() {
        let src = "
        ICONST 1
        ICONST 2
        IADD
        PRINT
        HALT
        ";
        let src: Vec<String> = src.lines()
            .map(|s| String::from_str(s).unwrap())
            .collect();

        let out = vec![
            ICONST.to_i32(), 1,
            ICONST.to_i32(), 2,
            IADD.to_i32(),
            PRINT.to_i32(),
            HALT.to_i32()
        ];

        let prog = Assembler::assemble(src);
        assert_eq!(7, prog.len());
        assert_eq!(prog, out);

        let mut mac = Svm::new(prog, 0);
        mac.run();
    }

    #[test]
    fn looper() {
        let src = "
			ICONST 10
			GSTORE 0
			ICONST 0
			GSTORE 1

			GLOAD 1
			GLOAD 0
			ILT
			BRF 24
	
			GLOAD 1
			ICONST 1
			IADD
			GSTORE 1
			BR 8

			HALT
        ";
        
        let src: Vec<String> = src.lines()
            .map(|s| String::from_str(s).unwrap())
            .collect();

        let prog = Assembler::assemble(src);

        assert_eq!(prog.len(), 25);
        let mut mac = Svm::new(prog, 0);
        mac.run();
    }

    #[test]
    fn factorial() {
        let src = "
			LOAD -3
			ICONST 2
			ILT
			BRF 10
			ICONST 1
			RET

			LOAD -3
			LOAD -3
			ICONST 1
			ISUB
			CALL 0 1
			IMUL
			RET

			ICONST 5
			CALL 0 1
			PRINT	
			HALT
        ";
        let src: Vec<String> = src.lines()
            .map(|s| String::from_str(s).unwrap())
            .collect();

        let prog = Assembler::assemble(src);
        let mut mac = Svm::new(prog, 22);
        mac.run();
    }

}