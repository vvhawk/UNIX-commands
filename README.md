# UNIX Commands 🛠️
This project was completed for my university class on [systems](https://www.cs.rutgers.edu/academics/undergraduate/course-synopses/course-details/01-198-214-systems-programming).

We implemented common UNIX commands used to manage system files and directories (ls, find, tree) in [C](https://en.wikipedia.org/wiki/C_(programming_language)).

Simply put, a directory is a fancy name for a folder. On your computer, you have many folders for your applications. These folders are used to store files with important data.

Folders can even contain more folders. This is the basis for file organization.

<p align="center">
  <img src="./extras/folders.gif"/>
</p>

If you're new to or a little fuzzy on files and directories learn more [here](https://jdblischak.github.io/2014-09-18-chicago/novice/shell/01-filedir.html).

All code was developed and tested remotely on Rutgers [Instructional Lab Machines](https://report.cs.rutgers.edu/nagiosnotes/iLab-machines.html). Remote connection was established using [SSH](https://en.wikipedia.org/wiki/Secure_Shell).

A [Makefile](https://www.gnu.org/software/make/manual/make.html#Introduction) is provided for build automation.

<p align="center">
  <img src="./extras/clean.gif"/>
</p>

Below I've included an overview of the commands implemented. 

For each command...

I run the actual command,

compile the corresponding program using *"make program-name"* ,

and run using *"./program-name"* to show that the results are the same. 

## [ls](https://man7.org/linux/man-pages/man1/ls.1.html)
List contents of a directory

<p align="center">
  <img src="./extras/ls.gif"/>
</p>

### ls -l [option](http://www.catb.org/~esr/writings/taoup/html/ch10s05.html)
ls -l (lowercase “l” for “long”), prints the “long format” with extra information about each file

<p align="center">
  <img src="./extras/ls-l.gif"/>
</p>


## [find](https://man7.org/linux/man-pages/man1/find.1.html)
Recursively searches and finds files/directories matching a pattern given as a command-line argument

<p align="center">
  <img src="./extras/find.gif"/>
</p>

## [tree](https://linux.die.net/man/1/tree)
Recursively searches and prints files/directories as a tree

<p align="center">
  <img src="./extras/tree.gif"/>
</p>

## Credits
Instructor   
[Jeffrey Ames](https://www.cs.rutgers.edu/people/professors/details/jeffrey-ames)

Vasanth Banumurthy  
Aqil Farooqui    
Sameed Hussain       
   
