use crate::hcomp::compile::lexer::Token;

#[derive(Debug)]
pub struct Item {
    pub itype: String,
    pub token: *const Token,
    pub group: Vec<Item>,
}

pub fn group_braces(tokens: Vec<Token>, ingroup: bool) -> Vec<Item> {

    let mut new_tokens: Vec<Item> = Vec::new();
    let mut i: usize = 0;

    while i < tokens.len() {

        if !ingroup && tokens[i].name == "}" {
            println!("Unexpected closing brace found at row {} col {}", tokens[i].row, tokens[i].col);
            std::process::exit(1);
        }

        if tokens[i].name == "{" {

            let mut bracecnt = 1;
            let mut group: Vec<Token> = Vec::new();
            let gtoken = &tokens[i];

            i+=1;
            for o in i..(tokens.len()) {
                if tokens[o].name == "{" {
                    bracecnt+=1;
                }
                if tokens[o].name == "}" {
                    bracecnt-=1;
                }
                i+=1;

                if bracecnt == 0 {
                    break;
                }
                group.push(Token{
                    name: (*tokens[o].name).to_string(),
                    ktype: (*tokens[o].ktype).to_string(),
                    row: tokens[o].row,
                    col: tokens[o].col,
                });
            }

            new_tokens.push(Item{
                itype: "brace".to_string(),
                token: gtoken,
                group: group_braces(group, true),
            });
            i-=1;
        }

        new_tokens.push(Item{
            itype: tokens[i].name.to_string(),
            token: &tokens[i],
            group: Vec::new(),
        });
        i+=1;
    }

    return new_tokens;
}