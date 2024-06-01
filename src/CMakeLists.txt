set(SOURCES
	bitter.c
)

add_library(bitter SHARED ${SOURCES})
add_library(bitterstatic STATIC ${SOURCES})

target_include_directories(bitter
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>)
target_include_directories(bitterstatic
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>)

install(TARGETS bitter bitterstatic
	DESTINATION lib)
install(DIRECTORY bitter DESTINATION include)
