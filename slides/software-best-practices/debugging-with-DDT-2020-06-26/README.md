# IDEAS Best Practices Debugging with DDT Tutorial

# We are RECORDING this Webinar

The goal of this tutorial is to show how to setup DDT on the NERSC
Cori system and cover a few DDT basics.

This README is not a stand-alone text, it is intended to go along with
the Webinar tutorial.

This is not a complete tutorial due to time limits.  The focus is on
showing basics of getting going so you can experiment with the
debugger and follow other tutorial guides.  If there is interest we
can have deeper dives into specific features of DDT.

## What is DDT?

The ARM Forge package is a combination of DDT and MAP.  DDT is a
parallel debugger and MAP is a parallel profiler.  DDT is available on
at a number of HPC centers, including NERSC.

The other most common parallel debugger is TotalView; they are very
similar.  Knowledge in one will transfer reasonably easy to the
other.

## Additional Tutorials/Documentation

### Short tutorial and Cori setup on NERSC, good place to start

https://docs.nersc.gov/development/performance-debugging-tools/ddt/

### ARM Forge User Guide

https://developer.arm.com/docs/101136/2003

### Several example use cases with DDT:

https://computing.llnl.gov/tutorials/allineaDDT/Examples.pdf

https://www.nersc.gov/assets/Uploads/DebuggingwithDDT2013.pdf

### Debugging and Profiling your HPC Applications I Srinath Vadlamani, ARM, From ANL training series  DDT and Map tools from ARM.

https://www.youtube.com/watch?v=5x26fc57jXI

### Debugging and Profiling HPC Applications  Ryan Hulguin, ARM, Introduction to DDT and Map

https://www.youtube.com/watch?v=-2hksdglTS4&list=PLGj2a3KTwhRYzsPSwv-OisopqsCxQxazC&index=7&t=0s

### Tutorials from ARM on YouTube, several short tutorials:

https://www.youtube.com/results?search_query=ARM+DDT

## Setting up you code for debugging

Need to add compiler option for debugging and NERSC recommends turning off optimization for Intel compilers.

Indeed if you do not do -O0 on Cori, DDT does not seem to find symbol information.

```bash
   cc -g -O0 -o hello-world hello-world.c
```

`-g` to enable debugging symbols.

`-O0 -O1 -O2 -O3` are common flags for optimization levels, 0=no
optimization.  

## Connect to Cori / Load Forge/DDT

Login as you normally would.  In order to run DDT you need an X server
installed on your local machine or install the DDT client.

From a Linux/MacOS machine connect to Cori using a command line ssh with forwarding X11:

```bash
ssh -Y username@cori.nersc.gov
```

## Loading the Forge environment

DDT is not available from the default Cori environment.  Use the
module load command to make DDT available.

```bash
module load allinea-forge
```

## Launch interactive session

Since we are debugging a parallel application, need to grab node(s) to run on

```bash
salloc -q interactive -C haswell -t 01:00:00 -N 1
```

`-q` is which queue to run on, in this case the interactive partition

`-C` is the architecture, in this case we want a haswell node, we are not running a Knights Landing job.

`-t` is really important, default seems to be 5 minutes on Cori?

`-N` is the number of nodes we want, in this case we are doing small
debugging job so just need 1.  A node of Cori has 32 cores so we can
run 32 rank MPI debugging jobs with a single node.

## Run Hello World under DDT with X11

DDT can be run from the command line as any other X11 program, this
requires an X11 server on your local machine and forwarding X11 with ssh (`-Y or -X` options).

```bash
ddt ./hello-world
```

Should see DDT screen come up.

## Run DDT using local client

X11 connections can be slow, DDT has local client you can install.  The client
connects to Cori to run the job with the UI running locally.  This can speed-up
the UI significantly.

### Install local client

https://developer.arm.com/tools-and-software/server-and-hpc/downloads/arm-forge

### Local client setup

Not the NERSC web page for DDT appears incorrect.   I could not connect using the
options they have supplied.  (Have opened a ticket).

I found the installation directory for ddt using `which ddt` and using that
directory for the "Remote Installation Directory".

Run DDT on the local machine.  Since I'm on Linux:

```bash
ddt
```

Configure "Remote Launch" options.

Settings I used are:

```
Connection Name : cori
Host Name : <username>@cori.nersc.gov, <username>@cmom02.nserc.gov
Remote Installation Diretory: /usr/common/software/allinea-forge/20.0.3-Suse-15.0-x86_64
Remote Scipt : <blank>
```

Did not select any of the checkboxes.  <username> should be your Cori userid.

<image>

To initiate a remote connect on the client, select the "cori" entry you just created from the Remote Launch pull-down.

You will likely have to enter your Cori password when prompted.
  
### Reverse Connection Method

On Corie initiate the connect to the local client using the DDT reverse connection
method.  Again this should be done from an salloc interactive session as above.

```bash
salloc -q interactive -C haswell -t 01:00:00 -N 1 

ddt --connect
```

Should get popup from local client asking verify the connection.

## DDT Overview

### Basic commands

Standard commands step, step-into, stop-over etc are available on the
button bar and through keyboard shortcuts.

### Looking at data

Hovering over a value in a code window will yield a popup with value
and type information.  `Local` panel will show local variables.

Can also expressions to evaluate (e.g. radians * 180 / 3.14 ).

### Breakpoints

Key difference from sequential debugging is ability to set breakpoints
in parallel.  Can set for all ranks or one rank.

Note the "Stop on nth pass" feature.  Useful for
time-stepping/iterative algorithms, if you know what step you are on
you can skip.

### Watchpoints

Watch is a variable (or memory location) or expression you can use to stop when it is changed or accessed.

E.G. When does the variable become non-zero?

### Tracepoints

"Tracepoints allow you to see what lines of code your program is executing, and the variables, without stopping it. Whenever a thread reaches a tracepoint it will print the file and line number of the tracepoint to the Input/Output view. You can also capture the value of any number of variables or expressions at that point

Examples of situations in which this feature will prove invaluable include:

    Recording entry values in a function that is called many times, but crashes only occasionally. Setting a tracepoint makes it easier to correlate the circumstances that cause a crash.
    Recording entry to multiple functions in a library, enabling the user or library developer to check which functions are being called, and in which order. An example of this is the MPI History Plugin, which records MPI usage. See section 13.3 Using a plugin.
    Observing progress of an application and variation of values across processes without having to interrupt the application."

### Message Queues

Since we are MPI land, understanding messages between ranks is a
useful.  DDT has support for looking at the message queues on each
rank.  Shows if message has been sent but not received.

Unfortunetly....DDT manual : "Some MPIs, notably Crays MPI, do not
support message queue debugging at all."

## Debug core file

On DDT main page, "Open Core".  When running DDT with the "Remote
Launch" will show core files on Cori.
