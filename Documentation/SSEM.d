[h2]	Introduction:
	The Small-Scale Experimental Machine (SSEM), also known as the Manchester
	Baby is widely considered to be the world's first stored program computer.
	Unlike The ENIAC or Z3 which used some form of mechanical storage, the 
	SSEM stored programs and data electronically and could be changed during
	the course of a program run.  SSEM ran its first program on June 21, 1948.
[=]
	The SSEM was not intended to be a full blown computer, but rather a
	testbed for technologies that would be used to build the Manchester Mark I.
	The SSEM used the Williams tube as its means of storage.  The Williams
	tube was essentially a CRT with a detection grid placed in front of it. 
	Bits of information were stored as dots on the screen that could then be
	detected by the grid.  A feedback circuit would read the bits off the 
	detection grid and were used to refresh the dots on the screen, keeping
	them in memory.  The SSEM memory consisted of 32 words of 32 bits each.
[=]
	The SSEM understood 7 different instructions and despite this small
	instruction set and only 32 words of storage many interesting program had
	been written for it.
[=]
	This program is a simulation of the SSEM, giving you the opportunity to
	see what it was like to program on this historic machine.  The program
	has been setup in such a way to mirror as closely as possible the 
	procedures needed to program and run the actual SSEM.  Although this
	simulation is not guaranteed to be a 100% emulation of the original 
	machine, it does faithfully run all SSEM programs that I could get my
	hands on.  It supports some of the operational idiosyncrocies but does
	not claim to support every idiosyncracy of the original machine.
[=]
[h2]	Note about bit ordering:
	It is important to note that the binary order is backwards from what is
	considered normal today.  The least significant bit is to the left and
	the most significant is to the right.  With a little practice it becomes
	second nature to be able to read these binary values in the opposite 
	direction.
[=]
[h2]	Hardware:
	In addition to the 32x32 memory there were 3 registers used during
	operation.  They are A, the accumulator, CI or Control Instruction which
	held the address of the instruction being executed and PI or Present
	Instruction which held the instruciton itself that was currently being
	executed.  All registers were 32 bits in size.
[=]
	There were 40 typewriter keys, labelled 0-39 that were used during 
	programming.  There were also numerous control switches used to operate
	the machine.  A display tube was used to show the contents of the 
	memory store.  No other input/output devices existed on this machine.
[=]
	The original computer had no way to save programs nor any way to input
	programs other than through the use of the control buttons and switches.
[=]
	The emulator adds the ability to save and load programs as well as a
	simple assembler to make program input a little easier, however if you
	want the full experience like in the beginning, best to stick with the
	switches. :)
[=]
[h2]	Instruction Format:
[-]	| Line No.  | Not used | Func. No. | Not Used |
[-]	| 0 1 2 3 4 | 6 .. 12  | 13 14 15  | 16 .. 31 |
[=]
[h2]	Instruction Set:
[i2]
[tb]
	| Function  |   Binary  |   Mnemonic | Description        |
	|    0      |   000     |     JMP    | line -> CI         |
	|    1      |   100     |     JRP    | CI + line -> CI    |
	|    2      |   010     |     LDN    | line negated to A  |
	|    3      |   110     |     STO    | A -> line          |
	|    4      |   001     |     SUB    | A - line -> A      |
	|    5      |   101     |     SUB    | A - line -> A      |
	|    6      |   011     |     CMP    | Skip next if A < 0 |
	|    7      |   111     |     STP    | Stop machine       |
[te]
[i-2]
[=]
[h2]	Switches:
[i2]
[tb]
	|CS    | Stop  | Set machine to idle |
	|CS    | Run   | Set machine to execute instructions |
	|KC    | ON    | Execute one instruction |
	|KAC   | ON    | Clear accumulator register |
	|KCC   | ON    | Clear control and accumulator registers |
	|KLC   | ON    | Clear action line |
	|KSC   | ON    | Clear entire store |
	|Wr/Er | Write | 0-31 buttons will set bit to 1 in action line |
	|Wr/Er | Erase | 0-31 buttons will set bit to 0 in action line |
	|Stat  | Man   | Execute instruction from the lstat, fstat switches |
	|Stat  | Auto  | Execute instructions from store |
	|0-31  |       | Set/Clear bits in action line |
	|0-4   |       | Select action line |
	|13-15 |       | Function code for Stat=Man mode |
[te]
[i-2]
[=]
[h2]	The display selection switches work as follows:
[i2]
[tb]
	| C | The display shows the contents of CI and while running CI/PI |
	| A | The display shows the contents of the accumulator            |
	| S | The display shows the contents of the store                  |
[te]
[i-2]
[=]
[h2]	Entering a program the traditional way:
	For the purpose of demonstrating how to input a program in the traditional
	way, I am going to provide a really simple program which reads the value
	of one line, negates it and then writes it into another line.  In the 
	mnemonic form this program looks like:
