cmake_minimum_required(VERSION 3.27)
string(TIMESTAMP configurationTime "%y.%m.%d.%H" UTC)
project(grpcServer VERSION ${configurationTime} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    set(execName grpcServer)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(execName grpcServerd)
endif ()

message(STATUS "OS type: " ${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_VERSION})
message(STATUS "OS processor architecture: " ${CMAKE_SYSTEM_PROCESSOR})
message(STATUS "Build type:  ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Default compiler flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "Additional compiler flags: ${_flags}")
message(STATUS "Version: ${configurationTime}")

find_library(libsystemd systemd)
if (libsystemd)
    message(STATUS "Found system library systemd: ${libsystemd}")
else ()
    message(FATAL_ERROR "Could NOT find library systemd. Please install it via your system package manager to build this project !")
endif ()

find_library(libpthread pthread)
if (libpthread)
    message(STATUS "Found system library pthread: ${libpthread}")
else ()
    message(FATAL_ERROR "Could NOT find library pthread. Please install it via your system package manager to build this project !")
endif ()

find_library(libdl dl)
if (libdl)
    message(STATUS "Found system library dl: ${libdl}")
else ()
    message(FATAL_ERROR "Could NOT find library dl. Please install it via your system package manager to build this project !")
endif ()

find_library(librt rt)
if (librt)
    message(STATUS "Found system library rt: ${librt}")
else ()
    message(FATAL_ERROR "Could NOT find library rt. Please install it via your system package manager to build this project !")
endif ()

add_library(libgrpcpp_channelz STATIC IMPORTED)
set_target_properties(libgrpcpp_channelz PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libgrpcpp_channelz.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libgrpcpp_channelz.a)

add_library(libgrpc++_reflection STATIC IMPORTED)
set_target_properties(libgrpc++_reflection PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libgrpc++_reflection.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libgrpc++_reflection.a)

add_library(libgrpc++_alts STATIC IMPORTED)
set_target_properties(libgrpc++_alts PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libgrpc++_alts.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libgrpc++_alts.a)

add_library(libgrpc++ STATIC IMPORTED)
set_target_properties(libgrpc++ PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libgrpc++.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libgrpc++.a)

add_library(libgrpc++_error_details STATIC IMPORTED)
set_target_properties(libgrpc++_error_details PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libgrpc++_error_details.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libgrpc++_error_details.a)

add_library(libgrpc STATIC IMPORTED)
set_target_properties(libgrpc PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libgrpc.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libgrpc.a)

add_library(libgrpc++_unsecure STATIC IMPORTED)
set_target_properties(libgrpc++_unsecure PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libgrpc++_unsecure.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libgrpc++_unsecure.a)

add_library(libgrpc_unsecure STATIC IMPORTED)
set_target_properties(libgrpc_unsecure PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libgrpc_unsecure.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libgrpc_unsecure.a)

add_library(libgrpc_authorization_provider STATIC IMPORTED)
set_target_properties(libgrpc_authorization_provider PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libgrpc_authorization_provider.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libgrpc_authorization_provider.a)

add_library(libgrpc_plugin_support STATIC IMPORTED)
set_target_properties(libgrpc_plugin_support PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libgrpc_plugin_support.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libgrpc_plugin_support.a)

add_library(libprotoc STATIC IMPORTED)
set_target_properties(libprotoc PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libprotoc.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libprotoc.a)

add_library(libprotobuf STATIC IMPORTED)
set_target_properties(libprotobuf PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libprotobuf.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libprotobuf.a)

add_library(libabsl_flags_parse STATIC IMPORTED)
set_target_properties(libabsl_flags_parse PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_flags_parse.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_flags_parse.a)

add_library(libabsl_flags_usage STATIC IMPORTED)
set_target_properties(libabsl_flags_usage PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_flags_usage.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_flags_usage.a)

add_library(libprotobuf-lite STATIC IMPORTED)
set_target_properties(libprotobuf-lite PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libprotobuf-lite.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libprotobuf-lite.a)

add_library(libgpr STATIC IMPORTED)
set_target_properties(libgpr PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libgpr.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libgpr.a)

add_library(libabsl_flags_usage_internal STATIC IMPORTED)
set_target_properties(libabsl_flags_usage_internal PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_flags_usage_internal.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_flags_usage_internal.a)

add_library(libabsl_log_flags STATIC IMPORTED)
set_target_properties(libabsl_log_flags PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_log_flags.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_log_flags.a)

add_library(libabsl_statusor STATIC IMPORTED)
set_target_properties(libabsl_statusor PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_statusor.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_statusor.a)

add_library(libabsl_die_if_null STATIC IMPORTED)
set_target_properties(libabsl_die_if_null PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_die_if_null.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_die_if_null.a)

add_library(libabsl_flags_reflection STATIC IMPORTED)
set_target_properties(libabsl_flags_reflection PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_flags_reflection.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_flags_reflection.a)

add_library(libabsl_log_internal_check_op STATIC IMPORTED)
set_target_properties(libabsl_log_internal_check_op PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_log_internal_check_op.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_log_internal_check_op.a)

add_library(libabsl_log_internal_message STATIC IMPORTED)
set_target_properties(libabsl_log_internal_message PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_log_internal_message.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_log_internal_message.a)

add_library(libabsl_status STATIC IMPORTED)
set_target_properties(libabsl_status PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_status.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_status.a)

add_library(libabsl_cord STATIC IMPORTED)
set_target_properties(libabsl_cord PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_cord.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_cord.a)

add_library(libabsl_cordz_sample_token STATIC IMPORTED)
set_target_properties(libabsl_cordz_sample_token PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_cordz_sample_token.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_cordz_sample_token.a)

add_library(libabsl_flags_internal STATIC IMPORTED)
set_target_properties(libabsl_flags_internal PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_flags_internal.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_flags_internal.a)

add_library(libabsl_log_initialize STATIC IMPORTED)
set_target_properties(libabsl_log_initialize PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_log_initialize.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_log_initialize.a)

add_library(libabsl_log_internal_log_sink_set STATIC IMPORTED)
set_target_properties(libabsl_log_internal_log_sink_set PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_log_internal_log_sink_set.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_log_internal_log_sink_set.a)

add_library(libabsl_raw_hash_set STATIC IMPORTED)
set_target_properties(libabsl_raw_hash_set PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_raw_hash_set.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_raw_hash_set.a)

add_library(libabsl_cordz_info STATIC IMPORTED)
set_target_properties(libabsl_cordz_info PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_cordz_info.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_cordz_info.a)

add_library(libabsl_flags_config STATIC IMPORTED)
set_target_properties(libabsl_flags_config PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_flags_config.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_flags_config.a)

add_library(libabsl_log_globals STATIC IMPORTED)
set_target_properties(libabsl_log_globals PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_log_globals.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_log_globals.a)

add_library(libabsl_vlog_config_internal STATIC IMPORTED)
set_target_properties(libabsl_vlog_config_internal PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_vlog_config_internal.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_vlog_config_internal.a)

add_library(libabsl_cord_internal STATIC IMPORTED)
set_target_properties(libabsl_cord_internal PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_cord_internal.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_cord_internal.a)

add_library(libabsl_cordz_handle STATIC IMPORTED)
set_target_properties(libabsl_cordz_handle PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_cordz_handle.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_cordz_handle.a)

add_library(libabsl_flags_program_name STATIC IMPORTED)
set_target_properties(libabsl_flags_program_name PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_flags_program_name.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_flags_program_name.a)

add_library(libabsl_hashtablez_sampler STATIC IMPORTED)
set_target_properties(libabsl_hashtablez_sampler PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_hashtablez_sampler.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_hashtablez_sampler.a)

add_library(libabsl_synchronization STATIC IMPORTED)
set_target_properties(libabsl_synchronization PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_synchronization.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_synchronization.a)

add_library(libssl STATIC IMPORTED)
set_target_properties(libssl PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libssl.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libssl.a)

add_library(libabsl_crc_cord_state STATIC IMPORTED)
set_target_properties(libabsl_crc_cord_state PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_crc_cord_state.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_crc_cord_state.a)

add_library(libabsl_crc32c STATIC IMPORTED)
set_target_properties(libabsl_crc32c PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_crc32c.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_crc32c.a)

add_library(libabsl_flags_marshalling STATIC IMPORTED)
set_target_properties(libabsl_flags_marshalling PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_flags_marshalling.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_flags_marshalling.a)

add_library(libabsl_log_internal_format STATIC IMPORTED)
set_target_properties(libabsl_log_internal_format PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_log_internal_format.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_log_internal_format.a)

add_library(libabsl_log_sink STATIC IMPORTED)
set_target_properties(libabsl_log_sink PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_log_sink.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_log_sink.a)

add_library(libabsl_random_seed_sequences STATIC IMPORTED)
set_target_properties(libabsl_random_seed_sequences PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_random_seed_sequences.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_random_seed_sequences.a)

add_library(libabsl_failure_signal_handler STATIC IMPORTED)
set_target_properties(libabsl_failure_signal_handler PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_failure_signal_handler.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_failure_signal_handler.a)

add_library(libabsl_flags_private_handle_accessor STATIC IMPORTED)
set_target_properties(libabsl_flags_private_handle_accessor PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_flags_private_handle_accessor.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_flags_private_handle_accessor.a)

add_library(libabsl_kernel_timeout_internal STATIC IMPORTED)
set_target_properties(libabsl_kernel_timeout_internal PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_kernel_timeout_internal.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_kernel_timeout_internal.a)

add_library(libabsl_log_entry STATIC IMPORTED)
set_target_properties(libabsl_log_entry PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_log_entry.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_log_entry.a)

add_library(libabsl_log_internal_globals STATIC IMPORTED)
set_target_properties(libabsl_log_internal_globals PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_log_internal_globals.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_log_internal_globals.a)

add_library(libabsl_random_internal_distribution_test_util STATIC IMPORTED)
set_target_properties(libabsl_random_internal_distribution_test_util PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_random_internal_distribution_test_util.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_random_internal_distribution_test_util.a)

add_library(libabsl_random_internal_pool_urbg STATIC IMPORTED)
set_target_properties(libabsl_random_internal_pool_urbg PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_random_internal_pool_urbg.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_random_internal_pool_urbg.a)

add_library(libabsl_str_format_internal STATIC IMPORTED)
set_target_properties(libabsl_str_format_internal PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_str_format_internal.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_str_format_internal.a)

add_library(libcrypto STATIC IMPORTED)
set_target_properties(libcrypto PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libcrypto.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libcrypto.a)

add_library(libutf8_validity STATIC IMPORTED)
set_target_properties(libutf8_validity PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libutf8_validity.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libutf8_validity.a)

add_library(libabsl_examine_stack STATIC IMPORTED)
set_target_properties(libabsl_examine_stack PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_examine_stack.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_examine_stack.a)

add_library(libabsl_hash STATIC IMPORTED)
set_target_properties(libabsl_hash PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_hash.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_hash.a)

add_library(libabsl_log_internal_fnmatch STATIC IMPORTED)
set_target_properties(libabsl_log_internal_fnmatch PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_log_internal_fnmatch.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_log_internal_fnmatch.a)

add_library(libabsl_log_internal_proto STATIC IMPORTED)
set_target_properties(libabsl_log_internal_proto PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_log_internal_proto.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_log_internal_proto.a)

add_library(libabsl_random_distributions STATIC IMPORTED)
set_target_properties(libabsl_random_distributions PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_random_distributions.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_random_distributions.a)

add_library(libabsl_random_internal_seed_material STATIC IMPORTED)
set_target_properties(libabsl_random_internal_seed_material PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_random_internal_seed_material.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_random_internal_seed_material.a)

add_library(libabsl_time STATIC IMPORTED)
set_target_properties(libabsl_time PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_time.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_time.a)

add_library(libabsl_flags_commandlineflag STATIC IMPORTED)
set_target_properties(libabsl_flags_commandlineflag PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_flags_commandlineflag.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_flags_commandlineflag.a)

add_library(libabsl_symbolize STATIC IMPORTED)
set_target_properties(libabsl_symbolize PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_symbolize.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_symbolize.a)

add_library(libabsl_strings STATIC IMPORTED)
set_target_properties(libabsl_strings PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_strings.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_strings.a)

add_library(libabsl_crc_cpu_detect STATIC IMPORTED)
set_target_properties(libabsl_crc_cpu_detect PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_crc_cpu_detect.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_crc_cpu_detect.a)

add_library(libabsl_crc_internal STATIC IMPORTED)
set_target_properties(libabsl_crc_internal PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_crc_internal.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_crc_internal.a)

add_library(libabsl_log_internal_conditions STATIC IMPORTED)
set_target_properties(libabsl_log_internal_conditions PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_log_internal_conditions.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_log_internal_conditions.a)

add_library(libabsl_low_level_hash STATIC IMPORTED)
set_target_properties(libabsl_low_level_hash PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_low_level_hash.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_low_level_hash.a)

add_library(libabsl_random_internal_randen STATIC IMPORTED)
set_target_properties(libabsl_random_internal_randen PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_random_internal_randen.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_random_internal_randen.a)

add_library(libupb_json_lib STATIC IMPORTED)
set_target_properties(libupb_json_lib PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libupb_json_lib.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libupb_json_lib.a)

add_library(libupb_textformat_lib STATIC IMPORTED)
set_target_properties(libupb_textformat_lib PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libupb_textformat_lib.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libupb_textformat_lib.a)

add_library(libabsl_city STATIC IMPORTED)
set_target_properties(libabsl_city PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_city.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_city.a)

add_library(libabsl_demangle_internal STATIC IMPORTED)
set_target_properties(libabsl_demangle_internal PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_demangle_internal.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_demangle_internal.a)

add_library(libabsl_graphcycles_internal STATIC IMPORTED)
set_target_properties(libabsl_graphcycles_internal PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_graphcycles_internal.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_graphcycles_internal.a)

add_library(libabsl_malloc_internal STATIC IMPORTED)
set_target_properties(libabsl_malloc_internal PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_malloc_internal.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_malloc_internal.a)

add_library(libabsl_string_view STATIC IMPORTED)
set_target_properties(libabsl_string_view PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_string_view.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_string_view.a)

add_library(libabsl_strings_internal STATIC IMPORTED)
set_target_properties(libabsl_strings_internal PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_strings_internal.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_strings_internal.a)

add_library(libabsl_bad_optional_access STATIC IMPORTED)
set_target_properties(libabsl_bad_optional_access PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_bad_optional_access.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_bad_optional_access.a)

add_library(libabsl_bad_variant_access STATIC IMPORTED)
set_target_properties(libabsl_bad_variant_access PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_bad_variant_access.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_bad_variant_access.a)

add_library(libabsl_base STATIC IMPORTED)
set_target_properties(libabsl_base PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_base.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_base.a)

add_library(libabsl_cordz_functions STATIC IMPORTED)
set_target_properties(libabsl_cordz_functions PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_cordz_functions.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_cordz_functions.a)

add_library(libabsl_debugging_internal STATIC IMPORTED)
set_target_properties(libabsl_debugging_internal PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_debugging_internal.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_debugging_internal.a)

add_library(libabsl_random_internal_randen_hwaes STATIC IMPORTED)
set_target_properties(libabsl_random_internal_randen_hwaes PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_random_internal_randen_hwaes.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_random_internal_randen_hwaes.a)

add_library(libabsl_stacktrace STATIC IMPORTED)
set_target_properties(libabsl_stacktrace PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_stacktrace.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_stacktrace.a)

add_library(libabsl_throw_delegate STATIC IMPORTED)
set_target_properties(libabsl_throw_delegate PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_throw_delegate.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_throw_delegate.a)

add_library(libre2 STATIC IMPORTED)
set_target_properties(libre2 PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libre2.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libre2.a)

add_library(libabsl_bad_any_cast_impl STATIC IMPORTED)
set_target_properties(libabsl_bad_any_cast_impl PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_bad_any_cast_impl.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_bad_any_cast_impl.a)

add_library(libabsl_scoped_set_env STATIC IMPORTED)
set_target_properties(libabsl_scoped_set_env PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_scoped_set_env.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_scoped_set_env.a)

add_library(libcares STATIC IMPORTED)
set_target_properties(libcares PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libcares.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libcares.a)

add_library(libabsl_periodic_sampler STATIC IMPORTED)
set_target_properties(libabsl_periodic_sampler PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_periodic_sampler.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_periodic_sampler.a)

add_library(libabsl_random_internal_randen_hwaes_impl STATIC IMPORTED)
set_target_properties(libabsl_random_internal_randen_hwaes_impl PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_random_internal_randen_hwaes_impl.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_random_internal_randen_hwaes_impl.a)

add_library(libabsl_random_internal_randen_slow STATIC IMPORTED)
set_target_properties(libabsl_random_internal_randen_slow PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_random_internal_randen_slow.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_random_internal_randen_slow.a)

add_library(libabsl_raw_logging_internal STATIC IMPORTED)
set_target_properties(libabsl_raw_logging_internal PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_raw_logging_internal.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_raw_logging_internal.a)

add_library(libupb_message_lib STATIC IMPORTED)
set_target_properties(libupb_message_lib PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libupb_message_lib.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libupb_message_lib.a)

add_library(libutf8_range STATIC IMPORTED)
set_target_properties(libutf8_range PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libutf8_range.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libutf8_range.a)

add_library(libabsl_civil_time STATIC IMPORTED)
set_target_properties(libabsl_civil_time PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_civil_time.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_civil_time.a)

add_library(libabsl_exponential_biased STATIC IMPORTED)
set_target_properties(libabsl_exponential_biased PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_exponential_biased.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_exponential_biased.a)

add_library(libabsl_flags_commandlineflag_internal STATIC IMPORTED)
set_target_properties(libabsl_flags_commandlineflag_internal PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_flags_commandlineflag_internal.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_flags_commandlineflag_internal.a)

add_library(libabsl_int128 STATIC IMPORTED)
set_target_properties(libabsl_int128 PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_int128.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_int128.a)

add_library(libabsl_leak_check STATIC IMPORTED)
set_target_properties(libabsl_leak_check PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_leak_check.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_leak_check.a)

add_library(libabsl_log_internal_nullguard STATIC IMPORTED)
set_target_properties(libabsl_log_internal_nullguard PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_log_internal_nullguard.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_log_internal_nullguard.a)

add_library(libabsl_log_severity STATIC IMPORTED)
set_target_properties(libabsl_log_severity PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_log_severity.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_log_severity.a)

add_library(libabsl_random_internal_platform STATIC IMPORTED)
set_target_properties(libabsl_random_internal_platform PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_random_internal_platform.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_random_internal_platform.a)

add_library(libabsl_random_seed_gen_exception STATIC IMPORTED)
set_target_properties(libabsl_random_seed_gen_exception PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_random_seed_gen_exception.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_random_seed_gen_exception.a)

add_library(libabsl_spinlock_wait STATIC IMPORTED)
set_target_properties(libabsl_spinlock_wait PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_spinlock_wait.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_spinlock_wait.a)

add_library(libabsl_strerror STATIC IMPORTED)
set_target_properties(libabsl_strerror PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_strerror.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_strerror.a)

add_library(libabsl_time_zone STATIC IMPORTED)
set_target_properties(libabsl_time_zone PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libabsl_time_zone.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libabsl_time_zone.a)

add_library(libaddress_sorting STATIC IMPORTED)
set_target_properties(libaddress_sorting PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libaddress_sorting.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libaddress_sorting.a)

add_library(libupb_base_lib STATIC IMPORTED)
set_target_properties(libupb_base_lib PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libupb_base_lib.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libupb_base_lib.a)

add_library(libupb_mem_lib STATIC IMPORTED)
set_target_properties(libupb_mem_lib PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libupb_mem_lib.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libupb_mem_lib.a)

add_library(libutf8_range_lib STATIC IMPORTED)
set_target_properties(libutf8_range_lib PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libutf8_range_lib.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libutf8_range_lib.a)

add_library(libz STATIC IMPORTED)
set_target_properties(libz PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/Debug/lib/libz.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/RelWithDebInfo/lib/libz.a)

# include define
include_directories(
        ${PROJECT_SOURCE_DIR}/../../../../clib/grpc/include
)

list(APPEND _libs_prebuilt libgrpcpp_channelz libgrpc++_reflection libgrpc++_alts libgrpc++ libgrpc++_error_details
        libgrpc libgrpc++_unsecure libgrpc_unsecure libgrpc_authorization_provider libgrpc_plugin_support
        libprotoc libprotobuf libabsl_flags_parse libabsl_flags_usage libprotobuf-lite
        libgpr libabsl_flags_usage_internal libabsl_log_flags libabsl_statusor libabsl_die_if_null
        libabsl_flags_reflection libabsl_log_internal_check_op libabsl_log_internal_message libabsl_status libabsl_cord
        libabsl_cordz_sample_token libabsl_flags_internal libabsl_log_initialize libabsl_log_internal_log_sink_set libabsl_raw_hash_set
        libabsl_cordz_info libabsl_flags_config libabsl_log_globals libabsl_vlog_config_internal libabsl_cord_internal
        libabsl_cordz_handle libabsl_flags_program_name libabsl_hashtablez_sampler libabsl_synchronization libssl
        libabsl_crc_cord_state libabsl_crc32c libabsl_flags_marshalling libabsl_log_internal_format libabsl_log_sink
        libabsl_random_seed_sequences libabsl_failure_signal_handler libabsl_flags_private_handle_accessor libabsl_kernel_timeout_internal libabsl_log_entry
        libabsl_log_internal_globals libabsl_random_internal_distribution_test_util libabsl_random_internal_pool_urbg libabsl_str_format_internal libcrypto
        libutf8_validity libabsl_examine_stack libabsl_hash libabsl_log_internal_fnmatch libabsl_log_internal_proto
        libabsl_random_distributions libabsl_random_internal_seed_material libabsl_time libabsl_flags_commandlineflag libabsl_symbolize
        libabsl_strings libabsl_crc_cpu_detect libabsl_crc_internal libabsl_log_internal_conditions libabsl_low_level_hash
        libabsl_random_internal_randen libupb_json_lib libupb_textformat_lib libabsl_city libabsl_demangle_internal
        libabsl_graphcycles_internal libabsl_malloc_internal libabsl_string_view libabsl_strings_internal libabsl_bad_optional_access
        libabsl_bad_variant_access libabsl_base libabsl_cordz_functions libabsl_random_internal_randen_hwaes
        libabsl_stacktrace libabsl_debugging_internal libabsl_throw_delegate libre2 libabsl_bad_any_cast_impl libabsl_scoped_set_env
        libcares libabsl_periodic_sampler libabsl_random_internal_randen_hwaes_impl libabsl_random_internal_randen_slow libabsl_raw_logging_internal
        libupb_message_lib libutf8_range libabsl_civil_time libabsl_exponential_biased libabsl_flags_commandlineflag_internal
        libabsl_int128 libabsl_leak_check libabsl_log_internal_nullguard libabsl_log_severity libabsl_random_internal_platform
        libabsl_random_seed_gen_exception libabsl_spinlock_wait libabsl_strerror libabsl_time_zone libaddress_sorting
        libupb_base_lib libupb_mem_lib libutf8_range_lib libz )
list(APPEND _libs_system ${libsystemd} ${libpthread} ${libdl} ${librt})
add_executable(${execName} main.cpp
        gen-cpp/route_guide.pb.h # protobuf generated message classes
        gen-cpp/route_guide.pb.cc
        gen-cpp/route_guide.grpc.pb.h # grpc generated service classes
        gen-cpp/route_guide.grpc.pb.cc
        RouteGuideServer.cpp
        RouteGuideServer.h
        Helper.cpp
        Helper.h)

target_link_libraries(${execName} ${_libs_prebuilt} ${_libs_system})
