cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)

project(wzNetCommon)

find_package(CapnProto CONFIG REQUIRED )
capnp_generate_cpp(wzNetSources wzNetHeaders ./capnp/wzNet.capnp)

add_library(wzNetCapnp ./capnp/wzNet.capnp.c++ ./capnp/wzNet.capnp.h)
