#[derive(Debug)]
pub struct Token {
    pub name:  String,
    pub ktype: String,
    pub row:   u64,
    pub col:   u64,
}

static BREAKERS: [char; 5] = ['.', '{', ',', '>', '\''];

pub fn tokenize(file: String) -> Vec<Token> {

    let mut row: u64 = 0;
    let mut col: u64 = 0;
    let rows = file.split("\n").collect::<Vec<&str>>();

    let mut tokens: Vec<Token> = Vec::new();

    while row < (rows.len() as u64) {
        let currow = rows[row as usize];
        let mut curtoken: String = "".to_string();

        while col < (currow.len() as u64) {
            let curcol = currow.as_bytes()[col as usize] as char;
            let mut was_broken: bool = false;

            for it in BREAKERS.iter() {
                if *it == curcol { //if it is an operation, break the current token

                    if curtoken.len() != 0 {
                        tokens.push(Token{
                            name: curtoken.trim().to_string(), //remove the whitespace from the token
                            /*
                            body: style="color:blue;" {}
                            //body is a tag, style is a property
                            */
                            ktype: if *it == '.' || *it == '>' || *it == '{' { "tag".to_string() } else { "class".to_string() },
                            row: row + 1,
                            col: col + 1,
                        });
                    }

                    tokens.push(Token{
                        name: it.to_string(),
                        ktype: "breaker".to_string(),
                        row: row + 1,
                        col: col + 2,
                    });

                    was_broken = true;
                    curtoken = "".to_string();
                }
            }

            if !was_broken { //if it was broken, do not add to the token
                curtoken+=&curcol.to_string();
            }

            col+=1;
        }

        col = 1; //reset `col`
        row+=1;
    }

    let mut filtered: Vec<Token> = Vec::new();

    for i in tokens {

        if i.name == "" {
            continue;
        }

        filtered.push(i);
    }

    return filtered;
}
