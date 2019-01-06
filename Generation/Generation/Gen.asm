.586 
.model flat, stdcall 
includelib libucrt.lib 
includelib kernel32.lib 
includelib ../Debug/GenLib.lib 
ExitProcess PROTO: DWORD 
pows	PROTO: DWORD, : DWORD 
strlength	PROTO :DWORD 
absnum	PROTO: DWORD 
output_int	PROTO: DWORD 
output_str	PROTO: DWORD 
catlines	PROTO: DWORD, : DWORD, :DWORD

.stack 4096

.const
 ltrl5	byte 'MPG2018', 0
 hope	byte 'I will pass the course project ', 0
 dream	byte 'with a good mark!', 0
 chance	byte 'Your chances are equal: ', 0
 ltrl7	byte 'percent.', 0

.data
buffer	byte 256 dup(0)
acalc	dword 0
bcalc	dword 0
mark	dword 0
course	dword 0
att	dword 9
coursepr	dword 0
happy	dword 0
len	dword 0
.code

calc PROC scalc:DWORD, fcalc:DWORD
 push scalc
 push 2
 call pows
 mov acalc, eax
 push acalc
 push 27
 pop ebx 
 mov edx, 0 
 pop eax 
 idiv ebx 
 push eax 
 
 push fcalc
 push 4
 pop eax 
 pop ebx 
 add eax, ebx 
 push eax 

 push 2
 pop eax 
 pop ebx 
 imul ebx 
 push eax 
 
 pop ebx 
 pop eax 
 sub eax, ebx 
 push eax 
 
 push 6
 pop eax 
 pop ebx 
 add eax, ebx 
 push eax 

 mov bcalc, eax
 pop eax
 ret
calc ENDP

main PROC
 push offset ltrl5
 call output_str
 push att
 push 15
 pop ebx 
 pop eax 
 sub eax, ebx 
 push eax 
 
 mov coursepr, eax
 push coursepr
 call absnum
 mov course, eax
 push course
 push att
 call calc
 mov mark, eax
 push offset hope
 push offset dream
 push offset buffer
 call catlines
 mov happy, eax
 push happy
 call output_str
 push offset chance
 call strlength
 mov len, eax
 push offset chance
 call output_str
 push len
 call output_int
 push offset ltrl7
 call output_str
 push mark
 call output_int

 push 0
 call ExitProcess
main ENDP
end main