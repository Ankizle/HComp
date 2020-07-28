pub fn start(directory: &String) {
    let path = std::path::Path::new(directory);
    let files = std::fs::read_dir(path.join("public")).unwrap();

    //store in a variable to avoid a warning
    let _ = std::env::set_current_dir(&path); //change the working directory

    let mut hcomp_files: Vec<String> = Vec::new();

    for file in files {

        let fpath = (&file).to_owned().as_ref().unwrap().path();
        let extension = fpath.extension();
        let extstr: String = extension.unwrap().to_str().unwrap().into();

        if extstr == "html" { //if it is an html file, push it to the list of hcomp files
            let htmlfilename: String = file.unwrap().path().to_str().unwrap().into(); //get the filename of the hcomp file
            hcomp_files.push(std::fs::read_to_string(htmlfilename).expect(""));
        }
    }

    println!("{:?}", hcomp_files);
}
