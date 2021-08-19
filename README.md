# Practice projects: pipex
The goal of this project is to write a program, that takes multiple arguments: input file, command1, command2, output file. Next, the program simulates the pipeline: it reads from the input file, transfers the read to the input to command1, then result of command1 is transfered to command2, then result of command2 is written to the output file. The execution of the pipex program should do the same as the shell command "infile < cmd1 | cmd2 > outfile"

#### Command to compile and execute:
`make` <br /> `./pipex infile cmd1 cmd2 outfile`
