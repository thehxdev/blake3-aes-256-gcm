execute_process(
	COMMAND date -u
	OUTPUT_VARIABLE DATE
	OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
	COMMAND git rev-parse HEAD
	OUTPUT_VARIABLE COMMIT_REV
	OUTPUT_STRIP_TRAILING_WHITESPACE
)
configure_file(blake3aes256gcm.c.in "${CMAKE_CURRENT_SOURCE_DIR}/blake3aes256gcm.c" @ONLY)

add_executable(
	blake3aes256gcm
	base64.c
	blake3aes256gcm.c
	main.c
)

target_compile_options(blake3aes256gcm PRIVATE "$<BUILD_INTERFACE:-Wall;-Wextra>")

target_compile_features(blake3aes256gcm PRIVATE c_std_99)
target_include_directories(blake3aes256gcm PRIVATE "${DEPS_DIR}/include")
target_link_directories(blake3aes256gcm PRIVATE "${DEPS_DIR}/lib")
target_link_libraries(blake3aes256gcm PRIVATE wolfssl blake3)
