# MINISHELL
A simple shell, built after bash, a group project by: <strong>[@Rexbrainz](https://github.com/Rexbrainz)</strong> and <strong>[@Thopterek](https://github.com/Thopterek)</strong>


Work was divided into two main parts and you can see it also by style in which code was written:
- Parsing and signals by [@Rexbrainz](https://github.com/Rexbrainz)
- Execution and builtins by [@Thopterek](https://github.com/Thopterek)
- Of course in some points its interconnected

<img width="375" alt="Structure" src="https://github.com/user-attachments/assets/2fd65da9-fa1f-4d82-9a9a-b4258dd8b9ab" />

Things we are handling in this project are:
- $ sign expansions and generally working with things like export expanding to commands
- executing commands in different ways (relative path etc) asynchronus or not depening on input
- pipes '|' and logic operators '&&' '||' with their full functionality
- signals (CONTROL + C, CONTROLD + D)
- minishell inside the minishell
- really weird input

<img width="1027" alt="mini" src="https://github.com/user-attachments/assets/46868e86-7344-4278-a9b0-168076641b23" />


As always everything starts in main, but here you should go first over the headers:
- everywhere in the code you can read through the functions with comments about them to help out
- if you want to look for explanation of what is exactly happening you have to understand the logic
- structure helps with just that organising everything, from how the data is saved to how its being passed to execution


<img width="1183" alt="main and struct" src="https://github.com/user-attachments/assets/f620931e-911a-449d-92b6-edf0c5150631" />


Project was written in accordance with 42 NORM but handles some of the things outside of minishell project:
- unclosed single and double quotes, plus delimiters ('|', '&&', '||') at the end
- input with the '\\' sign asking for more input

To run the project:
- git clone [repo link]
- cd [into cloned folder]
- make
- ./minishell

Disclaimer: it might be problematic to run the code outside of the 42, all depening on which library version for readline you have.
