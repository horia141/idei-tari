#!/usr/bin/env tclsh

proc doTest {driver method problem} {
    exec cat out/cfg/$driver out/cfg/$method out/cfg/$problem | out/opt-$driver-$method-$problem > dumpFile
    exec echo $method [expr int([scan [lindex [split [read [open dumpFile r]] "\n"] end-1] { Cost : %f}])] >> results
    exec rm -f dumpFile
}

exec rm -f results
doTest st rs an
doTest st hc an
doTest st es an
doTest st ga-rs-opc an
doTest st ga-rs-tpc an
doTest st ga-rs-uc an
doTest st ga-rs-spc an
doTest st ga-ts-opc an
doTest st ga-ts-tpc an
doTest st ga-ts-uc an
doTest st ga-ts-spc an
puts -nonewline [read [open results r]]
exec rm -f results
