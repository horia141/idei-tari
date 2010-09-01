#!/usr/bin/env tclsh
# arguments: ./plotrf1d [driver] [method]

proc check {args} {
    set condition [lrange $args 0 end-1]
    set message [lindex $args end]

    if {[uplevel 1 expr $condition] == 0} {
        puts [uplevel 1 subst -nocommands [list $message]]
        exit
    }
}

namespace eval parseOptCfg {
    proc parseParams {driver method problem output} {
	return [_parseParams-$driver $method $problem $output]
    }

    proc parseStates {driver method problem output} {
	set outputLeft $output

	while {![string is space $outputLeft]} {
	    regexp {^\s*(.+?)\s*:\s+(.*)$} $outputLeft - driverName outputLeft
	    regexp {^\s*Iteration\s*:\s*(\d+)\s+(.*)$} $outputLeft - iteration outputLeft
	    regexp {^\s*(.+?)\s*:\s+(.*)$} $outputLeft - methodName outputLeft
	    regexp {^\s*Iteration\s*:\s*(\d+)\s+(.*)$} $outputLeft - iteration outputLeft
	    regexp {^\s*ProblemStatesCnt\s*:\s*(\d+)\s+(.*)$} $outputLeft - problemStatesCnt outputLeft
	    regexp {^\s*ProblemStates\s*:\s+(.*)$} $outputLeft - outputLeft

	    lappend result(States,IterationsIds) $iteration

	    for {set i 1} {$i <= $problemStatesCnt} {incr i} {
		lappend result(States,Iterations,$iteration,IndividualIds) $i
		set problemResult [_parseStates-$problem norm $iteration $i $outputLeft]
		set outputLeft [lindex $problemResult 0]
		array set result [lindex $problemResult 1]
	    }

	    set problemResult [_parseStates-$problem best 0 0 $outputLeft]
	    set outputLeft [lindex $problemResult 0]
	    array set result [lindex $problemResult 1]
	}

	return [list $outputLeft [array get result]]
    }

    proc _parseParams-st {method problem output} {
	set outputLeft $output

	regexp {^\s*SingleThreadedParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*IterationsNr\s*:\s*(\d+)\s+(.*)$} $outputLeft - iterationsNr outputLeft
	regexp {^\s*StatePrintInterval\s*:\s*(\d+)(\s+(.*))?$} $outputLeft - statePrintInterval outputLeft

	set result(Driver,IterationsNr) $iterationsNr
	set result(Driver,StatePrintInterval) $statePrintInterval

	set methodResult [_parseParams-$method $outputLeft]
	set outputLeft [lindex $methodResult 0]
	array set result [lindex $methodResult 1]
	set problemResult [_parseParams-$problem $outputLeft]
	set outputLeft [lindex $problemResult 0]
	array set result [lindex $problemResult 1]

	return [list $outputLeft [array get result]]
    }

    proc _parseParams-rs {output} {
	set outputLeft $output

	regexp {^\s*RandomSearchParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*ProblemStatesCnt\s*:\s*(\d+)(\s+(.*))?$} $outputLeft - problemStatesCnt outputLeft
	
	set result(Method,ProblemStatesCnt) $problemStatesCnt

	return [list $outputLeft [array get result]]
    }

    proc _parseParams-hc {output} {
    }

    proc _parseParams-es {output} {
    }

    proc _parseParams-ga {output} {
    }

    proc _parseParams-ga-rs {output} {
    }

    proc _parseParams-ga-tos {output} {
    }

    proc _parseParams-ga-opc {output} {
    }

    proc _parseParams-ga-tpc {output} {
    }

    proc _parseParams-ga-spc {output} {
    }

    proc _parseParams-ga-uc {output} {
    }

    proc _parseParams-rf1d {output} {
	set outputLeft $output

	regexp {^\s*RealFunction1DParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*Function\s*:\s*(.+?)\n\s*(.*)$} $outputLeft - function outputLeft
	regexp {^\s*IntervalStart\s*:\s*(.+?)\n\s*(.*)$} $outputLeft - intervalStart outputLeft
	regexp {^\s*IntervalEnd\s*:\s*(.+?)(\n\s*(.*))?$} $outputLeft - intervalEnd outputLeft

	set result(Problem,Function) $function
	set result(Problem,IntervalStart) $intervalStart
	set result(Problem,IntervalEnd) $intervalEnd

	return [list $outputLeft [array get result]]
    }

    proc _parseParams-rf2d {output} {
    }

    proc _parseParams-an {output} {
    }

    proc _parseStates-rf1d {type iteration individual output} {
	set outputLeft $output

	regexp {^\s*RealFunction1DState\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*Position\s*:\s*(.+?)\n\s*(.*)$} $outputLeft - position outputLeft
	regexp {^\s*Cost\s*:\s*(.+?)(\n\s*(.*))?$} $outputLeft - cost outputLeft

	switch $type {
	    norm {
		set result(States,Iterations,$iteration,Individuals,$individual,Position) $position
		set result(States,Iterations,$iteration,Individuals,$individual,Cost) $cost
	    }

	    best {
		set result(States,Iterations,$iteration,Best,Position) $position
		set result(States,Iterations,$iteration,Best,Cost) $cost
	    }
	}

	return [list $outputLeft [array get result]]
    }
    
    proc _parseStates-rf2d {type iteration individual output} {
    }

    proc _parseStates-an {type iteration individual output} {
    }
}

proc main {argv} {
    check [llength $argv] == 2 {Improper call syntax: should be plotrf1d [driver] [method]}

    set driver [lindex $argv 0]
    set method [lindex $argv 1]

    set config(cfgDirPath) [file join [pwd] cfg]
    set config(cfgDriverPath) [file join $config(cfgDirPath) $driver]
    set config(cfgMethodPath) [file join $config(cfgDirPath) $method]
    set config(cfgProblemPath) [file join $config(cfgDirPath) rf1d]
    set config(binPath) [file join [pwd] .. out opt-$driver-$method-rf1d]
    set config(optOutPath) [file join [pwd] output-$driver-$method-rf1d]

    exec cat $config(cfgDriverPath) $config(cfgMethodPath) $config(cfgProblemPath) | $config(binPath) > $config(optOutPath)

    array set result [parseOptCfg::parseParams $driver $method rf1d [read [open $config(optOutPath)]]]
    
    exec rm -rf $config(optOutPath)
}

# main $argv
set x [read [open result-st-rs-rf1d r]]
set ab [parseOptCfg::parseParams st rs rf1d $x]
puts [parseOptCfg::parseStates st rs rf1d [lindex $ab 0]]
