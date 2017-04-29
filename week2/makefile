###############################################################
# Program:
#     Week 02, STACK
#     Brother JonesL, CS235
# Author:
#     Wesley Dike
#     Hans Peterson
#     Joslyn Sidamonidze
#     Daniel Nacher
# Summary:
#     This program creates the stack class, and also contains
#     a function which will convert infix notation to postfix
#     notation.
# Time:
#     <how long did it take to complete this program>?
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h week02.o infix.o 
	g++ -o a.out week02.o infix.o 
	tar -cf week02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week02.o       : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
week02.o: stack.h infix.h week02.cpp
	g++ -c week02.cpp

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp

