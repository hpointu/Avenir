file(
	GLOB_RECURSE
	AV_CORE_SOURCES
	core/*
)

file(
	GLOB_RECURSE
	AV_GAME_SOURCES
	game/*
)


add_executable(Avenir main.cpp ${AV_CORE_SOURCES} ${AV_GAME_SOURCES})

target_link_libraries(Avenir ${mainLibs})
