# FileTypeOrganization by. sean jesky

(Runs on Windows And Linux without any changes within Main, just copy main into a project for Visual Studio, wont work otherwise..)
Organize a filesystem by file type, makes analysis of a system easier for people who need to quickly comb through a system that isn't their own, or people who just want to run a program for fun. 

    Unlike the StarSaver program, this program will go through a 
    directory of your choice and will organize all the files by file extension type,
    and save those files within a choosen directory by the user instead of a searching for
    A specific filename and then organize by type. Ones general, the other is more specific. 

thought something like this could be used to do analysis of a system visually much easier

- enter program name, and a source location (where you wish to look) and the destination (where you wish to save)
- The Program will go through a directory and collect all file types, and filenames
- Next the program will create a directories within the destination location and begin to copy files of type T, to that location
- The Program Ends (program runs relatively fast and without hassle. 

To run program in command line: 

     FileTypeOrganization <whereToLook> <WhereToSave>
    
     Where To Look is where you want the program to find the files for searching through.
     
     Where To Save is where the program will save the organized file data. 


not really done the way I like to write code, but the reality is, I did it on a whim and It was before starsaver, but it was unwieldy in how I wrote it and adding to this wouldn't be that good of an idea. 

[Warning, will not work in VS Debug mode... idk why yet]

    TODO:...why are so many people using my codes... I didn't expect any of them to have even >30 people so fast. I am, and will be supporting these projects in my free time (not studying, or taking care of my dad or the house...fml)
    FIXED:: fix hidden file error in Linux (add .erase(0,1) to erase directories naming with a dot; .<extension> in front of name. 
    FIXED:: Other Bugs related to program structure eg. shadowing parameters, and data types, decltype fixed one bug, so that was really cool
    
    Compile: 
    clang++ main.cpp -lstdc++fs --std=c++17 -Oz -s -o  FTO
    
    Compile for bugs:
    clang++ main.cpp -Wshadow -Wall -g  -lstdc++fs --std=c++17 -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG
