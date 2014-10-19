PokerStars_Hack_Window_Colors
=============================

<b>That is something  i did a long time ago as a challenge . As you will see the code is undocumented because really i did not think i could make it :) .But i decided to make it public because there are not many examples doing what i did and it may help someone.<b>

The goal of this hack was to be able to alert the player that a pokerstars table needs his attention more than the others.<br>
I did that by setting a colored   rectangle on the pokerstars table .<br>
A red rectangle would mean that you should give the table more attention , a green would mean something other etc.<br>
In the end i wanted the player to be able to set the rules for the colors but i lost interest :)<br>

PokerDll (C++) is the folder that has the dll for the hooking into a process<br>
PokerLogic (C#) is  the main program which is responsible for the hand history and the decisions about colors and
setting a hook on pokerstars windows to manipulate and draw a rectangle depending on the Hand history log.<br>

So the main program gets some info about the user like his name in the game and the directory of the Hand history.<br>
After we have those information we set a file watcher on the directory of the Hand history.<br>
Every time a player starts a game a new Hand history file is created in the directory so we start a series of actions :<br>

1) We start reading the file and getting some basic info about the table itself (number of players etc , tournament number etc )<br>
2) We search for the process id of the window . We do that by finding all the processes with name POKERSTARS and title the tournament number we got from Hand History.<br>
3) We set the drawing hook into that process id and we can now manipulate the drawing of the window<br>
4) We keep reading the hand history and we draw different colors on the window  .<br>

The code works for multiple pokerstars windows also.<br>



<b>I am not going to improve the code.<br><b>

LICENCE <br>
MIT
