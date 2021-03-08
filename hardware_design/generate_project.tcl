# Retrieve Script Location for being able to run script from everywhere
variable myLocation [file normalize [info script]]

proc getScriptDirectory {} {
    variable myLocation
    return [file dirname $myLocation]
}

set SCRIPT_DIR [getScriptDirectory]

cd $SCRIPT_DIR

# Create Project - Change the FPGA part here to yours
create_project cordic $SCRIPT_DIR/proj -part xc7a100tcsg324-1
set_property target_language VHDL [current_project]

# Add Source Files
add_files -norecurse "$SCRIPT_DIR/rtl/"
update_compile_order -fileset sources_1

# Add Constraints - Change the board_support.xdc to your board support file
add_files -fileset constrs_1 -force -norecurse "$SCRIPT_DIR/constraints/board_support.xdc"
update_compile_order -fileset sources_1