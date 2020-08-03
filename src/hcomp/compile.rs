mod lexer;
mod group_quotes;
mod group_braces;

pub fn start(directory: &String) {
    let path = std::path::Path::new(directory);
    let files = std::fs::read_dir(path.join("public")).unwrap();

    //store in a variable to avoid a warning
    let _ = std::env::set_current_dir(&path.join("public")); //change the working directory

    let mut tokenized_files: Vec<Vec<group_braces::Item>> = Vec::new();

    for file in files {

        let fpath = (&file).to_owned().as_ref().unwrap().path();
        let extension = fpath.extension();
        let extstr: String = extension.unwrap().to_str().unwrap().into();

        if extstr == "hcp" { //if it is an hcomp file, push it to the list of hcomp files
            let hcompfilename: String = file.unwrap().path().to_str().unwrap().into(); //get the filename of the hcomp file
            tokenized_files.push(
                group_braces::group_braces(
                    group_quotes::group_quotes(
                        lexer::tokenize(std::fs::read_to_string(hcompfilename).expect("")),
                    ),
                    false,
                ),
            );
        }
    }

    println!("{:#?}", tokenized_files);
}
