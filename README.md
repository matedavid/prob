# Prob

## Description:

* A git based private backup system, where, instead of all the files being saved on a remote server, you can choose to save them locally wherever you want to 

## Use:
prob command [flags]

### Commands:

* init: initializes the environment for prob to work

* config: to set and acces various configurations of your environment

* add: used to add the files that you want to be backed up

* backup: command that backs up all the files that you added

### Specific commands: 
* <strong>init</strong>: The first step to initialize the prob environment. Creates a folder where all the files needed will be saved. 
* <strong>config</strong>: Used to configure necessary information for the program to run.
	* <strong>config path [path]</strong>: configures the path to the folder where the files will be saved
	* <strong>config path</strong>: will display the file you have configured
	* <strong>config added</strong>: will display the files added
* <strong>add</strong>: Used to add the files that when you backup will be saved
	* <strong>add [files]</strong>: will add the files specified
	* <strong>add .</strong> : will add all the files in the directory
* <strong>backup</strong>: will backup all the files added


## Compile code
Simply run `cmake .` and `make` and the program will be compiled on the `build/` folder