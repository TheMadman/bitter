function(testcase target)
	add_executable(test_${target} ${target}.c)
	target_link_libraries(test_${target} bitter)
	add_test(NAME ${target} COMMAND test_${target})
endfunction()

testcase(bitter_bitter)

