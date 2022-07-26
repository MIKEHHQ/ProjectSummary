# 
# Synthesis run script generated by Vivado
# 

set TIME_start [clock seconds] 
proc create_report { reportName command } {
  set status "."
  append status $reportName ".fail"
  if { [file exists $status] } {
    eval file delete [glob $status]
  }
  send_msg_id runtcl-4 info "Executing : $command"
  set retval [eval catch { $command } msg]
  if { $retval != 0 } {
    set fp [open $status w]
    close $fp
    send_msg_id runtcl-5 warning "$msg"
  }
}
create_project -in_memory -part xc7z020clg400-2

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_msg_config -source 4 -id {IP_Flow 19-2162} -severity warning -new_severity info
set_property webtalk.parent_dir H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_3/axi_gpio.cache/wt [current_project]
set_property parent.project_path H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_3/axi_gpio.xpr [current_project]
set_property XPM_LIBRARIES {XPM_CDC XPM_MEMORY} [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property ip_output_repo h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_3/axi_gpio.cache/ip [current_project]
set_property ip_cache_permissions {read write} [current_project]
add_files H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/NN_250_125_bp.coe
add_files H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/N_250g_125s_lp.coe
add_files H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/ask_100g_125fs_15.coe
read_mem {
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_1/activehdl/fir_compiler_1.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_0/questa/fir_compiler_0.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_0/vcs/fir_compiler_0.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/mem_init_files/fir_compiler_0.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_1/xcelium/fir_compiler_1.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_2/ies/fir_compiler_2.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/mem_init_files/fir_compiler_2.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_1/riviera/fir_compiler_1.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_0/xsim/fir_compiler_0.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_1/ies/fir_compiler_1.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_0/xcelium/fir_compiler_0.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_1/questa/fir_compiler_1.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_0/riviera/fir_compiler_0.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_2/vcs/fir_compiler_2.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_2/modelsim/fir_compiler_2.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/mem_init_files/fir_compiler_1.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_0/ies/fir_compiler_0.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_1/xsim/fir_compiler_1.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_0/activehdl/fir_compiler_0.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_0/modelsim/fir_compiler_0.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_1/vcs/fir_compiler_1.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_2/questa/fir_compiler_2.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_1/modelsim/fir_compiler_1.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_2/xsim/fir_compiler_2.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_2/activehdl/fir_compiler_2.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_2/xcelium/fir_compiler_2.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir_compiler_0.mif
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.ip_user_files/sim_scripts/fir_compiler_2/riviera/fir_compiler_2.mif
}
read_verilog -library xil_defaultlib {
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/new/HC595.v
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/new/ask.v
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/new/devide.v
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/new/gate.v
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/new/pll.v
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/new/receiver.v
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/new/uart.v
  H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_3/axi_gpio.srcs/sources_1/bd/system/hdl/system_wrapper.v
}
add_files H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_3/axi_gpio.srcs/sources_1/bd/system/system.bd
set_property used_in_implementation false [get_files -all h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_3/axi_gpio.srcs/sources_1/bd/system/ip/system_processing_system7_0_0/system_processing_system7_0_0.xdc]
set_property used_in_implementation false [get_files -all h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_3/axi_gpio.srcs/sources_1/bd/system/ip/system_axi_gpio_0_0/system_axi_gpio_0_0_board.xdc]
set_property used_in_implementation false [get_files -all h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_3/axi_gpio.srcs/sources_1/bd/system/ip/system_axi_gpio_0_0/system_axi_gpio_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_3/axi_gpio.srcs/sources_1/bd/system/ip/system_axi_gpio_0_0/system_axi_gpio_0_0.xdc]
set_property used_in_implementation false [get_files -all h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_3/axi_gpio.srcs/sources_1/bd/system/ip/system_rst_ps7_0_50M_0/system_rst_ps7_0_50M_0_board.xdc]
set_property used_in_implementation false [get_files -all h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_3/axi_gpio.srcs/sources_1/bd/system/ip/system_rst_ps7_0_50M_0/system_rst_ps7_0_50M_0.xdc]
set_property used_in_implementation false [get_files -all h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_3/axi_gpio.srcs/sources_1/bd/system/ip/system_auto_pc_0/system_auto_pc_0_ooc.xdc]
set_property used_in_implementation false [get_files -all H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_3/axi_gpio.srcs/sources_1/bd/system/system_ooc.xdc]

read_ip -quiet H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/ip/fir_compiler_2/fir_compiler_2.xci
set_property used_in_implementation false [get_files -all h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/ip/fir_compiler_2/constraints/fir_compiler_v7_2.xdc]
set_property used_in_implementation false [get_files -all h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/ip/fir_compiler_2/fir_compiler_2_ooc.xdc]

read_ip -quiet H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/ip/fir_compiler_1/fir_compiler_1.xci
set_property used_in_implementation false [get_files -all h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/ip/fir_compiler_1/constraints/fir_compiler_v7_2.xdc]
set_property used_in_implementation false [get_files -all h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/ip/fir_compiler_1/fir_compiler_1_ooc.xdc]

read_ip -quiet H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/ip/fir_compiler_0/fir_compiler_0.xci
set_property used_in_implementation false [get_files -all h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/ip/fir_compiler_0/constraints/fir_compiler_v7_2.xdc]
set_property used_in_implementation false [get_files -all h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/ip/fir_compiler_0/fir_compiler_0_ooc.xdc]

read_ip -quiet H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/ip/clk_wiz_1/clk_wiz_1.xci
set_property used_in_implementation false [get_files -all h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/ip/clk_wiz_1/clk_wiz_1_board.xdc]
set_property used_in_implementation false [get_files -all h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/ip/clk_wiz_1/clk_wiz_1.xdc]
set_property used_in_implementation false [get_files -all h:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_1/fir.srcs/sources_1/ip/clk_wiz_1/clk_wiz_1_ooc.xdc]

# Mark all dcp files as not used in implementation to prevent them from being
# stitched into the results of this synthesis run. Any black boxes in the
# design are intentionally left as such for best results. Dcp files will be
# stitched into the design at a later time, either when this synthesis run is
# opened, or when it is stitched into a dependent implementation run.
foreach dcp [get_files -quiet -all -filter file_type=="Design\ Checkpoint"] {
  set_property used_in_implementation false $dcp
}
read_xdc H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_3/axi_gpio.srcs/constrs_1/new/Navigator.xdc
set_property used_in_implementation false [get_files H:/学习资料-山东大学/大三上课程/EECompetition/FINAL/final_3/axi_gpio.srcs/constrs_1/new/Navigator.xdc]

read_xdc dont_touch.xdc
set_property used_in_implementation false [get_files dont_touch.xdc]
set_param ips.enableIPCacheLiteLoad 1
close [open __synthesis_is_running__ w]

synth_design -top system_wrapper -part xc7z020clg400-2


# disable binary constraint mode for synth run checkpoints
set_param constraints.enableBinaryConstraints false
write_checkpoint -force -noxdef system_wrapper.dcp
create_report "synth_1_synth_report_utilization_0" "report_utilization -file system_wrapper_utilization_synth.rpt -pb system_wrapper_utilization_synth.pb"
file delete __synthesis_is_running__
close [open __synthesis_is_complete__ w]
