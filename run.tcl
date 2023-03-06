#!/usr/bin/tclsh

# Run programs
# Each chapter contains exercise files and 1 p (program) file
# Usage: ./run.tcl chapterNumber exerciseNumber/p

# Examples
# Chapter 1, exercise 2: './run.tcl 1 2'
# Chapter 1, program: './run.tcl 1 p'

set lbs "-lsfml-graphics -lsfml-window -lsfml-system"

set data "

  {{{ex1.cpp ../Programs/numbers_functions.cpp}
    {ex2.cpp ../Programs/numbers_functions.cpp}}
   {numbers.cpp numbers_functions.cpp}}

  {{{ex1.cpp ../Programs/arithmetic_functions.cpp}
    {ex2.cpp ../Programs/arithmetic_functions.cpp}
    {-c ex3.cpp ../Programs/arithmetic_functions.cpp
     && ex3.o arithmetic_functions.o $lbs}}
   {arithmetic.cpp arithmetic_functions.cpp}}

  {{{ex1.cpp ../Programs/algebra_functions.cpp
    ../../Chapter\\ 2/Programs/arithmetic_functions.cpp}
    {ex2.cpp ../Programs/algebra_functions.cpp
     ../../Chapter\\ 2/Programs/arithmetic_functions.cpp}
    {ex3.cpp ../Programs/algebra_functions.cpp
     ../../Chapter\\ 2/Programs/arithmetic_functions.cpp}}
   {algebra.cpp algebra_functions.cpp
    ../../Chapter\\ 2/Programs/arithmetic_functions.cpp}}

  {{{ex1.cpp ../Programs/geometry_functions.cpp}
    {ex2.cpp ../Programs/geometry_functions.cpp}}
   {geometry.cpp geometry_functions.cpp}}

  {{{-c ex1.cpp ../Programs/vectors_functions.cpp &&
     ex1.o vectors_functions.o $lbs}
    {ex2.cpp}}
   {-c vectors.cpp vectors_functions.cpp &&
    vectors.o vectors_functions.o $lbs}}

  {{{ex1.cpp}
    {ex2.cpp}}
   {calculus.cpp calculus_functions.cpp}}

  {{{ex1.cpp ../Programs/energy_functions.cpp}
    {ex2.cpp}
    {ex3.cpp ../Programs/energy_functions.cpp}}
   {energy.cpp ../Programs/energy_functions.cpp}}
   
  {{{ex1.cpp}
    {ex2.cpp}}
   {collisions.cpp ../Programs/collisions_functions.cpp}}
   
  {{{ex1.cpp}
    {ex2.cpp}}
   {resolution.cpp ../Programs/resolution_functions.cpp}}
   
  {{{ex1.cpp}
    {ex2.cpp}}
   {shapes.cpp}}

  {{{ex1.cpp}
    {ex2.cpp}}
   {game.cpp}}

  {{{-c ex1.cpp ../Programs/force_functions.cpp &&
     ex1.o force_functions.o $lbs}}
   {force.cpp ../Programs/force_functions.cpp}}

  {{{ex1.cpp}
    {ex2.cpp}}
   {angular.cpp}}

  {{{ex1.cpp}}
   {friction.cpp ../Programs/friction_functions.cpp}}

  {{{ex1.cpp}}
   {pulley.cpp ../Programs/pulley_functions.cpp}}

  {{{ex1.cpp}}
   {oscillation.cpp ../Programs/oscillation_functions.cpp}}

  {{{-c ex1.cpp ../Programs/geometry3d_functions.cpp &&
     ex1.o geometry3d_functions.o $lbs}}
   {geometry3d.cpp ../Programs/geometry3d_functions.cpp}}

  {{{ex1.cpp}}
   {transforms.cpp}}

  {{{ex1.cpp}}
   {collision3d.cpp}}

  {{{ex1.cpp}}
   {lighting.cpp}}

  {{{ex1.cpp}
    {ex2.cpp}}
   {modeling.cpp}}

  {{{ex1.cpp}
    {ex2.cpp}}
   {speed.cpp ../Programs/speed_functions.cpp}}

  {{{ex1.cpp}}
   {tiles.cpp}}

  {{{ex1.cpp}}
   {-c maze.cpp maze_functions.cpp &&
    maze.o maze_functions.o $lbs}}

  {{{ex1.cpp}
    {-c ex2.cpp &&
     ex2.o $lbs}}
   {ai.cpp ai_functions.cpp}}

  {{{ex1.cpp}}
   {search.cpp}}

"

set prefix g++

if {$argc==2} {

  set chapter [lindex $argv 0]
  set exerciseIndex [lindex $argv 1]
  
  if {$chapter>=1&&$chapter<=6} {
    set part 1
  } elseif {$chapter>=7&&$chapter<=11} {
    set part 2
  } elseif {$chapter>=12&&$chapter<=16} {
    set part 3
  } elseif {$chapter>=17&&$chapter<=21} {
    set part 4
  } elseif {$chapter>=22&&$chapter<=26} {
    set part 5
  } else {
    puts "Error" ; return
  }
  
  set a "Part $part" ; set b "Chapter $chapter"
  
  incr part -1 ; incr chapter -1 ;
  
  # Get last part of path and command
  if {$exerciseIndex=="p"} {
    set c "Programs"
    set currentCommand [lindex $data $chapter 1]
  } else {
    set c "Exercises" ; incr exerciseIndex -1
    set currentCommand [lindex $data $chapter 0 $exerciseIndex]
  }
  
  # Check if command exists
  if {$currentCommand==""} { puts "Wrong arguments" ; return }
  
  cd "$a/$b/$c"
  
  # Split
  set commandParts [split $currentCommand &]
  set lenParts [llength $commandParts]
  
  # Execute all command parts
  for {set i 0} {$i < $lenParts} {incr i} {
    set currentPart [lindex $commandParts $i]
    if {$currentPart!=""} { exec $prefix {*}$currentPart }
  }
  
  # Run and show output
  set output [exec ./a.out]
  if {$output!=""} { puts $output }
  
} else {
  puts "Wrong number of arguments"
}


