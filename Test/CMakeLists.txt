set(TestTargetName ${TargetName}Test)
include (GroupSet)

set_group(
    TestTarget_SRC
    Source:*.cpp
)

include_directories(
    ${GTEST_INCLUDE}
    ${Svg_INCLUDE}
    ${Utils_INCLUDE}
)

add_executable(
    ${TestTargetName}
    ${TestTarget_SRC}
)
target_link_libraries(
    ${TestTargetName} 
    ${GTEST_LIBRARY}
    ${Svg_LIBRARY}
    ${Utils_LIBRARY}
)

set_target_properties(
    ${TestTargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)

if (Svg_AUTO_RUN_TEST)
    run_test(${TestTargetName})
endif()
