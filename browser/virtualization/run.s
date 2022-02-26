section .text
    global run_prog

run_prog:
    ;function starts with 
    ;   rdi contains the start of the virtual memory (exec)
    ;   rsi contains the entry point within that memory (e_entry)

    add rdi, rsi
    call rdi

    ret                 ;just in case ;)
