#!/usr/bin/env tclsh

namespace eval cfg {
    set BIN_PATH ./out
    set WORK_PATH [file join $cfg::BIN_PATH large-run]
    set CFG_WORK_PATH [file join $cfg::WORK_PATH cfg]
    set TMP_WORK_PATH [file join $cfg::WORK_PATH tmp]
    set RES_WORK_PATH [file join $cfg::WORK_PATH res]
    set DRIVERS {st}
    set METHODS {rs hc es ga-rs-opc ga-rs-tpc ga-rs-spc ga-rs-uc ga-tos-opc ga-tos-tpc ga-tos-spc ga-tos-uc}
    set PROBLEMS {rf1d rf2d an}
    set RUNS 1

    array set DRIVER_DIRECTORY {
	st {Single Threaded}
    }

    array set METHOD_DIRECTORY {
	rs         {Random Search}
	hc         {Hill Climbing}
	es         {Evolution Strategy}
	ga-rs-opc  {Genetic Algorithm + Random Selection + One Point CrossOver}
	ga-rs-tpc  {Genetic Algorithm + Random Selection + Two Point CrossOver}
	ga-rs-spc  {Genetic Algorithm + Random Selection + Single Point CrossOver}
	ga-rs-uc   {Genetic Algorithm + Random Selection + Uniform CrossOver}
	ga-trs-opc {Genetic Algorithm + Truncation Selection + One Point CrossOver}
	ga-trs-tpc {Genetic Algorithm + Truncation Selection + Two Point CrossOver}
	ga-trs-spc {Genetic Algorithm + Truncation Selection + Single Point CrossOver}
	ga-trs-uc  {Genetic Algorithm + Truncation Selection + Uniform CrossOver}
	ga-tos-opc {Genetic Algorithm + Tournament Selection + One Point CrossOver}
	ga-tos-tpc {Genetic Algorithm + Tournament Selection + Two Point CrossOver}
	ga-tos-spc {Genetic Algorithm + Tournament Selection + Single Point CrossOver}
	ga-tos-uc  {Genetic Algorithm + Tournament Selection + Uniform CrossOver}
    }

    array set PROBLEM_DIRECTORY {
	rf1d {1D Real Function}
	rf2d {2D Real Function}
	an   {Access Network}
    }
}

proc runOneTest {testedProblem driver method index} {
    set programPath [file join $cfg::BIN_PATH opt-$driver-$method-$testedProblem]
    set driverCfgPath [file join $cfg::CFG_WORK_PATH $driver]
    set methodCfgPath [file join $cfg::CFG_WORK_PATH $method]
    set problemCfgPath [file join $cfg::CFG_WORK_PATH $testedProblem]
    set programCfgPath [file join $cfg::TMP_WORK_PATH cfg-$driver-$method-$testedProblem]
    set resultOutPath [file join $cfg::TMP_WORK_PATH result-$driver-$method-$testedProblem]
    set timeOutPath [file join $cfg::TMP_WORK_PATH time-$driver-$method-$testedProblem]

    exec cat $driverCfgPath $methodCfgPath $problemCfgPath > $programCfgPath
    exec time -v -o $timeOutPath $programPath < $programCfgPath > $resultOutPath

    set resultFile [open $resultOutPath r]
    set timeFile [open $timeOutPath r]

    set resultContents [read $resultFile]
    set timeContents [read $timeFile]

    close $resultFile
    close $timeFile

    set result($driver,$method,runs,$index,nodes) [lindex [regexp -inline {^.*?NodesIds\s*:\s*(.*)$} [lindex [split $resultContents "\n"] end-2]] 1]
    set result($driver,$method,runs,$index,cost) [lindex [regexp -inline {^.*?Cost\s*:\s*(.*)$} [lindex [split $resultContents "\n"] end-1]] 1]
    set result($driver,$method,runs,$index,time) [lindex [regexp -inline {^.*?Elapsed [(]wall clock[)] time [(]h:mm:ss or m:ss[)]\s*:\s*(.*?)[.]\d\d$} [lindex [split $timeContents "\n"] 4]] 1]

    exec rm -f $programCfgPath
    exec rm -f $resultOutPath
    exec rm -f $timeOutPath

    return [array get result]
}

if {[llength $argv] != 1} {
    error "Improper syntax"
}

set testedProblem [lindex $argv 0]

set goodDrivers st
set goodMethods ga-tos-uc

array set result {}

for {set i 1} {$i <= $cfg::RUNS} {incr i} {
    puts "Run $i/$cfg::RUNS:"

    foreach d $goodDrivers {
	puts "  $cfg::DRIVER_DIRECTORY($d):"

	foreach m $goodMethods {
	    puts "    $cfg::METHOD_DIRECTORY($m)"

	    lappend result($d,$m,runIds) $i
	    array set result [runOneTest $testedProblem $d $m $i]
	}
    }
}

foreach d $goodDrivers {
    foreach m $goodMethods {
	set baseTime [clock scan 00:00]
	set averageTimeSum 0

	foreach run $result($d,$m,runIds) {
	    incr averageTimeSum [expr [clock scan $result($d,$m,runs,$run,time)] - $baseTime]
	}

	set averageTime [expr $averageTimeSum / [llength $result($d,$m,runIds)]]
	set result($d,$m,time) [clock format [expr $averageTime + $baseTime] -format %T]
    }
}

puts "Results:"

foreach $d $goodDrivers {
    puts "  $cfg::DRIVER_DIRECTORY($d):"

    foreach m $goodMethods {
	puts "    $cfg::METHOD_DIRECTORY($m):"
	puts "      Network:      $result($d,$m,runs,1,nodes)"
	puts "      Cost:         $result($d,$m,runs,1,cost)"
	puts "      Average Time: $result($d,$m,time)"
    }
}
