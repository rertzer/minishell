
clear
make
echo MINI
./minishell 2> tester/errormini.txt > tester/resultmini.txt
echo BASH
bash tester/mini_test_list 2> tester/errorbash.txt > tester/resultbash.txt
echo DIFF
