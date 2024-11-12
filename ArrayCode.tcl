#!/usr/bin/env tclsh

#
# A simple tool to query Array30 Input Method code.
# Version: 0.0.2
# Encoding: UTF-8
#

#=================================================================
# Event Handler
#=================================================================

proc getInputUpdate {} {
    set s [.getinput get]

    if {[string length $s]==0} {
        return
    }

    .t delete 0 end

    # Just query the last word
    set words [split $s {}]
    set mykey [lindex $words end]
    if {[dict exists $::array30map $mykey]} {
        set values [dict get $::array30map $mykey]
        foreach value $values {
           set kvalue [string map $::keyname $value]
           .t insert end [list $kvalue]
        }
    } else {
        .t insert end [list $::NoFound]
    }
}

proc Exit {} {
    set answer [tk_messageBox -message $::QuitMsg -type yesno -icon warning]
    switch -- $answer {
        yes exit
    }
}

proc HelpAbout {} {
    set ans [tk_messageBox -title $::About -type ok -message $::AboutMsg ]
}

#=================================================================
# Help function
#=================================================================

proc getArray30Map {filename} {
    set infile [open $filename r]
    set array30map [dict create]
	while { [gets $infile line] >= 0 } {
		if {[string length $line]==0} {
			continue
		}

		set first [string index $line 0]
		if {[string compare $first "#"]==0 || [string compare $first "%"]==0} {
			continue
		}

		set result [split $line "\t"]
		set key [lindex $result 1]
		set value [lindex $result 0]
		if {[dict exists $array30map $key]==0} {
			set values [list $value]
			dict set array30map $key $values
		} else {
			set values [dict get $array30map $key]
			lappend values $value
			dict set array30map $key $values
		}
	}

	close $infile
    return $array30map
}

#=================================================================
# Main function
#=================================================================

package require Tcl 8.6-
package require Tk
package require tablelist
package require msgcat

ttk::setTheme "alt"

set array30map [getArray30Map "ar30-regular.txt"]

set keyname [list a {1-} \
b {5v} \
c {3v} \
d {3-} \
e {3^} \
f {4-} \
g {5-} \
h {6-} \
i {8^} \
j {7-} \
k {8-} \
l {9-} \
m {7v} \
n {6v} \
o {9^} \
p {0^} \
q {1^} \
r {4^} \
s {2-} \
t {5^} \
u {7^} \
v {4v} \
w {2^} \
x {2v} \
y {6^} \
z {1v} \
{.} {9v} \
{/} {0v} \
{;} {0-} \
{,} {8v}]


set Title "ArrayCode"
set File "File"
set Help "Help"
set Quit "Quit"
set Exit "Exit"
set About "About"
set code "code"
set NoFound "(No data found)"
set QuitMsg "Really quit?"
set AboutMsg "It is a simple tool to query Array30 Input Method code."

set language [::msgcat::mclocale]
if [file isfile "./msgs/${language}.msg" ] {
    source "./msgs/${language}.msg"
}

namespace eval ::msgcat_exp1 {
    set Title [::msgcat::mc "ArrayCode"]
    set File [::msgcat::mc "File"]
    set Help [::msgcat::mc "Help"]
    set Quit [::msgcat::mc "Quit"]
    set Exit [::msgcat::mc "Exit"]
    set About [::msgcat::mc "About"]
    set code [::msgcat::mc "code"]
    set NoFound [::msgcat::mc "(No data found)"]
    set QuitMsg [::msgcat::mc "Really quit?"]
    set AboutMsg [::msgcat::mc "It is a simple tool to query Array30 Input Method code."]
}

wm geometry . 800x600+50+50
wm title . $Title
font configure TkDefaultFont -family {Noto Sans CJK TC} -size 9

frame .menubar -relief raised -bd 2
pack .menubar -side top -fill x

ttk::menubutton .menubar.file -text $File -menu .menubar.file.menu
menu .menubar.file.menu -tearoff 0
.menubar.file.menu add command -label $Quit -command Exit
ttk::menubutton .menubar.help -text $Help -menu .menubar.help.menu
menu .menubar.help.menu -tearoff 0
.menubar.help.menu add command -label $About -command HelpAbout
pack .menubar.file .menubar.help -side left

# Contextual Menus
menu .menu
foreach {i j} [list $Exit Exit] {
    .menu add command -label $i -command $j
}

if {[tk windowingsystem]=="aqua"} {
    bind . <2> "tk_popup .menu %X %Y"
    bind . <Control-1> "tk_popup .menu %X %Y"
} else {
    bind . <3> "tk_popup .menu %X %Y"
}

font create AppFont -family {Noto Serif CJK TC} -size 14

ttk::entry .getinput -textvariable inputword -font AppFont
pack .getinput -fill x -ipadx 3 -ipady 3 -pady 3 -padx 3 -side top -anchor nw

tablelist::tablelist .t -columns "0 $code" -stretch all \
     -background white -font AppFont
pack .t -fill both -expand 1 -side top

# Handle special key
bind all <F1> HelpAbout
bind .getinput <Return> getInputUpdate
