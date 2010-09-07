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
	    regexp {^\s*ProblemStatesCnt\s*:\s*(\d+)\s+(.*)$} $outputLeft - problemStatesCnt outputLeft
	    regexp {^\s*ProblemStates\s*:\s+(.*)$} $outputLeft - outputLeft

	    lappend result(States,IterationIds) $iteration

	    for {set i 1} {$i <= $problemStatesCnt} {incr i} {
		lappend result(States,Iterations,$iteration,IndividualIds) $i
		set problemResult [_parseStates-$problem norm $iteration $i $outputLeft]
		set outputLeft [lindex $problemResult 0]
		array set result [lindex $problemResult 1]
	    }

	    set problemResult [_parseStates-$problem best $iteration 0 $outputLeft]
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

    proc _parseParams-bfs {output} {
	set outputLeft $output

	regexp {^\s*BruteForceSearchParams\s*:\s+(.*)$} $outputLeft - outputLeft

	return [list $outputLeft {}]
    }

    proc _parseParams-rs {output} {
	set outputLeft $output

	regexp {^\s*RandomSearchParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*ProblemStatesCnt\s*:\s*(\d+)(\s+(.*))?$} $outputLeft - problemStatesCnt outputLeft
	
	set result(Method,ProblemStatesCnt) $problemStatesCnt

	return [list $outputLeft [array get result]]
    }

    proc _parseParams-hc {output} {
	set outputLeft $output

	regexp {^\s*HillClimbingParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*ExplorationFactor\s*:\s*(\d+)\s+(.*)$} $outputLeft - explorationFactor outputLeft
	regexp {^\s*ProblemStatesCnt\s*:\s*(\d+)(\s+(.*))?$} $outputLeft - problemStatesCnt outputLeft

	set result(Method,ExplorationFactor) $explorationFactor
	set result(Method,ProblemStatesCnt) $problemStatesCnt

	return [list $outputLeft [array get result]]
    }

    proc _parseParams-es {output} {
	set outputLeft $output

	regexp {^\s*EvolutionStrategyParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*Miu\s*:\s*(\d+)\s+(.*)$} $outputLeft - miu outputLeft
	regexp {^\s*Lambda\s*:\s*(\d+)(\s+(.*))?$} $outputLeft - lambda outputLeft

	set result(Method,Miu) $miu
	set result(Method,Lambda) $lambda

	return [list $outputLeft [array get result]]
    }

    proc _parseParams-ga-rs-opc {output} {
	set outputLeft $output

	regexp {^\s*GeneticAlgorithmParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*MutationChance\s*:\s*(\d+)\s+(.*)$} $outputLeft - mutationChance outputLeft
	regexp {^\s*ProblemStatesCnt\s*:\s*(\d+)\s+(.*)$} $outputLeft - problemStatesCnt outputLeft
	regexp {^\s*RandomSelectionParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*OnePointCrossOverParams\s*:(\s+(.*))?$} $outputLeft - outputLeft

	set result(Method,MutationChance) $mutationChance
	set result(Method,ProblemStatesCnt) $problemStatesCnt

	return [list $outputLeft [array get result]]
    }

    proc _parseParams-ga-rs-tpc {output} {
	set outputLeft $output

	regexp {^\s*GeneticAlgorithmParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*MutationChance\s*:\s*(\d+)\s+(.*)$} $outputLeft - mutationChance outputLeft
	regexp {^\s*ProblemStatesCnt\s*:\s*(\d+)\s+(.*)$} $outputLeft - problemStatesCnt outputLeft
	regexp {^\s*RandomSelectionParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*TwoPointCrossOverParams\s*:(\s+(.*))?$} $outputLeft - outputLeft

	set result(Method,MutationChance) $mutationChance
	set result(Method,ProblemStatesCnt) $problemStatesCnt

	return [list $outputLeft [array get result]]
    }

    proc _parseParams-ga-rs-spc {output} {
	set outputLeft $output

	regexp {^\s*GeneticAlgorithmParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*MutationChance\s*:\s*(\d+)\s+(.*)$} $outputLeft - mutationChance outputLeft
	regexp {^\s*ProblemStatesCnt\s*:\s*(\d+)\s+(.*)$} $outputLeft - problemStatesCnt outputLeft
	regexp {^\s*RandomSelectionParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*SinglePointCrossOverParams\s*:(\s+(.*))?$} $outputLeft - outputLeft

	set result(Method,MutationChance) $mutationChance
	set result(Method,ProblemStatesCnt) $problemStatesCnt

	return [list $outputLeft [array get result]]
    }

    proc _parseParams-ga-rs-uc {output} {
	set outputLeft $output

	regexp {^\s*GeneticAlgorithmParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*MutationChance\s*:\s*(\d+)\s+(.*)$} $outputLeft - mutationChance outputLeft
	regexp {^\s*ProblemStatesCnt\s*:\s*(\d+)\s+(.*)$} $outputLeft - problemStatesCnt outputLeft
	regexp {^\s*RandomSelectionParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*UniformCrossOverParams\s*:(\s+(.*))?$} $outputLeft - outputLeft

	set result(Method,MutationChance) $mutationChance
	set result(Method,ProblemStatesCnt) $problemStatesCnt

	return [list $outputLeft [array get result]]
    }

    proc _parseParams-ga-tos-opc {output} {
	set outputLeft $output

	regexp {^\s*GeneticAlgorithmParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*MutationChance\s*:\s*(\d+)\s+(.*)$} $outputLeft - mutationChance outputLeft
	regexp {^\s*ProblemStatesCnt\s*:\s*(\d+)\s+(.*)$} $outputLeft - problemStatesCnt outputLeft
	regexp {^\s*TournamentSelectionParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*TournamentSize\s*:\s*(\d+)\s+(.*)$} $outputLeft - tournamentSize outputLeft
	regexp {^\s*OnePointCrossOverParams\s*:(\s+(.*))?$} $outputLeft - outputLeft

	set result(Method,MutationChance) $mutationChance
	set result(Method,ProblemStatesCnt) $problemStatesCnt
	set result(Method,TournamentSize) $tournamentSize

	return [list $outputLeft [array get result]]
    }

    proc _parseParams-ga-tos-tpc {output} {
	set outputLeft $output

	regexp {^\s*GeneticAlgorithmParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*MutationChance\s*:\s*(\d+)\s+(.*)$} $outputLeft - mutationChance outputLeft
	regexp {^\s*ProblemStatesCnt\s*:\s*(\d+)\s+(.*)$} $outputLeft - problemStatesCnt outputLeft
	regexp {^\s*TournamentSelectionParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*TournamentSize\s*:\s*(\d+)\s+(.*)$} $outputLeft - tournamentSize outputLeft
	regexp {^\s*TwoPointCrossOverParams\s*:(\s+(.*))?$} $outputLeft - outputLeft

	set result(Method,MutationChance) $mutationChance
	set result(Method,ProblemStatesCnt) $problemStatesCnt
	set result(Method,TournamentSize) $tournamentSize

	return [list $outputLeft [array get result]]
    }

    proc _parseParams-ga-tos-spc {output} {
	set outputLeft $output

	regexp {^\s*GeneticAlgorithmParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*MutationChance\s*:\s*(\d+)\s+(.*)$} $outputLeft - mutationChance outputLeft
	regexp {^\s*ProblemStatesCnt\s*:\s*(\d+)\s+(.*)$} $outputLeft - problemStatesCnt outputLeft
	regexp {^\s*TournamentSelectionParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*TournamentSize\s*:\s*(\d+)\s+(.*)$} $outputLeft - tournamentSize outputLeft
	regexp {^\s*SinglePointCrossOverParams\s*:(\s+(.*))?$} $outputLeft - outputLeft

	set result(Method,MutationChance) $mutationChance
	set result(Method,ProblemStatesCnt) $problemStatesCnt
	set result(Method,TournamentSize) $tournamentSize

	return [list $outputLeft [array get result]]
    }

    proc _parseParams-ga-tos-uc {output} {
	set outputLeft $output

	regexp {^\s*GeneticAlgorithmParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*MutationChance\s*:\s*(\d+)\s+(.*)$} $outputLeft - mutationChance outputLeft
	regexp {^\s*ProblemStatesCnt\s*:\s*(\d+)\s+(.*)$} $outputLeft - problemStatesCnt outputLeft
	regexp {^\s*TournamentSelectionParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*TournamentSize\s*:\s*(\d+)\s+(.*)$} $outputLeft - tournamentSize outputLeft
	regexp {^\s*UniformCrossOverParams\s*:(\s+(.*))?$} $outputLeft - outputLeft

	set result(Method,MutationChance) $mutationChance
	set result(Method,ProblemStatesCnt) $problemStatesCnt
	set result(Method,TournamentSize) $tournamentSize

	return [list $outputLeft [array get result]]
    }

    proc _parseParams-rf1d {output} {
	set outputLeft $output

	regexp {^\s*RealFunction1DParams\s*:\s+(.*)$} $outputLeft - outputLeft
	regexp {^\s*Function\s*:\s*(.+?)\n\s*(.*)$} $outputLeft - function outputLeft
	regexp {^\s*IntervalStart\s*:\s*(.+?)\n\s*(.*)$} $outputLeft - intervalStart outputLeft
	regexp {^\s*IntervalEnd\s*:\s*(.+?)\n\s*(.*)$} $outputLeft - intervalEnd outputLeft
	regexp {^\s*IntervalStep\s*:\s*(.+?)(\s\s*(.*))?$} $outputLeft - intervalStep outputLeft

	set result(Problem,Function) $function
	set result(Problem,IntervalStart) $intervalStart
	set result(Problem,IntervalEnd) $intervalEnd
	set result(Problem,IntervalStep) $intervalStep

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
    check [llength $argv] == 2 {Improper call syntax: should be plot-rf1d [driver] [method]}

    set driver [lindex $argv 0]
    set method [lindex $argv 1]

    set config(cfgDirPath) [file join [pwd] out plot-rf1d cfg]
    set config(cfgDriverPath) [file join $config(cfgDirPath) $driver]
    set config(cfgMethodPath) [file join $config(cfgDirPath) $method]
    set config(cfgProblemPath) [file join $config(cfgDirPath) rf1d]
    set config(binPath) [file join [pwd] out opt-$driver-$method-rf1d]
    set config(scrPath) [file join [pwd] out plot-rf1d tmp out.scr]
    set config(datPath) [file join [pwd] out plot-rf1d tmp out.dat]
    set config(stepGranularity) 100

    set cfgDriver [read [open $config(cfgDriverPath) r]]
    set cfgMethod [read [open $config(cfgMethodPath) r]]
    set cfgProblem [read [open $config(cfgProblemPath) r]]

    set optFid [open |$config(binPath) r+]

    puts $optFid $cfgDriver
    puts $optFid $cfgMethod
    puts $optFid $cfgProblem
    flush $optFid

    set output [read $optFid]
    set outputLeft $output

    set paramsResult [parseOptCfg::parseParams $driver $method rf1d $outputLeft]
    set outputLeft [lindex $paramsResult 0]
    array set result [lindex $paramsResult 1]
    set statesResult [parseOptCfg::parseStates $driver $method rf1d $outputLeft]
    array set result [lindex $statesResult 1]

    set scrFid [open $config(scrPath) w]
    set datFid [open $config(datPath) w]

    set xMin $result(Problem,IntervalStart)
    set xMax $result(Problem,IntervalEnd)
    set step [expr abs($xMax - $xMin) / $config(stepGranularity)]
    set expression "set x \$i; expr [regsub -all {x} $result(Problem,Function) {$x}]"
    set yMin +inf
    set yMax -inf
    set minimaHistory {}

    puts $datFid "# Function $result(Problem,Function)"

    for {set i $xMin} {$i <= $xMax} {set i [expr $i + $step]} {
	set value [eval $expression]

 	puts $datFid "$i $value"

	if {$value < $yMin} {
	    set yMin $value
	}

	if {$value > $yMax} {
	    set yMax $value
	}
    }

    foreach iteration $result(States,IterationIds) {
	puts -nonewline $datFid "\n\n"
	puts $datFid "# Iteration $iteration Current Points"

	foreach individual $result(States,Iterations,$iteration,IndividualIds) {
	    set x $result(States,Iterations,$iteration,Individuals,$individual,Position)
	    set y $result(States,Iterations,$iteration,Individuals,$individual,Cost)

	    puts $datFid "$x $y"
	}

	puts -nonewline $datFid "\n\n"
	puts $datFid "# Iteration $iteration Current Minimum"

	set bestX $result(States,Iterations,$iteration,Best,Position)
	set bestY $result(States,Iterations,$iteration,Best,Cost)

	puts $datFid "$bestX $bestY"

	lappend minimaHistory $bestX
	lappend minimaHistory $bestY

	puts -nonewline $datFid "\n\n"
	puts $datFid "# Iteration $iteration Minima History"

	foreach {minimaX minimaY} $minimaHistory {
	    puts $datFid "$minimaX $minimaY"
	}
    }

    puts $scrFid "set title \"Function $result(Problem,Function)\""
    puts $scrFid "set key top left box"
    puts $scrFid "set xrange \[$xMin:$xMax\]"
    puts $scrFid "set yrange \[$yMin:$yMax\]"
    puts $scrFid "plot '$config(datPath)' index 0 with lines title \"Function\""
    puts $scrFid "pause 1"

    set index 1

    foreach iteration $result(States,IterationIds) {
	puts $scrFid "set title \"Iteration $iteration\""
	puts $scrFid "set key top left box"
	puts $scrFid "set xrange \[$xMin:$xMax\]"
	puts $scrFid "set yrange \[$yMin:$yMax\]"
	puts $scrFid "plot '$config(datPath)' index 0 with lines title \"Function\", \
                     '$config(datPath)' index [expr $index + 0] with points title \"Current Points\" pointtype 3 pointsize 2 linecolor rgb \"blue\",\
                     '$config(datPath)' index [expr $index + 1] with points title \"Current Minimum\" pointtype 8 pointsize 4 linecolor rgb \"magenta\",\
                     '$config(datPath)' index [expr $index + 2] with points title \"Minima History\" pointtype 7 pointsize 2 linecolor rgb \"black\""
	puts $scrFid "pause 1"

	incr index 3
    }

    close $scrFid
    close $datFid

    # check gnuplot exists in $env(PATH)

    exec gnuplot -p $config(scrPath)
    exec rm -f $config(scrPath)
    exec rm -f $config(datPath)
}

main $argv
