# microshell_using_tree
Microshell is a small lightweight command-line interface or shell with a minimal set of features and commands.

## GRAMMAR
```Shell
FG           ::= 
                  | ";"

pipeline     ::=  command
                  |   pipeline "|" command

commandexec  ::=  word
```
<img width="782" alt="grammar" src="https://user-images.githubusercontent.com/80905157/226901110-d194736b-6375-4256-aa1c-5f0d5a10e8dd.png">
