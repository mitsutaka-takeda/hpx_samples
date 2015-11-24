cmake_minimum_required(VERSION 3.3)

project(hpx_practice)

find_package(HPX)

include(CMakeParseArguments)
include(HPX_Utils)

set(sources hello_world.cpp) # ソース・ファイルのリスト
source_group("Source Files" FILES ${source}) # グループ化してIDEなどで見やすく
# ビルド用のフラグを設定
set(hello_world_FLAGS 
  COMPONENT_DEPENDENCIES 
  iostreams # 他にどんなコンポーネントがある？
  )

# cmakeのモジュールのパスの通しかた。
# -DCMAKE_MODULE_PATH=/home/mtakeda/etc/hpx/lib/cmake/HPX
add_hpx_executable(
  hello_world # target name
  SOURCES ${sources}
  ${hello_world_FLAGS}
  )
# add_hpx_executable(name ...)
# はname_exe("nameに_exeアンダースコアとexeをsuffixした")

target_link_libraries(
  hello_world_exe
  boost_program_options
  boost_system)
