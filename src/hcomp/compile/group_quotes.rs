use crate::hcomp::compile::lexer::Token;

pub fn group_quotes(tokens: Vec<Token>) -> Vec<Token> {

    let mut new_tokens: Vec<Token> = Vec::new();
    let mut i: usize = 0;

    while i < tokens.len() {

        if tokens[i].name == "\'".to_string() {

            let mut string = "".to_string();
            let qrow = tokens[i].row;
            let qcol = tokens[i].col;

            i+=1;

            for _ in i..tokens.len() {
                if i + 1 >= tokens.len() {
                    println!("No quote found to match quote found at row {} col {}", qrow, qcol);
                    std::process::exit(1);
                }

                if tokens[i].name == "\'" {
                    break;
                }
                string+=&tokens[i].name;
            }

            let qtoken = Token{
                name: string,
                ktype: "string".to_string(),
                col: qcol,
                row: qrow,
            };
            new_tokens.push(qtoken);
        }

        new_tokens.push(Token{
            name: tokens[i].name.to_string(),
            ktype: tokens[i].ktype.to_string(),
            row: tokens[i].row,
            col: tokens[i].col,
        });
        i+=1;
    }

    return new_tokens;
}