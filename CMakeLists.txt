cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)

project(wzNet)

#set(CAPNPC_SRC_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/common/capnp/")
#find_package(CapnProto CONFIG REQUIRED )
#capnp_generate_cpp(wzNetSources wzNetHeaders ./common/capnp/wzNet.capnp)

#subdirs(client server wzplugin)
subdirs(common client)
