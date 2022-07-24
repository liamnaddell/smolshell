basic:
cmd1 $

#$ = tostring
#| = pipe

cmd1 $ cmd2 |

arg1 arg2 arg3 cmd1 $ arg4 arg5 cmd2 |


#ff=from file
text.txt ff $ cmd2 $

# $(cmd2) is done with

#ss=subshell

#cmd2 arg0 $(cmd1 arg1 arg2) arg3 arg4
arg0 "arg1 arg2" cmd1 ss $ arg3 arg4 cmd2 $

#rule: All builtins consume 1 argument, eeh not a great rule

#if cmd1 then cmd2 else if cmd3 then cmd4 else cmd5

#no if statements, use || and && and !


cmd1 $ cmd2 $ &&

args cmd1 $ "arg1 arg2" cmd2 ss $ cmd3 $ ||

# cmd1 args || cmd3 $(cmd2 "arg1 arg2")


#run cmd3 then cmd2
cmd2 $ cmd3 $

#no multiline commands, no ;, no case


#for i in "./"*; do i=5 echo $i; done

($i echo $ i 5 bind) $"  "./"* i for $
