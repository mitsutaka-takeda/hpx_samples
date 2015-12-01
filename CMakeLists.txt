cmake_minimum_required(VERSION 3.3)

project(hpx_practice)

find_package(HPX)

# ビルド用のフラグを設定
set(hello_world_FLAGS 
  COMPONENT_DEPENDENCIES 
  iostreams # 他にどんなコンポーネントがある？
  )

# cmakeのモジュールのパスの通しかた。
# -DCMAKE_MODULE_PATH=/home/mtakeda/etc/hpx/lib/cmake/HPX
add_hpx_executable(
  hello_world # target name
  SOURCES hello_world.cpp
  ${hello_world_FLAGS}
  )

# set(fibonacci_FLAGS
#   COMPONENT_DEPENDENCIES
#   iostreams)

add_hpx_executable(
  fibonacci
  SOURCES fibonacci.cpp
  COMPONENT_DEPENDENCIES 
  iostreams
  )

add_hpx_executable(
  quick_sort
  SOURCES quick_sort.cpp
  COMPONENT_DEPENDENCIES 
  iostreams
  )
# add_hpx_executable(name ...)
# はname_exe("nameに_exeアンダースコアとexeをsuffixした")

add_hpx_executable(
  quick_sort_concurrent
  SOURCES quick_sort.concurrent.cpp
  COMPONENT_DEPENDENCIES 
  iostreams
)

target_link_libraries(
  hello_world_exe
  boost_program_options
  boost_system)
