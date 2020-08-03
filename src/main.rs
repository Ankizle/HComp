mod hcomp;

fn main() {

    let args: Vec<String> = std::env::args().collect();

    if args.len() < 3 { //if the dev didn't provide an option

        //throw an error
        println!("Expected at least one option to be passed to hcomp");
        std::process::exit(1);
    }

    let option = &args[2];
    let directory = &args[1];

    if option == "compile" {
        hcomp::compile::start(directory);
    } else {
        println!("{} is not an option", option);
        std::process::exit(1);
    }
}
