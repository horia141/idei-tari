#!/usr/bin/env tclsh

source trythrow.tcl

namespace import trythrow::try
namespace import trythrow::throw

proc checkPathIsFile {path} {
    if {![file exists $path]} {
        throw CheckPathError "File \"$path\" does not exist!"
    }

    if {![file isfile $path]} {
        throw CheckPathError "File \"$path\" is not a file!"
    }
}

proc checkPathIsExecutableFile {path} {
    checkPathIsFile $path

    if {![file executable $path]} {
        throw CheckPathError "File \"$path\" is not executable!"
    }
}

proc readFile {path} {
    try {
        set file [open $path r]
        set size [file size $path]
        set text [read $file $size]

        return $text
    } catch TclError {msg} {
        throw FileReadError $msg
    } final {
        if {[info exists file]} {
            close $file
        }
    }
}

set binDirPath [pwd]/../out
set driver [lindex $argv 0]
set method [lindex $argv 1]

if {[string is space $driver]} {
    puts "You need to specify a driver!"
    exit
}

if {[string is space $method]} {
    puts "You need to specify a method!"
    exit
}

set optBinFile [file join $binDirPath opt-$driver-$method-rf1d]
set driverCfgFile [file join $binDirPath cfg $driver]
set methodCfgFile [file join $binDirPath cfg $method]
set problemCfgFile [file join $binDirPath cfg rf1d]

set optOutFile output

try {
    checkPathIsExecutableFile $optBinFile
    checkPathIsFile $driverCfgFile
    checkPathIsFile $methodCfgFile
    checkPathIsFile $problemCfgFile

    puts "Driver         : $driver"
    puts "Method         : $method"
    puts "Binaries Path  : $binDirPath"
    puts "Target Binary  : $optBinFile"
    puts "Driver Config  : $driverCfgFile"
    puts "Method Config  : $methodCfgFile"
    puts "Problem Config : $problemCfgFile"
    puts "Output         : $optOutFile"

    try {
        exec cat $driverCfgFile $methodCfgFile $problemCfgFile | $optBinFile > $optOutFile
    } catch TclError {msg} {
        throw ApplicationExecError $msg
    }

    set outFile [readFile $optOutFile]

    # we assume every output file is of the form : params + [driver states]
    # and each driver state has one population and one best. Also each
    # method has a very similar structure to it's state.

    regexp {^\s*(\w+)Params\s*:\s*(.*)$} $outFile - out(Driver,Name) rest
    regexp {^\s*IterationsNr\s*:\s*(\d+)\s*(.*)$} $rest - out(Driver,IterationsNr) rest
    regexp {^\s*StatePrintInterval\s*:\s*(\d+)\s*(.*)$} $rest - out(Driver,StatePrintInterval) rest
    regexp {^\s*.*?\s*(\w+)Params\s*:\s*(.*)$} $rest - out(Method,Name) rest
    regexp {^\s*.*?\s*(\w+)Params\s*:\s*(.*)$} $rest - out(Problem,Name) rest
    regexp {^\s*Function\s*:\s*(.+?)\s*\n(.*)$} $rest - out(Problem,Function) rest
    regexp {^\s*IntervalStart\s*:\s*(.+?)\s*\n(.*)$} $rest - out(Problem,IntervalStart) rest
    regexp {^\s*IntervalEnd\s*:\s*(.+?)\s*\n(.*)$} $rest - out(Problem,IntervalEnd) rest

    set out(Run,IterationIds) {}

    for {set st 0} {$st < floor($out(Driver,IterationsNr) / $out(Driver,StatePrintInterval)) + 1} {incr st} {
        regexp "^\\s*.*?\\s*$out(Driver,Name)State\\s*:\\s*(.*)$" $rest - rest
        regexp {^\s*Iteration\s*:\s*0\s*(.*)$} $rest - rest
        regexp "^\\s*.*?\\s*$out(Method,Name)State\\s*:\\s*(.*)$" $rest - rest
        regexp {^\s*Iteration\s*:\s*(\d+)\s*(.*)$} $rest - iteration rest

        lappend out(Run,IterationIds) $iteration

        regexp {^\s*ProblemStatesCnt\s*:\s*(\d+)\s*(.*)} $rest - problemStatesCnt rest

        set out(Run,Iterations,$iteration,ProblemStatesIds) {}

        for {set i 0} {$i < $problemStatesCnt} {incr i} {
            lappend out(Run,Iterations,$iteration,ProblemStateIds) $i

            regexp {^\s*.*?\s*RealFunction1DState\s*:\s*(.*)} $rest - rest
            regexp {^\s*Position\s*:\s*(.+?)\s*\n(.*)$} $rest - position rest
            regexp {^\s*Cost\s*:\s*(.+?)\s*\n(.*)$} $rest - cost rest

            set out(Run,Iterations,$iteration,ProblemStates,$i,Position) $position
            set out(Run,Iterations,$iteration,ProblemStates,$i,Cost) $cost
        }

        regexp {^\s*.*?\s*RealFunction1DState\s*:\s*(.*)} $rest - rest
        regexp {^\s*Position\s*:\s*(.+?)\s*\n(.*)$} $rest - position rest
        regexp {^\s*Cost\s*:\s*(.+?)\s*\n(.*)$} $rest - cost rest

        set out(Run,Iterations,$iteration,Best,Position) $position
        set out(Run,Iterations,$iteration,Best,Cost) $cost

        puts $out(Driver,Name)
        puts $out(Driver,IterationsNr)
        puts $out(Driver,StatePrintInterval)
        puts $out(Method,Name)
        puts $out(Problem,Name)
        puts $out(Problem,Function)
        puts $out(Problem,IntervalStart)
        puts $out(Problem,IntervalEnd)
    }

    foreach iteration [lsort -integer $out(Run,IterationIds)] {
        puts "Iteration $iteration"
        puts -nonewline "  ProblemStates: "

        foreach problemState [lsort -integer $out(Run,Iterations,$iteration,ProblemStateIds)] {
            puts -nonewline "\($out(Run,Iterations,$iteration,ProblemStates,$problemState,Position),"
            puts -nonewline "$out(Run,Iterations,$iteration,ProblemStates,$problemState,Cost)\) "
        }

        puts -nonewline "\n  Best: \($out(Run,Iterations,$iteration,Best,Position),"
        puts -nonewline "$out(Run,Iterations,$iteration,Best,Cost)\)\n"
    }
} catch CheckPathError {msg} {
    puts "An error occured:"
    puts $msg
} catch ApplicationExecError {msg} {
    puts "The following error occured while the optimisation system ran:"
    puts $msg
} catch FileReadError {msg} {
    puts "A file could not be read:"
    puts $msg
}
