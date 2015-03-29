# RoboLab-WS1415-TUD

This repository houses the RoboLab project for the course RoboLab at TU Dresden and was created by **Felix Wittwer, Steffi Macak, Tim Stelzig** and **Max Ulitzka** (Group 7, 16.03.2015 - 28.03.2015).

**A message to participants of the RoboLab course:**
Copying our whole code won't work. It fitted perfectly to our Robots behaviour and it's oddities. If you came here to have a look for some inspiration, you're fine to continue. But if you came here in the search for some complete project data to copy: don't do it. You won't learn anything. This internship is supposed to be fun and a chance to gather some experience. Don't ruin that chance for you. :)

## Setting up the Workspaces

If you want to use the Source Code provided in this repo on your NXT, follow these steps:

1. Git-clone the Repo.

2. If you have not already, install the `Eclipse IDE for C/C++` (can be found [here](http://www.eclipse.org)) on your computer along with the additional packages and drivers, provided in this [Dropbox folder](https://www.dropbox.com/sh/1g4fsap2re78npf/AAA6sP436yRCfl63jRXyvyo8a) inside the HowTo-File.

3. Download the Eclipse-Workspace for the Robot from [here](https://www.dropbox.com/sh/1g4fsap2re78npf/AAAIDFSSb8KU26nl98dBy6_oa/workspace_robot.zip).

4. Extract the files from the archive, rename the folder `workspace_robot` to `Robot-Workspace` and rename the folder `example` inside to `RoboLab`.

5. Now copy this folder in the Repo and type `git checkout -- .` in the Git Bash (Windows)/Terminal (Mac and Linux) to discard all changes made during the copying process.

6. **You're done!**


If you want to run the Simulation, follow these steps:

1. Git-clone the Repo.

2. If you have not already, install the `Eclipse IDE for C/C++` (can be found [here](http://www.eclipse.org)) on your computer and follow the steps 8 - 16 provided in the [HowTo-File](https://www.dropbox.com/sh/1g4fsap2re78npf/AACJvdiu4OgfuEIxI9zx_3Mba/How_to_start.txt).

3. Download the Eclipse-Workspace for the Simulation from [here](https://www.dropbox.com/sh/1g4fsap2re78npf/AADFN1Pjng5CqbAXEfx-IaBga/workspace_simulation.zip).

4. Extract the files from the archive, rename the folder `workspace_simulation` to `Simulation-Workspace`.

5. Now copy this folder in the Repo and type `git checkout -- .` in the Git Bash (Windows)/Terminal (Mac and Linux) to discard all changes made during the copying process.

6. **You're done!**

If you want to build the Simulation, use the commands provided in this [README](https://github.com/max-leuthaeuser/RobolabSim/tree/master/package/solution).

## NOTICE

+ The Makefile provided in the Robot-Workspace folder is for Windows. You can also build it with Mac, if you have installed the Driver package that contains Wine. But for native support on Mac OS X and Linux you will have to rewrite the Makefile (you can look in the Dropbox folder for a hint).

## Additional Information

* [What is RoboLab?](http://tu-dresden.de/die_tu_dresden/fakultaeten/fakultaet_informatik/sysa/se/teaching/courses/ws/einfuehrungspraktikum_roboter_lab/index_html/document_view?set_language=en)

* [Simulator-Repo](https://github.com/max-leuthaeuser/RobolabSim)