[=]
[i2]
[tb]
	| [0] |     | 6  |
	| [1] | LDN | 0  |
	| [2] | STO | 16 |
	| [3] | STP |    |
[te]
[i-2]
[=]
	This must now be coded into binary for input to the machine.  Here is the
	binary encoding:
[=]
[i2]
[tb]
	| [0] | 01100 00000 00000 00000 00000 00000 00 |
	| [1] | 00000 00000 00001 00000 00000 00000 00 |
	| [2] | 11110 00000 00011 00000 00000 00000 00 |
	| [3] | 00000 00000 00011 10000 00000 00000 00 |
[te]
[i-2]
[=]
	You must now setup the machine to make it ready for program input. Set
	the switches as follows:
[=]
[i2]
[tb]
	| CS             | = | Stop  |
	| Wr/Er          | = | Write |
	| Stat           | = | Auto  |
	| Display Select | = | S     |
	| 0-4            | = | Off   |
	| 13-15          | = | On    |
[te]
[i-2]
[=]
	If the display is showing that some bits are set, then set KSC to On to 
	clear the memory store.  If the memory store is already cleared then you do
	not need to do this step.
[=]
	Now you can enter the program.  To program each line of you must first use
	the 0-4 lstat switches to set the address of the line you want to modify.
	So to program line 0, all 5 of the lstat switches need to be off.  
[=]
	After the lstat switches have been set to the correct address, you use the
	typewriter (0-39 buttons) to turn bits on or off on the selected line.  When
	the Wr/Er switch is set to WRite then 1 bits will be written, when the Wr/ER
	switch is set to Erase then 0 bits will be written.
[=]
	For line 0: the lstat switches should be set to: Off Off Off Off Off
	Now press the 1 and then 2 buttons to set the two bits needed on program line
	0.
[=]
	For line 1: The lstat switches should be set to: On Off Off Off Off
	Now press the 14 button to turn on the only bit needed in line 1.
[=]
	For line 2: the lstat switches should be set to: Off On Off Off Off
	Now press the 0, 1, 2, 3, 13, and 14 buttons to program the 1 bits.
[=]
	For line 3: the lstat switches should be set to: On On Off Off Off
	Now press the 13,14, and 15 buttons to program line 3.
[=]
	If everything was entered correctly, then the bit pattern on the display
	should look like the bit patterns show above.  If not, then select the line
	that does not match by puttings its binary equivalent on the lstat switches
	and using the Wr/Er switch to set whether you need to write a bit or erase
	it and then use the typewriter buttons to set/clear the bits until your
	display matches the required bit patterns.
[=]
	Once programming is complete the final step is to be sure that all of the
	lstat and fstat switches are in the ON position.
[=]
[h2]	Running a program:
	In order for a program to run correctly, before setting CS to Run be sure the
	following switches are at:
[=]
[i2]
[tb]
	| Wr/Er | = | WRITE |
	| STAT  | = | Auto  |
	| 0-4   | = | ON    |
	| 13-15 | = | ON    |
[te]
[i-2]
[=]
	If you want to ensure the program runs from the start it is a good idea to
	set KCC On temporarily to clear the CI register, otherwise when the 
	machine is set to run it will use the current value in CI.
[=]
	Then to start the program running set CS to Run.
[=]
	If you loaded the program from the previous section the result of the 
	program will be to write this bit pattern into memory line 15:
[=]
	01011 11111 11111 11111 11111 11111 11
[=]
	Which is -6.
[=]
	When the computer executes a Stop (function 7) instruction automatic program
	execution will stop and the stop indicator will light up.
[=]
	It is important to note that from a reset state the first instruction to be
	executed will be at line 1, not 0.  This is because the SSEM incremented CI
	before an instruction was fetched and executed.  This is unlike many modern
	processors where the instruction pointer is pointing to the instruction 
	after the one currently being executed.  This is also true of the jmp
	instructions, they need to jump to the address prior to the instruction you
	want to execute next.
[=]
[h2]	Simulated idiosyncrocies:
	In the original SSEM it was necessary that the lstat and fstat switches all
	be set to On before running a program.  This was because the instruction
	as it was read was passed through the stat switches and if any of them were
	set to off that particular bit would be turned off while the instruction
	was read into PI.  This is simulated.
[=]
	When the display is set to A, all 32 lines of the display would show the 
	accumulator, not just a single line.  This is simulated.
[=]
	When the display is set to C, all 32 lines of the display would show the
	contents of the CI register if the machine was not running.  If the machine
	was running then the lines would alternate between showing CI and PI. This
	is simulated.
[=]
	The Wr/Er switch needs to be in the Write position during program runs, if
	not then the memory store would be corrupted.  This is simulated.
[=]
	If any of the typewriter buttons were pressed while the computer was 
	running, then the corresponding bits would get set for each action line
	exectued.  This is simulated.
[=]
