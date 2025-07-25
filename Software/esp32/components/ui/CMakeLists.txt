file(GLOB_RECURSE SOURCES "*.c")
file(GLOB_RECURSE HEADERS "*.h")

set(HEADERS_DIRS "")
foreach(header ${HEADERS})
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND HEADERS_DIRS ${dir})
endforeach()
list(REMOVE_DUPLICATES HEADERS_DIRS)

idf_component_register(
    SRCS ${SOURCES}
    INCLUDE_DIRS "." ${HEADERS_DIRS}
    REQUIRES lvgl lvgl_porting adc
)