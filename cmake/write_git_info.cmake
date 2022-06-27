cmake_minimum_required(VERSION 3.22)

execute_process(
    COMMAND ${GIT_PROGRAM} rev-parse HEAD
    OUTPUT_VARIABLE THIS_REPO_SHA
    OUTPUT_STRIP_TRAILING_WHITESPACE
    COMMAND_ERROR_IS_FATAL ANY
)

list(LENGTH FILES FILE_ARG_COUNT)

    message(STATUS ${FILES})
math(EXPR IS_ODD "${FILE_ARG_COUNT} % 2")
if (IS_ODD)
    message(FATAL_ERROR "Positional arguments should be pairs but got ${FILE_ARG_COUNT}")
endif()

math(EXPR ITER_END "${FILE_ARG_COUNT} - 1")

foreach(INPUT_IX RANGE 0 ${ITER_END} 2)
    math(EXPR OUTPUT_IX "${INPUT_IX} + 1")

    list(GET FILES ${INPUT_IX} INPUT)
    list(GET FILES ${OUTPUT_IX} OUTPUT)

    configure_file(${INPUT} ${OUTPUT} @ONLY)
endforeach()
